#ifndef DEMO_JS_H
#define DEMO_JS_H

//RAW STRING LITERAL
const char* demoJS = R"=====(
    //Function To Open & Close The Dropdown Menu
function toggleDropdown(id) {
    //Finds The Element With Given ID And Toggles The CSS Class 'Show'
    document.getElementById(id).classList.toggle("show");
}
//Wait Until The Page Is Fully Loaded Before Running The Script
document.addEventListener("DOMContentLoaded", () => {
    //Array Containing The ID's Of The Dropdown menu
    const dropdowns = ['hour', 'minute'];
    
    //Loop Through Each Dropdown (Hour & Minute)
    dropdowns.forEach(id => {
        //Select All <p> Elements Inside The Dropdown
        const options = document.querySelectorAll(`#${id} p`);

        //Get The Button That Displays The Selected Value
        const button = document.getElementById(`selected-${id}`);
        
        //Add Click Event For Each Option
        options.forEach(option => {
            option.addEventListener('click', function() {
                //Set The Button Text To The Selected Option Text
                button.textContent = this.textContent;
                //Close The Dropdown After Selection
                document.getElementById(id).classList.remove('show');
            });
        });
    });

    //Close Dropdowns If User Clicks Anywhere Outside Of A Dropdown Menu
    window.addEventListener('click', function(e) {
        if (!e.target.matches('.dropbtn')) {
            dropdowns.forEach(id => {
                const dropdown = document.getElementById(id);
                dropdown.classList.remove('show');
            });
        }
    });

    //When The 'Save' Button Is CLicked
    document.getElementById("save-btn").addEventListener('click', () => {
        //Get Selected Hour & Minute
        const hour = document.getElementById('selected-hour').innerText;
        const minute = document.getElementById('selected-minute').innerText;

//Send Selected Time To Backend Using HTTP GET Request
        fetch(`/setAlarm?hour=${hour}&minute=${minute}`)
        //Convert Server To Response Text
            .then(response => response.text())
            //If Successful, Show Confirmation
            .then(data => {
                alert('Alarm Set For ' + hour + ' : ' + minute);
            })
            //If request Fails, Show Error
            .catch(err => {
                console.error(err);
                alert('Failed To Set Alarm');
            });
    });
});
)=====";

#endif

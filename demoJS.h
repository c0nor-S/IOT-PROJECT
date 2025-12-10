#ifndef DEMO_JS_H
#define DEMO_JS_H

const char* demoJS = R"=====(
// Toggle any dropdown by ID
function toggleDropdown(id) {
    document.getElementById(id).classList.toggle("show");
}

// Attach listeners when DOM loads
document.addEventListener("DOMContentLoaded", () => {
    // Hours & Minutes IDs
    const dropdowns = ['hour', 'minute'];
    
    dropdowns.forEach(id => {
        const options = document.querySelectorAll(`#${id} p`);
        const button = document.getElementById(`selected-${id}`);
        
        options.forEach(option => {
            option.addEventListener('click', function() {
                button.textContent = this.textContent;
                document.getElementById(id).classList.remove('show');
            });
        });
    });

    // Close dropdowns if clicked outside
    window.addEventListener('click', function(e) {
        if (!e.target.matches('.dropbtn')) {
            dropdowns.forEach(id => {
                const dropdown = document.getElementById(id);
                dropdown.classList.remove('show');
            });
        }
    });

    // Save Alarm Button
    document.getElementById("save-btn").addEventListener('click', () => {
        const hour = document.getElementById('selected-hour').innerText;
        const minute = document.getElementById('selected-minute').innerText;

        fetch(`/setAlarm?hour=${hour}&minute=${minute}`)
            .then(response => response.text())
            .then(data => {
                alert('Alarm Set For ' + hour + ' : ' + minute);
            })
            .catch(err => {
                console.error(err);
                alert('Failed To Set Alarm');
            });
    });
});
)=====";

#endif

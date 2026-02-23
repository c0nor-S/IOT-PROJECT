String contPagePart1 = F(R"=====(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>SmartRise — Wake Smarter, Rise Easier</title>
  <link rel="stylesheet" href="cont.css" />
  <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@400;500;600&display=swap" rel="stylesheet">
</head>
<body>

  <div class="header">
    <div class="logo">SmartRise
        <span class ="subheader">Control Panel</span>
    </div>
  </div> 

  <section class="hero">
    <div class="hero-content">
        <h1>Wake-Up Options</h1>
        <p>Select Which Methods To Wake Up With</p>

        <div class ="toggle-container">
            <div class ="toggle-item">
                <span>Light</span>
                <label class ="switch">
                    <input type ="checkbox" id ="light-toggle">
                    <span class="slider"></span>
                </label>
            </div>
        

            <div class ="toggle-item">
                <span>Sound</span>
                <label class ="switch">
                    <input type ="checkbox" id ="sound-toggle">
                    <span class="slider"></span>
                </label>
            </div>

            <div class ="toggle-item">
                <span>Fan</span>
                <label class ="switch">
                    <input type ="checkbox" id ="fan-toggle">
                    <span class="slider"></span>
                </label>
            </div>

            <div class ="toggle-item">
                <span>Vibration</span>
                <label class ="switch">
                    <input type ="checkbox" id ="vibration-toggle">
                    <span class="slider"></span>
                </label>
            </div>
        </div>
        <button id="save-btn">Save Settings</button>
     </div>
    </div>
  </section>

  <footer>
    <p>© 2025 SmartRise. All rights reserved.</p>
  </footer>
  
<script>
//Wait Until The Page Is Fully Loaded
window.addEventListener('DOMContentLoaded', () => {
    //Get Referance To The Save Button
    const btn = document.getElementById("save-btn");

//When Save Button Is Clicked
    btn.addEventListener('click', () => {
        //Check Toggle States: Checked = TRUE
        //Convert Boolean 1 (ON) or 0 (OFF)
        const light = document.getElementById('light-toggle').checked ? 1 : 0;
        const fan = document.getElementById('fan-toggle').checked ? 1 : 0;
        const sound = document.getElementById('sound-toggle').checked ? 1 : 0;
        const vibration = document.getElementById('vibration-toggle').checked ? 1 : 0;

        //Build Query String Parameters
        const params = `light=${light}&fan=${fan}&sound=${sound}&vibration=${vibration}`;
        //Contruct Backend URL
        const url = `/saveSettings?${params}`;

        //Send Request To Backend
        fetch(url)
        //Convert Response To Text
            .then(response => response.text())
            //If Successfull, Show Which Devices Are On
            .then(data => {
                alert("Settings Sent!\nCurrently HIGH: " + 
                    [light && "Light", fan && "Fan", sound && "Sound", vibration && "Vibration"]
                        .filter(Boolean)
                        .join(", ")
                );
            })
            //If Request Fails
            .catch(err => {
                console.error(err);
                alert("Failed to send settings");
            });
    });
});
</script>

</body>
</html>)=====");
String dashPagePart1 = F(R"=====(<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>SmartRise — Wake Smarter, Rise Easier</title>
  <link rel="stylesheet" href="dash.css" />
  <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@400;500;600&display=swap" rel="stylesheet">
</head>
<body>

  <div class="header">
    <div class="logo">SmartRise
        <span class ="subheader">Dashboard</span>
    </div>
  </div> 

  <section class="hero">
    <div class="dashboard-readings">
    <div class="hero-content">
      <div class ="sensor-cards" id="temp-card">
        <h3>Temperature</h3>
        <p id =temp-value>)=====");

String dashPagePart2 = F(R"=====(°C</p>
      </div>

      <div class ="sensor-cards" id="humi-card">
        <h3>Humidity</h3>
        <p id =humi-value>)=====");

String dashPagePart3 = F(R"=====(%</p>
      </div>

      <div class ="sensor-cards" id="light-card">
        <h3>Light</h3>
        <p id =light-value>)=====");

String dashPagePart4 = F(R"=====(</p>
      </div>

      <div class ="sensor-cards" id="motion-card">
        <h3>Motion</h3>
        <p id =motion-value>)=====");

String dashPagePart5 = F(R"=====(</p>
      </div>

      <div class ="sensor-cards" id="sound-card">
        <h3>Sound</h3>
        <p id =sound-value>)=====");

String dashPagePart6 = F(R"=====(</p>
      </div>
    </div>
    </div>
  </section>

  <footer>
    <p>© 2025 SmartRise. All rights reserved.</p>
  </footer>

  <script>
    function refreshDashboard() {
      fetch('/dashData')
      .then(response => response.text())
      .then(html => {
        document.querySelector('.dashboard-readings').innerHTML = html;
      })
      .catch(err => console.error('Error Refreshing Dashboard:', err));
    }
    setInterval(refreshDashboard, 2000);
    window.addEventListener('DOMContentLoaded', refreshDashboard);
  </script>

</body>
</html>)=====");
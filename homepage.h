String homePagePart1 = F(R"=====(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>SmartRise — Wake Smarter, Rise Easier</title>
  <link rel="stylesheet" href="home.css" />
  <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@400;500;600&display=swap" rel="stylesheet">
</head>
<body>

  <nav class="navbar">
    <div class="logo">SmartRise</div>
    <div class="nav-links">
      <a href="index.html">Home</a>
      <!--Brings Back To Home Page-->

      <a target ="_blank" href="cont.html">Control</a>
      <!--Bring To Page With All Options For Alarm Controls-->
      
      <a target ="_blank" href="feat.html">Features</a>
      <!--Bring To Page With List, Info & Images Of All Components And What They Do-->
      
      <a target ="_blank" href="dash.html">Dashboard</a>
      <!--Bring To Page With All Recorded Stats From Different Sensors (e.g. Temp & Humi - Motion Detetction...) -->
      
      <a target ="_blank" href="demo.html" class="demo">Live Demo</a>
      <!-- Bring To Page With Every Wake Up Option, Set Time, Colour-Scheme...-->
    </div>
  </nav>

  <section class="hero">
    <div class="hero-content">
      <h1>Wake Smarter, Rise Easier</h1>
      <p>SmartRise is a smart alarm that wakes you gently with light, sound, vibration and a soft breeze - Starting your day right one step at a time.</p>
      <a target ="_self" href="demo.html" class="cta-btn">Try Out</a>
    </div>
  </section>

  <footer>
    <p>© 2025 SmartRise. All rights reserved.</p>
  </footer>

  
</body>
</html>
)=====");

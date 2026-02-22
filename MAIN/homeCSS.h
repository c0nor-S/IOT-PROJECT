const char* homeCSS = R"=====(/* Global */
body {
    margin: 0;
    font-family: 'Poppins', sans-serif;
    background-color: #fdfdfd;
    color: #333;
  }
 
  /* Navbar */
  .navbar {
    position: fixed;
    top: 0;
    width: 100%;
    background-color: rgba(255, 255, 255, 0.9);
    backdrop-filter: blur(10px);
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 12px 30px;
    box-shadow: 0 2px 6px rgba(0,0,0,0.05);
    z-index: 1000;
  }
  
  .logo {
    font-size: 24px;
    font-weight: 700;
    color: #f1c74a;
    letter-spacing: 1px;
  }
  
  .nav-links a {
    color: #555;
    text-decoration: none;
    margin-left: 15px;
    margin-right: 35px;
    padding: 10px 15px;
    border-radius: 30px;
    transition: all 0.3s ease;
    font-weight: 500;
  }
  
  .nav-links a:hover {
    background-color: #ffd87c;
    color: #fff;
  }
  
  .nav-links .demo {
    background-color: #f1c74a;
    color: #fff;
  }
  
  .nav-links .demo:hover {
    background-color: #e6b938;
    color: #fff;
  }
  
  /* Hero Section */
  .hero {
    height: 100vh;
    display: flex;
    align-items: center;
    justify-content: center;
    text-align: center;
    padding: 0 20px;
    background-color: #fdfdfd;
  }
  
  .hero-content {
    max-width: 700px;
    margin-top: 60px;
  }
  
  .hero h1 {
    font-size: 3rem;
    color: #333;
    margin-bottom: 20px;
  }
  
  .hero p {
    font-size: 1.1rem;
    color: #666;
    margin-bottom: 40px;
    line-height: 1.6;
  }
  
  .cta-btn {
    background-color: #f1c74a;
    color: #fff;
    padding: 14px 32px;
    border-radius: 50px;
    font-weight: 600;
    text-decoration: none;
    transition: all 0.3s ease;
  }
  
  .cta-btn:hover {
    background-color: #e6b938;
    transform: translateY(-2px);
  }
  
  /* Footer */
  footer {
    background-color: #fff;
    text-align: center;
    padding: 20px;
    font-size: 0.9rem;
    color: #666;
    border-top: 1px solid #eee;
  })=====";
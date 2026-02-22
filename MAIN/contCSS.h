const char* contCSS = R"=====(/* Global */
body {
    margin: 0;
    font-family: 'Poppins', sans-serif;
    background-color: #fdfdfd;
    color: #333;
  }
  
  /* Navbar */
  .header {
    position: fixed;
    top: 0;
    width: 100%;
    background-color: rgba(255, 255, 255, 0.9);
    backdrop-filter: blur(10px);
    display: flex;
    justify-content: center;
    align-items: center;
    padding: 12px 30px;
    box-shadow: 0 2px 6px rgba(0, 0, 0, 0.05);
    z-index: 1000;
    text-align: center;
  }
  
  .logo {
    font-size: 70px;
    font-weight: 700;
    color: #f1c74a;
    letter-spacing: 1px;
    text-align: center;
  }
  
  .logo .subheader {
    display: block;
    font-size: 24px;
    color: #777;
    letter-spacing: 2px;
    text-transform: uppercase;
    margin-top: 4px;
    text-align: center;
  }
  
  /* Hero Section */
  .hero {
    height: 100vh;
    display: flex;
    flex-direction: column;
    align-self: center;
    align-items: center;
    justify-content: center;
    text-align: center;
    padding: 0 10px;
  }
  
  .hero h1 {
    font-size: 3rem;
    color: #333;
    margin-bottom: 20px;
  }
  
  .hero p {
    font-size: 1.5rem;
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

  .alarm{
    position: relative;
    justify-content: center;
    align-items: center;
    display: flex;
    gap: 10px;
  }

  .dropbtn {
    padding: 16px;
    border: none;
    cursor: pointer;
    background-color: #f1c74a;
    color: #fff;
    border-radius: 8px;
    font-size: 40px;
    font-weight: 600;
    transition: all 0.25s ease;
  }

  .dropbtn:hover{
    background-color: #e6b938
  }

  .toggle-container {
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 25px;
    margin-top: 40px;
  }

  .toggle-item{
    display: flex;
    justify-content: space-between;
    align-items: center;
    width: 300px;
    font-size: 1.5rem;
    font-weight: 500;
  }

  .switch {
    position: relative;
    display: inline-block;
    width: 60px;
    height: 34px;
  }

  .switch input{
    opacity: 0;
    width: 0;
    height: 0;
  }

  .slider {
    position: absolute;
    cursor: pointer;
    top: 0; left: 0;
    right: 0; bottom: 0;
    background-color: #ccc;
    transition: 0.4s;
    border-radius: 34px;
  }

  .slider:before {
    position: absolute;
    content: "";
    height: 26px;
    width: 26px;
    left: 4px;
    bottom: 4px;
    background-color: #fff;
    transition: 0.4s;
    border-radius: 50%;
  }

  input:checked + .slider {
    background-color: #f1c74a;
  }

  input:checked + .slider:before{
    transform: translateX(26px);
  }

  #save-btn {
    margin-top: 50px;
    background-color: #f1c74a;
    color: #fff;
    border: none;
    padding: 16px 40px;
    border-radius: 50px;
    font-weight: 600;
    cursor: pointer;
    font-size: 1.2rem;
    transition: all 0.3 ease;
  }

  #save-btn:hover{
    background-color: #e6b938;
  }

#save-btn:active{ 
    transition: all 0.3s ease;
    transform: scale(0.95);
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
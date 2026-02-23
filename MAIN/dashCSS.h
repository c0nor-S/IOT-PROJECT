const char* dashCSS = R"=====(
/* Global */
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
}

.logo .subheader {
    display: block;
    font-size: 24px;
    color: #777;
    letter-spacing: 2px;
    text-transform: uppercase;
    margin-top: 4px;
}

/* Hero Section */
.hero {
    min-height: 100vh;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    text-align: center;
    padding: 0 20px;
}

.hero-content {
    display: flex;
    flex-wrap: wrap;      /* Wrap cards on smaller screens */
    justify-content: center;
    gap: 20px;            /* Space between cards */
}

.sensor-cards {
    background-color: #fff;
    padding: 20px;
    border-radius: 15px;
    box-shadow: 0 4px 12px rgba(0,0,0,0.1);
    width: 180px;          /* Fixed width for uniform cards */
    text-align: center;
    transition: transform 0.2s ease;
}

.sensor-cards:hover {
    transform: translateY(-5px);
}

.sensor-cards h3 {
    margin-bottom: 10px;
    font-size: 1.2rem;
    color: #333;
}

.sensor-cards p {
    font-size: 1.5rem;
    font-weight: 600;
    color: #f1c74a;
}

/* Footer */
footer {
    background-color: #fff;
    text-align: center;
    padding: 20px;
    font-size: 0.9rem;
    color: #666;
    border-top: 1px solid #eee;
}
)=====";

String demoPagePart1 = F(R"=====(<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>SmartRise — Wake Smarter, Rise Easier</title>
  <link rel="stylesheet" href="/demo.css" />
  <script src="/demo.js"></script>
  <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@400;500;600&display=swap" rel="stylesheet">
</head>
<body>

  <div class="header">
    <div class="logo">SmartRise
        <span class ="subheader">Demo</span>
    </div>
  </div> 

  <section class="hero">
    <div class="hero-content">
      <h1>Alarm Clock</h1>
      <p>Select Your Alarm Time</p>
      <div class="wrapper">
        <div class ="alarm">
          <button onclick="toggleDropdown('hour')" class ="dropbtn" id ="selected-hour">00</button>
          <div id="hour" class="hour_content">
            <p>00</p>
            <p>01</p>
            <p>02</p>
            <p>03</p>
            <p>04</p>
            <p>05</p>
            <p>06</p>
            <p>07</p>
            <p>08</p>
            <p>09</p>
            <p>10</p>
            <p>11</p>
            <p>12</p>
            <p>13</p>
            <p>14</p>
            <p>15</p>
            <p>16</p>
            <p>17</p>
            <p>18</p>
            <p>19</p>
            <p>20</p>
            <p>21</p>
            <p>22</p>
            <p>23</p>
          </div>
        </div>

        <span class = "seperator"> : </span>

        <div class="alarm">
          <button onclick="toggleDropdown('minute')" class ="dropbtn" id ="selected-minute">00</button>
          <div id="minute" class="hour_content">
            <p>00</p>
            <p>01</p>
            <p>02</p>
            <p>03</p>
            <p>04</p>
            <p>05</p>
            <p>06</p>
            <p>07</p>
            <p>08</p>
            <p>09</p>
            <p>10</p>
            <p>11</p>
            <p>12</p>
            <p>13</p>
            <p>14</p>
            <p>15</p>
            <p>16</p>
            <p>17</p>
            <p>18</p>
            <p>19</p>
            <p>20</p>
            <p>21</p>
            <p>22</p>
            <p>23</p>
            <p>24</>
            <p>25</p>
            <p>26</p>
            <p>27</p>
            <p>28</p>
            <p>29</p>
            <p>30</p>
            <p>31</p>
            <p>32</p>
            <p>33</p>
            <p>34</p>
            <p>35</p>
            <p>36</p>
            <p>37</p>
            <p>38</p>
            <p>39</p>
            <p>40</p>
            <p>41</p>
            <p>42</p>
            <p>43</p>
            <p>44</p>
            <p>45</p>
            <p>46</p>
            <p>47</p>
            <p>48</p>
            <p>49</p>
            <p>50</p>
            <p>51</p>
            <p>52</p>
            <p>53</p>
            <p>54</p>
            <p>55</p>
            <p>56</p>
            <p>57</p>
            <p>58</p>
            <p>59</p>
          </div>
        </div>
      </div>
               <button id="save-btn">Save Settings</button>
    </div>
  </section>

  <footer>
    <p>© 2025 SmartRise. All rights reserved.</p>
  </footer>
</body>
</html>)=====");
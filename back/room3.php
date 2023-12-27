<!DOCTYPE html>
<html lang="en">

<head>
    <title>Room3</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet"
        integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <link href="https://fonts.googleapis.com/css2?family=Montserrat:wght@400;500;900&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css2?family=Zen+Tokyo+Zoo&display=swap" rel="stylesheet">
    <script src="https://code.jquery.com/jquery-3.6.4.min.js"></script>

    <style>
        body {
            background: linear-gradient(120deg, #2980b9, #8e44ad);
            min-height: 100vh;
            margin: 0;
            display: flex;
            flex-direction: column;
            align-items: center;
            color: white;
        }

        .container {
            text-align: center;
            padding: 20px;
        }

        h1 {
            font-size: 2.5em;
            font-weight: bold;
            margin-bottom: 20px;
        }

        #info {
            font-size: 1.2em;
            margin-bottom: 20px;
        }

        a {
            color: white;
            text-decoration: none;
            font-size: 1em;
            width: 80%;
            display: block;
            margin: 5px auto;
            padding: 10px;
            border-radius: 5px;
        }

        @media (max-width: 767px) {
            h1 {
                font-size: 2em;
            }

            .modal-dialog {
                margin: 0 auto;
                width: 100%;
            }
        }

        .action-container {
            display: flex;
            flex-direction: column;
            align-items: center;
            width: 100%;
            max-width: 120px;
            justify-content: center;
            /* Added line to center elements vertically */
        }

        .action-container label,
        .action-container input,
        .action-container button {
            width: 100%;
            margin-bottom: 10px;
        }

        .btn {
            display: block;
            background-color: black;
            width: 40px;
            height: 30px;
            color: white;
            border-radius: 50%;
        }

        .btn:active {
            background-color: #111;
            /* Change the background color when clicked */
        }


        .modal-content {
            max-width: 300px;
            /* Set a maximum width */
            padding: 40px 20px;
            /* Increased vertical padding */
            background: linear-gradient(120deg, #2980b9, #8e44ad);
            border-radius: 10px;
            box-shadow: 0 5px 15px rgba(0, 0, 0, 0.3);
            /* Subtle box shadow */
            transition: background 0.3s, box-shadow 0.3s;
            /* Transitions on hover */

            display: flex;
            /*  these three lines so that the inner div comes in the middle of the outer div*/
            justify-content: center;
            align-items: center;
        }

        /* Change background color on hover */
        #tvdiv:hover {
            background: linear-gradient(120deg, #3498db, #9b59b6);
            /* Slightly different gradient on hover */
            box-shadow: 0 10px 20px rgba(0, 0, 0, 0.5);
            /* Shadow becomes slightly more prominent on hover */
        }


        #tvdiv {
            text-align: center;
            /* Optional: Center the content horizontally */
        }

        #myButton {
            border-radius: 50%;

        }

        #ledContainer {
            background: linear-gradient(120deg, #2980b9, #8e44ad);
            border-radius: 10px;
            box-shadow: 0 8px 20px rgba(0, 0, 0, 0.5);
            transition: background 0.3s, box-shadow 0.3s;
            padding: 20px;
            /* Keep the necessary padding */
            margin-top: 20px;
            text-align: center;
            position: absolute;
            top: 40%;
            left: 50%;
            transform: translate(-50%, -50%);
            display: none;
            flex-direction: column;
            align-items: center;
            width: 80%;
            max-width: 250px;
            background-color: #f0f0f0;
            border-radius: 10px;
            text-align: center;
        }

        #leddiv:hover {
            background: linear-gradient(120deg, #3498db, #9b59b6);
            box-shadow: 0 10px 20px rgba(0, 0, 0, 0.5);
        }

        #leddiv {
            text-align: center;
        }

    </style>
</head>

<body>
    <h1>Room 3</h1>
    <div class="container">
        <h1 class="mt-5">LED</h1>
        <button id="myButton" ontouchstart="startTimer()" ontouchend="endTimer()" onmousedown="startTimer()"
            onmouseup="endTimer()" onclick="toggle()" class=" btn-lg btn-danger mt-3">OFF</button>
    </div>

    <div class="action-container " id="ledContainer">
        <div>
            <button type="button" class="btn-close" aria-label="Close" onclick="$('#ledContainer').toggle();">
            </button>
            <h3 class="modal-title" for='colorInput'>lED Light</h3>
        </div>
        <div id="leddiv" class="modal-body text-center">
            <div>
                <label for='ledseconds' id="ledtimerlabel">set a timer</label>
                <input type='number' class='form-control' id='ledseconds' min='0' oninput="validity.valid||(value='');">
                <button class=' btn-warning mt-3' onclick="setTimer('ledseconds')">Set</button>
            </div>
        </div>
    </div>


    <div class="container mt-5">
        <a data-bs-toggle="modal" onclick="$('#TVmod').toggle();" class="btn-primary btn1" data-bs-target="#TVmod"
            style="height: 50px; width: 50px;">TV</a>

        <div class="modal" id="TVmod" tabindex="-1" role="dialog" aria-labelledby="TVmodLabel" aria-hidden="true">
            <div class="modal-dialog modal-dialog-centered modal-md w-100" style="max-width: fit-content;">
                <div class="modal-content">
                    <div class="modal-header" style="background-color: #3498db; color: white;">
                        <h3 class="modal-title" id="TVmodLabel">TV Remote</h3>
                        <button type="button" onclick="$('#TVmod').toggle();" class="btn-close" data-bs-dismiss="modal"
                            aria-label="Close"></button>
                    </div>
                    <div id="tvdiv" class="modal-body text-center">
                        <table>
                            <tr>
                                <td><button
                                        style="border-radius: 50%; background-color: red; width: 40px; height: 30px;"
                                        onclick="irsignal('toggle')">&#x2609</button></td>
                                <td style="border-spacing: 15px;"></td>
                                <td><button style="border-radius: 50%; width: 40px; height: 30px;"
                                        onclick="irsignal('x')">&#x293A;</button></td>

                            </tr>
                            <tr>
                                <td><button class="btn" onclick="irsignal('1')">1</button></td>
                                <td><button class="btn" onclick="irsignal('2')">2</button></td>
                                <td><button class="btn" onclick="irsignal('3')">3</button></td>
                            </tr>
                            <tr>
                                <td><button class="btn" onclick="irsignal('4')">4</button></td>
                                <td><button class="btn" onclick="irsignal('5')">5</button></td>
                                <td><button class="btn" onclick="irsignal('6')">6</button></td>
                            </tr>
                            <tr>
                                <td><button class="btn" onclick="irsignal('7')">7</button></td>
                                <td><button class="btn" onclick="irsignal('8')">8</button></td>
                                <td><button class="btn" onclick="irsignal('9')">9</button></td>
                            </tr>
                            <tr>
                                <td style="border-spacing: 15px;"></td>
                                <td><button class="btn" onclick="irsignal('0')">0</button></td>
                                <td style="border-spacing: 15px;"></td>
                            </tr>
                            <tr>
                                <td><button class="btn" onclick="irsignal('volup')">&#8679;</button></td>
                                <td style="border-spacing: 15px;"></td>
                                <td><button class="btn" onclick="irsignal('chup')">&#8679;</button>
                                </td>
                            </tr>
                            <tr>
                                <td><button class="btn" onclick="irsignal('voldown')">&#8681;</button></td>
                                <td style="border-spacing: 15px;"></td>
                                <td><button class="btn" onclick="irsignal('chdown')">&#8681;</button>
                                </td>
                            </tr>
                        </table>
                        <div class="action-container" id="actionContainer">
                            <label for='tvseconds' id="timerlabel" style="color:black">Enter seconds:</label>
                            <input type='number' class='form-control' id='tvseconds' min='0'
                                oninput="validity.valid||(value='');">
                            <button onclick="setTimer('tvseconds')" class=' btn-warning mt-3'>set</button>
                        </div>

                    </div>

                </div>
            </div>
        </div>
    </div>


    <script type="text/javascript">
        var clickTimer;

        function startTimer() {  // for long press on the button
            clickTimer = setTimeout(function () {
                $('#ledContainer').toggle();
            }, 1000); // if i click for 1000 millies then it will call togglevisibility()
        }

        function endTimer() {  // for long press on the button
            clearTimeout(clickTimer);
        }

        function setTimer(itemID) {   // for put timer to toggleflag
            var secondsValue = document.getElementById(itemID).value;
            xmlhttp = new XMLHttpRequest();
            xmlhttp.open("POST", "updatetimer.php", true);
            xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
            if (itemID == 'tvseconds') {
                xmlhttp.send("table=tv&id=esp1&roomID=3&timer=" + encodeURIComponent(secondsValue));
            }
            else if (itemID == 'ledseconds') {
                xmlhttp.send("table=led&id=esp1&roomID=3&timer=" + encodeURIComponent(secondsValue));
            }

        }

        function toggle() {
            var button = document.getElementById("myButton");
            xmlhttp = new XMLHttpRequest();

            xmlhttp.open("POST", "updatestate.php", true);
            xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
            if (button.innerHTML == "OFF") {
                xmlhttp.send("table=led&id=esp1&roomID=3&state=OFF&changed_by=room3page");
                button.innerHTML = "ON";
                button.classList.remove("btn-danger");
                button.classList.add("btn-success");
            }
            else {
                xmlhttp.send("table=led&id=esp1&roomID=3&state=ON&changed_by=room3page");
                button.innerHTML = "OFF";
                button.classList.remove("btn-success");
                button.classList.add("btn-danger");

            }

        }

        function irsignal(code) {   // for put timer to toggle
            xmlhttp = new XMLHttpRequest();

            xmlhttp.open("POST", "updatetv.php", true);
            xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
            xmlhttp.send("id=esp1&roomID=3&signal_value=" + code);
        }


        setInterval(Get_Data, 500);

        //------------------------------------------------------------
        function getTimeDifferenceInSeconds(databaseTime, buttonID) {

            var [hours, minutes, seconds] = databaseTime.split(':').map(Number);

            var now = new Date();
            var noww = new Date();

            now.setHours(hours);
            now.setMinutes(minutes);
            now.setSeconds(seconds);

            var timeDifferenceInSeconds = Math.floor(((now.getTime()) - Date.now()) / 1000);

            if (timeDifferenceInSeconds < 0) return "set a timer";
            if (buttonID == "tv")
                return "TV will toggle after " + timeDifferenceInSeconds;
            else {
                var button = document.getElementById(buttonID);
                var btnnextstate = button.innerHTML == "OFF" ? "OFF" : "ON";

                if (timeDifferenceInSeconds < 0) return "set a timer";
                return "led will be " + btnnextstate + " after " + timeDifferenceInSeconds;
            }
        }
        //------------------------------------------------------------
        function Get_Data() {
            updatetv();
            updateled();
        }

        function updatetv() {
            xmlhttp = new XMLHttpRequest();

            xmlhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    const myObj = JSON.parse(this.responseText);
                    if (myObj.id == "esp1" && myObj.roomID == "3") {// it should always be true

                        var timer = document.getElementById("timerlabel");

                        var previousDate = myObj.timer_time;
                        timer.innerHTML = getTimeDifferenceInSeconds(previousDate, "tv");

                    }
                }
            };
            xmlhttp.open("POST", "getdata.php", true);
            xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
            xmlhttp.send("id=esp1&table=tv&roomID=3");
        }

        function updateled() {
            xmlhttp = new XMLHttpRequest();

            xmlhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    const myObj = JSON.parse(this.responseText);
                    if (myObj.id == "esp1" && myObj.roomID == "3") {// it should always be true
                        var button = document.getElementById("myButton");
                        var timer = document.getElementById("ledtimerlabel");
                        var previousDate = myObj.timer_time;
                        timer.innerHTML = getTimeDifferenceInSeconds(previousDate, "myButton");


                        if (myObj.state == "ON") {
                            button.innerHTML = "OFF";
                            button.classList.remove("btn-success");
                            button.classList.add("btn-danger");
                        } else if (myObj.state == "OFF") {
                            button.innerHTML = "ON";
                            button.classList.remove("btn-danger");
                            button.classList.add("btn-success");
                        }

                    }
                }
            };
            xmlhttp.open("POST", "getdata.php", true);
            xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
            xmlhttp.send("id=esp1&table=led&roomID=3");

        }

    </script>


</body>

</html>
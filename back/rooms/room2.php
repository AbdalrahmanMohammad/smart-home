<!DOCTYPE html>
<html lang="en">
<?php
session_start();
if ($_SESSION['login'] == false || !(in_array($_SESSION['role'], array('admin'))) && (strpos($_SESSION['role'], '2') == false)) {
    header("location: ../index.php?loginError=1");
    exit;
}
?>

<head>
    <title>Room2</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet"
        integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <link href="https://fonts.googleapis.com/css2?family=Montserrat:wght@400;500;900&display=swap" rel="stylesheet">
    <link href="https://fonts.googleapis.com/css2?family=Zen+Tokyo+Zoo&display=swap" rel="stylesheet">
    <script src="https://code.jquery.com/jquery-3.6.4.min.js"></script>
    <script src="../checkConnection.js"></script>


    <style>
        /* Custom CSS for centering content */
        html,
        body {
            height: 100%;
        }

        body {
            background: linear-gradient(120deg, #2980b9, #8e44ad);
            min-height: 100vh;
            margin: 0;
            display: flex;
            flex-direction: column;
            align-items: center;
            color: white;
        }

        .btn-container {
            text-align: center;
            border-radius: 50%;
        }

        .btn {
            border-radius: 50%;
        }

        .action-container {
            background: linear-gradient(120deg, #2980b9, #8e44ad);
            border-radius: 10px;
            box-shadow: 0 8px 20px rgba(0, 0, 0, 0.5);
            transition: background 0.3s, box-shadow 0.3s;
            padding: 10px;
            margin-top: 20px;
            text-align: center;
            position: absolute;
            padding: 20px;

            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            display: none;
            flex-direction: column;
            align-items: center;
            width: 80%;
            max-width: 250px;
        }

        #leddiv:hover,
        #rgbdiv:hover {
            background: linear-gradient(120deg, #3498db, #9b59b6);
            /* Slightly different gradient on hover */
            box-shadow: 0 10px 20px rgba(0, 0, 0, 0.5);
            /* Shadow becomes slightly more prominent on hover */
        }

        #returnButton {
            position: absolute;
            top: 1px;
            left: 10px;
            cursor: pointer;
            font-size: 55px;
            background: none;
            border: none;
            color: orangered;
        }

        #leddiv,
        #rgbdiv {
            text-align: center;
            /* Optional: Center the content horizontally */
        }

        #left-container,
        #middle-container,
        #right-container {
            width: 100%;
            text-align: center;
            margin-bottom: 20px;
        }

        #left-container,
        #right-container {
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        #rgbseconds,
        #ledseconds,
        #colorInput {
            width: 80%;
            margin-bottom: 10px;
        }

        #ledseconds {
            width: 100%;
        }


        .btn-close {
            position: absolute;
            top: 20px;
            right: 5px;
            cursor: pointer;
            color: white;
        }

        .return-button {
            position: absolute;
            top: 20px;
            left: 5px;
            cursor: pointer;
        }

        #middle-container {
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
        }

        #middle-container button {
            display: block;
            margin-bottom: 10px;
        }

        #rgbtimerbutton {
            width: 80%;
            border-radius: 0;
        }

        .rgb-box {
            background-color: #3498db;
            /* Set your desired color */
            padding: 10px;
            border-radius: 5px;
            margin-bottom: 10px;
            color: white;
            width: 100%;
            position: relative;
        }


        #ledButton {
            border-radius: 50%;
        }
    </style>
</head>

<body>
    <h1>Room 2</h1>

    <div class="container">
        <button id="returnButton" onclick="window.history.back()">&#8592;</button>
        <div class="btn-container">
            <h1 class="mt-5">RGB LED Control</h1>
            <button id="rgbButton" onclick="toggle('rgbButton')" ontouchstart="startTimer('#actionContainer')"
                ontouchend="endTimer()" onmousedown="startTimer('#actionContainer')" onmouseup="endTimer()"
                class="btn btn-lg btn-danger mt-3">OFF</button>

            <h1 class="mt-5">LED</h1>
            <button id="ledButton" onclick="toggle('ledButton')" ontouchstart="startTimer('#ledContainer')"
                ontouchend="endTimer()" onmousedown="startTimer('#ledContainer')" onmouseup="endTimer()"
                class=" btn-lg btn-danger mt-3">OFF</button>
        </div>

        <div class="action-container" id="actionContainer">
            <div class="rgb-box">
                <button type="button" class="btn-close" aria-label="Close" onclick="$('#actionContainer').toggle();">
                </button>
                <h3 class="modal-title" for='colorInput'>RGB Light</h3>
                <span class="return-button" onclick="undo()">&#9100</span>

            </div>
            <div id="rgbdiv" class="modal-body text-center">

                <!-- Right Container: Color input and Set Color button -->
                <div id="right-container">
                    <label for='colorInput'>Choose color:</label>
                    <input type='color' id='colorInput'>
                    <button onclick="setColor()" class='btn btn-warning mt-3'>Set Color</button>
                </div>

                <!-- Middle Container: Buttons -->
                <div id="middle-container">
                    <label id="brightlabel" for="control">Control:</label>
                    <button onclick="buttonClick('button1')" class='btn btn-info'>&#8593</button>
                    <button onclick="buttonClick('button2')" class='btn btn-info'>&#8595</button>
                </div>

                <!-- Left Container: Input and Perform Action button -->
                <div id="left-container">
                    <label for='rgbseconds' id="rgbtimerlabel">set a timer</label>
                    <input type='number' class='form-control' id='rgbseconds' min='0'
                        oninput="validity.valid||(value='');">
                    <button onclick="setTimer('rgbseconds')" id="rgbtimerbutton"
                        class='btn btn-warning mt-3'>Set</button>
                </div>
            </div>
        </div>
    </div>

    <div class="container">

    </div>

    <div class="action-container " id="ledContainer">
        <div class="btn-container">
            <button type="button" class="btn-close" aria-label="Close" onclick="$('#ledContainer').toggle();">
            </button>
            <h3 class="modal-title" for='colorInput'>lED Light</h3>
        </div>
        <div id="leddiv" class="modal-body text-center">
            <div>
                <label id="ledtimerlabel">set a timer</label>
                <input type='number' class='form-control' id='ledseconds' min='0' oninput="validity.valid||(value='');">
                <button onclick="setTimer('ledseconds')" class='btn btn-warning mt-3'>Set</button>
            </div>
        </div>

        <script>
            var clickTimer;

            function startTimer(itemID) {
                clickTimer = setTimeout(function () {
                    $(itemID).toggle();
                }, 1000);
            }

            function endTimer() {
                clearTimeout(clickTimer);
            }

            function setTimer(itemID) {
                var secondsValue = document.getElementById(itemID).value;
                xmlhttp = new XMLHttpRequest();
                xmlhttp.open("POST", "../controlData/updatetimer.php", true);

                xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
                if (itemID == 'rgbseconds') {
                    xmlhttp.send("table=rgb&id=esp1&roomID=2&timer=" + encodeURIComponent(secondsValue));
                }
                if (itemID == 'ledseconds') {
                    xmlhttp.send("table=led&id=esp1&roomID=2&timer=" + encodeURIComponent(secondsValue));
                }
            }

            function toggle(itemID) {
                var button = document.getElementById(itemID);
                xmlhttp = new XMLHttpRequest();

                xmlhttp.open("POST", "../controlData/updatestate.php", true);
                xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
                if (button.innerHTML == "OFF") {
                    if (itemID == 'rgbButton')
                        xmlhttp.send("table=rgb&id=esp1&roomID=2&state=OFF&changed_by=<?php echo ($_SESSION['userName']); ?>");
                    else if (itemID == 'ledButton')
                        xmlhttp.send("table=led&id=esp1&roomID=2&state=OFF&changed_by=<?php echo ($_SESSION['userName']); ?>");
                    button.innerHTML = "ON";
                    button.classList.remove("btn-danger");
                    button.classList.add("btn-success");
                }
                else {
                    if (itemID == 'rgbButton')
                        xmlhttp.send("table=rgb&id=esp1&roomID=2&state=ON&changed_by=<?php echo ($_SESSION['userName']); ?>");
                    else if (itemID == 'ledButton')
                        xmlhttp.send("table=led&id=esp1&roomID=2&state=ON&changed_by=<?php echo ($_SESSION['userName']); ?>");
                    button.innerHTML = "OFF";
                    button.classList.remove("btn-success");
                    button.classList.add("btn-danger");

                }

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
                var button = document.getElementById(buttonID);
                var btnnextstate = button.innerHTML == "OFF" ? "OFF" : "ON";

                if (timeDifferenceInSeconds < 0) return "set a timer";
                return "led will be " + btnnextstate + " after " + timeDifferenceInSeconds;
            }
            //------------------------------------------------------------
            function Get_Data() {
                updateled();
                updatergb();
            }

            function updateled() {
                xmlhttp = new XMLHttpRequest();

                xmlhttp.onreadystatechange = function () {
                    if (this.readyState == 4 && this.status == 200) {
                        const myObj = JSON.parse(this.responseText);
                        if (myObj.id == "esp1" && myObj.roomID == "2") {// it should always be true
                            var button = document.getElementById("ledButton");
                            var timer = document.getElementById("ledtimerlabel");

                            var previousDate = myObj.timer_time;
                            timer.innerHTML = getTimeDifferenceInSeconds(previousDate, "ledButton");


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
                xmlhttp.open("POST", "../controlData/getdata.php", true);
                xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
                xmlhttp.send("id=esp1&table=led&roomID=2");

            }

            function updatergb() {

                xmlhttp = new XMLHttpRequest();

                xmlhttp.onreadystatechange = function () {
                    if (this.readyState == 4 && this.status == 200) {
                        const myObj = JSON.parse(this.responseText);
                        if (myObj.id == "esp1" && myObj.roomID == "2") {// it should always be true
                            var button = document.getElementById("rgbButton");
                            var timer = document.getElementById("rgbtimerlabel");
                            var brightnessLabel = document.getElementById("brightlabel");

                            var previousDate = myObj.timer_time;
                            timer.innerHTML = getTimeDifferenceInSeconds(previousDate, "rgbButton");

                            brightnessLabel.innerHTML = myObj.brightness;

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
                xmlhttp.open("POST", "../controlData/getdata.php", true);
                xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
                xmlhttp.send("table=rgb&id=esp1&roomID=2");

            }


            function buttonClick(buttonName) { // dimdown and up
                xmlhttp = new XMLHttpRequest();
                xmlhttp.open("POST", "../controlData/updatergb.php", true);
                xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
                if ((buttonName == 'button1'))
                    xmlhttp.send("id=esp1&roomID=2&dimup_flag=1");
                else
                    xmlhttp.send("id=esp1&roomID=2&dimdown_flag=1");

            }

            function setColor() {
                var colorInput = document.getElementById('colorInput');
                var colorValue = colorInput.value;
                if (colorValue.toUpperCase() === "#000000") { // if the color is black turn off the rgb
                    var myButton = document.getElementById('rgbButton');
                    myButton.innerHTML = "OFF";
                    myButton.click();
                } else {
                    var xmlhttp = new XMLHttpRequest();
                    xmlhttp.open("POST", "../controlData/updatergb.php", true);
                    xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
                    xmlhttp.send("id=esp1&roomID=2&color_flag=1&color=" + encodeURIComponent(colorValue));
                }
            }


            function undo() {
                xmlhttp = new XMLHttpRequest();
                xmlhttp.open("POST", "../controlData/updatergb.php", true);
                xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
                xmlhttp.send("id=esp1&roomID=2&undo_flag=1");
            }
        </script>
        <script>
            Check_Connection('esp1');
        </script>

</body>

</html>
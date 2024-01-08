<!DOCTYPE html>
<html>
<?php
    session_start();
    if ($_SESSION['login'] == false || !(in_array($_SESSION['role'], array('admin')))) {
      header("location: ../index.php?loginError=1");
      exit;
    }
    ?>
<head>
  <title>Smart socket</title>
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet"
    integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
  <link href="https://fonts.googleapis.com/css2?family=Montserrat:wght@400;500;900&display=swap" rel="stylesheet">
  <link href="https://fonts.googleapis.com/css2?family=Zen+Tokyo+Zoo&display=swap" rel="stylesheet">
  <script src="https://code.jquery.com/jquery-3.6.4.min.js"></script>

  <style>
    html,
    body {
      height: 100%;
    }

    .action-container {
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
    }

    .btn {
      border-radius: 50%;
    }
  </style>
</head>

<body>
  <div class="container">
    <div class="btn-container">
      <h1 class="mt-5">Smart socket</h1>
      <button id="myButton" onclick="toggle()" ontouchstart="startTimer()" ontouchend="endTimer()"
        onmousedown="startTimer()" onmouseup="endTimer()" class="btn btn-lg btn-danger mt-3">OFF</button>
    </div>

    <div class="action-container " id="actionContainer">
      <div>
        <button type="button" class="btn-close" aria-label="Close" onclick="$('#actionContainer').toggle();">
        </button>
        <h3 class="modal-title" for='colorInput'>Smart socket</h3>
      </div>
      <div id="leddiv" class="modal-body text-center">
        <div>
          <label for='seconds' id="timerlabel">set a timer</label>
          <input type='number' class='form-control' id='seconds' min='0' oninput="validity.valid||(value='');">
          <button onclick="setTimer()" class='btn btn-warning mt-3'>Set</button>
        </div>
      </div>
    </div>

  </div>

  <script>
    var clickTimer;

    function startTimer() {  // for long press on the button
      clickTimer = setTimeout(function () {
        $('#actionContainer').toggle();
      }, 1000); // if i click for 1000 millies then it will call togglevisibility()
    }

    function endTimer() {  // for long press on the button
      clearTimeout(clickTimer);
    }

    function setTimer() {   // for put timer to toggle
      var secondsValue = document.getElementById('seconds').value;
      xmlhttp = new XMLHttpRequest();

      xmlhttp.open("POST", "../controlData/updatetimer.php", true);
      xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      xmlhttp.send("id=esp01&table=socket&roomID=-&timer=" + encodeURIComponent(secondsValue));

    }




    function toggle() {
      var button = document.getElementById("myButton");
      xmlhttp = new XMLHttpRequest();

      xmlhttp.open("POST", "../controlData/updatestate.php", true);
      xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      if (button.innerHTML == "OFF") {
        xmlhttp.send("id=esp01&table=socket&roomID=-&state=OFF&changed_by=smartsocket");
        button.innerHTML = "ON";
        button.classList.remove("btn-danger");
        button.classList.add("btn-success");
      }
      else {
        xmlhttp.send("id=esp01&table=socket&roomID=-&state=ON&changed_by=smartsocket");
        button.innerHTML = "OFF";
        button.classList.remove("btn-success");
        button.classList.add("btn-danger");

      }

    }


    setInterval(Get_Data, 500);

    //------------------------------------------------------------
    function getTimeDifferenceInSeconds(databaseTime) {

    var [hours, minutes, seconds] = databaseTime.split(':').map(Number);

    var now = new Date();
    var noww = new Date();

    now.setHours(hours);
    now.setMinutes(minutes);
    now.setSeconds(seconds);

    var timeDifferenceInSeconds = Math.floor(((now.getTime())-Date.now())/1000);

    var button = document.getElementById("myButton");
      var btnnextstate=button.innerHTML=="OFF"?"OFF":"ON";
    
      if (timeDifferenceInSeconds<0) return "set a timer";
    return "your socket will be "+btnnextstate+" after "+timeDifferenceInSeconds;
}
    //------------------------------------------------------------
    function Get_Data(id) {

      xmlhttp = new XMLHttpRequest();

      xmlhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          const myObj = JSON.parse(this.responseText);
          if (myObj.id == "esp01"&&myObj.roomID == "-") {// it should always be true
            var button = document.getElementById("myButton");
            var timer = document.getElementById("timerlabel");

            var previousDate = myObj.timer_time;
            timer.innerHTML =  getTimeDifferenceInSeconds(previousDate);


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
      xmlhttp.send("id=esp01&table=socket&roomID=-");
    }
    //------------------------------------------------------------



  </script>

</body>

</html>
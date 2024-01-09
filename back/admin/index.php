<!DOCTYPE html>
<html lang="en">

<head>
  <title>Admin Page</title>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/sweetalert2@10.16.6/dist/sweetalert2.min.css">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
  <style>
    /* Custom CSS for the page background with linear gradient */
    body {
      background: linear-gradient(120deg, #2980b9, #8e44ad);
      min-height: 100vh;
      margin: 0;
      display: flex;
      flex-direction: column;
      align-items: center;
      color: white;
    }

    /* New style for the top bar */
    .top-bar {
      background-color: #2c3e50;
      width: 100%;
      padding: 10px;
      text-align: center;
      display: flex;
      justify-content: space-between;
      align-items: center;
    }

    .top-bar h2 {
      margin: 0;
    }

    .icon {
      width: 50px;
      height: 50px;
      cursor: pointer;
      margin-left: 10px;
      /* Adjust margin as needed */
    }

    /* Media query for larger screens (PCs) */
    @media (min-width: 992px) {
      .icon {
        width: 70px;
        /* Adjust the icon size for larger screens */
        height: 70px;
      }
    }

    .container {
      text-align: center;
      padding: 20px;
      max-width: 80%;
      /* Adjusted max-width for responsiveness */
    }

    h1 {
      font-size: 2.5em;
      font-weight: bold;
      margin-bottom: 20px;
    }

    #clock {
      font-size: 2.2em;
      font-weight: bold;
    }

    #info {
      font-size: 1.2em;
      margin-bottom: 20px;
    }

    a {
      color: white;
      text-decoration: none;
      font-size: 1em;
      display: block;
      margin-bottom: 10px;
      padding: 10px;
      border-radius: 5px;
      width: 100%;
      /* Default width for all devices */
    }

    .btn {
      margin: 0 auto;
      padding: 10px;
      border-radius: 28px;
      display: block;

    }

    /* Different background colors for buttons */
    .btn1 {
      background-color: #3498db;
      /* Blue */
    }

    .btn2 {
      background-color: #e67e22;
      /* Orange */
    }

    .btn3 {
      background-color: #2ecc71;
      /* Green */
    }

    .btn4 {
      background-color: #e74c3c;
      /* Red */
    }

    /* Improve button style */
    .custom-button:hover {
      background-color: #2980b9;
    }

    /* Media query for smaller screens (phones) */
    @media (max-width: 576px) {
      a {
        width: 100%;
        /* Set width to 100% for smaller screens (phones) */
      }

    }

    /* Media query for larger screens (PCs) */
    @media (min-width: 992px) {
      .btn {
        width: 30%;
        /* Set width to 30% for larger screens (PCs) */
        display: block;
        margin-bottom: 10px;

      }

      /* Different background colors for buttons */
      .btn1 {
        width: 30%;
      }

      .btn2 {
        width: 27%;
      }

      .btn3 {
        width: 23%;
      }

      .btn4 {
        width: 18%;
      }

    }
  </style>
</head>

<body>
  <!-- Top bar -->
  <div class="top-bar">
    <img id="doorIcon" class="icon" src="open.png" alt="Door Icon">
    <img id="tempIcon" class="icon" src="temp.webp" alt="temp Icon">
    <img id="powerIcon" class="icon" src="power.png" alt="power Icon">
    <img id="lcdIcon" class="icon" src="lcd.png" alt="lcd Icon">
  </div>

  <div class="container mt-3">
    <?php
    session_start();
    if ($_SESSION['login'] == false || !(in_array($_SESSION['role'], array('admin')))) { // the second condition is !$_SESSION['role']=="admin"
      header("location: ../index.php?loginError=1");
      exit;
    }
    ?>

    <h1>This is Admin Page</h1>
    <div id="info">
      <div>Welcome:
        <?php echo $_SESSION['userName'] ?>
      </div>
    </div>

    <a href="del.php" class="btn btn-primary custom-button btn1">Edit Users</a>
    <a href="create_user.php" class="btn btn-secondary custom-button btn2">Add User</a>
    <a href="../rooms/room1.php" class="btn btn-info custom-button btn3">Room 1</a>
    <a href="../rooms/room2.php" class="btn btn-info custom-button btn3">Room 2</a>
    <a href="../rooms/room3.php" class="btn btn-info custom-button btn3">Room 3</a>
    <a href="../smartsocket" class="btn btn-info custom-button btn3">Smart socket</a>
    <a href="../logout.php" class="btn btn-danger custom-button btn4">Logout</a>
  </div>

  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/jquery@3.6.0/dist/jquery.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/sweetalert2@10.16.6/dist/sweetalert2.min.js"></script>
  <script>
    let fireFlag = false;
    let doorOpen = true;

    // Update the clock every second
    function updateClock() {
      const now = new Date();
      const hours = now.getHours().toString().padStart(2, '0');
      const minutes = now.getMinutes().toString().padStart(2, '0');

      document.getElementById('clock').innerText = hours + ':' + minutes;
    }

    // Update temperature and humidity (placeholders in this example)
    function updateTempHumidity() {
      document.getElementById('temperature').innerText = '25°C'; // Placeholder, replace with real data
      document.getElementById('humidity').innerText = '10%';
    }

    // Toggle door icon on click
    document.getElementById('doorIcon').addEventListener('click', function () {
      const xmlhttp = new XMLHttpRequest();
      xmlhttp.open('POST', '../controlData/controldoor.php', true);
      xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
      if (doorOpen) {
        this.src = 'closed.png';
        xmlhttp.send('id=esp1&state=closed&flag=1');
        doorOpen=false;
      } else {
        this.src = 'open.png';
        xmlhttp.send('id=esp1&state=open&flag=1');
        doorOpen=true;
      }
    });

    setInterval(Get_Data, 500);
    function Get_Data() {
      Get_Data_Fire();
      Get_Data_Door();
    }
    function Get_Data_Door() {
      const xmlhttp = new XMLHttpRequest();

      xmlhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          const myObj = JSON.parse(this.responseText);
          if (myObj.id == 'esp1') {
            if (myObj.state == 'open'&&doorOpen==false) {
              document.getElementById('doorIcon').src='open.png';
              doorOpen=true;
            }
            else if (myObj.state == 'closed'&&doorOpen==true) {
              document.getElementById('doorIcon').src='closed.png';
              doorOpen=false;
            }
          }
        }
      };

      xmlhttp.open('POST', '../controlData/controldoor.php', true);
      xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
      xmlhttp.send('id=esp1');
    }

    function Get_Data_Fire() {
      const xmlhttp = new XMLHttpRequest();

      xmlhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          const myObj = JSON.parse(this.responseText);
          if (myObj.id == 'esp1') {
            if (myObj.fire == 'true' && !fireFlag) {
              fireFlag = true;

              Swal.fire({
                title: 'THE HOUSE IS ON FIRE',
                text: 'Smoke sensor detected smoke in the house',
                icon: 'warning',
                confirmButtonColor: '#3085d6',
                confirmButtonText: 'Stop the Alert',
              }).then((result) => {
                if (result.isConfirmed) {
                  Swal.fire({
                    title: 'Alert stopped!',
                    text: 'Thanks for dealing with the situation',
                    icon: 'success',
                  });
                  fireFlag = false;
                  xmlhttp.open('POST', '../controlData/updatesmokesensor.php', true);
                  xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
                  xmlhttp.send('id=esp1&fire=false');
                }
              });
            }
          }
        }
      };

      xmlhttp.open('POST', '../controlData/getsmokesensor.php', true);
      xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
      xmlhttp.send('id=esp1');
    }
  </script>
</body>

</html>
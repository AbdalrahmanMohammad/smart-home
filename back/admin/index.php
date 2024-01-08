<!DOCTYPE html>
<html>

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
  <div class="container mt-5">
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
      <div id="clock"></div>
      <div>Temperature: <span id="temperature">25°C</span>, Humidity: <span id="humidity">50%</span></div>
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

    setInterval(Get_Data_rgb, 500);

    function Get_Data_rgb() {
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
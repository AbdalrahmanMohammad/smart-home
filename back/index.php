<?php 
	require 'Class.login.php';
	
	if ( !empty($_POST)){
	 login::checkIn($_POST['Username'],$_POST['password']);
	} 
?>
<!DOCTYPE html>
<html>

<head>
  <title>Smart Home Control</title>
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
  <style>
    /* Custom CSS for clock */
    #clock {
      font-size: 2.5em;
      font-weight: bold;
      text-align: center;
      margin-bottom: 20px;
      color: white; /* White text for visibility on the gradient background */
    }

    /* Custom CSS for temperature and humidity display */
    #temp-humidity {
      text-align: center;
      margin-bottom: 20px;
      color: white; /* White text for visibility on the gradient background */
    }

    /* Custom CSS for login section */
    #login-section {
      max-width: 300px; /* Set a maximum width */
      padding: 40px 20px; /* Increased vertical padding */
      background: linear-gradient(120deg, #2980b9, #8e44ad);
      border-radius: 10px;
      box-shadow: 0 5px 15px rgba(0, 0, 0, 0.3); /* Subtle box shadow */
      transition: background 0.3s, box-shadow 0.3s; /* Transitions on hover */
    }

    /* Change background color on hover */
    #login-section:hover {
      background: linear-gradient(120deg, #3498db, #9b59b6); /* Slightly different gradient on hover */
      box-shadow: 0 10px 20px rgba(0, 0, 0, 0.5); /* Shadow becomes slightly more prominent on hover */
    }

    /* Custom CSS for login button */
    .login-button {
      background-color: #e74c3c; /* Alizarin red */
      border: none;
    }
    .login-button:hover {
      background-color: #c0392b; /* Darker red on hover */
    }

    /* Custom CSS for the page background with linear gradient */
    body {
      background: linear-gradient(120deg, #2980b9, #8e44ad);
      min-height: 100vh;
      margin: 0;
      display: flex;
      flex-direction: column;
      color: white; /* White text for visibility on the gradient background */
    }

    /* Remove margin from the last child of the container */
    .container>:last-child {
      margin-bottom: 0;
    }
  </style>
</head>

<body>
<?php
  if (isset($_GET['loginError'])) {//header("location: index.php?loginError=1");
    Tools::printError('error logging in   ');
  }

  ?>
  <div class="container mt-5">
    <div id="clock" class="text-center"></div>
    <div id="temp-humidity">PTUK SMART HOME</div>

    <div id="login-section" class="mx-auto">
      <h3 class="text-center mb-4">Login</h3>
      <form method="POST" action="index.php" method="post">
        <div class="form-group">
          <label for="username">Username</label>
          <input type="text" class="form-control" id="username" placeholder="Enter username" name="Username" required>
        </div>
        <div class="form-group">
          <label for="password">Password</label>
          <input type="password" class="form-control" id="password" placeholder="Password"name="password" required>
        </div>
        <button type="submit" class="btn btn-danger btn-block login-button" value="Login" >Login</button>

      </form>
    </div>
  </div>

  <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>

  <script>
    // Update the clock every second
     function updateClock() {
            var now = new Date();
            var hours = now.getHours().toString().padStart(2, '0');
            var minutes = now.getMinutes().toString().padStart(2, '0');
            var seconds = now.getSeconds().toString().padStart(2, '0');

            document.getElementById('clock').innerText = hours + ':' + minutes + ':' + seconds;
        }

    // Update the clock immediately and then every second
    updateClock();
    setInterval(updateClock, 1000);
  </script>
</body>

</html>

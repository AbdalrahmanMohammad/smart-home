<?php 
	require 'Class.login.php';
	
	if ( !empty($_POST)){
	 login::checkIn($_POST['Username'],$_POST['password']??null);
	} 
?>
<!DOCTYPE html>
<html>

<head>
  <title>Smart Home Control</title>
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
  <style>
    #clock {
      font-size: 2.5em;
      font-weight: bold;
      text-align: center;
      margin-bottom: 20px;
      color: white; 
    }

    #temp-humidity {
      text-align: center;
      margin-bottom: 20px;
      color: white; 
    }

    #login-section {
      max-width: 300px;
      padding: 40px 20px; 
      background: linear-gradient(120deg, #2980b9, #8e44ad);
      border-radius: 10px;
      box-shadow: 0 5px 15px rgba(0, 0, 0, 0.3); 
      transition: background 0.3s, box-shadow 0.3s; 
    }

    #login-section:hover {
      background: linear-gradient(120deg, #3498db, #9b59b6); 
      box-shadow: 0 10px 20px rgba(0, 0, 0, 0.5); 
    }

    .login-button {
      background-color: #e74c3c; 
      border: none;
    }
    .login-button:hover {
      background-color: #c0392b; 
    }

    body {
      background: linear-gradient(120deg, #2980b9, #8e44ad);
      min-height: 100vh;
      margin: 0;
      display: flex;
      flex-direction: column;
      color: white; 
    }

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
     function updateClock() {
            var now = new Date();
            var hours = now.getHours().toString().padStart(2, '0');
            var minutes = now.getMinutes().toString().padStart(2, '0');
            var seconds = now.getSeconds().toString().padStart(2, '0');

            document.getElementById('clock').innerText = hours + ':' + minutes + ':' + seconds;
        }

    updateClock();
    setInterval(updateClock, 1000);
  </script>
</body>

</html>

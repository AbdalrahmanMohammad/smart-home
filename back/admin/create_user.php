<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Create Account</title>
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
  <script src="../checkConnection.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
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

    #createuser-section {
      max-width: 330px;
      width: 100%;
      margin-top: 50px;
      padding: 20px;
      background: linear-gradient(120deg, #2980b9, #8e44ad);
      border-radius: 10px;
      box-shadow: 0 5px 15px rgba(0, 0, 0, 0.3);
      transition: background 0.3s, box-shadow 0.3s;
    }

    #createuser-section:hover {
      background: linear-gradient(120deg, #3498db, #9b59b6);
      box-shadow: 0 10px 20px rgba(0, 0, 0, 0.5);
    }

    .create-button {
      background-color: #27ae60;
      border: none;
      transition: background-color 0.3s;
    }

    .create-button:hover {
      background-color: #2ecc71;
    }

    .back-button {
      background-color: #3498db;
      border: none;
      transition: background-color 0.3s;
    }

    .back-button:hover {
      background-color: #2980b9;
    }

    /* Added style for checkboxes */
    .checkbox-group {
      display: flex;
      justify-content: space-between;
    }

    .checkbox-group label {
      flex-basis: 30%;
    }
  </style>
</head>

<script>
  Check_Connection('esp1');

  $(document).ready(function () {
    $("#role").change(function () {
      if ($(this).val() === "normal") {
        $(".checkbox-group input").prop("disabled", false);
        $(".checkbox-group ").show();
        $(".allowed_rooms").show();
      } else {
        $(".checkbox-group input").prop("disabled", true);
        $(".checkbox-group ").hide();
        $(".allowed_rooms").hide();
      }
    });
  });
</script>


<?php
if (!empty($_POST)) {
  require_once("../Class.data.php");
  require_once("../Class.Tools.php");

  $allowedRoomsString = "";

  if (isset($_POST['room1'])) {
    $allowedRoomsString = $allowedRoomsString . $_POST['room1'];
  }
  if (isset($_POST['room2'])) {
    $allowedRoomsString = $allowedRoomsString . $_POST['room2'];
  }
  if (isset($_POST['room3'])) {
    $allowedRoomsString = $allowedRoomsString . $_POST['room3'];
  }
  $roleWithRooms = $_POST['role'] . '' . $allowedRoomsString;

  $result = data::addNew($_POST['username'], $_POST['email'], $_POST['password'], $roleWithRooms);

  if ($result === true) {
    Tools::printSuccess("One record has been inserted successfully.");
  } else {
    Tools::printError("Unexpected result: " . var_export($result, true));
  }
}
?>


<body>
  <?php
  session_start();
  if ($_SESSION['login'] == false or !(in_array($_SESSION['role'], array('admin')))) {
    header("location: ../index.php?loginError=1");
    exit;
  }
  ?>
  <div id="createuser-section" class="mx-auto">
    <h1 class="text-center mb-4">Create Account</h1>
    <form method="POST" action="create_user.php" enctype="multipart/form-data">
      <div class="form-group">
        <label for="username">Username:</label>
        <input type="text" class="form-control" id="username" name="username" required>
      </div>
      <div class="form-group">
        <label for="password">Password:</label>
        <input type="password" class="form-control" id="password" name="password" required>
      </div>
      <div class="form-group">
        <label for="email">Email:</label>
        <input type="email" class="form-control" id="email" name="email" required>
      </div>
      <div class="form-group">
        <label for="role">Role:</label>
        <select class="form-control" id="role" name="role" required>
          <option value="normal">Normal</option>
          <option value="admin">Admin</option>
        </select>
      </div>
      <div class="form-group allowed_rooms">
        <label>Allowed Rooms:</label>
        <div class="checkbox-group">
          <label><input type="checkbox" id="room1" name="room1" value="1"> Room 1</label>
          <label><input type="checkbox" id="room2" name="room2" value="2"> Room 2</label>
          <label><input type="checkbox" id="room3" name="room3" value="3"> Room 3</label>
        </div>
      </div>
      <button type="submit" class="btn btn-danger btn-block create-button">Create Account</button>
      <a href="index.php" class="btn btn-light btn-block mt-2 back-button">Back</a>
    </form>
  </div>
  <script>
    Check_Connection('esp1');
  </script>
</body>

</html>
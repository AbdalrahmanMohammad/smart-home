<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Edit User</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
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

        #edituser-section {
            max-width: 330px;
            width: 100%;
            margin-top: 50px;
            padding: 20px;
            background: linear-gradient(120deg, #2980b9, #8e44ad);
            border-radius: 10px;
            box-shadow: 0 5px 15px rgba(0, 0, 0, 0.3);
            transition: background 0.3s, box-shadow 0.3s;
        }

        #edituser-section:hover {
            background: linear-gradient(120deg, #3498db, #9b59b6);
            box-shadow: 0 10px 20px rgba(0, 0, 0, 0.5);
        }

        .save-button {
            background-color: #27ae60;
            border: none;
            transition: background-color 0.3s;
        }

        .save-button:hover {
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

<?php
require_once("../Class.data.php");

if (!empty($_POST['submit']) && $_POST['submit'] == 'Save') {
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

    $test = data::updateuser($_POST['name'], $_POST['email'], $_POST['password'], $roleWithRooms);

    if ($test) {
        Tools::printSuccess("Updated Successfully <a href ='index.php'>Go back</a>");
    } else {
        Tools::printError("Updated Failed <a href ='index.php'>Go back</a>");
    }
}

$usrinfo = data::getallinfo($_POST['name']); // get user info
$row = $usrinfo->fetch();

?>

<script>
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

<body>
    <?php

    session_start();
    if ($_SESSION['login'] == false or !(in_array($_SESSION['role'], array('admin')))) {
        header("location: ../index.php?loginError=1");
        exit;
    }

    ?>
    <div id="edituser-section" class="mx-auto">
        <h1 class="text-center mb-4">Edit Account</h1>
        <form method="POST" action="" enctype="multipart/form-data">
            <div class="form-group">
                <label for="name">Username:</label>
                <input type="text" class="form-control" id="name" name="name" required readonly
                    value="<?php echo $row['name']; ?>">
            </div>
            <div class="form-group">
                <label for="password">Password:</label>
                <input type="password" class="form-control" id="password" name="password">
            </div>
            <div class="form-group">
                <label for="email">Email:</label>
                <input type="email" class="form-control" id="email" name="email" required
                    value="<?php echo $row['email']; ?>">
            </div>
            <div class="form-group">
                <label for="role">Role:</label>
                <select class="form-control" id="role" name="role" required>
                    <option value="normal" <?php if (strpos($row['role'], 'normal') !== false)
                        echo "selected"; ?>>Normal
                    </option>
                    <option value="admin" <?php if ($row['role'] == "admin")
                        echo "selected"; ?>>Admin</option>
                </select>
            </div>
            <div class="form-group allowed_rooms" <?php if ($row['role'] == "admin") echo "style='display: none;'"; ?>>
                <label>Allowed Rooms:</label>
                <div class="checkbox-group">
                    <label><input type="checkbox" id="room1" name="room1" value="1" <?php if (strpos($row['role'], '1') !== false)
                        echo "checked"; ?>> Room 1</label>
                    <label><input type="checkbox" id="room2" name="room2" value="2" <?php if (strpos($row['role'], '2') !== false)
                        echo "checked"; ?>> Room 2</label>
                    <label><input type="checkbox" id="room3" name="room3" value="3" <?php if (strpos($row['role'], '3') !== false)
                        echo "checked"; ?>> Room 3</label>
                </div>
            </div>
            <button type="submit" class="btn btn-danger btn-block save-button" name="submit" value="Save">Save</button>
            <a href="del.php" class="btn btn-light btn-block mt-2 back-button">Back</a>
        </form>
    </div>
</body>

</html>
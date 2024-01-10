<?php
include '../database.php';
session_start();
if ($_SESSION['login'] == false || !(in_array($_SESSION['role'], array('admin')))) { // the second condition is !$_SESSION['role']=="admin"
    header("location: ../index.php?loginError=1");
    exit;
}

$id = $_GET['id'];
$device = $_GET['device'];
$selectedDate = $_GET['date'] ?? date('Y-m-d');

$parts = explode("-", $device);

$table = trim($parts[0]);
$roomID = trim($parts[1]);

$id = ($table == "socket") ? "esp01" : "esp1";
$roomID = ($roomID == "") ? "-" : $roomID;

$pdo = Database::connect();

$sql = "SELECT * FROM records WHERE id=? AND `table`=? AND roomID=? AND `date`=?";
$stmt = $pdo->prepare($sql);
$stmt->execute(array($id, $table, $roomID, $selectedDate));
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>devices records</title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
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

        #container {
            max-width: 100%;
            padding: 10px;
            background: linear-gradient(120deg, #2980b9, #8e44ad);
            border-radius: 10px;
            box-shadow: 0 5px 15px rgba(0, 0, 0, 0.3);
            transition: background 0.3s, box-shadow 0.3s;
            margin: 10px auto;
        }

        #container:hover {
            background: linear-gradient(120deg, #3498db, #9b59b6);
            box-shadow: 0 10px 20px rgba(0, 0, 0, 0.5);
        }

        /* Table Styles */
        #container table {
            width: 100%;
            margin-bottom: 20px;
            color: white;
            border-collapse: collapse;
        }

        #container table th,
        #container table td {
            border: none;
            padding: 12px;
            text-align: center;
        }

        #container table th {
            background-color: #2c3e50;
        }

        #container table tr:hover {
            background-color: rgba(255, 255, 255, 0.1);
        }

        .back-button {
            background-color: #3498db;
            border: none;
            transition: background-color 0.3s;
            display: block;
            width: 100%;
            padding: 15px;
            margin-top: 10px;
            text-decoration: none;
            color: white;
            border-radius: 5px;
            text-align: center;
        }

        .back-button:hover {
            background-color: #2980b9;
        }
    </style>
</head>

<body>
    <div id="container">
        <h1 class="text-center">devices records</h1>
        <div class="table-responsive">
            <table class="table">
                <thead class="thead-dark">
                    <tr>
                        <th>ID</th>
                        <th>Room ID</th>
                        <th>Table</th>
                        <th>State</th>
                        <th>Time</th>
                        <th>Date</th>
                        <th>Changed By</th>
                    </tr>
                </thead>
                <tbody>
                    <?php
                    foreach ($stmt as $row) {
                        echo "<tr>
                                <td>{$row['id']}</td>
                                <td>{$row['roomID']}</td>
                                <td>{$row['table']}</td>
                                <td>{$row['state']}</td>
                                <td>{$row['time']}</td>
                                <td>{$row['date']}</td>
                                <td>{$row['changed_by']}</td>
                            </tr>";
                    }
                    ?>
                </tbody>
            </table>
        </div>
        <a href="../admin/power_statistics.php" class="back-button">Back</a>
    </div>
</body>

</html>

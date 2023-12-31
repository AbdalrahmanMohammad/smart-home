<?php
include 'database.php';

if (!empty($_POST)) {

    $id = $_POST['id'];

    $myObj = (object) array();

    // Connect to the database
    $pdo = Database::connect();

    // Retrieve data from the database
    $sql = "SELECT * FROM lcd WHERE id=?";
    $stmt = $pdo->prepare($sql);
    $stmt->execute(array($id));

    if ($stmt->rowCount() > 0) {
        $row = $stmt->fetch(PDO::FETCH_ASSOC);

        $myObj->id = $row['id'];
        $myObj->show = $row['show'];

        // Get the current date and time for Jerusalem, Palestine timezone
        $timezone = new DateTimeZone('Asia/Jerusalem');
        $datetime = new DateTime('now', $timezone);

        // Add date and time as separate properties
        $myObj->date = $datetime->format('Y-m-d');
        $myObj->time = $datetime->format('H:i');

    }

    $sql = "SELECT * FROM smoke_sensor WHERE id=?";
    $stmt = $pdo->prepare($sql);
    $stmt->execute(array($id));

    if ($stmt->rowCount() > 0) {
        $row = $stmt->fetch(PDO::FETCH_ASSOC);

        $myObj->fire = $row['fire'];
    }

    $myJSON = json_encode($myObj);
    echo $myJSON;
    // Disconnect from the database
    Database::disconnect();
}
?>

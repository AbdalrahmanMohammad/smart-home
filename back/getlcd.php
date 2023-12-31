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

        $myObj->show = $row['show'];

        // Get the current date and time for Jerusalem, Palestine timezone
        $timezone = new DateTimeZone('Asia/Jerusalem');
        $datetime = new DateTime('now', $timezone);

        // Add date and time as separate properties
        $myObj->date = $datetime->format('Y-m-d');
        $myObj->time = $datetime->format('H:i');

        // Convert the object to JSON
        $myJSON = json_encode($myObj);

        // Echo the JSON data
        echo $myJSON;
    }

    // Disconnect from the database
    Database::disconnect();
}
?>

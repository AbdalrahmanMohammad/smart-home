<?php
require 'database.php';

//---------------------------------------- Condition to check that POST value is not empty.
if (!empty($_POST)) {
    //........................................ keep track POST values
    $id = $_POST['id'];
    $roomID = $_POST['roomID'];
    $led_state = $_POST['LED'];

    //........................................

    //........................................ Get the time and date.
    date_default_timezone_set("Asia/Jerusalem");
    $tm = date("H:i:s");
    $dt = date("Y-m-d");
    //........................................

    //........................................ Updating the data in the table.
    $pdo = Database::connect();
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $sql = 'SELECT * FROM room WHERE id="' . $id . '" AND roomID="' . $roomID . '"';
    $q = $pdo->prepare($sql);
    $q->execute();

    $state = "unknown";
    if ($row = $q->fetch(PDO::FETCH_ASSOC)) {
        $state = $row['LED'];
    }

    if ($state != $led_state && $state != "unknown") {
        $sql = "UPDATE room SET LED = ?, time = ?, date = ? WHERE id = ? AND roomID = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($led_state, $tm, $dt, $id, $roomID));
    }

    Database::disconnect();
    //........................................
}
?>
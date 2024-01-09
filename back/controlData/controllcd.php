<?php
include '../database.php';
require 'Class.authorization.php';
if (!empty($_POST) && authorization::authorize($_POST['id'], $_POST['password'] ?? null)) {
    // if it gets show then it updates, else it will return

    $id = $_POST['id'];
    $show = $_POST['show'] ?? null;


    $myObj = (object) array();

    $pdo = Database::connect();

    if ($show == null) {
        $sql = "SELECT * FROM lcd WHERE id=?";
        $stmt = $pdo->prepare($sql);
        $stmt->execute(array($id));

        if ($stmt->rowCount() > 0) {
            $row = $stmt->fetch(PDO::FETCH_ASSOC);

            $myObj->id = $row['id'];
            $myObj->show = $row['show'];

            $timezone = new DateTimeZone('Asia/Jerusalem');
            $datetime = new DateTime('now', $timezone);

            $myObj->date = $datetime->format('Y-m-d');
            $myObj->time = $datetime->format('H:i');

        }
        //////////////////////////////////////////////////////// this part is important to show fire alert in the lcd 
        $sql = "SELECT * FROM smoke_sensor WHERE id=?";   // in case there is fire, otherwise it will just show the time or temperature.
        $stmt = $pdo->prepare($sql);
        $stmt->execute(array($id));

        if ($stmt->rowCount() > 0) {
            $row = $stmt->fetch(PDO::FETCH_ASSOC);

            $myObj->fire = $row['fire'];
        }

        $myJSON = json_encode($myObj);
        echo $myJSON;
    } else {
        $sql = "UPDATE lcd SET `show` = ? WHERE id = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($show, $id));
    }
    Database::disconnect();
}
?>
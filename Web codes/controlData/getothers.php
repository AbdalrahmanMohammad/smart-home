<?php
include '../database.php';//it reutrns smokesensor, lcd, door, bedtimeCommand
require 'Class.authorization.php';
if (!empty($_POST) && authorization::authorize($_POST['id'], $_POST['password'] ?? null)) {

    $id = $_POST['id'];

    $myObj = (object) array();

    //........................................ 
    $pdo = Database::connect();

    $sql = "SELECT * FROM smoke_sensor WHERE id=?";
    $stmt = $pdo->prepare($sql);
    $stmt->execute(array($id));

    if ($stmt->rowCount() > 0) {
        $row = $stmt->fetch(PDO::FETCH_ASSOC);

        $myObj->id = $row['id'];
        $myObj->fire = $row['fire'];
    }
////////////
    $sql = "SELECT id, state, flag FROM door WHERE id = ?";
    $stmt = $pdo->prepare($sql);
    $stmt->execute(array($id));

    if ($stmt->rowCount() > 0) {
        $row = $stmt->fetch(PDO::FETCH_ASSOC);
        $myObj->doorstate = $row['state'];
        $myObj->doorflag = $row['flag'];
    }

//////////////
$sql = "SELECT * FROM lcd WHERE id=?";
        $stmt = $pdo->prepare($sql);
        $stmt->execute(array($id));

        if ($stmt->rowCount() > 0) {
            $row = $stmt->fetch(PDO::FETCH_ASSOC);

            $myObj->show = $row['show'];

            $timezone = new DateTimeZone('Asia/Jerusalem');
            $datetime = new DateTime('now', $timezone);

            $myObj->date = $datetime->format('Y-m-d');
            $myObj->time = $datetime->format('H:i');

        }
        ////////////////////////////////////

        $sql = "SELECT id, flag FROM bed_time_command WHERE id = ?";
        $stmt = $pdo->prepare($sql);
        $stmt->execute(array($id));

        if ($stmt->rowCount() > 0) {
            $row = $stmt->fetch(PDO::FETCH_ASSOC);

            $myObj->bedflag = $row['flag'];
        }


    $myJSON = json_encode($myObj);

    echo $myJSON;
    Database::disconnect();
    //........................................ 
}
//---------------------------------------- 
?>
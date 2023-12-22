<?php
require 'database.php';

if (!empty($_POST)) {
    //........................................ keep track POST values
    $id = $_POST['id'];
    $roomID = $_POST['roomID'];
    $timer = $_POST['timer'];
    $table = $_POST['table'];
    $timer_flag = $_POST['timer_flag'];// this flag for esp32 if it is 0 it doesn't read the time, else it reads it and write it 1
    date_default_timezone_set("Asia/Jerusalem");
    $timer_time = date("H:i:s");
    $timer_time = date("H:i:s", strtotime($timer_time) + $timer);// stores the time that the led will toggle in, it is important to show how much time to toggle


    //........................................


    $pdo = Database::connect();
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $sql = "UPDATE $table SET timer = ?, timer_flag = ?, timer_time = ? WHERE id = ? AND roomID = ?";
    $q = $pdo->prepare($sql);
    $q->execute(array($timer, $timer_flag, $timer_time, $id, $roomID));
    



    Database::disconnect();
    //........................................
}
?>
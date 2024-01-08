<?php
require '../database.php';

if (!empty($_POST)) {
    //........................................ keep track POST values
    $id = $_POST['id'];
    $roomID = $_POST['roomID'];
    $timer = $_POST['timer'];
    $table = $_POST['table'];
    date_default_timezone_set("Asia/Jerusalem");
    $timer_time = date("H:i:s");
    $timer_time = date("H:i:s", strtotime($timer_time) + $timer); // stores the time that the led will toggle in, it is important to show how much time to toggle


    //........................................


    $pdo = Database::connect();
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    if (isset($_POST['flag'])) { // when esp sends request here it sends flag to indicate not to update timer_time. we don't care the value of flag, just we need to check its existence.
        $sql = "UPDATE $table SET timer = ? WHERE id = ? AND roomID = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($timer, $id, $roomID));
    } else {
        $sql = "UPDATE $table SET timer = ?, timer_time = ? WHERE id = ? AND roomID = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($timer, $timer_time, $id, $roomID));
    }



    Database::disconnect();
    //........................................
}
?>
<?php
include 'database.php';

if (!empty($_POST)) {

    $id = $_POST['id'];
    $roomID = $_POST['roomID'];

    $myObj = (object) array();   

    //........................................ 
    $pdo = Database::connect();

    $sql = 'SELECT * FROM room WHERE id="' . $id . '" AND roomID="' . $roomID . '"';
    foreach ($pdo->query($sql) as $row) {
        $date = date_create($row['date']);
        $dateFormat = date_format($date, "d-m-Y");

        $myObj->id = $row['id'];
        $myObj->LED = $row['LED'];
        $myObj->roomID = $row['roomID'];
        $myObj->timer = $row['timer'];
        $myObj->timer_flag = $row['timer_flag'];
        $myObj->timer_time = $row['timer_time'];
        $myObj->ls_time = $row['time'];
        $myObj->ls_date = $dateFormat;

        $myJSON = json_encode($myObj);

        echo $myJSON;
    }
    Database::disconnect();
    //........................................ 
}
//---------------------------------------- 
?>
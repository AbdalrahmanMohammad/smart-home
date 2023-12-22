<?php
include 'database.php';

if (!empty($_POST)) {

    $id = $_POST['id'];
    $roomID = $_POST['roomID'];
    $table = $_POST['table'];

    $myObj = (object) array();

    //........................................ 
    $pdo = Database::connect();

    $sql = "SELECT * FROM $table WHERE id=? AND roomID=?";
    $stmt = $pdo->prepare($sql);
    $stmt->execute(array($id, $roomID));

    foreach ($stmt as $row) {
        $date = date_create($row['date']);
        $dateFormat = date_format($date, "d-m-Y");

        $myObj->id = $row['id'];
        $myObj->state = $row['state'];
        $myObj->roomID = $row['roomID'];
        $myObj->timer = $row['timer'];
        $myObj->timer_flag = $row['timer_flag'];
        $myObj->timer_time = $row['timer_time'];
        $myObj->ls_time = $row['time'];
        $myObj->ls_date = $dateFormat;
        if ($table == 'rgb') {
            // Put the rgb attributes

        }

        $myJSON = json_encode($myObj);

        echo $myJSON;
    }
    Database::disconnect();
    //........................................ 
}
//---------------------------------------- 
?>
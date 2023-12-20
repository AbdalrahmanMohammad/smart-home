<?php
include 'database.php';

if (!empty($_POST)) {

    $id = $_POST['id'];

    $myObj = (object) array();   

    //........................................ 
    $pdo = Database::connect();

    $sql = 'SELECT * FROM room WHERE id="' . $id . '"';
    foreach ($pdo->query($sql) as $row) {
        $date = date_create($row['date']);
        $dateFormat = date_format($date, "d-m-Y");

        $myObj->id = $row['id'];
        $myObj->LED = $row['LED'];
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
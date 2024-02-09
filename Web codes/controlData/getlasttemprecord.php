<?php
include '../database.php';
require 'Class.authorization.php';
if (!empty($_POST) && authorization::authorize($_POST['id'], $_POST['password']??null)) {

    $id = $_POST['id'];

    $myObj = (object) array();

    //........................................ 
    $pdo = Database::connect();

    $sql = "SELECT * FROM temp_sensor_records ORDER BY CONCAT(date, ' ', time) DESC LIMIT 1;    ";
    $stmt = $pdo->prepare($sql);
    $stmt->execute();

    if ($stmt->rowCount() > 0) {
        $row = $stmt->fetch(PDO::FETCH_ASSOC);

        $myObj->temperature = $row['temperature'];
        $myObj->humidity = $row['humidity'];
        $myObj->id = $row['id'];

        $myJSON = json_encode($myObj);

        echo $myJSON;
    }

    Database::disconnect();
    //........................................ 
}
//---------------------------------------- 
?>

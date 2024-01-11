<?php
include '../database.php';// this page now is unused but i'll keep it
require 'Class.authorization.php';
if (!empty($_POST) && authorization::authorize($_POST['id'], $_POST['password']??null)) {

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

        $myJSON = json_encode($myObj);

        echo $myJSON;
    }

    Database::disconnect();
    //........................................ 
}
//---------------------------------------- 
?>

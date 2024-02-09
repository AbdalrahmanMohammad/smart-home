<?php
require '../database.php';
require 'Class.authorization.php';
if (!empty($_POST) && authorization::authorize($_POST['id'], $_POST['password']??null)) {
    
    $id = $_POST['id'];
    $fire = $_POST['fire'];

    $pdo = Database::connect();
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $sql = "UPDATE smoke_sensor SET fire = ? WHERE id = ?";
    $q = $pdo->prepare($sql);
    $q->execute(array($fire, $id));

    Database::disconnect();
}
?>

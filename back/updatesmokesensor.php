<?php
require 'database.php';

// Condition to check that POST value is not empty.
if (!empty($_POST)) {
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

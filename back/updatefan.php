<?php
require 'database.php';

if (!empty($_POST)) {
    //........................................ keep track POST values
    $id = $_POST['id'];
    $roomID = $_POST['roomID'];
    $speedup_flag = $_POST['speedup_flag'] ?? null; 
    $speeddown_flag = $_POST['speeddown_flag'] ?? null;
    $speed = $_POST["speed"] ?? null;


    //........................................


    $pdo = Database::connect();
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    if ($speed !== null) { // this is reached only from the esp
        $sql = "UPDATE fan SET speed = ? WHERE id = ? AND roomID = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($speed, $id, $roomID));
    }

    if ($speedup_flag !== null) {
        $sql = "UPDATE fan SET speedup_flag = ? WHERE id = ? AND roomID = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($speedup_flag, $id, $roomID));
    }

    if ($speeddown_flag !== null) {
        $sql = "UPDATE fan SET speeddown_flag = ? WHERE id = ? AND roomID = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($speeddown_flag, $id, $roomID));
    }


    Database::disconnect();
    //........................................
}
?>
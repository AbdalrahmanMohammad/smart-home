<?php
require 'database.php'; // dimup_flag, dimdown_flag, color from web page // brightness from esp32

if (!empty($_POST)) {
    //........................................ keep track POST values
    $id = $_POST['id'];
    $roomID = $_POST['roomID'];
    $dimup_flag = $_POST['dimup_flag'] ?? null; // this means if it is set get its value else put it null
    $dimdown_flag = $_POST['dimdown_flag'] ?? null;
    $undo_flag = $_POST['undo_flag'] ?? null;
    $color_flag = $_POST['color_flag'] ?? null;
    $color = $_POST["color"] ?? null;
    $brightness = $_POST["brightness"] ?? null;


    //........................................


    $pdo = Database::connect();
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    if ($brightness !== null) { // it is from web page
        $sql = "UPDATE rgb SET brightness = ? WHERE id = ? AND roomID = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($brightness, $id, $roomID));
    }
    if ($color !== null) {
        $st="ON";
        $sql = "UPDATE rgb SET color = ?, state = ? WHERE id = ? AND roomID = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($color,$st, $id, $roomID));
    }

    if ($dimup_flag !== null) {
        $sql = "UPDATE rgb SET dimup_flag = ? WHERE id = ? AND roomID = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($dimup_flag, $id, $roomID));
    }

    if ($dimdown_flag !== null) {
        $sql = "UPDATE rgb SET dimdown_flag = ? WHERE id = ? AND roomID = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($dimdown_flag, $id, $roomID));
    }
    if ($undo_flag !== null) {
        $sql = "UPDATE rgb SET undo_flag = ? WHERE id = ? AND roomID = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($undo_flag, $id, $roomID));
    }
    if ($color_flag !== null) {
        $sql = "UPDATE rgb SET color_flag = ? WHERE id = ? AND roomID = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($color_flag, $id, $roomID));
    }


    Database::disconnect();
    //........................................
}
?>
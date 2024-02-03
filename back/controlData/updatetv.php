<?php
require '../database.php';
require 'Class.authorization.php';
if (!empty($_POST) && authorization::authorize($_POST['id'], $_POST['password']??null)) {
    // ........................................ keep track POST values
    $id = $_POST['id'];
    $roomID = $_POST['roomID'];
    $signal_value = $_POST['signal_value'] ?? null;
    // ........................................

    $pdo = Database::connect();
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    if ($signal_value !== null) {
        $sql = ($signal_value == "toggle")
            ? "UPDATE tv SET signal_value = ?, time = NOW(), date = NOW() WHERE id = ? AND roomID = ?"
            : "UPDATE tv SET signal_value = ? WHERE id = ? AND roomID = ?";

        $q = $pdo->prepare($sql);
        $q->execute(array($signal_value, $id, $roomID));
    }

    Database::disconnect();
    // ........................................
}
?>

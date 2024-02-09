<?php
include '../database.php';
require 'Class.authorization.php';

if (!empty($_POST) && authorization::authorize($_POST['id'], $_POST['password'] ?? null)) {
    $id = $_POST['id'];
    $send = $_POST['send'] ?? null;

    date_default_timezone_set('Asia/Jerusalem');


    $pdo = Database::connect();

    if ($send == null) {
        $sql = "SELECT time FROM check_connection WHERE id=?";
        $stmt = $pdo->prepare($sql);
        $stmt->execute(array($id));

        if ($stmt->rowCount() > 0) {
            $row = $stmt->fetch(PDO::FETCH_ASSOC);
            $storedTime = strtotime($row['time']);
            $currentTime = time();

            // Check if the difference is less than three seconds
            $timeDifference = $currentTime - $storedTime;
            $connected = ($timeDifference < 5);
            echo json_encode(array('id' => $id, 'connected' => $connected));

        }
    } else {
        // Update time with current time
        $sql = "UPDATE check_connection SET `time` = NOW() WHERE id = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($id));
    }


    Database::disconnect();
}
?>

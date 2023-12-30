<?php
require 'database.php';

if (!empty($_POST)) {// if it gets state and flag then it updates them, else it will return the value of them
    $id = $_POST['id'];
    $state = $_POST['state'] ?? null;
    $flag = $_POST['flag'] ?? null;

    $myObj = (object) array();


    $pdo = Database::connect();
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    if ($state === null && $flag === null) {
        $sql = "SELECT id, state, flag FROM door WHERE id = ?";
        $stmt = $pdo->prepare($sql);
        $stmt->execute(array($id));

        if ($stmt->rowCount() > 0) {
            $row = $stmt->fetch(PDO::FETCH_ASSOC);

            $myObj->id = $row['id'];
            $myObj->state = $row['state'];
            $myObj->flag = $row['flag'];

            $myJSON = json_encode($myObj);

            echo $myJSON;
        } 
    } else {
        $sql = "UPDATE door SET state = ?, flag = ? WHERE id = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($state, $flag, $id));
    }

    Database::disconnect();
}
?>

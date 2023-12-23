<?php
include 'database.php';

if (!empty($_POST)) {

    $id = $_POST['id'];
    $roomID = $_POST['roomID'];
    $table = $_POST['table'];

    $myObj = (object) array();

    //........................................ 
    $pdo = Database::connect();

    $sql = "SELECT * FROM $table WHERE id=? AND roomID=?";
    $stmt = $pdo->prepare($sql);
    $stmt->execute(array($id, $roomID));

    foreach ($stmt as $row) {
        $date = date_create($row['date']);
        $dateFormat = date_format($date, "d-m-Y");

        if ($table != "tv")// just for led & rgb
            $myObj->state = $row['state'];

        $myObj->id = $row['id'];
        $myObj->roomID = $row['roomID'];
        $myObj->timer = $row['timer'];
        $myObj->timer_time = $row['timer_time'];
        $myObj->ls_time = $row['time'];
        $myObj->ls_date = $dateFormat;
        if ($table == 'rgb') {
            $myObj->color = $row['color'];
            $myObj->dimup_flag = $row['dimup_flag'];
            $myObj->dimdown_flag = $row['dimdown_flag'];
            $myObj->undo_flag = $row['undo_flag'];
            $myObj->color_flag = $row['color_flag'];
            $myObj->brightness = $row['brightness'];
        }
        if ($table == "tv") {
            $myObj->signal_value = $row['signal_value'];
        }

        $myJSON = json_encode($myObj);

        echo $myJSON;
    }
    Database::disconnect();
    //........................................ 
}
//---------------------------------------- 
?>
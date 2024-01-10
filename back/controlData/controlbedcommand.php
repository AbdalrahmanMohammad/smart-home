<?php
require '../database.php';
require 'Class.authorization.php';

if (!empty($_POST) && authorization::authorize($_POST['id'], $_POST['password'] ?? null)) {
    $id = $_POST['id'];
    $flag = $_POST['flag'] ?? null;

    $myObj = (object) array();
    $pdo = Database::connect();
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    if ($flag === null) {
        $sql = "SELECT id, flag FROM bed_time_command WHERE id = ?";
        $stmt = $pdo->prepare($sql);
        $stmt->execute(array($id));

        if ($stmt->rowCount() > 0) {
            $row = $stmt->fetch(PDO::FETCH_ASSOC);

            $myObj->id = $row['id'];
            $myObj->flag = $row['flag'];

            $myJSON = json_encode($myObj);
            echo $myJSON;
        }
    } else {

        $sql = "UPDATE bed_time_command SET flag = ? WHERE id = ?";
        $stmt = $pdo->prepare($sql);
        $stmt->execute(array($flag, $id));

        if ($flag == '0') // it comes from ESP
        {
            // Define the target URL
            $url = 'http://192.168.8.110/GP/back/controlData/updatestate.php';

            $combinations = [
                ['roomID' => 1, 'table' => 'fan'],
                ['roomID' => 1, 'table' => 'rgb'],
                ['roomID' => 2, 'table' => 'led'],
                ['roomID' => 2, 'table' => 'rgb'],
                ['roomID' => 3, 'table' => 'led'],
            ];

            foreach ($combinations as $combination) {
                $postData = [
                    'id' => $_POST['id'],
                    'password' => $_POST['password'],
                    'roomID' => $combination['roomID'],
                    'table' => $combination['table'],
                    'state' => "OFF",
                    'changed_by' => 'bedTime command',
                ];

                $options = [
                    'http' => [
                        'method' => 'POST',
                        'header' => 'Content-type: application/x-www-form-urlencoded',
                        'content' => http_build_query($postData),
                    ],
                ];

                $context = stream_context_create($options);
                $response = file_get_contents($url, false, $context);
            }
        }
    }
    Database::disconnect();
}
?>

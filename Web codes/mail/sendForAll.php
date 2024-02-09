<?php
require '../controlData/Class.authorization.php';
require_once('../Class.data.php');

if (!empty($_POST) && authorization::authorize($_POST['id'], $_POST['password'])) { // password can't be null because just the ESP is what uses this php file
    $query1 = data::getAll();
    while ($row = $query1->fetch()) {
        if ($row['role'] == "admin") {
            $url = 'http://192.168.8.110/GP/back/mail/send.php';

            $postData = [
                'id' => $_POST['id'],
                'password' => $_POST['password'],
                'email' => $row['email']
            ];

            $options = [
                'http' => [
                    'method' => 'POST',
                    'header' => 'Content-type: application/x-www-form-urlencoded',
                    'content' => http_build_query($postData)
                ]
            ];

            $context = stream_context_create($options);
            $response = file_get_contents($url, false, $context);
        }
    }
}

?>
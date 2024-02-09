<?php
include '../database.php';
require 'Class.authorization.php';

if (!empty($_POST) && authorization::authorize($_POST['id'], $_POST['password'] ?? null)) {
    $id = $_POST['id'];
    $password = $_POST['password'];

    $url = 'http://192.168.8.110/GP/back/controlData/getdata.php';

    function makeHttpPostRequest($url, $postData)
    {
        $options = [
            'http' => [
                'method' => 'POST',
                'header' => 'Content-type: application/x-www-form-urlencoded',
                'content' => http_build_query($postData),
            ],
        ];

        $context = stream_context_create($options);
        $response = file_get_contents($url, false, $context);

        if ($response === false) {
            return null;
        }

        return json_decode($response);
    }

    $postData = [
        'id' => $id,
        'password' => $password,
        'roomID' => 1,
        'table' => "rgb"
    ];
    $rgb1Obj = makeHttpPostRequest($url, $postData);

    $postData = [
        'id' => $id,
        'password' => $password,
        'roomID' => 1,
        'table' => "fan"
    ];
    $fan1Obj = makeHttpPostRequest($url, $postData);

    $postData = [
        'id' => $id,
        'password' => $password,
        'roomID' => 2,
        'table' => "rgb"
    ];
    $rgb2Obj = makeHttpPostRequest($url, $postData);

    $postData = [
        'id' => $id,
        'password' => $password,
        'roomID' => 2,
        'table' => "led"
    ];
    $led2Obj = makeHttpPostRequest($url, $postData);

    $postData = [
        'id' => $id,
        'password' => $password,
        'roomID' => 3,
        'table' => "tv"
    ];
    $tv3Obj = makeHttpPostRequest($url, $postData);

    $postData = [
        'id' => $id,
        'password' => $password,
        'roomID' => 3,
        'table' => "led"
    ];
    $led3Obj = makeHttpPostRequest($url, $postData);

    // Organize the data into an associative array
    $responseArray = [
        'rgb1' => $rgb1Obj,
        'fan1' => $fan1Obj,
        'rgb2' => $rgb2Obj,
        'led2' => $led2Obj,
        'tv3' => $tv3Obj,
        'led3' => $led3Obj,
    ];

    // Convert the associative array to JSON format
    $jsonResponse = json_encode($responseArray);

    header('Content-Type: application/json');

    echo $jsonResponse;
}
//----------------------------------------
?>

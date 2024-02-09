<?php
include '../database.php';
require 'Class.authorization.php';
if (!empty($_POST) && authorization::authorize($_POST['id'], $_POST['password']??null)) {

date_default_timezone_set('Asia/Jerusalem'); // Set the time zone to Jerusalem, Palestine

$selectedDate = $_POST['date'] ?? date('Y-m-d'); // Get the date from the POST request, default to current date

$pdo = Database::connect();

$sql = "SELECT * FROM records WHERE date = :selectedDate ORDER BY time";
$stmt = $pdo->prepare($sql);
$stmt->bindParam(':selectedDate', $selectedDate);
$stmt->execute();

$deviceUsage = [];

$allDevices = ['fan-1', 'rgb-1', 'led-2', 'rgb-2', 'led-3', 'socket--']; // these two lines important to return all devices even though if some didn't get on for any time
foreach ($allDevices as $device) {
    $deviceUsage["$device"] = ['start' => null, 'duration' => 0];
}


while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $device = $row['table'];
    $roomID = $row['roomID'];
    $state = $row['state'];
    $timestamp = strtotime($row['time']);

    $primaryKey = "$device-$roomID";

    if ($state == 'ON' && !isset($deviceUsage[$primaryKey]['start'])) {
        $deviceUsage[$primaryKey]['start'] = $timestamp;
    } elseif ($state == 'OFF' && isset($deviceUsage[$primaryKey]['start'])) {
        $deviceUsage[$primaryKey]['duration'] += ($timestamp - $deviceUsage[$primaryKey]['start']);
        unset($deviceUsage[$primaryKey]['start']);
    } elseif ($state == 'OFF' && !isset($deviceUsage[$primaryKey]['start'])) { // it means that the device was already on at 0 O'clock and it was turend off after this
        $deviceUsage[$primaryKey]['duration'] += $timestamp - strtotime("00:00:00");
    }
}

foreach ($deviceUsage as &$usage) {
    if (isset($usage['start'])) {// if the last state was on
        $startTimestamp = $usage['start'];

        if ( $selectedDate == date('Y-m-d')) {
            $usage['duration'] += abs(time() - $startTimestamp);// if it is today
        } else {// if it is in previous day
            $usage['duration'] += strtotime("23:59:59") - $startTimestamp;
        }

        unset($usage['start']);
    }
}

echo json_encode($deviceUsage);

Database::disconnect();
// some cases is didn't cover: -if the device was on all day without toggling it
//                             -if the electricity goes out and the device was on, it will be counted as it was on
}
?>
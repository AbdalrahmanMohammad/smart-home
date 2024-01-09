<?php
include '../database.php';
require 'Class.authorization.php';

if (!empty($_POST) && authorization::authorize($_POST['id'], $_POST['password'] ?? null)) {
    $id = $_POST['id'];
    $selectedDate = $_POST['date'] ?? date('Y-m-d'); // Get the date from the POST request, default to current date

    // Convert date format to match the database date format
    $selectedDate = date('Y-m-d', strtotime($selectedDate));

    $pdo = Database::connect();

    $hourlyData = array_fill(0, 24, ['temperature' => null, 'humidity' => null]);

    try {
        $sql = "SELECT HOUR(time) as hour, AVG(temperature) as avg_temperature, AVG(humidity) as avg_humidity
                FROM temp_sensor_records
                WHERE date = :selectedDate
                GROUP BY hour
                ORDER BY hour";

        $stmt = $pdo->prepare($sql);
        $stmt->bindParam(':selectedDate', $selectedDate);
        $stmt->execute();

        while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
            $hour = $row['hour'];
            $hourlyData[$hour]['temperature'] = round($row['avg_temperature'], 2);
            $hourlyData[$hour]['humidity'] = round($row['avg_humidity'], 2);
        }

        echo json_encode($hourlyData);
    } catch (PDOException $e) {
        // Output any errors for debugging
        echo json_encode(['error' => $e->getMessage()]);
    }

    Database::disconnect();
}
?>

<!DOCTYPE html>
<html lang="en">
<?php
    session_start();
    if ($_SESSION['login'] == false || !(in_array($_SESSION['role'], array('admin')))) { // the second condition is !$_SESSION['role']=="admin"
      header("location: ../index.php?loginError=1");
      exit;
    }
    ?>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Device Usage</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            flex-direction: column;
        }

        #dateInput {
            margin-bottom: 20px;
        }

        #usageChart {
            width: 70%;
            /* Adjust the width as needed */
            max-width: 90%;
            /* Set a maximum width */
            max-height: 90%;
            /* Set a maximum width */
            margin-top: 20px;
        }
    </style>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
</head>

<body>
    <div>
        <label for="dateInput">Select Date:</label>
        <input type="date" id="dateInput" onchange="fetchDeviceUsage()" value="<?php echo date('Y-m-d'); ?>">
    </div>

    <canvas id="usageChart"></canvas>

    <script>
        let usageChart; // Store the chart instance globally

        document.addEventListener('DOMContentLoaded', function () {
            fetchDeviceUsage();
        });

        function fetchDeviceUsage() {
            const xhr = new XMLHttpRequest();
            const dateInput = document.getElementById('dateInput').value;

            xhr.onreadystatechange = function () {
                if (xhr.readyState === 4 && xhr.status === 200) {
                    try {
                        const data = JSON.parse(xhr.responseText);
                        displayDeviceUsageChart(data);
                        console.log(data);
                    } catch (error) {
                        console.error('Error parsing data:', error);
                        // Handle data parsing errors here
                    }
                }
            };

            xhr.open('POST', '../controlData/getdevicesrecords.php', true);
            xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhr.send('id=esp1&date=' + encodeURIComponent(dateInput));
        }


        function displayDeviceUsageChart(data) {
            const labels = [];
            const durations = [];

            for (const deviceKey in data) {
                if (data.hasOwnProperty(deviceKey)) {
                    const [device, roomID] = deviceKey.split('-');
                    const durationInSeconds = data[deviceKey]['duration'];

                    labels.push(`${device}-${roomID}`);
                    durations.push(durationInSeconds);
                }
            }
            if (usageChart) {
                usageChart.destroy(); // Destroy existing chart before creating a new one
            }
            const ctx = document.getElementById('usageChart').getContext('2d');
             usageChart = new Chart(ctx, {
                type: 'bar',
                data: {
                    labels: labels,
                    datasets: [{
                        label: 'Usage Duration (seconds)',
                        data: durations,
                        backgroundColor: 'rgba(75, 192, 192, 0.2)',
                        borderColor: 'rgba(75, 192, 192, 1)',
                        borderWidth: 1
                    }]
                },
                options: {
                    scales: {
                        y: {
                            beginAtZero: true
                        }
                    }
                }
            });
        }
    </script>
</body>

</html>
<!DOCTYPE html>
<html lang="en">
<head>
<?php
		session_start();
		if ($_SESSION['login'] == false or !(in_array($_SESSION['role'], array('admin')))) {
			header("location: ../index.php?loginError=1");
			exit;
		}
		?>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Temperature and Humidity Chart</title>
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

        .chart-container {
            width: 80%;
            margin-top: 20px;
        }

        #dateInput {
            margin-top: 20px;
        }

        #returnButton {
            position: absolute;
            top: 1px;
            left: 10px;
            cursor: pointer;
            font-size: 55px;
            background: none;
            border: none;
            color: #007bff;
        }
        @media (max-width: 768px) {
            .chart-container {
                margin-top: 0;
            }

            #dateInput {
                width: 100%;
                margin-bottom: 10px;
            }
            .chart-container {
            width: 100%; 
            margin-top: 20px;
        }
        }
    </style>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
</head>
<body>
    <div>
        <button id="returnButton" onclick="goBack()">&#8592;</button>
        <input type="date" id="dateInput" onchange="fetchData()" value="<?php echo date('Y-m-d'); ?>">
    </div>

    <div class="chart-container">
        <canvas id="temperatureHumidityChart"></canvas>
    </div>

    <script>
        let temperatureHumidityChart; // Variable to store the chart instance

        // Function to update the chart with new data
        function updateChart(temperatureData, humidityData) {
            const ctx = document.getElementById('temperatureHumidityChart').getContext('2d');

            // Destroy existing chart if it exists
            if (temperatureHumidityChart) {
                temperatureHumidityChart.destroy();
            }

            temperatureHumidityChart = new Chart(ctx, {
                type: 'line',
                data: {
                    labels: Array.from({ length: 24 }, (_, i) => `${i} AM`),
                    datasets: [
                        {
                            label: 'Temperature (°C)',
                            data: temperatureData,
                            borderColor: 'rgb(75, 192, 192)',
                            borderWidth: 2,
                            fill: false,
                        },
                        {
                            label: 'Humidity (%)',
                            data: humidityData,
                            borderColor: 'rgb(255, 99, 132)',
                            borderWidth: 2,
                            fill: false,
                        }
                    ]
                },
                options: {
                    scales: {
                        y: {
                            beginAtZero: true,
                        }
                    }
                }
            });
        }

        function fetchData() {
            const xhr = new XMLHttpRequest();
            const dateInput = document.getElementById('dateInput').value;

            xhr.onreadystatechange = function () {
                if (xhr.readyState === 4 && xhr.status === 200) {
                    const data = JSON.parse(xhr.responseText);

                    const temperatureData = data.map(item => item.temperature);
                    const humidityData = data.map(item => item.humidity);

                    updateChart(temperatureData, humidityData);
                }
            };

            xhr.open('POST', '../controlData/getaveragetemprecordss.php', true);
            xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
            xhr.send('id=esp1&date=' + encodeURIComponent(dateInput)); 
        }

        function goBack() {
            window.history.back();
        }

        document.addEventListener('DOMContentLoaded', function () {
            fetchData(); 
        });
    </script>
</body>
</html>

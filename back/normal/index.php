<!DOCTYPE html>
<html>

<head>
	<title>Normal User</title>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
	<style>
		body {
			background: linear-gradient(120deg, #2980b9, #8e44ad);
			min-height: 100vh;
			margin: 0;
			display: flex;
			flex-direction: column;
			align-items: center;
			color: white;
		}

		.container {
			text-align: center;
			padding: 20px;
			max-width: 80%;
		}

		h1 {
			font-size: 2.5em;
			font-weight: bold;
			margin-bottom: 20px;
		}

		#info {
			font-size: 1.2em;
			margin-bottom: 20px;
		}

		a {
			color: white;
			text-decoration: none;
			font-size: 1em;
			display: block;
			margin-bottom: 10px;
			padding: 10px;
			border-radius: 5px;
			width: 100%;
		}

		.btn {
			margin: 0 auto;
			padding: 10px;
			border-radius: 28px;
			display: block;
		}

		.btn3 {
			background-color: #2ecc71;
			/* Green */
		}

		.btn4 {
			background-color: #e74c3c;
			/* Red */
		}

		/* Improve button style */
		.custom-button:hover {
			background-color: #2980b9;
		}

		/* Media query for smaller screens (phones) */
		@media (max-width: 576px) {
			a {
				width: 100%;
			}
		}

		/* Media query for larger screens (PCs) */
		@media (min-width: 992px) {
			.btn {
				width: 30%;
				display: block;
				margin-bottom: 10px;
			}

			/* Different background colors for buttons */
			.btn3 {
				width: 23%;
			}

			.btn4 {
				width: 18%;
			}
		}
	</style>
</head>

<body>
	<div class="container mt-5">
		<?php
		session_start();
		if ($_SESSION['login'] == false or (strpos($_SESSION['role'], 'normal') === false)) {
			header("location: ../index.php?loginError=1");
			exit;
		}
		?>

		<h1>This is Normal user page</h1>
		<div id="info">
			<div>Welcome:
				<?php echo $_SESSION['userName'] ?>
			</div>
			<div id="clock"></div>
			<div>Temperature: <span id="temperature">25°C</span>, Humidity: <span id="humidity">50%</span></div>
		</div>
		<?php
		if ((strpos($_SESSION['role'], '1') == true)) {
			echo '<a href="../rooms/room1.php" class="btn btn-info custom-button btn3">Room 1</a>';
		}
		if ((strpos($_SESSION['role'], '2') == true)) {
			echo '<a href="../rooms/room2.php" class="btn btn-info custom-button btn3">Room 2</a>';
		}
		if ((strpos($_SESSION['role'], '3') == true)) {
			echo '<a href="../rooms/room3.php" class="btn btn-info custom-button btn3">Room 3</a>';
		}
		?>

		<a href="../logout.php" class="btn btn-danger custom-button btn4">Logout</a>
	</div>

	<script src="https://code.jquery.com/jquery-3.2.1.slim.min.js"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>
	<script>
		// Update temperature and humidity (placeholders in this example)
		function updateTempHumidity() {
			document.getElementById('temperature').innerText = '25°C'; // Placeholder, replace with real data
			document.getElementById('humidity').innerText = "10%";
		}
	</script>
</body>

</html>
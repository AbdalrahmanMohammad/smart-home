<!DOCTYPE html
	PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>
	<style>
		body {
			background: linear-gradient(120deg, #2980b9, #8e44ad);
			min-height: 100vh;
			margin: 0;
			display: flex;
			flex-direction: column;
			color: white;
		}

		#container {
			max-width: 100%;
			padding: 10px;
			background: linear-gradient(120deg, #2980b9, #8e44ad);
			border-radius: 10px;
			box-shadow: 0 5px 15px rgba(0, 0, 0, 0.3);
			transition: background 0.3s, box-shadow 0.3s;
			margin: 10px auto;
		}

		#container:hover {
			background: linear-gradient(120deg, #3498db, #9b59b6);
			box-shadow: 0 10px 20px rgba(0, 0, 0, 0.5);
		}

		.container table {
			width: 100%;
			margin-bottom: 20px;
			color: white;
		}

		.container table th,
		.container table td {
			border: none;
			padding: 12px;
		}

		.container table th {
			background-color: #2c3e50;
		}

		.container table tr:hover {
			background-color: rgba(255, 255, 255, 0.1);
		}

		.container table .btn {
			padding: 6px 12px;
			font-size: 12px;
		}

		.back-button {
			background-color: #3498db;
			border: none;
			transition: background-color 0.3s;
		}

		.back-button:hover {
			background-color: #2980b9;
		}
	</style>
</head>

<body>
	<div id="container">
		<h1 class="text-center">Users Information</h1>
		<?php
		session_start();
		if ($_SESSION['login'] == false or !(in_array($_SESSION['role'], array('admin')))) {
			header("location: ../index.php?loginError=1");
			exit;
		}
		?>
		<?php
		require_once('../Class.data.php');
		if ($_SERVER['REQUEST_METHOD'] == 'POST') {
			data::delete($_POST['name']);
		}
		$query1 = data::getAll();
		echo "<div class='table-responsive'>";
		echo "<table class='table table-hover'>";
		echo "<thead><tr><th>Name</th><th>Email</th><th>Password</th><th>Role</th><th>Rooms</th><th>Actions</th><th>Actions</th></tr></thead>";
		while ($row = $query1->fetch()) {
			$role= preg_replace("/[^a-zA-Z]/", "", $row['role']);// extract the role wheather is admin or normal
			$rooms=preg_replace("/[^1-9]/", "", $row['role']);// extracts allowed rooms for normal
			$rooms = implode(',', str_split($rooms));// split between rooms numbers with a ,
			$rooms = ($rooms==""&&$role=="normal")?"nothing": $rooms;// in case it is normal and has access to no rooms
			$rooms = ($rooms==""&&$role=="admin")?"all rooms": $rooms;// in case he is an admin
			echo "<tr><td>{$row['name']}</td><td>{$row['email']}</td><td>***</td><td>" .$role. "</td><td>". $rooms."</td>";
			echo "<td>";
			?>
			<form action="" method="post" onsubmit="return confirm('Are you sure to delete?')">
				<input type="hidden" name='name' value="<?php echo $row['name']; ?>" />
				<button type="submit" class="btn btn-danger btn-sm">Delete</button>
			</form>
			<?php
			echo "</td><td>";
			?>
			<form action="edit.php" method="post">
				<input type="hidden" name='name' value="<?php echo $row['name']; ?>" />
				<button type="submit" class="btn btn-warning btn-sm">Edit</button>
			</form>
			<?php
			echo "</td></tr>";
		}
		echo "</table>";
		echo "</div>";
		?>
		<div class="back-button">
			<a href="index.php" class="btn btn-light btn-block mt-2 back-button">Back</a>
		</div>
	</div>
</body>

</html>
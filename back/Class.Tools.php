<?php
require_once("database.php");

class Tools
{
	static function cleanData($data)
	{
		$data=trim($data);
		$data=stripslashes($data);
		$data=htmlspecialchars($data);
		return $data;
	}
	
	static function printSuccess($message)
	{
		echo "<div class='alert alert-success alert-dismissable'>";
		echo "<a  class='close' data-dismiss='alert' aria-label='close'>&times;</a>";
		echo "<strong>Success!</strong>$message</div>";
	}
	
	static function printError($message)
	{
		echo "<div class='alert alert-danger alert-dismissable'>";
		echo "<a  class='close' data-dismiss='alert' aria-label='close'>&times;</a>";
		echo "<strong>ERROR!</strong>$message</div>";
	}
	
}
?>
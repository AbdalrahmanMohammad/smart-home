<?php

require_once("Class.Tools.php");

class data
{
	static function addNew($name, $email, $password, $role)
	{
		try {
			$name = Tools::cleanData($name);
			$email = Tools::cleanData($email);
			$password = Tools::cleanData($password);
			$role = Tools::cleanData($role);
			$password = password_hash($password, PASSWORD_DEFAULT);
	
			$pdo = Database::connect();
			$query = $pdo->prepare("insert into user (name,email,password,role) values(?,?,?,?)");
			$test = $query->execute(array($name, $email, $password, $role));
			Database::disconnect();
			return $test;
		} catch (PDOException $e) {
			return $e->getMessage(); 
		}
	}
	

	static function delete($name)
	{
		$name = Tools::cleanData($name);

		$pdo = Database::connect();
		$sql = "delete from user where name=?";
		$Dquery = $pdo->prepare($sql);
		$Dquery->execute(array($name));
		Database::disconnect();
	}

	static function getAll() // gets everything other than password
	{
		$pdo = Database::connect();
		$query = $pdo->prepare("select name, email, role from user");
		$query->execute();
		Database::disconnect();
		return $query;
	}

	static function getallinfo($name)
	{
		$pdo = Database::connect();
		$query = $pdo->prepare("select name, email, role from user where name=?");
		$query->execute(array($name));
		Database::disconnect();
		return $query;
	}
	static function updateuser($name, $email, $password, $role)
	{
		$email = Tools::cleanData($email);
		$name = Tools::cleanData($name);
		$role = Tools::cleanData($role);

		$pdo = Database::connect();

		// Build the SQL query based on whether the password is provided or not
		if (!empty($password)) {
			$passwordHash = password_hash($password, PASSWORD_DEFAULT);
			$query = $pdo->prepare("UPDATE user SET email=?, password=?, role=? WHERE name=?");
			 $query->execute(array($email, $passwordHash, $role, $name));
		} else {
			$query = $pdo->prepare("UPDATE user SET email=?, role=? WHERE name=?");
			 $query->execute(array($email, $role, $name));
		}
		Database::disconnect();
		return $query;
	}


}

?>
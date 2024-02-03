<?php
require_once("../Class.Tools.php");
require_once '../database.php';

class authorization
{
    static function authorize($userName, $password)
    {// if i get password then it is the microcontroller and it has accessability to everything
        // if password is null then it is a user and he must have a session
        $userName = Tools::cleanData($userName);
        $password = Tools::cleanData($password);
        if ($password == null) {
            session_start();
            if ($_SESSION['login'] == false)
                return false;
            return true;
        }

        $pdo = Database::connect();
        $sql = "SELECT * FROM authorization WHERE id = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($userName));

        if ($q->rowCount() > 0) {
            $row = $q->fetch(PDO::FETCH_ASSOC);

            if (password_verify($password, $row['password'])) { // password verify gets the hash of $password
                return true;
            } else {
                return false;
            }
        }
        Database::disconnect();
        return false; // in case a problem with accessing Data base(prevent the suer from access)
    }
}
?>
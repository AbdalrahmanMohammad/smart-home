<?php
require_once("Class.Tools.php");

class login
{
    static function checkIn($userName, $password)
    {
        session_start();

        $userName = Tools::cleanData($userName);
        $password = Tools::cleanData($password);

        $pdo = Database::connect();
        $sql = "SELECT * FROM user WHERE name = ?";
        $q = $pdo->prepare($sql);
        $q->execute(array($userName));

        if ($q->rowCount() > 0) {
            $row = $q->fetch(PDO::FETCH_ASSOC);

            if (password_verify($password, $row['password'])) { // password verify gets the hash of $password
                $_SESSION['login'] = true;
                $_SESSION['userName'] = $row['name'];
                $_SESSION['role'] = $row['role'];

                Database::disconnect();

                if (strpos($_SESSION['role'], 'normal') !== false) {
                    header("Location: normal/");
                } elseif ($_SESSION['role'] == "admin") {
                    header("Location: admin/");
                } else {
                    header("Location: index.php?loginError=1");
                }
            } else {
                header("Location: index.php?loginError=1");
            }
        } else {
            header("Location: index.php?loginError=1");
        }
    }
}
?>

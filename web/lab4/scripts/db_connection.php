<?php
function getDbConnection() {
    $dsn = 'mysql:host=localhost;charset=utf8mb4';
    $username = 'root';
    $password = '';

    try {
        $pdo = new PDO($dsn, $username, $password);
        $pdo->exec("USE ecuador_cities"); // Явное указание БД
        return $pdo;
    } catch (PDOException $e) {
        die("Connection failed: " . $e->getMessage());
    }
}
?>

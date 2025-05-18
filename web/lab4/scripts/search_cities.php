<?php
header('Content-Type: application/json');

require_once __DIR__ . '/db_connection.php';

try {
    $pdo = getDbConnection();


    if (isset($_GET['get_all'])) {
        $stmt = $pdo->query("SELECT name FROM cities ORDER BY name ASC");
        $cities = $stmt->fetchAll(PDO::FETCH_COLUMN, 0);
        echo json_encode($cities);
        exit;
    }


    $query = isset($_GET['query']) ? trim($_GET['query']) : '';

    $stmt = $pdo->prepare("SELECT name FROM cities WHERE name LIKE :query LIMIT 5");
    $stmt->execute(['query' => $query . '%']);
    $cities = $stmt->fetchAll(PDO::FETCH_COLUMN);

    echo json_encode($cities ?: [], JSON_UNESCAPED_UNICODE);
} catch (PDOException $e) {
    echo json_encode(['error' => $e->getMessage()], JSON_UNESCAPED_UNICODE);
}
?>

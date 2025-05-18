<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <title>Справочник городов Эквадора</title>
    <link rel="stylesheet" href="styles/main.css">
</head>
<body>
    <div class="container">
        <h1>Справочник городов Эквадора</h1>

        <form method="GET">
            <input type="text" id="city-input" name="city" placeholder="Введите город" autocomplete="off">
            <button type="submit" name="action" value="search">Найти</button>
            <button type="submit"name="action" value="show_all">Показать все города</button>
            <div id="autocomplete-list"></div>
        </form>

        <div id="city-result">
            <?php
            require_once 'scripts/db_connection.php';


            if (isset($_GET['action'])) {
                if ($_GET['action'] === 'search' && isset($_GET['city'])) {
                    $searchCity = trim($_GET['city']);
                    echo "<h2>Результаты поиска: " . htmlspecialchars($searchCity) . "</h2>";

                    try {
                        $pdo = getDbConnection();
                        $stmt = $pdo->prepare("SELECT * FROM cities WHERE name = :name");
                        $stmt->execute(['name' => $searchCity]);
                        $city = $stmt->fetch(PDO::FETCH_ASSOC);

                        if ($city) {
                            echo "<div class='city-info'>";
                            echo "<h3>" . htmlspecialchars($city['name']) . "</h3>";
                            echo "<p><strong>Население:</strong> " . htmlspecialchars($city['population']) . "</p>";
                            echo "<p><strong>Регион:</strong> " . htmlspecialchars($city['region']) . "</p>";
                            echo "<p><strong>Достопримечательности:</strong> " . htmlspecialchars($city['attractions']) . "</p>";
                            echo "<p><strong>Описание:</strong> " . htmlspecialchars($city['description']) . "</p>";
                            echo "</div>";
                            } else {
                                echo "<p>Город не найден. Попробуйте: Кито, Гуаякиль, Куэнка, Амбато, Манта.</p>";
                            }
                    } catch (PDOException $e) {
                        echo "<p class='error'>Ошибка запроса: " . $e->getMessage() . "</p>";
                    }
                } elseif ($_GET['action'] === 'show_all') {
                    try {
                        $pdo = getDbConnection();
                        $stmt = $pdo->query("SELECT * FROM cities ORDER BY name ASC");
                        $cities = $stmt->fetchAll();

                        if ($cities) {
                            echo "<h2>Все города (по алфавиту)</h2>";
                            echo "<div class='cities-list'>";
                            foreach ($cities as $city) {
                                echo "<div class='city-info'>";
                                echo "<h3>" . htmlspecialchars($city['name']) . "</h3>";
                                echo "<p><strong>Население:</strong> " . htmlspecialchars($city['population']) . "</p>";
                                echo "<p><strong>Регион:</strong> " . htmlspecialchars($city['region']) . "</p>";
                                echo "<p><strong>Достопримечательности:</strong> " . htmlspecialchars($city['attractions']) . "</p>";
                                echo "<p><strong>Описание:</strong> " . htmlspecialchars($city['description']) . "</p>";
                                echo "</div>";
                            }
                            echo "</div>";
                        }
                        else {
                            echo "<p>Нет данных о городах</p>";
                        }
                    } catch (PDOException $e) {
                        echo "<p class='error'>Ошибка запроса: " . $e->getMessage() . "</p>";
                    }
                }
            }
            ?>
        </div>
    </div>

    <script src="scripts/main.js"></script>
</body>
</html>

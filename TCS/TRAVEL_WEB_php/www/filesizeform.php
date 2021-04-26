<?php
include_once $_SERVER['DOCUMENT_ROOT'] . './scriptphp/filesize.php';
include_once $_SERVER['DOCUMENT_ROOT'] . './scriptphp/parser.php';
include_once $_SERVER['DOCUMENT_ROOT'] . './scriptphp/phpQuery/phpQuery.php';

?>
<!DOCTYPE html>
<html lang="ru">
<head>
</head>
<body>
<section class="section"> 
<div >
        <h1>Подсчёт размера файла</h1>
        <form action="" method="GET">
            <label for="">Введите путь</label>
            <input type="text" value="<?= $_GET['path'] ?? '' ?>" name="path" placeholder="/от корня...">
            <input type="submit">
        </form>
		<div>
            <span>Результат: </span>
            <?= !empty($_GET) ? getRes($_GET['path'])  : '' ?>
        </div>
</div>
</section>
<section class = "section">
<div>
    <span> Текст с сайта</span>
   <? $obj = new Parser();
    $obj->parsHtml() ?>
</div>
</section>
</body>
</html>
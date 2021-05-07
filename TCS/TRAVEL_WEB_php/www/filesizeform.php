<?php
include_once $_SERVER['DOCUMENT_ROOT'] . './scriptphp/filesize.php';
include_once $_SERVER['DOCUMENT_ROOT'] . './scriptphp/phpQuery/phpQuery.php';
include_once $_SERVER['DOCUMENT_ROOT'] . './scriptphp/watermark.php';


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

    <span> Фотография с Watermark</span>
    <form enctype="multipart/form-data" action="filesizeform.php" method="post">
			Выберите файл: <input name="uploadedFile" type="file" />
			<input type="submit" name = "uploadBtn" value="Загрузить" />
		</form>
<?php
 require('upload.php');
 ?>      
</section>

</body>
</html>
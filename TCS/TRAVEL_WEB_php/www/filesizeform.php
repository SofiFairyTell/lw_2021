<?php
include_once $_SERVER['DOCUMENT_ROOT'] . './scriptphp/filesize.php';
include_once $_SERVER['DOCUMENT_ROOT'] . './scriptphp/parser.php';
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
<div>
    <span> Текст с сайта</span>
   <? $obj = new Parser();
    // $obj->parsHtml();
    // $obj->statParser();
    $watermark = new Watermark();
    $img = imagecreatefromjpeg('./img/photo3.jpg');
    $image = $watermark->add_watermark($img2,'travelblog.ru','erasbd.ttf');
 
    //выводим изображение
    imageJPEG($image);
    //освобождаем память
    imagedestroy($image);
    imagedestroy($img2);
    ?>
</div>
</section>

<section class = "section">
<form enctype="multipart/form-data" action="05_upload.php" method="post">
			Выберите файл: <input name="userfile" type="file" />
			<input type="submit" value="Загрузить" />
		</form>
</section>

</body>
</html>
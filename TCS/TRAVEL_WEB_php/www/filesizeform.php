<?php
$title_page = 'Подсчет размера файла';
 require('header.php');
?>
<section class="section_hack">
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
    <span> <h1> Фотография с Watermark </h1></span>
    <form enctype="multipart/form-data" action="filesizeform.php" method="post">
			Выберите файл: <input name="uploadedFile" type="file" />
			<input type="submit" name = "uploadBtn" value="Загрузить" />
            <input type="submit" name = "dowlandBtn" value="Скачать" />
		</form>
		<?php 
		    require('./scriptphp/upload.php');	
		?>
</section> <!--section-hack-->

<?php 
require('script.php');
require('footer.php');
?>
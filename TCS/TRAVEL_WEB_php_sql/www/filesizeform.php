<?php
$title_page = 'Подсчет размера файла';
 require('header.php');
?>
<section class="section_hack">
<div class="contain">
        
        <form action="" method="GET" class="form-contain">
            <h1>Подсчёт размера файла</h1>
			<label for="">Введите путь</label>
            <input type="text" value="<?= $_GET['path'] ?? '' ?>" name="path" placeholder="/от корня...">
            <input type="submit" class="btn">
        	<div>
				<span>Результат: </span>
					<?= !empty($_GET) ? getRes($_GET['path'])  : '' ?>
			</div>
		
		</form>

    
    <form enctype="multipart/form-data" class="form-contain" action="filesizeform.php" method="post">
			<span> <h1> Фотография с Watermark </h1></span>
					<input class="btn" type="file" id="uploadedFile" size="50"/> 
			<hr>
			<input type="submit" name = "uploadBtn" class="btn" value="Загрузить" />
            <input type="submit" name = "dowlandBtn" class="btn" value="Скачать" />
			<span></span>
			<hr>
			<button class="btn">
			<?php 
			require('./scriptphp/upload.php');	
			?>
			</button>

		</form>

</div>

</section> <!--section-hack-->

<?php 
require('script.php');
require('footer.php');
?>
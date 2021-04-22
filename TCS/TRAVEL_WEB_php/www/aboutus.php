<!DOCTYPE html>
<html lang="ru">
<head>
	<title>О нас</title>
	    <link rel="stylesheet" type="text/css" href="css/travelstyle.css">
</head>
<!-- Обращение к файлу с шапкой -->
<?php
 require('header.php');
?>

<section class="section"> 

<div class="wrapper">
	<input type="radio" name="point" id="slide1" checked>
	<input type="radio" name="point" id="slide2">
	<input type="radio" name="point" id="slide3">
	<input type="radio" name="point" id="slide4">
	<input type="radio" name="point" id="slide5">
	<div class="slider">
		<div class="slides slide1">
			<div class="photo_txt">
				Путешествие это всегда приятное дело, если есть компания. 
				<br>Мы команда исследователей,<br>фотографов <br>и просто хороших людей. 
			</div>
		</div>
		<div class="slides slide2"></div>
		<div class="slides slide3">
			<div class="photo_txt">
				Наше кредо: 
				<br>Видеть необычное в обычном. 
			</div>
		</div>
	</div>	<!--slider-->
	<div class="controls">
		<label for="slide1"></label>
		<label for="slide2"></label>
		<label for="slide3"></label>
	</div> <!--controls-->
</div> <!--wrapper-->
</section>
<script>
	document.addEventListener('DOMContentLoaded', function () {
	document.body.classList.add('loaded_hiding');
	window.setTimeout(function () {
		document.body.classList.add('loaded');
		document.body.classList.remove('loaded_hiding');
	}, 2000);
	});
</script>
</body>
</html>
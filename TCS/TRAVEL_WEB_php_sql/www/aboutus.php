<!-- Обращение к файлу с шапкой -->
<?php
$title_page = 'О нас';
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
	<?php			
				$result = getSliderIMG("sld");
				$row = mysqli_fetch_assoc($result);		
	?>	
		<div class="slides slide1">
			<div class="photo_txt">

				<!-- Путешествие это всегда приятное дело, если есть компания. 
				<br>Мы команда исследователей,<br>фотографов <br>и просто хороших людей.  -->
				<?= $row['img_paragraph']?>
			</div>
		</div>
		<div class="slides slide2">

		</div>
		<div class="slides slide3">
			<div class="photo_txt">
				Наше кредо: 
				<br>Видеть необычное в обычном. 
			</div>
		</div>

		<?php
			$path2 = $row['img_path'];
			$path = "../img/photo2.jpg";
			echo "<script>	$('.slide1').css('background-image','url($path2)');	</script>";
		?>
	</div>	<!--slider-->
	<div class="controls">
		<label for="slide1"></label>
		<label for="slide2"></label>
		<label for="slide3"></label>
	</div> <!--controls-->
</div> <!--wrapper-->
</section>

<?php
 require('script.php');
 require('footer.php');
 ?>
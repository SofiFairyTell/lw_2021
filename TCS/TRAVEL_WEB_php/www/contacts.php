<!DOCTYPE html>
<html lang="ru">
<head>
	<title>Контакты</title>
	  <link rel="stylesheet" type="text/css" href="css/travelstyle.css">
</head>
<?php
 require('header.php');
?>
	<section class="section" >
		<div class="contain">
				<div class="section_header">
					<h2 class="section_title">Контакты & ссылки & координаты</h3>
					<div class="section_text">
						<p>По юридическим спорам, вопросам cотрудничества и просто посмотреть<br>Вы можете по указанным контактам:</p>
					</div><!--section_text-->
				</div> <!--section_header-->	
			<div class="contact_main">
				<div class="contact_item">
					<div class="accordion">
						<div class = "accordion_item" >
							   <div class="collapse-content">
		      						<div class="collapse" id="network">
		      							<div class="accordion_header">
		      								<img class="accordeon_icon" src="img/icon.png">
		      								<h3><a class="contact_header" href="#network"><i class="fab fa-contact"></i> Наши социальные сети </a></h3>
		      							</div><!--accordeon_header-->
		       							<div class="content">
				          					<div class="inner-content">
				          						<h3 >Можно посмотреть наши путевые заметки здесь:</h3>
				          						<ol class="rounded">
												  <li><a href="#">Instagram</a></li>
												  <li><a href="#">YouTube</a></li>
												  <li><a href="#">Vk </a></li>
												</ol><!--список-->
				          					</div><!--inner-content-->
			        					</div> <!--content-->
		      						</div><!--collapse-->
							      	<div class="collapse" id="official">
							      		<div class="accordion_header">
		      								<img class="accordeon_icon" src="img/icon.png">
		      								 <a class="official" href="#official"><i class="fab fa-official"></i>Для юридических лиц и СМИ</a>
		      							</div><!--accordeon_header-->						       
							        	<div class="content">
							          		<div class="inner-content">
							            		<h3>Телефон и email</h3>
												<div class="table-wrapper">
												    <table class="fl-table">
												        <thead>
													        <tr>
													        	<th>Ответственый</th>
													            <th colspan="2">Телефоны</th>
													            <th>Почты</th>
													        </tr>
												        </thead> <!--thead-->
												        <tbody>
												        <tr>
												            <td>Sofi Fairy Tell</td>
												            <td>+99999999</td>
												            <td>+998999</td>
												            <td>fairytellsblog@gmail.com</td>
												        <tr>
												            <td>Digital Assintem</td>
												            <td>+9999909</td>
												            <td>+99909</td>
												             <td>Digital@gmail.com</td>
												        </tr>
												        </tbody> <!--tbody-->
												    </table><!--fl-table-->
												</div> <!--table-wrapper-->
							          		</div><!--inner-content-->
							        	</div><!--content-->
							      	</div>collapse
							    </div> <!--collapse-content-->
						</div><!--accordion_item-->
					</div><!--accordion-->
				</div><!--contact_item-->
			</div><!--contact_main-->
		</div><!--contain-->
    </section><!--section-->	

	<button class="open-button" onclick="openForm()">Отправить сообщение</button>

	<!-- <div class="form-popup" id="myForm">
	  <form action="../action_page.php" class="form-container">
		<h1>Связаться</h1>
	
		<label for="email"><b>Ваше имя</b></label>

		<input type="text" placeholder="Ваша имя" id="name" >

		<label for="email"><b>Почта</b></label>

		<input type="text" placeholder="Ваша почта" id="email" >
	
		<label for="psw"><b>Сообщение</b></label>
		<textarea class="input2" placeholder="Ваше сообщение" id="msg" oninput="getCount()" ></textarea>

		<div class="under">
			<p class="counter"><span id="count"></span> /10 знаков</p>
		</div>

		<button type="submit" class="btn" onclick="">Отправить</button>
		<button type="button" class="btn cancel" onclick="closeForm()">Закрыть</button>
	  </form>
	</div> -->



<?php
 require('form.php');
 require('script.php');
?>

</body>
</html>

<?php 
$name = checkRegularName();
$email = checkRegularEmail();
$message = checkTextBox();
?> 



<!-- 
//require('header.php');
//require('contacts.php'); -->
<?php
if (isset($_GET['message']) && $_GET['message'] == 'ok')  // если был редирект с сообщением OK
	echo '<script> alert("Корректное имя!")</script>';
?>

<div class="form-popup" id="myForm">
	  <form action = "<?= $_SERVER['PHP_SELF'] ?>"  class="form-container" method = "post">
		<h1>Связаться</h1>

        <label class="<?= $name ? 'error' : '' ?>" for="name"> <?= $name ? "Только символы кириллицы!" : 'Имя' ?></label>

		<input type="text" id="name"  
            value="<?= !empty($_POST['name']) ? $_POST['name'] : '' ?>" placeholder ="Ваша имя" >

        <label class="<?= $email ? 'error' : '' ?>" for="email"><?= $email ? 'Формат email: jjjjj.dfdf2011@yandex.ru' : 'email' ?></label>
		

	    <input type="text" id="email" name="email" value="<?= !empty($_POST['email']) ? $_POST['email'] : '' ?>" 
        placeholder="Ваша почта" maxlength="40" type="text">

        <label class="<?= $message ? 'error' : '' ?>"> <?= $message ? 'Минимальная длина сообщения 30 символов!' : 'Введите сообщение' ?></label>

		<!-- <textarea class="input2" placeholder="Ваше сообщение" id="msg" oninput="getCount()" ></textarea> -->
        <textarea class="input2" placeholder="Ваше сообщение" id='msg' oninput="getCount()" name="message"><?= !empty($_POST['message']) ? $_POST['message'] : '' ?></textarea>
		
        <div class="under">
			<p class="counter"><span id="count"></span> /30 знаков</p>
		</div>

		<button type="submit" class="btn">Отправить</button>
		<button type="button" class="btn cancel" onclick="closeForm()">Закрыть</button>
	  </form>
</div>

<?php
 require('script.php'); 
 ?>

 </body>
</html>
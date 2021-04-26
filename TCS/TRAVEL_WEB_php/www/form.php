<?php 
$name = checkRegularName();
$email = checkRegularEmail();
$message = checkTextBox();
?> 


<?php
if (!empty($_GET)) 
{
    if($_GET['ok']==="ok") 
    {
    echo '<div class = "form-success"> Форма успешно отправлена!</div>'
    echo '<script>alert("Форма успешно отправлена!")</script>';
}}
?>

<div class="form-popup" id="myForm">
	  <form action="./contacts.php" class="form-container" method = "post">
		<h1>Связаться</h1>

        <label class="<?= $name ? 'error' : '' ?>" for="name"> <?= $name ? "Только символы кириллицы!" : 'Имя' ?></label>

		<input type="text"id="name"  
            value="<?= !empty($_POST['name']) ? $_POST['name'] : '' ?>" placeholder ="Ваша имя" >

        <label class="<?= $email ? 'error' : '' ?>" for="email"><?= $email ? 'Формат email: jjjjj.dfdf2011@yandex.ru' : 'email' ?></label>
		

	    <input type="text" id="email" name="email" value="<?= !empty($_POST['email']) ? $_POST['email'] : '' ?>" 
        placeholder="Ваша почта" maxlength="40" type="text">

        <label class="<?= $message ? 'error' : '' ?>"> <?= $message ? 'Минимальная длина сообщения 30 символов!' : 'Введите сообщение' ?></label>

		<!-- <textarea class="input2" placeholder="Ваше сообщение" id="msg" oninput="getCount()" ></textarea> -->
        <textarea class="input2" placeholder="Ваше сообщение" id='msg' oninput="getCount()" name="message"><?= !empty($_POST['message']) ? $_POST['message'] : '' ?></textarea>
		
        <div class="under">
			<p class="counter"><span id="count"></span> /10 знаков</p>
		</div>

		<button type="submit" class="btn">Отправить</button>
		<button type="button" class="btn cancel" onclick="closeForm()">Закрыть</button>
	  </form>
</div>
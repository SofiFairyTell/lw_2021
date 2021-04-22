<?php
if (!empty($_GET)) {
    if($_GET['ok']==="ok") {?>
    <!-- <div class="form-success">Форма успешно отправлена!</div>  -->
    alert('Форма успешно отправлена!');
    <?php
}}
?>


<div class="form-popup" id="myForm">
	  <form action="contacts.php" class="form-container" method = "post">
		<h1>Связаться</h1>

        <label class="<?= $name ? 'error' : '' ?>" for="name"><?= $name ? "Только символы кириллицы!" : 'Имя' ?></label>

		<input type="text" placeholder="Ваша имя" id="name" >

		<!-- <label for="email"><b>Почта</b></label> -->
        <label class="<?= $email ? 'error' : '' ?>" for="email"><?= $email ? 'Формат email: jjjjj.dfdf2011@yandex.ru' : 'email' ?></label>
		
        <!-- <input type="text" placeholder="Ваша почта" id="email" > -->
	    <input type="text" id="email" name="email" value="<?= !empty($_POST['email']) ? $_POST['email'] : '' ?>" placeholder="Ваша почта" maxlength="40" type="text">

        <label class="<?= $message ? 'error' : '' ?>"> <?= $message ? 'Минимальная длина сообщения 30 символов!' : 'Введите сообщение' ?></label>

		<!-- <label for="psw"><b>Сообщение</b></label> -->
		<!-- <textarea class="input2" placeholder="Ваше сообщение" id="msg" oninput="getCount()" ></textarea> -->
        <textarea class="input2" id='msg' oninput="getCount()" name="message"><?= !empty($_POST['message']) ? $_POST['message'] : '' ?></textarea>
		
        <div class="under">
			<p class="counter"><span id="count"></span> /10 знаков</p>
		</div>

		<button type="submit" class="btn" onclick="">Отправить</button>
		<button type="button" class="btn cancel" onclick="closeForm()">Закрыть</button>
	  </form>
</div>
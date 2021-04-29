<?php 
// $name = checkRegularName();
$email = checkRegularEmail();
$message = checkTextBox();

$validname = false;
if($_SERVER['REQUEST_METHOD'] === 'POST') 
{
    if (isset($_POST['btn'])) 
    {
        if (isset($_POST['name'])) {
            $validname = preg_match('|^[А-Я][а-я]{2,}$|u', $_POST['name'], $matches,
            PREG_OFFSET_CAPTURE);
        }
        
        // if (isset($_POST['last_name'])) {
        //     $validLastName = preg_match('|^[А-Я][а-я]{2,}$|u', $_POST['last_name'], $matches,
        //     PREG_OFFSET_CAPTURE);
        // }
        
        // if (isset($_POST['email'])) {
        //     $validEmail = preg_match('|^[A-Z0-9][A-Z0-9._%+-]+@[A-Z0-9-]+\.[A-Z]{2,4}$|i', $_POST['email'], $matches,
        //     PREG_OFFSET_CAPTURE);
        // }
        
        // if (isset($_POST['password1'])) {
        //     $validPassword1 = preg_match('|^[A-Z0-9\\\/*-+.,]{6,20}$|i', $_POST['password1'], $matches,
        //     PREG_OFFSET_CAPTURE);
        // }
        
        // if (isset($_POST['password2'])) {
        //     $validPassword2 = strcmp($_POST['password1'], $_POST['password2']) == 0;
        // }
    }
}
// if (isset($_GET['message']) && $_GET['message'] == 'ok')  // если был редирект с сообщением OK
// 	echo '<script> alert("Корректное имя!")</script>';
// 
?> 



<div class="form-popup" id="myForm">
	  <form action = "<?= $_SERVER['PHP_SELF'] ?>"  class="form-container" method = "post">
		<h1>Связаться</h1>

        <label for="name"><b>Ваше имя</b></label>
        <input type="text" name="name" value="<?= isset($_POST['name']) ? $_POST['name']: ""; ?>">
                <?php if ($_SERVER['REQUEST_METHOD'] === 'POST') 
                { ?>
                <?php if (!preg_match('|[А-Я][а-я]{2,}$|u', $_POST['name'], $matches,PREG_OFFSET_CAPTURE)): ?>
                        <label for="name" >"Err"</label>
                    <?php else: ?>
                        <label for="name"> "Good"</label> 
                    <?php endif; ?>
                <?php }?>
				
		<label for="email"><b>Почта</b></label>
		<input type="text" placeholder="Ваша почта" name="email" value="<?= isset($_POST['email']) ? $_POST['email']: ""; ?>">
				<?php if ($_SERVER['REQUEST_METHOD'] === 'POST') 
                { ?>
                <?php if (!preg_match('|[A-Z0-9][A-Z0-9._%+-]+@[A-Z0-9-]+\.[A-Z]{2,4}$|i', $_POST['email'], $matches,PREG_OFFSET_CAPTURE)): ?>
                        <label for="email" >"Err"</label>
                    <?php else: ?>
                        <label for="email"> "Good"</label> 
                    <?php endif; ?>
                <?php }?>
				
		<label class="<?= $message ? 'error' : '' ?>"> <?= $message ? 'Минимальная длина сообщения 30 символов!' : 'Введите сообщение' ?></label>
		<textarea class="input2" placeholder="Ваше сообщение" id='msg' oninput="getCount()" name="message"><?= !empty($_POST['message']) ? $_POST['message'] : '' ?></textarea>

        <div class="under">
			<p class="counter"><span id="count"></span> /30 знаков</p>
		</div>

		<button type="submit" class="btn">Отправить</button>
		<button type="button" class="btn cancel" onclick="closeForm()">Закрыть</button>
	  </form>
</div>

<?php
 if (isset($_GET['message']) && $_GET['message'] == 'ok')  // если был редирект с сообщением OK
 	echo '<script> alert("Сообщение успешно отправлено!")</script>';
?>
<?php
 require('script.php'); 
 ?>

 </body>
</html>
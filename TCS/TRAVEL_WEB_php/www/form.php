
<?php
//$message = checkTextBox();
$validName = false;
$validEmail = false;
$formvalid = false;

if($_SERVER['REQUEST_METHOD'] === 'POST')
{
	if (isset($_POST['btn_ok'])) 
	{
		echo "<script type='text/javascript'>alert('КНОПКА СРАББОТАЛА ЗДЕСЬ');</script>";
		if (isset($_POST['login']))
		{
             $validName = preg_match('|^[А-Я][а-я]{2,}$|u', $_POST['login'], $matches,PREG_OFFSET_CAPTURE);
			 $formvalid = true;
			 echo "<script type='text/javascript'>alert('КНОПКА  ЗДЕСЬ');</script>";
        }
		
		
		if (isset($_POST['email'])) 
		{
			$re = '|^[A-Z0-9][A-Z0-9._%+-]+@[A-Z0-9-]+\.[A-Z]{2,4}$|i';
            $validEmail = preg_match($re , $_POST['email'], $matches,PREG_OFFSET_CAPTURE);
			$formvalid = true;
			echo "<script type='text/javascript'>alert('КНОПКА тут');</script>";
        }
	}
	
	if($formvalid)
	{
		//header('Location: '.$_SERVER['PHP_SELF'].'?message=ok');
		$message = " Ваше сообщение отправлено!";
		echo "<script type='text/javascript'>alert('$message');</script>";
	}

}
?>

<div class="form-popup" id="myForm">
	  <form action = ""  class="form-container" method = 'post'>
		<h1>Связаться</h1>
        <label for="login"><b>Ваше имя</b></label>
        <input type="text" name="login" value="<?= isset($_POST['login']) ? $_POST['login']: ""; ?>">
                <?php if ($_SERVER['REQUEST_METHOD'] === 'POST') { ?>
                <?php if (!validName): ?>
                    <p >
                        Имя должно состоять минимум из 3 букв,
                        содержать буквы русского алфавита и не содержать пробелов.<br>
                        Первая буква должна быть прописной.
                    </p>
                    <?php else: ?>
                    <p >&#10003;</p>
                    <?php endif; ?>
                <?php }?>

				
		<label for="email"><b>Почта</b></label>
		<input type="text" placeholder="Ваша почта" name="email" value="<?= isset($_POST['email']) ? $_POST['email']: ""; ?>">
				<?php if ($_SERVER['REQUEST_METHOD'] === 'POST') 
                { ?>
                <?php if (!validEmail): ?>
                        <label for="email" >"Err"</label>
                    <?php else: ?>
                        <label for="email"> </label> 
                    <?php endif; ?>
                <?php }?>
		
		
	<label for="msg"><b>Ваше сообщение</b></label>
		<textarea class="input2" placeholder="Ваше сообщение" id='msg' oninput="getCount()" name="message"><?= !empty($_POST['message']) ? $_POST['message'] : '' ?></textarea>

        <div class="under">
			<p class="counter"><span id="count"></span> /30 знаков</p>
		</div>

		<input type="submit" name = "btn_ok" class="btn" value = "Отправить">
		<button type="button" name = "btn_cancel" class="btn cancel" onclick="closeForm()">Закрыть</button>
	  </form>
</div>

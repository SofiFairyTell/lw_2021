<?php
$title_page = 'О нас';
 require('header.php');
?>

<section class="section_hack">
<form action = ""  class="form-container" method = 'post'>
		<h1>Связаться</h1>
        <label for="login"><b>Ваше имя</b></label>
        <input type="text" name="login" value="<?= isset($_POST['login']) ? $_POST['login']: ""; ?>">
                <?php if ($_SERVER['REQUEST_METHOD'] === 'POST') { ?>
                <?php if (!$validName): ?>
                    <p >
                        Имя должно состоять минимум из 3 букв, содержать буквы русского алфавита и не содержать пробелов.<br>
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
                <?php if (!$validEmail): ?>
                        <label for="email" >"Err"</label>
                    <?php else: ?>
                        <label for="email"> </label> 
                    <?php endif; ?>
                <?php }?>

		<label for="Password"><b>Пароль</b></label>
		<input type="text" placeholder="Ваша пароль" name="password" value="<?= isset($_POST['password']) ? $_POST['password']: ""; ?>">
				<?php if ($_SERVER['REQUEST_METHOD'] === 'POST') 
                { ?>
                <?php if (!$validEmail): ?>
                        <label for="password" >"Wrong password"</label>
                    <?php else: ?>
                        <label for="password"> </label> 
                    <?php endif; ?>
                <?php }?>



		<input type="submit" name = "btn_ok" class="btn" value = "Войти">
		<button type="button" name = "btn_regist" class="btn registration" onclick="closeForm()">Регистрация</button>
	  </form>    
</section> <!--section-hack-->

<?php
require('script.php');  
require('footer.php');
?>

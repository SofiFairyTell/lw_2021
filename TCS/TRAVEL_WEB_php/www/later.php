<!-- 		
        <label class="<?= $email ? 'error' : '' ?>" for="email"><?= $email ? 'Формат email: jjjjj.dfdf2011@yandex.ru' : 'Email' ?></label>
		

	    <input type="text" id="email" name="email" value="<?= !empty($_POST['email']) ? $_POST['email'] : '' ?>" 
        placeholder="Ваша почта" maxlength="40" type="text">

        <label class="<?= $message ? 'error' : '' ?>"> <?= $message ? 'Минимальная длина сообщения 30 символов!' : 'Введите сообщение' ?></label>

		<!-- <textarea class="input2" placeholder="Ваше сообщение" id="msg" oninput="getCount()" ></textarea> -->
        <textarea class="input2" placeholder="Ваше сообщение" id='msg' oninput="getCount()" name="message"><?= !empty($_POST['message']) ? $_POST['message'] : '' ?></textarea>
		 -->
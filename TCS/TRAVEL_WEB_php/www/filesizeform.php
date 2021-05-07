<?php
include_once $_SERVER['DOCUMENT_ROOT'] . './scriptphp/filesize.php';
include_once $_SERVER['DOCUMENT_ROOT'] . './scriptphp/phpQuery/phpQuery.php';
include_once $_SERVER['DOCUMENT_ROOT'] . './scriptphp/watermark.php';


?>
<!DOCTYPE html>
<html lang="ru">
<head>
</head>
<body>
<section class="section"> 
<div >
        <h1>Подсчёт размера файла</h1>
        <form action="" method="GET">
            <label for="">Введите путь</label>
            <input type="text" value="<?= $_GET['path'] ?? '' ?>" name="path" placeholder="/от корня...">
            <input type="submit">
        </form>
		<div>
            <span>Результат: </span>
            <?= !empty($_GET) ? getRes($_GET['path'])  : '' ?>
        </div>
</div>
</section>
<section class = "section">
<div>
    <span> Фотография с Watermark</span>
   <?php 

    $watermark = new Watermark();
    $img = imagecreatefromjpeg('img/photo3.jpg');

    $font = dirname(__FILE__) . '/fonts/verdana.ttf';;
    $image = $watermark->add_watermark($img,'travelblog.ru',$font);
 
    //выводим изображение
    imageJPEG($img,'img/simpletext.jpg');

   //imagejpeg($image, NULL, 75);
    //освобождаем память
    imagedestroy($image);
   // imagedestroy($img);
    ?>
</div>
</section>

<section class = "section">
<form enctype="multipart/form-data" action="filesizeform.php" method="post">
			Выберите файл: <input name="uploadedFile" type="file" />
			<input type="submit" name = "uploadBtn" value="Загрузить" />
		</form>
<?php
$message = ''; 
if (isset($_POST['uploadBtn']) && $_POST['uploadBtn'] == 'Загрузить')
{
  if (isset($_FILES['uploadedFile']) && $_FILES['uploadedFile']['error'] === UPLOAD_ERR_OK)
  {
    // get details of the uploaded file
    $fileTmpPath = $_FILES['uploadedFile']['tmp_name'];
    $fileName = $_FILES['uploadedFile']['name'];
    $fileSize = $_FILES['uploadedFile']['size'];
    $fileType = $_FILES['uploadedFile']['type'];
    $fileNameCmps = explode(".", $fileName);
    $fileExtension = strtolower(end($fileNameCmps));

    // sanitize file-name
    $newFileName = md5(time() . $fileName) . '.' . $fileExtension;

    // check if file has one of the following extensions
    $allowedfileExtensions = array('jpg', 'gif', 'png', 'zip', 'txt', 'xls', 'doc');

    if (in_array($fileExtension, $allowedfileExtensions))
    {
      // directory in which the uploaded file will be moved
      $uploadFileDir = './uploaded_files/';
      $dest_path = $uploadFileDir . $newFileName;

      if(move_uploaded_file($fileTmpPath, $dest_path)) 
      {
        $message ='File is successfully uploaded.';
      }
      else 
      {
        $message = 'There was some error moving the file to upload directory. Please make sure the upload directory is writable by web server.';
      }
    }
    else
    {
      $message = 'Upload failed. Allowed file types: ' . implode(',', $allowedfileExtensions);
    }
  }
  else
  {
    $message = 'There is some error in the file upload. Please check the following error.<br>';
    $message .= 'Error:' . $_FILES['uploadedFile']['error'];
  }
}
?>        
</section>



</body>
</html>
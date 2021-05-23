<?php
session_start();
if (empty($_SESSION['user_store'])) 
{
    echo "<script type='text/javascript'>window.location.href = '../travelblog.php';</script>";
    exit();
}
$title_page = 'Управление сайтом';
require('../header.php');
?>

<section class="section_hack">
    <div class="contain">  
    <span> <h1> 
    <?php
            if($_SESSION['message'])
            {
                echo '<p class = "msg_registration">'.$_SESSION['message'] . '</p>';
            }
            unset ($_SESSION['message']);
            ?>
    </h1></span>
    <a class="nav_link" href="./managecontent.php?content=ok">Управление контентом</a>
	<a class="nav_link" href="./manageuser.php">Управление пользователями</a>
    </div><!--contain -->
<?php
    switch ($_GET) {
        case ($_GET['content'] === 'ok'):
            ?>
            <a class="nav_link"  href="./managecontent.php">Управление контентом</a>
            <div class="inner-content">
                <h3>Изображения на сайте</h3>
                <div class="table-wrapper">
                    <table class="fl-table">
                        <thead>
                            <tr>
                                <th>Положение</th>
                                <th>Название</th>
                                <th>Путь</th>
                                <th>Подпись</th>
                            </tr>
                        </thead> <!--thead-->
                        <tbody>
                        <?php			
                            $result = getAllIMG();
                            while($row = mysqli_fetch_assoc($result))
                            {?>
                                <tr>
                                    <td> <?=$row['img_slide']?></td>
                                    <td> <?=$row['img_name']?></td>
                                    <td> <?=$row['img_path']?></td>
                                    <td> <?=$row['img_paragraph']?></td>
                                    <td> <a href="./edit.php?id=<?= $row['img_id'] ?>">Редактировать</a></td>
                                    <td> <a href="./delete.php?id=<?= $row['img_id'] ?>">Удалить</a></td>
                                <tr>
                                <?php } ?>
                        </tbody> <!--tbody-->
                    </table><!--fl-table-->
                </div> <!--table-wrapper-->
            </div><!--inner-content-->
            <?php
            break;     
        default:
            ?>     <div class="inner-content"></div>
        <?php
    }
    ?>
</section> <!-- section_hack -->
<?php
require('../script.php');  
require('../footer.php');
?>
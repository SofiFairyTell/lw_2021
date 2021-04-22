<!DOCTYPE html>
<html lang="ru">
<head>
	<title>Лайфхаки</title>
	<link rel="stylesheet" type="text/css" href="css/travelstyle.css">
</head>

<?php
 require('header.php');
?>
	<link href='https://fonts.googleapis.com/css?family=Open+Sans:400,600,700' rel='stylesheet' type='text/css'>
<section class="section_hack">
<div class="contain">
	<div class="photo">
		<div class="carusel_item">
			<div class ="make-3D-space">
				<div class ="product-card" id = "prd_1">
					<div  class ="product-front" >
						<div class="shadow"></div> <!--shadow-->
						<img src="./img/lifehacks/plan.jpg" alt="plan" />
						<div class="image_overlay"></div> <!--image_overlay-->
						<div class="view_details">Узнать больше</div>
						<div class="stats">        	
							<div class="stats-container">
								<span class="product_price">1</span>
								<span class="product_name">Собираем вещи</span>    
								<p>Что взять с собой?</p>   		
								<div class="product-options">
									<strong>Сняряжение</strong>
									<span>
										<ul>
											<li> Документы </li>
											<li> Деньги </li>
											<li> Еда </li>
											<li> Аптечка </li>
										</ul>
									</span>		
								</div> <!--product-options-->
							</div><!--stats-container-->
						</div> <!--stats-->
					</div> <!--product-front-->
					<div  class ="product-back" >
						<div class="shadow"></div>
						<div class ="carousel">
							<ul>
								<li><img src="./img/lifehacks/medicinebag.jpg" alt="medicinebag" />
									<p>В аптечке должны быть лекарства первой необходимости</p>
									<p> Например: обезболиваюшее, спирт и йод.</p>
								</li>
								<li><img src="./img/lifehacks/document.jpg" alt="document"/>
								<p>	Среди документов всегда паспорт и билеты</p>
								</li>
								<li><img src="./img/lifehacks/scale_1200 (1).jpeg" alt="" />
								<p> Для перекуса подойдет вода, сухое печенье. </p>
								</li>
							</ul>
							<div class="arrows-perspective">
								<div class="carouselPrev">
									<div class="y"></div>
									<div class="x"></div>
								</div>
								<div class="carouselNext">
									<div class="y"></div>
									<div class="x"></div>
								</div>
							</div> <!--arrows-perspective-->
						</div> <!--carousel-->
						<div class ="flip-back">
							<div class="cy"></div>
							<div class ="cx"></div>
						</div> <!--flip-back-->
					</div>	 <!--product-back-->
				</div>	<!--product-card-->	
			</div><!--make-3D-space-->
		</div> <!--carusel_item-->
		<div class="carusel_item">
			<div class ="make-3D-space">
				<div class ="product-card" id = "prd_2">
					<div  class ="product-front">
						<div class="shadow"></div> <!--shadow-->
						<img src="./img/lifehacks/map.jpg" alt="map" />
						<div class="image_overlay"></div> <!--image_overlay-->
						<div class="view_details">Узнать больше</div> <!--view_details-->
						<div class="stats">        	
							<div class="stats-container">
								<span class="product_price">2</span>
								<span class="product_name">Строим маршрут</span>    
								<p>А куда мы едем?</p>   		
								<div class="product-options">
									<strong>Понадобиться следующий набор:</strong>
									<span>
										<ul>
											<li> Интернет </li>
											<li> Карта </li>
											<li> Атлас автодорог </li>
											<li> Блокнот </li>
											<li> Знающий дорогу </li>
										</ul>
									</span>		
								</div> <!--product-options-->
							</div><!--stats-container-->
						</div> <!--stats-->
					</div> <!--product-front-->
					<div  class ="product-back">
						<div class="shadow"></div>
						<div class ="carousel">
							<ul>
								<li><img src="./img/lifehacks/map.jpg" alt="map" /></li>
								<li><img src="./img/lifehacks/roadmap.jpg" alt="roadmap" /></li>
								<li><img src="./img/lifehacks/friend.jpeg" alt="friend" />
								<p>Верный друг это всегда очень важно,<br>
									особенно если собрался в дальную дорогу</p>
								<p><strong>ВАЖНО!</strong><br>Хотя бы один должен знать куда Вы идёте</p>
								
								</li>
							</ul>
							<div class="arrows-perspective">
								<div class="carouselPrev">
									<div class="y"></div>
									<div class="x"></div>
								</div>
								<div class="carouselNext">
									<div class="y"></div>
									<div class="x"></div>
								</div>
							</div> <!--arrows-perspective-->
						</div> <!--carousel-->
						<div class ="flip-back">
							<div class="cy"></div>
							<div class ="cx"></div>
						</div> <!--flip-back-->
					</div>	 <!--product-back-->
				</div>	<!--product-card-->	
			</div><!--make-3D-space-->
		</div> <!--carusel_item-->
	
	</div><!--photo-->
</div> <!--contain-->
</section> <!--section-hack-->



<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
<script src="./js/travelblock.js"></script>
<script>
	document.addEventListener('DOMContentLoaded', function () {
	document.body.classList.add('loaded_hiding');
	window.setTimeout(function () {
		document.body.classList.add('loaded');
		document.body.classList.remove('loaded_hiding');
	}, 2000);
	});
</script>

</body>
</html>
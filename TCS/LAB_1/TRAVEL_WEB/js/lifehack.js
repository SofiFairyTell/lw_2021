var a = document.querySelectorAll('.product_card');
// window.onload = function () {
// 	document.body.classList.add('loaded_hiding');
// 	window.setTimeout(function () {
// 	  document.body.classList.add('loaded');
// 	  document.body.classList.remove('loaded_hiding');
// 	}, 5000);
//   }
$(document).ready(function(){


	// Дополнительная информация о первой карточке
	$('.product-card').hover(function(){
			$(this).addClass('animate');
			$('div.carouselNext, div.carouselPrev').addClass('visible');			
		 }, function(){
			$(this).removeClass('animate');			
			$('div.carouselNext, div.carouselPrev').removeClass('visible');
	});	

    let $card = $('.product-card');
	let switching = false;
	//Показать оборотную сторону карты
	// $('.view_details').click(function()
	// {	
		// clickId = document.querySelector('.product-card').getAttribute('id');
		// $clickId.addClass('flip-10');
		// setTimeout(function()
		// {
		// 	$clickId.removeClass('flip-10').addClass('flip90').find('div.shadow').show().fadeTo( 80 , 1, 
		// 	// function()
		// 	// {
		// 	// 	$('.product-front, .product-front div.shadow').hide();			
		// 	// });
		// )
		// }, 50);

		// $('div.carouselNext, div.carouselPrev').removeClass('visible');
		// $('.product-card').addClass('flip-10');
		// setTimeout(function(){
		// 	$('.product-card').removeClass('flip-10').addClass('flip90').find('div.shadow').show().fadeTo( 80 , 1, function(){
		// 		$('.product-front, .product-front div.shadow').hide();			
		// 	});
		// }, 50);
		
		// setTimeout(function()
		// {
		// 	$('.product-card').removeClass('flip90').addClass('flip190');
		// 	$('.product-back').show().find('div.shadow').show().fadeTo( 90 , 0);
		// 	setTimeout(function(){				
		// 		$('.product-card').removeClass('flip190').addClass('flip180').find('div.shadow').hide();						
		// 		setTimeout(function(){
		// 			$('.product-card').css('transition', '100ms ease-out');			
		// 			$('.cx, .cy').addClass('s1');
		// 			setTimeout(function(){$('.cx, .cy').addClass('s2');}, 100);
		// 			setTimeout(function(){$('.cx, .cy').addClass('s3');}, 200);				
		// 			$('div.carouselNext, div.carouselPev').addClass('visible');				
		// 		}, 100);
		// 	}, 100);			
		// }, 150);		
				
	// });			
    

	// // Перевернуть карту рубашкой вверх
	// $('.flip-back').click(function(){		
		
	// 	$('.product-card').removeClass('flip180').addClass('flip190');
	// 	setTimeout(function()
	// 	{
	// 		$('.product-card').removeClass('flip190').addClass('flip90');
	
	// 		$('.product-back div.shadow').css('opacity', 0).fadeTo( 100 , 1, function(){
	// 			$('.product-back, .product-back div.shadow').hide();
	// 			$('.product-front, .product-front div.shadow').show();
	// 		});
	// 	}, 50);
		
	// 	setTimeout(function()
	// 	{
	// 		$('.product-card').removeClass('flip90').addClass('flip-10');
	// 		$('.product-front div.shadow').show().fadeTo( 100 , 0);
	// 		setTimeout(function(){						
	// 			$('.product-front div.shadow').hide();
	// 			$('.product-card').removeClass('flip-10').css('transition', '100ms ease-out');		
	// 			$('.cx, .cy').removeClass('s1 s2 s3');			
	// 		}, 100);			
	// 	}, 150);			
		
	// });	

	
	/* ----  Image Gallery Carousel   ---- */
	
	var carousel = $('.carousel ul');
	var carouselSlideWidth = 335;
	var carouselWidth = 0;	
	var isAnimating = false;
	
	// building the width of the casousel
	$('.carousel li').each(function(){
		carouselWidth += carouselSlideWidth;
	});
	$(carousel).css('width', carouselWidth);
	
	// Load Next Image
	$('div.carouselNext').on('click', function(){
		var currentLeft = Math.abs(parseInt($(carousel).css("left")));
		var newLeft = currentLeft + carouselSlideWidth;
		if(newLeft == carouselWidth || isAnimating === true){return;}
		$('.carousel ul').css({'left': "-" + newLeft + "px",
							   "transition": "300ms ease-out"
							 });
		isAnimating = true;
		setTimeout(function(){isAnimating = false;}, 300);			
	});
	
	// Load Previous Image
	$('div.carouselPrev').on('click', function(){
		var currentLeft = Math.abs(parseInt($(carousel).css("left")));
		var newLeft = currentLeft - carouselSlideWidth;
		if(newLeft < 0  || isAnimating === true){return;}
		$('.carousel ul').css({'left': "-" + newLeft + "px",
							   "transition": "300ms ease-out"
							 });
	    isAnimating = true;
		setTimeout(function()
		{
			isAnimating = false;
		}, 300);			
	});
  
    function tick() 
	{
        let head = document.querySelector('.header');
		head.classList.toggle('hot_color');
		head.classList.toggle('cold_color');
    }
// цвет: background-color: #46B973

    var interval = 5000;
    let timerId = () => {

		setInterval(()=> {
			tick();
		}, interval);
	}
	

});
function openForm() 
{
  document.getElementById("myForm").style.display = "block";
}

function closeForm() 
{
  document.getElementById("myForm").style.display = "none";
}

var startCount = 0;
var maxCount = 10;
var submitBtn = $("#submit");
$("#count").text(startCount);

function getCount() {
    var count = startCount + $("#msg").val().length;
    $("#count").text(count);
    if (count >= maxCount) {
        $(".counter").addClass("red");
    } else if (count < 10 && $(".counter").hasClass("red")) {
        $(".counter").removeClass("red");
        submitBtn.prop('disabled', false);
    }
    if (count >= 10) {
        submitBtn.prop('disabled', true);
    }
}

var validName = false;
var validEmail = false;
var validMessage = false;

$("form").submit(function(event){
    event.preventDefault();
    
    var name = $("#name").val();
    var email = $("#email").val();
    var message = $("#msg").val();
    if(name == "" && message == "" && email == "") {
    
        validName = false;
        validEmail = false;	
        validMessage = false;	
        console.log('Не ок!')    
    } 
    else {      

        console.log('Все ок!')        
        validName = true;
        validEmail = true;	
        validMessage = true;
    }


    if(validName == true && validEmail == true) {
        $("form").unbind('submit').submit();
    }

});

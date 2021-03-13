$(document).ready(function(){
			
    var validName = false;
    var validEmail = false;

    $("form").submit(function(event){
        event.preventDefault();

        var name = $("#name").val();
        var email = $("#email").val();

        if(name == "") {
            $("#name").parent().removeClass("has-success").addClass("has-error");	
            $(".nameBlock").append("<span class='glyphicon glyphicon-remove form-control-feedback' aria-hidden='true'></span>");
            $(".nameBlock .glyphicon-ok").remove();
            validName = false;
        } else {
            $("#name").parent().removeClass("has-error").addClass("has-success");	
            $(".nameBlock").append("<span class='glyphicon glyphicon-ok form-control-feedback' aria-hidden='true'></span>");
            $(".nameBlock .glyphicon-remove").remove();
            validName = true;
        }

        if(email == "") {
            $("#email").parent().removeClass("has-success").addClass("has-error");	
            $(".emailBlock").append("<span class='glyphicon glyphicon-remove form-control-feedback' aria-hidden='true'></span>");
            $(".emailBlock .glyphicon-ok").remove();
            validEmail = false;	
        } else {
            $("#email").parent().removeClass("has-error").addClass("has-success");	
            $(".emailBlock").append("<span class='glyphicon glyphicon-ok form-control-feedback' aria-hidden='true'></span>");
            $(".emailBlock .glyphicon-remove").remove();
            validEmail = true;	
        }


        if(validName == true && validEmail == true) {
            $("form").unbind('submit').submit();
        }

    });

});
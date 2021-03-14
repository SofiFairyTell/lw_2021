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

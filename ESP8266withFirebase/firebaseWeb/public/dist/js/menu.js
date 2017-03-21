$(document).ready(function(){
    $('<ul class="nav nav-pills pull-right">'+
      '<li role="presentation"><a href="index.html">Home</a></li>'+
      '<li role="presentation"><a href="home.html">智慧家庭</a></li>'+
      '<li role="presentation"><a href="lcd.html">LCD Relay</a></li>'+
      '<li role="presentation"><a href="record.html">RFID-出入記錄</a></li>'+
      '</ul>').prependTo('#menu');
    
    var pageName = location.pathname.substring(1);
    if(pageName.length == 0){
        pageName = "index.html";
    }
    $("ul.nav>li>a").each(function(i){
        if ($(this).attr("href") == pageName){
            $(this).parent().addClass("active");
        }
    });
});
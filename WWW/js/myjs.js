function goToAutho(){
    document.location.href = "authorityPage.html";
}
function goToReg(){
    document.location.href = "registrationPage.html";
}
function goToCart(){
    document.location.href = "cartPage.html";
}

$(function(){
    $('.sliderTeam  ').slick({
        slidesToShow: 3,
        slidesToScroll: 1,
        autoplay: false,
        autoplaySpeed: 2000,
        arroy: false,
        variableWidth: true
      });
});

$(function(){
    $('.minimized').click(function(event) {
      var i_path = $(this).attr('src');
      $('body').append('<div id="overlay"></div> <div id="magnify"><img src="'+i_path+'"><div id="close-popup"><i></i></div></div>');
      $('#magnify').css({
          left: ($(document).width() - $('#magnify').outerWidth())/2,
          // top: ($(document).height() - $('#magnify').outerHeight())/2 upd: 24.10.2016
              top: ($(window).height() - $('#magnify').outerHeight())/2
        });
      $('#overlay, #magnify').fadeIn('fast');
    });
    
    $('body').on('click', '#close-popup, #overlay', function(event) {
      event.preventDefault();
   
      $('#overlay, #magnify').fadeOut('fast', function() {
        $('#close-popup, #magnify, #overlay').remove();
      });
    });
  });


var options = [];

$( '.dropdown-menu a' ).on( 'click', function( event ) {
    $( '.dropdown-menu a' ).css.attr('background')="red"
   var $target = $( event.currentTarget ),
       val = $target.attr( 'data-value' ),
       $inp = $target.find( 'input' ),
       idx;

   if ( ( idx = options.indexOf( val ) ) > -1 ) {
      
      options.splice( idx, 1 );
      setTimeout( function() { 
         
          $inp.prop( 'checked', false )
           }, 0);
   } else {
      options.push( val );
      setTimeout( function() { 
          $inp.prop( 'checked', true )
        }, 0);
   }

   $( event.target ).blur();
      
   console.log( options );
   return false;
});

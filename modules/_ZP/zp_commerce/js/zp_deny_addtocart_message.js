(function ($) {

  Drupal.behaviors.zp_deny_addtocart_message = {
    attach: function (context, settings) {
       
       console.log('test');
       console.log(Drupal.settings['zp_commerce']);
       console.log(Drupal.settings['zp_commerce']['deny_message']);
       
       $(".deny-addtocart a").click(function(){
         
         console.log('click addtocart: ' + Drupal.settings['zp_commerce']['deny_message']);
         return false;

       });

       
    }
  };

}(jQuery));

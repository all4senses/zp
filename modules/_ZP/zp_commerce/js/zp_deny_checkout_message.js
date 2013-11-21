(function ($) {

  Drupal.behaviors.zp_deny_checkout_message = {
    attach: function (context, settings) {
       
//       console.log('test');
//       console.log(Drupal.settings['zp_commerce']);
//       console.log(Drupal.settings['zp_commerce']['deny_message']);
       
       $(".deny-checkout a").click(function(){
         
         //console.log('click addtocart: ' + Drupal.settings['zp_commerce']['deny_message']);
         alert(Drupal.settings['zp_commerce']['deny_checkout_message']);
         return false;

       });

       
    }
  };

}(jQuery));

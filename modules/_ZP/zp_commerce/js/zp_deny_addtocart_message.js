(function ($) {

  Drupal.behaviors.zp_deny_addtocart_message = {
    attach: function (context, settings) {
       
       console.log('test');
       console.log(Drupal.settings['zp_commerce']);
       console.log(Drupal.settings['zp_commerce']['deny_message']);

       
    }
  };

}(jQuery));

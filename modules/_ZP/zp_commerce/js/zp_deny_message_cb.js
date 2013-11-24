(function ($) {

  Drupal.behaviors.zp_deny_message_cb = {
    attach: function (context, settings) {
       
//       console.log('test');
//       console.log(Drupal.settings['zp_commerce']);
//       console.log(Drupal.settings['zp_commerce']['deny_message']);
       
       $(".deny-message a").click(function(){
         
          $.fn.colorbox({inline:true, href:"#deny-message-cb", width:780, height:440});  
          return false;

       });
       
       
        $("#deny-message-cb #no").click(function(){
            //console.log('Closedddddd');
            $.fn.colorbox.close();
        });

       
    }
  };

}(jQuery));
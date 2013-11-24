(function ($) {

  Drupal.behaviors.zp_deny_message_cb = {
    attach: function (context, settings) {
       
//       console.log('test');
//       console.log(Drupal.settings['zp_commerce']);
//       console.log(Drupal.settings['zp_commerce']['deny_message']);
       
       $(".deny-message a").click(function(){
         
          $.fn.colorbox({inline:true, href:"#exitIntent", width:780, height:440});  
          return false;

       });
       
       
        $("#exitIntent #no").click(function(){
            //console.log('Closedddddd');
            $.fn.colorbox.close();
        });

       
    }
  };

}(jQuery));
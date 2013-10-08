(function ($) {

  Drupal.behaviors.dmm_loginToCommentLink = {
    attach: function (context, settings) {
       
       $( ".login-to-comment a" ).click(function(event){
         
         
          $.ajax({
            //dataType: "jsonp",
            from: 'login-to-comment',
            url: "/comments-fragment"
            //,cache: false,
//            data: {
//                    lang: 'en'
//                  },
//            success: function(data){ 
//
//                  }
          });
          
          //alert('login-to-comment');
         
        });
        
        
        
        
        $( ".user-header a.dmm-login" ).click(function(event){
         
         
          $.ajax({
            //dataType: "jsonp",
            from: 'login',
            url: "/comments-fragment"
            //,cache: false,
//            data: {
//                    lang: 'en'
//                  },
//            success: function(data){ 
//
//                  }
          });
          
          //alert('login');
        
         
        });
       
       //console.log('blocks test!');
       
    }
  };

}(jQuery));

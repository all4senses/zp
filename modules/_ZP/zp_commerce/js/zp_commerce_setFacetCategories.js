(function ($) {

  Drupal.behaviors.gv_newsletterSubscribe_fieldHints = {
    attach: function (context, settings) {
      
      $('.block-facetapi .content .item-list li').each(function(){
        
        console.log(this);
//        if ($(this).val() == '') {
//          $(this).val($(this).attr('title'));
//          $(this).addClass('blur');
//        }
        
      });
      
      
      
    }
  };

}(jQuery));
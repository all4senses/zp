(function ($) {

  Drupal.behaviors.zp_commerce_setFacetCategories = {
    attach: function (context, settings) {
      
      console.log('zp_commerce_setFacetCategories.....');
      
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
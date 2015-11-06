(function ($) {

  Drupal.behaviors.zp_commerce_setFacetCategories = {
    attach: function (context, settings) {
      
      //console.log('zp_commerce_setFacetCategories.....');
      
      //var cat_name = null;
      
      
      //jQuery('.block-facetapi .content .item-list li').each(function(){
      jQuery('.block-facetapi .facetapi-facetapi-checkbox-links li').each(function(){
        
        //console.log(this);
        
        cat_name = jQuery(this).find('.cat-name');
        //console.log(jQuery(cat_name));
        if (cat_name.length) {
          //console.log(jQuery(cat_name).text());
          jQuery(cat_name).insertBefore(jQuery(this)).wrap('<li></li>').css('display','block');
          //jQuery(cat_name)
        }
        
      });
      
      
//        if ($(this).val() == '') {
//          $(this).val($(this).attr('title'));
//          $(this).addClass('blur');
//        }
        
      
    }
  };

}(jQuery));
(function ($) {

  Drupal.behaviors.zp_commerce_setFacetArticles = {
    attach: function (context, settings) {
      
      console.log('zp_commerce_setFacetArticles.....');
      
      //var cat_name = null;
      
      jQuery('.block-facetapi .facetapi-facet-field-article-product-depts li a.facetapi-inactive').each(function(){
        
        console.log(this);
        $(this).parent().find('.item-list').hide();

//        cat_name = jQuery(this).find('.cat-name');
//        
//        if (cat_name.length) {
//          //console.log(jQuery(cat_name).text());
//          jQuery(cat_name).insertBefore(jQuery(this)).wrap('<li></li>').css('display','block');
//          //jQuery(cat_name)
//        }
        
      });
      
      
//        if ($(this).val() == '') {
//          $(this).val($(this).attr('title'));
//          $(this).addClass('blur');
//        }
        
      
    }
  };

}(jQuery));
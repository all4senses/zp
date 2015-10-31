(function ($) {

  Drupal.behaviors.zp_commerce_setFacetArticles = {
    attach: function (context, settings) {
      
      console.log('zp_commerce_setFacetArticles.....');
      
      //var cat_name = null;
      //jQuery('.block-facetapi input').css("float", "left");
      jQuery('.block-facetapi input').each(function () {this.style.setProperty("float", "left", "important");});
      
      jQuery('.block-facetapi .facetapi-facet-field-article-product-depts li').each(function(){
        found = null;
        found = $(this).find('a.facetapi-active');
        console.log(found);
        if (found.length){
          console.log('found = 1');
        }
        else {
          console.log('found = 0');
          $(this).find('.item-list').hide();
        }
        
      });
      
      jQuery('.block-facetapi .facetapi-facet-field-article-product-depts li a.facetapi-inactive').each(function(){
        
        //console.log(this);
        //$(this).parent().find('.item-list').hide();

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
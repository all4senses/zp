(function ($) {

  Drupal.behaviors.zp_commerce_setFacetArticles = {
    attach: function (context, settings) {
      
      console.log('zp_commerce_setFacetArticles.....');
      
      // http://stackoverflow.com/questions/2655925/how-to-apply-important-using-css
      // http://stackoverflow.com/questions/11962962/overriding-important-with-css-or-jquery
      
      jQuery('.block-facetapi input').each(function () {
        //console.log('checkbox...');
        this.style.setProperty("float", "left", "important");
        //$(this).addClass('xxx');
      });
      
      
      //$('a.facetapi-inactive + .block-facetapi .facetapi-facet-field-article-product-depts .item-list').hide();
      
      $('.block-facetapi .facetapi-facet-field-article-product-depts li .item-list').hide();
      
//      $('.block-facetapi .facetapi-facet-field-article-product-depts li').each(function(){
//        found = $(this).find('a.facetapi-active');
//        if (!found.length){
//          $(this).find('.item-list').hide();
//        }
//      });
      
      $('.block-facetapi .facetapi-facet-field-article-product-depts .item-list:not(zp-processed) li a.facetapi-active').each(function(){
        $(this).parent().find('.item-list').show();
        $(this).parent().children('.item-list').show().children('.item-list').hide();
        $(this).parents('.item-list').show().addClass('zp-processed');
        
      });
      

        
      
    }
  };

}(jQuery));
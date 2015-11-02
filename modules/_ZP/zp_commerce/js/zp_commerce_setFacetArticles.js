(function ($) {

  Drupal.behaviors.zp_commerce_setFacetArticles = {
    attach: function (context, settings) {
      
      console.log('zp_commerce_setFacetArticles.....');
      
      // http://stackoverflow.com/questions/2655925/how-to-apply-important-using-css
      // http://stackoverflow.com/questions/11962962/overriding-important-with-css-or-jquery
      
      // Make facets checkboxes (or links if set so) float left to see it normally
      jQuery('.block-facetapi input, .block-facetapi a[id*="facetapi-link"].facetapi-active').each(function () {
        //Works
        //this.style.setProperty("float", "left", "important");
        //Works
        //$(this).css('cssText', 'float: left !important;');
        $(this).css('float', 'left');
        //$(this).addClass('xxx');
      });
      
      jQuery('.block-facetapi li.expanded div').css('margin-left', '10px');
      
      // Initially close all expanded categories
      $('.block-facetapi .facetapi-facet-field-article-product-depts .item-list .item-list').hide();
      
//      $('.block-facetapi .facetapi-facet-field-article-product-depts li').each(function(){
//        found = $(this).find('a.facetapi-active');
//        if (!found.length){
//          $(this).find('.item-list').hide();
//        }
//      });
      // And then open those branches that has active links (from the upper parent down to a first child)
      $('.block-facetapi .facetapi-facet-field-article-product-depts .item-list:not(zp-processed) li a.facetapi-active').each(function(){
        console.log($(this).html());
        //$(this).html('<span class="zp-expand opened">-</span>' + $(this).html());
        $(this).after('<span class="zp-expand opened" style="float: left">-</span>');
        $(this).parent().find('.item-list').show();
        $(this).parent().children('.item-list').show().children('.item-list').hide();
        $(this).parents('.item-list').show().addClass('zp-processed');
        
      });
      
      $('.block-facetapi .facetapi-facet-field-article-product-depts li a.facetapi-inactive').each(function(){
        itemList = $(this).siblings('.item-list');
        if (itemList.length){
          if($(itemList).css('display') == 'none') {
            $(this).before('<span class="zp-expand closed" style="float: left">+</span>');
          }
          else {
            $(this).before('<span class="zp-expand opened" style="float: left">-</span>');
          }
        }
        
      });
      
      $('.zp-expand').click(function(){
        console.log('click');
        if ($(this).hasClass('opened')) {
          $(this).removeClass('opened').addClass('cloded').text('+');
        }
        else {
          $(this).removeClass('closed').addClass('opened').text('-');
          //$(this).replaceWith('<span class="zp-expand opened" style="float: left">-</span>');
        }
      });
      
    }
  };

}(jQuery));
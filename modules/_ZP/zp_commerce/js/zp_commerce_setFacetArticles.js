(function ($) {

  Drupal.behaviors.zp_commerce_setFacetArticles = {
    attach: function (context, settings) {
      
      //console.log('zp_commerce_setFacetArticles.....');
      
      // http://stackoverflow.com/questions/2655925/how-to-apply-important-using-css
      // http://stackoverflow.com/questions/11962962/overriding-important-with-css-or-jquery
      
      // Make facets checkboxes (or links if set so) float left to see it normally
      jQuery('.block-facetapi input:checkbox:not(.zp-checkbox-processed), .block-facetapi a[id*="facetapi-link"].facetapi-active:not(.zp-checkbox-processed)').each(function () {
        //Works
        //this.style.setProperty("float", "left", "important");
        //Works
        //$(this).css('cssText', 'float: left !important;');
        $(this).css('float', 'left');
        $(this).addClass('zp-checkbox-processed'); 
      });
      
      //jQuery('.block-facetapi li.expanded div').css('margin-left', '10px');
      jQuery('.block-facetapi li.expanded ul').css('cssText', 'margin-left: 0; padding-left: 20px;');
      
      // Initially close all expanded categories
      if($('.block-facetapi .facetapi-facet-field-article-product-depts .item-list').length) {
        list_element = '.item-list';
      }
      else {
        list_element = 'ul';
      }
      ////$('.block-facetapi .facetapi-facet-field-article-product-depts .item-list .item-list').hide();
      $('.block-facetapi .facetapi-facet-field-article-product-depts ' + list_element + ' ' + list_element).hide();
      
//      $('.block-facetapi .facetapi-facet-field-article-product-depts li').each(function(){
//        found = $(this).find('a.facetapi-active');
//        if (!found.length){
//          $(this).find('.item-list').hide();
//        }
//      });
      // And then open those branches that has active links (from the upper parent down to a first child)
//      $('.block-facetapi .facetapi-facet-field-article-product-depts .item-list:not(.zp-processed) li a.facetapi-active').each(function(){
//        //console.log($(this).html());
//        $(this).after('<span class="zp-expand opened" style="float: left; cursor: alias;">-</span>');
//        $(this).parent().find('.item-list').show();
//        $(this).parent().children('.item-list').show().children('.item-list').hide();
//        $(this).parents('.item-list').show().addClass('zp-processed');
//        
//      });
        $('.block-facetapi .facetapi-facet-field-article-product-depts ul:not(.zp-processed) li a.facetapi-active').each(function(){
        //console.log($(this).html());
        $(this).after('<span class="zp-expand opened" style="float: left; cursor: alias;">-</span>');
        $(this).parent().find(list_element).show();
        $(this).parent().children(list_element).show().children(list_element).hide();
        $(this).parents(list_element).show().addClass('zp-processed');
        
      });
      
//      $('.block-facetapi .facetapi-facet-field-article-product-depts li a.facetapi-inactive').each(function(){
//        itemList = $(this).siblings('.item-list');
//        if (itemList.length){
//          if($(itemList).css('display') == 'none') {
//            $(this).before('<span class="zp-expand closed" style="float: left; cursor: alias;">+</span>');
//          }
//          else {
//            $(this).before('<span class="zp-expand opened" style="float: left; cursor: alias;">-</span>');
//          }
//        }
//        
//      });
      $('.block-facetapi .facetapi-facet-field-article-product-depts li a.facetapi-inactive').each(function(){
        itemList = $(this).siblings(list_element);
        if (itemList.length){
          if($(itemList).css('display') == 'none') {
            $(this).before('<span class="zp-expand closed" style="float: left; cursor: alias;">+</span>');
          }
          else {
            $(this).before('<span class="zp-expand opened" style="float: left; cursor: alias;">-</span>');
          }
        }
        
      });
      
//      $('.zp-expand').click(function(){
//        //console.log('click');
//        thisObject = $(this);
//        if ($(this).hasClass('opened')) {
//          $(this).siblings('.item-list').slideUp('slow', function(){$(thisObject).removeClass('opened').addClass('closed').text('+');});
//        }
//        else {
//          $(this).siblings('.item-list').slideDown('slow', function(){$(thisObject).removeClass('closed').addClass('opened').text('-');});
//          
//        }
//      });
      $('.zp-expand').click(function(){
        //console.log('click');
        thisObject = $(this);
        if ($(this).hasClass('opened')) {
          $(this).siblings(list_element).slideUp('slow', function(){$(thisObject).removeClass('opened').addClass('closed').text('+');});
        }
        else {
          $(this).siblings(list_element).slideDown('slow', function(){$(thisObject).removeClass('closed').addClass('opened').text('-');});
          
        }
      });
      
    }
  };

}(jQuery));
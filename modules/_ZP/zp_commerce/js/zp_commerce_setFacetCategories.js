(function ($) {

  Drupal.behaviors.zp_commerce_setFacetCategories = {
    attach: function (context, settings) {
      
      console.log('zp_commerce_setFacetCategories.....');
      
      
      
      // http://stackoverflow.com/questions/2655925/how-to-apply-important-using-css
      // http://stackoverflow.com/questions/11962962/overriding-important-with-css-or-jquery
      
      // Make facets checkboxes (or links if set so) float left to see it normally
      jQuery('.block-facetapi input, .block-facetapi a[id*="facetapi-link"].facetapi-active').each(function () {
        console.log('xxxxx');
        console.log($(this));
        //Works
        //this.style.setProperty("float", "left", "important");
        //Works
        $(this).css('cssText', 'float: left !important;');
        //$(this).css('float', 'left');
        $(this).addClass('xxx');
      });
      
      
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
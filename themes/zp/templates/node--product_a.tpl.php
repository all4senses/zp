<?php if (!$page): ?>
  <article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
<?php else: ?>
  
    <?php 
      $url = 'http://www.zapokupkami.com'. url('node/' . $node->nid);
      
      /*
        if (isset($node->metatags['title']['value']) && $node->metatags['title']['value']) {
          $share_title = $node->metatags['title']['value'];
        }
        else {
          $share_title = $title;
        }

        echo '<div class="float share">' . zp_blocks_getSocialiteButtons($url, $share_title) . '</div>';
      */
    ?>

  <div class="main-content"> 
<?php endif; ?>

 
      <?php if (!$page): ?>
        <header>
      <?php endif; ?>

          <?php print render($title_prefix); ?>
          
              <?php if ($page): ?>
              <h1 
              <?php else: ?>
              <h3 
              <?php endif; ?>

                <?php print ' ' . /*$title_attributes*/ /*preg_replace('/datatype=".*"/', '', $title_attributes);*/ ''/*preg_replace('/datatype=""/', '', $title_attributes)*/; 
                if (!$node->status) {echo ' class="not-published"';} 
                ?>><?php if (!isset($node->title_no_link) && !$page): ?><a href="<?php print $node_url; ?>"><?php print $title; ?></a>
                <?php else: ?><?php print $title; ?><?php endif; ?><?php if ($page): ?></h1><?php else: ?></h3><?php endif; ?> 

          <?php print render($title_suffix); ?>  
            
            
          <span class="submitted">
            <?php 
            
              $created_str = date('F d, Y \a\t g:ia', $node->created);
              $created_rdf = preg_replace('|(.*)content=\"(.*)\"\s(.*)|', '$2', $date);
              
              if ($page) {
                  
                  global $language;
                  
                  $submitted = '<span property="dc:date dc:created" content="' . $created_rdf . '" datatype="xsd:dateTime" rel="sioc:has_creator">' .
                                 $created_str .
                               '</span>';
                
                  echo $submitted;
              }
              else {
                  echo $created_str;
              }
              
            ?>
          </span>


      <?php if (!$page): ?>
        </header>
      <?php endif; ?>



      <div class="content <?php echo ($page ? 'page' : 'teaser'); ?>"<?php print $content_attributes; ?>>
        <?php
          // Hide comments, tags, and links now so that we can render them later.
          hide($content['comments']);
          hide($content['links']);
          hide($content['field_topics']);
          
          
          if (!$page) {
            //dpm($content);

            //hide($content['body']);
            echo render($content['body']);
            //echo 'summary...';
            
            // Hide user comment field on a teaser
            hide($content['field_product'][0]['line_item_fields']['field_u_product_comment']);
          }
          else {
            // Make a brand name as a link if there corresponding brand page is found.
            dpm($content);
            dpm($node);
            
            if (@$node->field_brand['und'][0]['safe_value'] || @$node->field_brand_code['und'][0]['safe_value']) {
              $query = db_select('node', 'n');
            
              $query->join('field_data_field_titles_alternative', 'ta', "ta.entity_id = n.nid"); 
              $query->join('field_data_field_brand_codes', 'bc', "bc.entity_id = n.nid"); 

              $query->condition('n.type', 'brand');
              
              //$query->condition('ta.type', 'brand');
              if (@$node->field_brand['und'][0]['safe_value']) {
                $db_or_title = db_or();
                  $db_or_title->condition('n.title', $node->field_brand['und'][0]['safe_value']);
                  $db_or_title->condition('ta.field_brand_codes_value', $node->field_brand['und'][0]['safe_value']);
                $query->condition($db_or_title);
              }
              if (@$node->field_brand_code['und'][0]['safe_value']) {
                $query->condition('ta.field_brand_codes_value', $node->field_brand_code['und'][0]['safe_value']);
              }
              
              $query->fields('n', array('nid', 'title'));

              if ($brand_page = $query->execute()->fetchObject()) {
                dpm($brand_page);
                $content['field_brand'][0]['#markup'] = l($brand_page->title, 'node/' . $brand_page->nid);
              }
            }
            
            
    
          }
          //dpm($content);
          echo render($content);
        ?>
      </div>

      <?php if ($page): ?>
    
          <footer>
            <div class="share">
              <?php 
                echo zp_blocks_getSidebarShareStaticBlock($node, '<span>Share:</span>');
              ?>  
            </div>
          </footer>

    
      <?php endif; ?>
    
      <div class="bottom-clear"></div>
 

  
    
  <?php //print render($content['comments']); ?>

<?php if (!$page): ?>
  </article> <!-- /.node -->
<?php endif; ?>

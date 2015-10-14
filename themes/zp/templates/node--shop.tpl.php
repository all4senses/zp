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
            echo 'summary...';
          }
          
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


  
  
<?php 
/*
if ($page) {
  
    dpm($content);
    echo 'Отделы'; 

    $term_children = taxonomy_get_children($node->field_catalog['und'][0]['tid']);//, $node->field_category['und'][0]['taxonomy_term']->vid);
    //dpm($term_children);
    
    $tids = NULL;
    foreach($term_children as $term_child) {
      $tids[$term_child->tid] = $term_child->tid;
    }

    if (!$tids) {
      return;
    }

    $display =  'bl_subdpts_of_dpt'; //'bl_dpts_of_shop';

    $view = views_get_view('zp_catalog');

    $options = array('id' => 'field_catalog_tid', 'value' => $tids, 'type' => 'select', 'vocabulary' => 'catalog', 'hierarchy' => 1, 'reduce_duplicates' => 1, 'group' => 0,);
    $view->add_item($display, 'filter', 'field_data_field_catalog', 'field_catalog_tid', $options);

    echo $view->preview($display);
    
}
*/

global $current_shop_zp_id;

$current_shop_zp_id = $node->field_zp_id['und'][0]['safe_value'];

dpm($current_shop_zp_id);
?>

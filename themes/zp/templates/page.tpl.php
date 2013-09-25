<div id="bshadow">
    


  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
    <?php if ($main_menu): ?>
      <a href="#navigation" class="element-invisible element-focusable"><?php print t('Skip to navigation'); ?></a>
    <?php endif; ?>
  </div>

  
  <header id="header" role="banner" class="clearfix">

    <nav id="navigation" role="navigation" class="clearfix">
      <div id="header-menu-back"></div>
      
      <div id="logo-block">
        <a href="<?php print $front_page; ?>" title="<?php print 'За Покупками!'; ?>" id="logo">
          <?php

              //echo '<img src="http://getvoip.com/sites/all/themes/gv_orange/css/images/getvoip-logo4.png" alt="GetVoIP" title="GetVoIP" />';
          ?>
          <div class="text1">Удобная Служба Доставки</div>
          <div id="test">За Покупками!</div>
          <div class="text2">в Ваши любимые магазины!</div>


        </a>
      </div>
      
      <?php 
          echo render($page['header']); 
      ?>
    </nav> <!-- /#navigation -->

  </header> <!-- /#header -->

  
  <?php  if ($page['highlighted']): ?>
    <section id="highlighted" class="clearfix">
      <?php print render($page['highlighted']); ?>
    </section>
  <?php endif;  ?>
  
  
  <div id="all-content" class="clearfix">
      
      
    
      <section id="main" role="main" class="clearfix">

          <?php 
            print $breadcrumb;
            print $messages; 
            // we aren't getting messages, get them manually
//            if (isset($_SESSION['messages'])) {
//                echo '<div class="messages">';
//                foreach($_SESSION['messages'] as $type=>$messages) {
//                    echo "<p class=\"$type\">".implode("</p><p class=\"$type\">", $messages)."</p>";
//                }
//                echo '</div>';
//                unset($_SESSION['messages']);
//            }

            
          ?>
          <a id="main-content"></a>
          
          <?php if (!empty($tabs['#primary'])): ?><div class="tabs-wrapper clearfix"><?php print render($tabs); ?></div><?php endif; ?>
          <?php print render($page['help']); ?>
          <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
          
          <?php print render($page['above_content']); ?>
          <?php print render($page['content']); ?>
          
      </section> <!-- /#main -->


      <?php if ($page['sidebar_first']): ?>
        <aside id="sidebar-first" role="complementary" class="sidebar clearfix">
          <?php print render($page['sidebar_first']); ?>
        </aside>  <!-- /#sidebar-first -->
      <?php endif; ?>

      <?php if ($page['sidebar_second']): ?>
        <aside id="sidebar-second" role="complementary" class="sidebar clearfix">
          <?php print render($page['sidebar_second']); ?>
        </aside>  <!-- /#sidebar-second -->
      <?php endif; ?>

  </div> <!-- /#all-content -->

  </div> <!-- <div id="bshadow"> -->


  <footer id="footer" role="contentinfo" class="clearfix">
   <div id="footer-inside">

      <?php

          //echo '<div id="block-gv-blocks-follow-links"><div class="follow-us">Follow Us</div>', gv_blocks_get_headerLinks(), '</div>';

          echo render($page['footer']);
      ?>


      <div class="c">За Покупками! ... 
      <div>© 2009-2013 zapokupkami.com | All Rights Reserved</div>
      </div>

    
   </div>
  </footer> <!-- /#footer -->


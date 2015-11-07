<?php
/**
 * @file
 * menu-tree.func.php
 */

/**
 * Overrides theme_menu_tree().
 */
function bootstrap_menu_tree(&$variables) {
  dpm($variables['tree']);
  return '<ul class="menu nav">' . $variables['tree'] . '</ul>';
}

/**
 * Bootstrap theme wrapper function for the primary menu links.
 */
function bootstrap_menu_tree__primary(&$variables) {
  //dpm($variables['tree']);
  return '<ul class="menu nav navbar-nav">' . $variables['tree'] . '</ul>';
}

/**
 * Bootstrap theme wrapper function for the secondary menu links.
 */
function bootstrap_menu_tree__secondary(&$variables) {
  //dpm($variables['tree']);
  return '<ul class="menu nav navbar-nav secondary">' . $variables['tree'] . '</ul>';
}

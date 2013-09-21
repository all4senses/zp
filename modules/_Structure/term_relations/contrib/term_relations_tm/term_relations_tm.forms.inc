<?php

require_once 'term_relations_tm.inc';

/**
 * @file
 * Collects all the taxonomy_mananger form alter and ajax handler functions into separate file for
 * easier maintenance.
 */

/**
 * 'Private' implementation of hook_form_FORM_ID_alter() for form id 'taxonomy_manager_double_tree_form':
 * - Adds double tree operations to relate terms and show relationships.
 * - Adds a custom submit handler to add relationships to the trees returned.
 */
function _term_relations_tm_form_taxonomy_manager_double_tree_form_alter(&$form, &$form_state) {
  if (!variable_get('term_relations_tm_disable_relationships_extra', 0)) {
    // use our own version of element process function and add relationships decorator
    $form['taxonomy2']['manager']['tree']['#process'] = array(
      'term_relations_tm_tree_process_elements',
      'term_relations_tm_tree_process_elements_add_relationships',
    );

    $form['taxonomy']['manager']['tree']['#process'] = array(
      'term_relations_tm_tree_process_elements',
      'term_relations_tm_tree_process_elements_add_relationships',
    );

    $module_path = drupal_get_path('module', 'term_relations_tm');

    $vid1 = $form['#parameters'][2];
    $vid2 = $form['#parameters'][3];

    if ($supported_directionality = _term_relations_tm_get_supported_directions($vid1, $vid2)) {
      // add directed relationship operations - depending on what's allowed
      if ($supported_directionality == 'l2r' || $supported_directionality == 'bi') {
        $form['double-tree']['operations']['relate_right'] = array(
          '#type' => 'image_button',
          '#value' => 'Relate right',
          '#attributes' => array('title' => t('Relate right')),
          '#src' => $module_path ."/images/add-relationships-right.png",
          '#prefix' => '<div class="taxonomy-manager-double-tree-operations-buttons">',
          '#suffix' => '</div>',
        );
        $form['double-tree']['operations']['show_relations_right'] = array(
          '#type' => 'image_button',
          '#value' => 'Show relations right',
          '#attributes' => array('title' => t('Show relations right')),
          '#src' => $module_path ."/images/show-relationships-right.png",
          '#prefix' => '<div class="taxonomy-manager-double-tree-operations-buttons">',
          '#suffix' => '</div>',
        );
      }

      if ($supported_directionality == 'r2l' || $supported_directionality == 'bi') {
        $form['double-tree']['operations']['relate_left'] = array(
          '#type' => 'image_button',
          '#value' => 'Relate left',
          '#attributes' => array('title' => t('Relate left')),
          '#src' => $module_path ."/images/add-relationships-left.png",
          '#prefix' => '<div class="taxonomy-manager-double-tree-operations-buttons">',
          '#suffix' => '</div>',
        );
        $form['double-tree']['operations']['show_relations_left'] = array(
          '#type' => 'image_button',
          '#value' => 'Show relations left',
          '#attributes' => array('title' => t('Show relations left')),
          '#src' => $module_path ."/images/show-relationships-left.png",
          '#prefix' => '<div class="taxonomy-manager-double-tree-operations-buttons">',
          '#suffix' => '</div>',
        );
      }
    }

    // show relationship information
    $form['taxonomy']['manager']['tree']['#relations_vid'] = $vid2;
    $form['taxonomy2']['manager']['tree']['#relations_vid'] = $vid1;
  }
}

/**
 * Override of AJAX Callback for Double Tree operations.
 *
 * @param $overriden_menu_item
 *  Use this to call the overridden callback. Could call taxonomy_manager_double_tree_edit
 *  explicitly but this is more polite in that it allows for a chain of overrides.
 */
function term_relations_tm_double_tree_edit($overriden_menu_item) {
  $params = $_POST;
  $op = $params['op'];

  $msg = "";
  $is_error_msg = FALSE;

  $json = array();

  if ($op == "move") {
    taxonomy_manager_double_tree_edit_move($params, $msg, $is_error_msg);
  }
  elseif ($op == "translation") {
    taxonomy_manager_doube_tree_edit_translate($params, $msg, $is_error_msg);
  }
  elseif ($op == "switch") {
    taxonomy_manager_double_tree_edit_switch($params, $msg, $is_error_msg);
  }
  elseif ($op == 'relate') {
    $json['related_tids'] = term_relations_tm_double_tree_edit_relate($params, $msg, $is_error_msg);
  }
  elseif ($op == 'show_relations') {
    $json['related_tids'] = term_relations_tm_double_tree_show_relations($params, $msg, $is_error_msg);
  }


  if ($msg == "") {
    $msg = t("Invalid operation.");
    $is_error_msg = TRUE;
  }
  $msg_type = ($is_error_msg) ? "error" : "status";

  $json['data'] = $msg;
  $json['type'] = $msg_type;

  drupal_json($json);

  // module_load_include('inc', 'taxonomy_manager', 'taxonomy_manager.admin');
  //
  // return taxonomy_manager_double_tree_edit();
}

/**
 * Override of taxonomy_manager_tree_build_child_form callback for generating and rendering nested child forms (AHAH).
 * I hate to duplicate so much code but without patching it's the only way.
 *
 * @param $tree_id
 * @param $parent term id of parent, that is expanded and of which children have to be loaded
 * @param $tid Term to expand, may be a single tid or an array of tids.
 */
function term_relations_tm_tree_build_child_form($tree_id, $vid, $parent, $tid = 0) {
  $params = $_GET;

  $GLOBALS['devel_shutdown'] = FALSE;

  $form_state = array('submitted' => FALSE);

  $tids = array();
  if (isset($tid) && $tid != 0) {
    // convert to array
    $tids = explode(',', $tid);
  }

  if (count($tids) == 1) {
    $language = _taxonomy_manager_term_get_lang($tids[0]);
  }
  else {
    $language = $params['language'];
  }

  // First #process callback adds multiple term expand - better as patch.
  // Second callback adds relationship info without having to override the tree
  // form builder as well - taxonomy_manager_tree_build_form().
  $child_form = array(
    '#type' => 'taxonomy_manager_tree',
    '#vid' => $vid,
    '#parent' => $parent,
    '#pager' => TRUE,
    '#language' => $language,
    '#term_to_expand' => $tids,
    '#process' => array(
      'term_relations_tm_tree_process_elements',
      'term_relations_tm_tree_process_elements_add_relationships',
    ),
  );


  if (!variable_get('term_relations_tm_disable_relationships_extra', 0)) {
    // set relations vid for displaying a has relationships flag
    if ($params['relations_vid']) {
      $child_form['#relations_vid'] = $params['relations_vid'];
    }
  }

  if (!$root_level) { //TODO ?
    $child_form['#siblings_page'] = 1;
  }

  $opertions_callback = 'taxonomy_manager_'. str_replace('-', '_', $tree_id) .'_operations';
  if (function_exists($opertions_callback)) {
    $child_form['#operations_callback'] = $opertions_callback;
  }

  $link_callback = 'taxonomy_manager_'. str_replace('-', '_', $tree_id) .'_link';
  if (function_exists($link_callback)) {
    $child_form['#link_callback'] = $link_callback;
  }

  _taxonomy_manager_tree_sub_forms_set_parents($tree_id, $parent, $child_form);

  //TODO use caching functions
  //$form = form_get_cache($param['form_build_id'], $form_state);
  //form_set_cache($param['form_build_id'], $form, $form_state);

  $child_form = form_builder($param['form_id'], $child_form, $form_state);

  print drupal_render($child_form);

  exit();
}

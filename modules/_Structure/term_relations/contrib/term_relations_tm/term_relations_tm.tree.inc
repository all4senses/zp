<?php

/**
 * @file
 * Code that provides additional tree functionality. Not specific to term relationships.
 * Specifically it allows multiple child terms to be expanded in one Ajax call.
 * @todo Would be much better as a patch.
 */

/**
 * Processes the tree form element.
 *
 * Very similar to original but adds multiple term expansion and calls a
 * different version of taxonomy_manager_tree_build_form.
 *
 * @param $element
 * @return the tree element
 */
function _term_relations_tm_tree_process_elements($element) {
  global $_taxonomy_manager_existing_ids; //TEMP: seems like this functions gets called twice in preview and cause problem because of adding the settings to js twice
  $_taxonomy_manager_existing_ids = is_array($_taxonomy_manager_existing_ids) ? $_taxonomy_manager_existing_ids : array();

  $module_path = drupal_get_path('module', 'taxonomy_manager') .'/';
  $id = form_clean_id(implode('-', $element['#parents']));
  $vid = $element['#vid'];

  if (!$element['#siblings_page'] && !in_array($id, $_taxonomy_manager_existing_ids)) {
    $_taxonomy_manager_existing_ids[$id] = $id;
    drupal_add_css($module_path .'css/taxonomy_manager.css');
    drupal_add_js($module_path .'js/tree.js');

    drupal_add_js(array('siblingsForm' => array('url' => url('admin/content/taxonomy_manager/siblingsform'), 'modulePath' => $module_path)), 'setting');
    drupal_add_js(array('childForm' => array('url' => url('admin/content/taxonomy_manager/childform'), 'modulePath' => $module_path)), 'setting');
    drupal_add_js(array('taxonomytree' => array('id' => $id, 'vid' => $vid)), 'setting');
  }

  if (!is_array($element['#operations'])) {
    $opertions_callback = 'taxonomy_manager_'. implode('_', $element['#parents']) .'_operations';
    if (function_exists($opertions_callback)) {
      $element['#operations_callback'] = $opertions_callback;
    }
  }
  if (!isset($element['#link'])) {
    $link_callback = 'taxonomy_manager_'. implode('_', $element['#parents']) .'_link';
    if (function_exists($link_callback)) {
      $element['#link_callback'] = $link_callback;
    }
  }


  $tree = _taxonomy_manager_tree_get_item($element['#vid'], $element['#parent'], $element['#pager'], $element['#siblings_page'], $element['#search_string'], $element['#language']);

  if ($element['#pager'] && !($element['#parent'] || $element['#siblings_page'])) {
    $element['pager'] = array('#value' => theme('pager', NULL, variable_get('taxonomy_manager_pager_tree_page_size', 50)));
  }

  $element['#default_value'] = is_array($element['#default_value']) ? $element['#default_value'] : array();
  $element['#multiple'] = isset($element['#multiple']) ? $element['#multiple'] : TRUE;
  $element['#add_term_info'] = isset($element['#add_term_info']) ? $element['#add_term_info'] : TRUE;
  $element['#tree'] = TRUE;
  $element['#id'] = $id;
  $element['#element_validate'] = array('taxonomy_manager_tree_validate');
  $element['#required'] = isset($element['#tree_is_required']) ? $element['#tree_is_required'] : FALSE;

  $terms_to_expand = array();
  if ($element['#term_to_expand']) {
    // allow multiple terms to be expanded
    $requested_terms_to_expand = is_array($element['#term_to_expand']) ? $element['#term_to_expand'] : array($element['#term_to_expand']);
    foreach ($requested_terms_to_expand as $term_to_expand) {
      // Multiple term version
      _term_relations_tm_tree_get_first_path($term_to_expand, $tree, $terms_to_expand);
    }
    $terms_to_expand = taxonomy_manager_tree_get_terms_to_expand($tree, $requested_terms_to_expand, TRUE);
  }

  if (count($element['#default_value']) && !$element['#expand_all']) {
    $terms_to_expand = taxonomy_manager_tree_get_terms_to_expand($tree, $element['#default_value'], $element['#multiple']);
  }

  if (!empty($element['#language'])) {
    $element['#elements']['language'] = array('#type' => 'hidden', '#value' => $element['#language'], '#attributes' => array('class' => 'tree-lang'));
    _taxonomy_manager_tree_element_set_params($element['#parents'], $element['#elements']);
  }

  taxonomy_manager_tree_build_form($index = 0, $tree, $element['#elements'], $element, $element['#parents'], $element['#siblings_page'], $element['#default_value'], $element['#multiple'], $terms_to_expand);

  return $element;
}

/**
 * Calculates a path to a certain term and merges it into the tree.
 * This version supports multiple term expansion.
 * This function call by element process function _term_relations_tm_tree_process_elements.
 */
function _term_relations_tm_tree_get_first_path($tid, &$tree, &$terms_to_expand) {
  $path = array();
  $next_tid = $tid;

  $i = 0;
  while ($i < 100) { //prevent infinite loop if inconsistent hierarchy
    $parents = taxonomy_get_parents($next_tid);
    if (count($parents)) {
      //takes first parent
      $parent = array_pop($parents);
      $path[] = $parent;
      $next_tid = $parent->tid;
      if (taxonomy_manager_term_is_root($next_tid)) {
        break;
      }
    }
    else {
      break;
    }
    $i++;
  }
  $path = array_reverse($path);
  $path[] = taxonomy_get_term($tid);
  $root_term = $path[0];
  $root_term_index;

  // build a map of the path keyed on tid - helps in avoiding duplicates when merging multiple paths to the tree
  $term_map = array();
  if (count($path) > 1) {
    foreach ($tree as $index => $term) {
      $term_map[$term->tid] = $index;
      if ($term->tid == $root_term->tid) {
        $root_term_index = $index;
      }
    }
    reset($tree);
  }

  if (isset($root_term_index)) {
    $path_tree = taxonomy_manager_get_partial_tree($path);

    // build map of path tree keyed on tids
    $path_term_map = array();
    foreach ($path_tree as $index => $term) {
      $path_term_map[$term->tid] = $index;
    }

    reset($path_tree);

    // first find the set of new terms that we need to add - new terms should be contiguous within $path_tree
    $new_path_terms_map = array_diff_key($path_term_map, $term_map);

    if (!empty($new_path_terms_map)) {
      // something to add
      $insert_term_index = reset($new_path_terms_map);
      if ($insert_term_index > 0) {
        // use previous term as insertion point
        $previous_tid = $path_tree[$insert_term_index-1]->tid;
        $insertion_index = $term_map[$previous_tid];
      }
      else {
        // use root index as insertion point
        $insertion_index = $root_term_index;
      }

      // get the new terms to add from the path tree
      $new_path_tree = array_slice($path_tree, $insert_term_index, count($new_path_terms_map));

      // stick the new terms into the tree at the insertion point
      array_splice($tree, $insertion_index+1, 0, $new_path_tree);
    }
  }
}


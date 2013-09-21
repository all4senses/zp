<?php

/**
 * @file
 * Supporting functions here to save overhead of parsing infrequently used functions.
 */

require_once 'term_relations_tm.tree.inc';

/**
 * Get whether directional relationships are enabled.
 */
function _term_relations_tm_is_directional() {
  if (module_exists('term_relations')) {
    return term_relations_is_directed();
  }
  else {
    return FALSE;
  }
}

/**
 * Determine which relationships may be created between two vocabularies.
 */
function _term_relations_tm_get_supported_directions($vid1, $vid2) {
  // If the term_relations_vocab module has not been enabled then can only relate terms in the same vocabulary.
  if (!module_exists('term_relations_vocab')) {
    if ($vid1 == $vid2) {
      if (_term_relations_tm_is_directional()) {
        // both directions allowed.
        return 'bi';
      }
      else {
        // only one direction allowed - doesn't matter which.
        return 'l2r';
      }
    }
  }
  else {
    // get mapping of allowed relationships
    $all_vocab_relationships = term_relations_vocab_get_relationships();
    if (_term_relations_tm_is_directional()) {
      if (!empty($all_vocab_relationships[$vid1]['l2r'][$vid2]) && !empty($all_vocab_relationships[$vid1]['r2l'][$vid2])) {
        return 'bi';
      }
      elseif (!empty($all_vocab_relationships[$vid1]['l2r'][$vid2])) {
        return 'l2r';
      }
      elseif (!empty($all_vocab_relationships[$vid1]['r2l'][$vid2])) {
        return 'r2l';
      }
    }
    else {
      // only one direction - preserve direction - but is there any point?
      if (!empty($all_vocab_relationships[$vid1]['l2r'][$vid2])) {
        return 'l2r';
      }
      elseif (!empty($all_vocab_relationships[$vid1]['r2l'][$vid2])) {
        return 'r2l';
      }
    }
  }

  return FALSE;
}

/**
 * 'Private' implmentation of hook_taxonomy_manager_term_data_submit().
 * @todo - implement this!
 */
function _term_relations_tm_taxonomy_manager_term_data_submit($param, $values) {

}

/**
 * Callback to do extra processing to the tree.
 */
function _term_relations_tm_tree_process_elements_add_relationships($element) {
  global $_term_relations_tm_existing_ids; //TEMP: seems like this functions gets called twice in preview and cause problem because of adding the settings to js twice

  // Add relations
  if ($element['#relations_vid']) {

    $_term_relations_tm_existing_ids = is_array($_taxonomy_manager_existing_ids) ? $_taxonomy_manager_existing_ids : array();

    $module_path = drupal_get_path('module', 'term_relations_tm');
    $id = form_clean_id(implode('-', $element['#parents']));

    if (!$element['#siblings_page'] && !in_array($id, $_term_relations_tm_existing_ids)) {
      $_term_relations_tm_existing_ids[$id] = $id;
      drupal_add_css($module_path .'/css/term_relations_tm.css');
      drupal_add_js($module_path .'/js/term_relations_tm.js');
    }

    // Add relationships information - used to add operation and class.
    _term_relations_tm_tree_add_relationships_elements($element['#elements'], $element['#relations_vid']);
  }

  return $element;
}

/**
 * Add relationship info to an array of elements and recurse into their children.
 */
function _term_relations_tm_tree_add_relationships_elements(&$elements, $related_vid) {
  foreach ($elements as $tid => &$element) {
    if (!empty($element['children'])) {
      // recursive call for children
      _term_relations_tm_tree_add_relationships_elements($element['children'], $related_vid);
    }

    if (_term_relations_tm_is_directional()) {
      if ($direction = _term_relations_tm_get_relationships_direction_summary($tid, $related_vid)) {
        // set the has-related class on the term element
        $element['#attributes']['class'] .= ' has-related '. $direction;
      }
    }
    else {
      $terms = _term_relations_tm_get_related_terms($tid, $related_vid);
      if (!empty($terms)) {
        $element['#attributes']['class'] .= ' has-related';
      }
    }
  }
}

/**
 * Get relationship direction summary for term.
 */
function _term_relations_tm_get_relationships_direction_summary($tid, $vid) {
  $relationships = term_relations_get_related_by_direction($tid, $vid);
  // summarise the direction for all of this term relationships with terms in $vid.
  if (!empty($relationships['bi']) || (!empty($relationships['l2r']) && !empty($relationships['r2l']))) {
    return 'bi';
  }
  elseif (!empty($relationships['l2r'])) {
    return 'l2r';
  }
  elseif (!empty($relationships['r2l'])) {
    return 'r2l';
  }
  else {
    return FALSE;
  }
}

/**
 * Create relationships based on parameters sent by double tree edit AJAX request.
 * Always sent in a left to right fashion.
 */
function term_relations_tm_double_tree_edit_relate($params, &$msg, &$is_error_msg) {
  $selected_relate_from_terms = $params['selected_terms'];
  $selected_relate_to_terms = $params['selected_parents'];
  $voc1 = taxonomy_vocabulary_load($params['voc1']);
  $voc2 = taxonomy_vocabulary_load($params['voc2']);

  // put a guard in to protect against spoofed requests
  $supported_directionality = _term_relations_tm_get_supported_directions($voc1->vid, $voc2->vid);

  if ($supported_directionality == 'bi' || $supported_directionality == 'l2r') {
    term_relations_tm_relate($selected_relate_from_terms, $voc1->vid, $selected_relate_to_terms, $voc2->vid);

    $selected_relate_from_term_names = array();
    foreach ($selected_relate_from_terms as $tid) {
      $term = taxonomy_get_term($tid);
      $selected_relate_from_term_names[] = $term->name;
    }
    $selected_relate_to_term_names = array();
    foreach ($selected_relate_to_terms as $tid) {
      $term = taxonomy_get_term($tid);
      $selected_relate_to_term_names[] = $term->name;
    }
    $term_from_names = implode(', ', $selected_relate_from_term_names);
    $term_to_names = implode(', ', $selected_relate_to_term_names);
    $msg = t("Terms %terms_from in %voc1 related to %terms_to in %voc2.", array('%terms_from' => $term_from_names, '%voc1' => $voc1->name, '%terms_to' => $term_to_names, '%voc2' => $voc2->name));
    $is_error_msg = FALSE;

    return _term_relations_tm_get_related_term_tids($params['selected_terms'], $params['voc2']);
  }
}

/**
 * Returns related terms in the RHS vocabulary for each selected LHS term.
 */
function term_relations_tm_double_tree_show_relations($params, &$msg, &$is_error_msg) {
  $msg = t("OK");
  $is_error_msg = FALSE;

  return _term_relations_tm_get_related_term_tids($params['selected_terms'], $params['voc2']);
}

/**
 * Get the tids of terms related to other terms within a given vocabulary.
 *
 * @return
 *  A array of related tid arrays.
 */
function _term_relations_tm_get_related_term_tids($tids, $vid) {
  $from_tids = array();

  foreach ($tids as $tid) {
    $related_terms = _term_relations_tm_get_related_terms($tid, $vid);
    $from_tids[$tid] = array_keys($related_terms);
  }

  return $from_tids;
}

/**
 * Relates terms from one vocabulary to terms in the same or other vocabulary. If a relationship already exists it is deleted.
 *
 * @param array $relate_from_terms
 *  Array of LHS term tids to add relationships to.
 * @param $vid_from
 *  The id of the vocabulary that the LHS terms belong to.
 * @param array $relate_to_terms
 *  Array of RHS term tids to relate to.
 * @param $vid_to
 *  The id of the vocabulary that the RHS terms belong to.
 */
function term_relations_tm_relate($relate_from_terms, $vid_from, $relate_to_terms, $vid_to) {
  foreach ($relate_from_terms as $relate_from_tid) {
    if (_term_relations_tm_is_directional()) {
      $already_related = term_relations_get_related($relate_from_tid, 'tid', $vid_to);
      foreach ($relate_to_terms as $relate_to_tid) {
        if (isset($already_related[$relate_to_tid])) {
          // existing relationship in this direction - remove
          db_query("DELETE FROM {term_relation} WHERE tid1 = %d AND tid2 = %d", $relate_from_tid, $relate_to_tid);
        }
        else {
          db_query('INSERT INTO {term_relation} (tid1, tid2) VALUES (%d, %d)', $relate_from_tid, $relate_to_tid);
        }
      }
    }
    else {
      $already_related = term_relations_get_related($relate_from_tid, 'tid', $vid_to);
      foreach ($relate_to_terms as $relate_to_tid) {
        if (isset($already_related[$relate_to_tid])) {
          // delete relation in both directions
          db_query("DELETE FROM {term_relation} WHERE (tid1 = %d AND tid2 = %d) OR (tid2 = %d AND tid1 = %d)", $relate_from_tid, $relate_to_tid, $relate_from_tid, $relate_to_tid);
        }
        else {
          db_query('INSERT INTO {term_relation} (tid1, tid2) VALUES (%d, %d)', $relate_from_tid, $relate_to_tid);
        }
      }
    }
  }
}

/**
 * Adds relationship information to the term.
 * @todo not currently used - is something missing?????
 *
 * @param $term
 *  A reference to term object to add relationship info to.
 * @param $vid
 *  The id of the vocabulary to get relationships for.
 */
function _taxonomy_manager_tree_add_relationship_info(&$term, $vid) {
  $related_terms = _term_relations_tm_get_related_terms($term->tid, $vid);
  if (!empty($related_terms)) {
    $term->related_terms = $related_terms;
  }
}

/**
 * Get terms in given vocabulary related to a single term.
 * This is a non-directional query.
 *
 * @return
 *  Array of related term objects keyed on their tids.
 */
function _term_relations_tm_get_related_terms($tid, $vid) {
  $result = db_query('SELECT t.*, tid1, tid2 FROM {term_relation}, {term_data} t WHERE (t.tid = tid1 OR t.tid = tid2) AND (tid1 = %d OR tid2 = %d) AND t.tid != %d AND t.vid = %d ORDER BY weight, name', $tid, $tid, $tid, $vid);
  $related_terms = array();
  while ($term = db_fetch_object($result)) {
    $related_terms[$term->tid] = $term;
  }
  return $related_terms;
}


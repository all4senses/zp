<?php

/**
 * @file
 * Load on demand include file containing 'private' implementations of
 * taxonomy and taxonomy form hooks.
 */

/**
 * 'Private' implementation of hook_form_FROM_ID_alter() for taxonomy_form_term.
 */
function _term_relations_core_form_taxonomy_form_term_alter(&$form, &$form_state) {
  $term = $form['#term'];
  $vocabulary = $form['#vocabulary'];

  $related_tids = array_keys(term_relations_get_related($term['tid'], 'tid'));

  $tree = taxonomy_get_tree($vocabulary->vid);
  $options = array('<' . t('root') . '>');

  foreach ($tree as $item) {
    $options[$item->tid] = str_repeat('-', $item->depth) . $item->name;
  }

  $form['relations']['relations'] = array(
    '#type' => 'select',
    '#title' => t('Related terms'),
    '#options' => $options,
    '#default_value' => $related_tids,
    '#multiple' => TRUE,
  );
}

/**
 * 'Private' implementation of hook_taxonomy_term_insert().
 * Saves term relations.
 */
function _term_relations_taxonomy_term_insert($term) {
  if (isset($term->relations)) {
    if (!is_array($term->relations)) {
      $term->relations = array($term->relations);
    }
    $query = db_insert('taxonomy_term_relation')
      ->fields(array('tid1', 'tid2'));
    foreach ($term->relations as $related_tid) {
      $query->values(array(
        'tid1' => $term->tid,
        'tid2' => $related_tid
      ));
    }
    $query->execute();

    // Reset the taxonomy term static variables.
    taxonomy_terms_static_reset();
  }
}

/**
 * 'Private' implementation of hook_taxonomy_term_update().
 * Saves term relations. Respects directed relationships setting.
 */
function _term_relations_taxonomy_term_update($term) {
  if (isset($term->relations)) {
    if(term_relations_is_directed()) {
      // only delete this relationships matching tid1
      db_delete('taxonomy_term_relation')
        ->condition('tid1', $term->tid)
        ->execute();
    }
    else {
      // delete relationships matching both tid1 and tid2
      db_delete('taxonomy_term_relation')
        ->condition(db_or()->condition('tid1', $term->tid)->condition('tid2', $term->tid))
        ->execute();
    }

    if (!is_array($term->relations)) {
      $term->relations = array($term->relations);
    }
    $query = db_insert('taxonomy_term_relation')
      ->fields(array('tid1', 'tid2'));
    foreach ($term->relations as $related_tid) {
      $query->values(array(
        'tid1' => $term->tid,
        'tid2' => $related_tid
      ));
    }
    $query->execute();

    // Reset the taxonomy term static variables.
    taxonomy_terms_static_reset();
  }
}

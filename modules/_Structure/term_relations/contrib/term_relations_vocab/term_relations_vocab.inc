<?php

/**
 * @file
 * Implementation of non-admin hooks.
 */

/**
 * 'Private' implementation of hook_form_FROM_ID_alter() for taxonomy_form_term.
 */
function _term_relations_vocab_form_taxonomy_form_term_alter(&$form, &$form_state) {
  $tid = $form['tid']['#value'];
  $vid = $form['#vocabulary']['vid'];
  $related_vid = term_relations_vocab_get_relationships($vid, 'l2r');
  $form['#submit'][] = 'term_relations_vocab_term_submit';

  unset($form['advanced']['relations']);

  foreach ($related_vid as $rvid => $related_vocab) {
    $related_tids = array_keys(term_relations_get_related($tid, 'tid', $rvid));
    $form['advanced']['relations_'. $rvid] = _taxonomy_term_select(t('Related terms in @vocab_name', array('@vocab_name' => $related_vocab->name)), 'relations', $related_tids, $rvid, NULL, 1, '<'. t('none') .'>', array($tid));
    $form['advanced']['relations_'. $rvid]['#weight'] = -14;
  }
}

/**
 * Extra submit handler for taxonomy_form_term to handle term multiple vocab relations.
 */
function term_relations_vocab_term_submit(&$form, $form_state) {
  $tid = $form_state['values']['tid'];
  $vid = $form['#vocabulary']['vid'];
  $related_vids = term_relations_vocab_get_relationships($vid, 'l2r');
  foreach ($related_vids as $rvid => $vocab) {
    foreach ($form_state['values']['relations_'. $rvid] as $related_id) {
      if ($related_id != 0) {
        // Just insert as all relationships deleted by main submit handler.
        db_query('INSERT INTO {term_relation} (tid1, tid2) VALUES (%d, %d)', $tid, $related_id);
      }
    }
  }
}



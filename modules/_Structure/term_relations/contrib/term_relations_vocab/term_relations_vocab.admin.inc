<?php

/**
 * @file
 * Admin functions for term relations vocabublary.
 */

/**
 * 'Private' implementation of hook_form_FORM_ID_alter() for taxonomy_form_vocabulary.
 */
function _term_relations_vocab_form_taxonomy_form_vocabulary_alter(&$form, &$form_state) {
  $vid = $form['vid']['#value'];
  $form['#submit'][] = 'term_relations_vocab_submit';

  if (!empty($vid)) {
    $related_vids = term_relations_vocab_get_relationships($vid);
    $defaults = array_keys($related_vids['l2r']);

    if (!empty($related_vids['r2l'])) {
      $names = array();
      foreach ($related_vids['r2l'] as $rvid => $vocab) {
        $names[] = $vocab->name;
      }
      $text = t('Vocabularies that are configured to relate to this one: @vocab-names.', array('@vocab-names' => implode(', ', $names)));
    }
    else {
      $text = t('No vocabularies are configured to relate to this one.');
    }

    $self_default = !empty($related_vids['l2r'][$vid]);
  }
  else {
    $self_default = TRUE;
    $defaults = array();
  }

  $form['settings']['trv'] = array(
    '#type' => 'fieldset',
    '#title' => t('Related term settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  // Checkbox to allow relationships between terms in same vocabulary.
  // Default for new vocabularies is to allow.
  $form['settings']['trv']['self'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow relationships between terms in this vocabulary.'),
    '#default_value' => $self_default,
  );


  $form['settings']['trv']['vocabs'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Relate this vocabulary to another vocabulary'),
    '#options' => _term_relations_vocab_vocabs($vid),
    '#default_value' => $defaults,
  );

  if (!empty($text)) {
    $form['settings']['trv']['r2l_vocabs'] = array(
      '#value' => $text,
    );
  }
}

/**
 * Extra submit handler for taxonomy_form_vocabulary to handle term relations vocab settings.
 */
function term_relations_vocab_submit(&$form, $form_state) {
  $vid = $form_state['vid'];
  $relations = $form_state['values']['trv']['vocabs'];

  // if self is set - add vid to list of related vids.
  if ($form_state['values']['trv']['self']) {
    $relations[$vid] = $vid;
  }
  else {
    $relations[$vid] = 0;
  }

  if (!empty($relations)) {
    variable_set('term_relations_vocab_'. $vid, $relations);
  }
  else {
    variable_del('term_relations_vocab_'. $vid);
  }
}

/**
 * Return an array of all vocabularies in system
 */
function _term_relations_vocab_vocabs($this_vid) {
  $options = array();
  $vocabs = taxonomy_get_vocabularies();
  foreach ($vocabs as $vid => $vocab) {
    if ($this_vid == $vid) {
      continue;
    }
    $options[$vid] = $vocab->name;
  }
  return $options;
}





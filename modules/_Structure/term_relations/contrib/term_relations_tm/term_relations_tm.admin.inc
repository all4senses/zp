<?php

/**
 * @file
 * Admin callback overrides and hook implementations.
 */

/**
 * 'Private' implementation of hook_form_FORM_ID_alter() for form id 'taxonomy_manager_settings'.
 */
function _term_relations_tm_form_taxonomy_manager_settings_alter(&$form, &$form_state) {
  $form['term_relations_tm_disable_relationships_extra'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable relationship controls and flags in double-tree view'),
    '#default_value' => variable_get('term_relations_tm_disable_relationships_extra', 0),
    '#description' => t('Disabling this feature speeds up the Taxonomy Manager'),
  );
}

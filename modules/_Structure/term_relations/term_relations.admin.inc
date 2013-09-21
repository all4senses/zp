<?php

/**
 * @file
 * Administration code including private implementations of hooks.
 */

/**
 * Administration settings for term relations.
 */
function term_relations_admin_settings() {
  // this setting should be elsewhere
  $form['term_relations_directional'] = array(
    '#type' => 'checkbox',
    '#title' => t('Treat term relationships as directed'),
    '#default_value' => variable_get('term_relations_directional', FALSE),
    '#description' => t('If you have a need for directed term relationships, enable this option. When disabled, the direction of term relationships may not be preserved.'),
  );

  return system_settings_form($form);
}

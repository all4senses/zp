<?php

/**
 * @file
 * A specific handler for CH.
 */

$plugin = array(
  'title' => t('Address form (CH add-on)'),
  'format callback' => 'zp_misc_addressfield_format_address_ch_generate',
  'type' => 'address',
  'weight' => -80,
);

function zp_misc_addressfield_format_address_ch_generate(&$format, $address, $context = array()) {
  if ($address['country'] == 'CH' && $context['mode'] == 'form') {
    $format['locality_block']['postal_code']['#wrapper_id'] = $format['#wrapper_id'];
    $format['locality_block']['postal_code']['#process'][] = 'ajax_process_form';
    $format['locality_block']['postal_code']['#process'][] = 'zp_misc_addressfield_format_address_ch_postal_code_process';

    $format['locality_block']['postal_code']['#element_validate'] = array('zp_misc_addressfield_form_ch_postal_code_validation');
    $format['locality_block']['postal_code']['#ajax'] = array(
      'callback' => 'addressfield_standard_widget_refresh',
      'wrapper' => $format['#wrapper_id'],
    );
  }
  else {
    if (isset($format['locality_block']['postal_code'])) {
      // Cancel the AJAX for forms we don't control.
      $format['locality_block']['postal_code']['#ajax'] = array();
    }
  }
}

function zp_misc_addressfield_format_address_ch_postal_code_process($element) {
  $element['#limit_validation_errors'] = array($element['#parents']);

  return $element;
}

function zp_misc_addressfield_form_ch_postal_code_validation($element, &$form_state, &$form) {
  $data = array(
    '1000' => array('town' => 'Lausanne', 'canton' => 'VD'),
    '1001' => array('town' => 'Lausanne', 'canton' => 'VD'),
    '1002' => array('town' => 'Lausanne', 'canton' => 'VD'),
    
    '2364' => array('town' => 'St-Brais', 'canton' => 'JU'),
    '8970' => array('town' => 'Urdorf Exchange', 'canton' => 'ZH'),
  );

  // Check if theres something for autocomplete
  if (!empty($element['#value']) && (isset($data[$element['#value']]))) {
    // Get the base #parents for this address form.
    $base_parents = array_slice($element['#parents'], 0, -1);
    $base_array_parents = array_slice($element['#array_parents'], 0, -2);

    $city = $data[$element['#value']];

    // Set the new values in the form.
    drupal_array_set_nested_value($form_state['values'], array_merge($base_parents, array('locality')), $city['town'], TRUE);
    drupal_array_set_nested_value($form_state['values'], array_merge($base_parents, array('administrative_area')), $city['canton'], TRUE);

    // Discard value the user has already entered there.
    drupal_array_set_nested_value($form_state['input'], array_merge($base_parents, array('locality')), NULL, TRUE);
    drupal_array_set_nested_value($form_state['input'], array_merge($base_parents, array('administrative_area')), NULL, TRUE);
  }
}

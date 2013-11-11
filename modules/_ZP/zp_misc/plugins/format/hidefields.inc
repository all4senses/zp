<?php
/**
 * @file
 * Hide the country, state and zip code.
 */
 
$plugin = array(
  'title' => t('Hide the country, state and zip'),
  'format callback' => 'proctors_format_address_hide_statezip',
  'type' => 'address',
  'weight' => -80,
);  
 
/** 
 * Format callback.
 *
 * @see CALLBACK_addressfield_format_callback() 
 */ 
function proctors_format_address_hide_statezip(&$format, $address, $context = array()) {
  //you may need to hide other address parts, such as phone number
  $format['country']['#access'] = 0;
  $format['locality_block']['administrative_area']['#access'] = 0;
  $format['locality_block']['postal_code']['#access'] = 0;
  $format['street_block']['premise']['#access'] = 0;
}
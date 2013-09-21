<?php

/**
 * @file
 * Form overrides and hooks for term data form. Replace single related terms
 * field with multiple fields for each related vocabulary. Respects relationship
 * direction if set.
 */

/**
 * 'Private' implementation of hook_form_FORM_ID_alter() for form id 'taxonomy_manager_form'.
 * Add cross vocabulary relationships to Taxonomy Manager term edit form.
 */
function _term_relations_tm_form_taxonomy_manager_form_alter(&$form, &$form_state) {
  // get the term
  $term = taxonomy_get_term($form['term_data']['tid']['#value']);

  $vocab_relationships = term_relations_vocab_get_relationships();

  // remove the standard relations form element.
  unset($form['term_data']['relations']);

  // for each vocabulary that this term can be related to add a relations form element
  if (!empty($vocab_relationships[$term->vid]['l2r'])) {
    $related_vid = variable_get('taxonomy_vocab_relate_'. $term->vid, array());

    // for now only get ltr relationships as the handling code in taxonomy_manager_term_data_edit()
    // doesn't cope with deleting r2l terms in the right hand term edit form.
    $related_terms = term_relations_get_related($term->tid);

    $form['term_data']['relations'] = array('#type' => 'fieldset', '#title' => t('Relations'));

    foreach ($vocab_relationships[$term->vid]['l2r'] as $rvid => $related_vocabulary) {
      // get the set of related terms in related vocabulary
      $v_related_terms = array();
      foreach ($related_terms as $rterm) {
        if ($rterm->vid == $rvid) $v_related_terms[] = $rterm;
      }

      // add form element for related vocabulary
      $form['term_data']['relations']['relations'. $rvid] = _taxonomy_manager_form_term_data_lists($term, $v_related_terms, t($related_vocabulary->name), 'related');
      $form['term_data']['relations']['relations'. $rvid]['#tree'] = TRUE;
      $form['term_data']['relations']['relations'. $rvid]['#weight'] = '51';

      // needed for ahah callback - requires tweak to taxonomy_manager js and .module
      $form['term_data']['relations']['relations'. $rvid]['op']['add_button']['vid'] = array('#type' => 'hidden', '#value' => $rvid);

      // fix the lookup vid
      $form['term_data']['relations']['relations'. $rvid]['op']['add']['#autocomplete_path'] = 'taxonomy_manager/autocomplete/'. $rvid;
    }
  }
}

/**
 * Override of term_edit.
 */
function term_relations_tm_term_data_edit() {
  $param = $_POST;

  $attr_type = $param['attr_type'];
  $op = $param['op'];

  if ($op == 'add' && $attr_type == 'related') {
    // get the vid by matching submitted value to value of each related vid field.
    $matching_params = array_keys($param, $param['value']);
    foreach ($matching_params as $param_key) {
      if ($param_key != 'value') {
        if (!empty($param[$param_key .'-button-vid'])) {
          $related_vid = $param[$param_key .'-button-vid'];
          // got the related vid - reasonably safe to set vid to related vid
          // as long as there aren't any hook_taxonomy_manager_term_data_submit
          // implementations depending on it.
          $_POST['vid'] = $related_vid;
          break;
        }
      }
    }
  }

  // call the overridden menu callback.
  module_load_include('inc', 'taxonomy_manager', 'taxonomy_manager.admin');
  taxonomy_manager_term_data_edit();
}

/**
 * Implementation of hook_taxonomy_manager_term_data_submit(). Safe to have it
 * in this include file as it is included in the menu override that calls
 */
function term_relations_taxonomy_manager_term_data_submit($param, $values) {
  // if not directional then delete both sides of any deleted relationship
  // as the core taxonomy_term_save does. Need to be consistent!
  if (!term_relations_is_directed() && $param['op'] == 'delete' && $param['attr_type'] == 'related') {
    $tid = $param['tid'];
    if (!$tid) {
      $tid = $param['term_data']['tid'];
    }
    if (!is_array($values)) $values = array($values);

    foreach ($values as $value) {
      if ($value != 0) {
        // basically just applying the commented out line.
        db_query("DELETE FROM {term_relation} WHERE tid2 = %d AND tid1 = %d", $tid, $value);
      }
    }
  }
}


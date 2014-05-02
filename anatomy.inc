<?php

function anatomy_page(){
  // Load library and plugins
  drupal_add_js('http://d3js.org/d3.v3.min.js');
  drupal_add_js('http://cpettitt.github.io/project/dagre-d3/latest/dagre-d3.min.js');
  drupal_add_js('http://cpettitt.github.io/project/graphlib-dot/latest/graphlib-dot.min.js');

  // Anatomy JS an CSS
  drupal_add_js(drupal_get_path('module', 'anatomy') . '/anatomy.js', 'file');
  drupal_add_css(drupal_get_path('module', 'anatomy') . '/anatomy.css');

  $settings['entity_types'] = array (
    'node' => array(
      'shape' => 'box',
      'group' => 'node',
      ),
    'taxonomy_term' => array(
      'shape' => 'circle',
      'group' => 'taxonomy_term',
      ),
  );

  // NODES
  $all_entities = entity_get_info();
  $nodes = array();
  $edges = array();
  $output = '';

  // Get nodes data
  foreach ($settings['entity_types'] as $key => $settings) {
    foreach ($all_entities[$key]['bundles'] as $id => $entity_type) {
      $nodes[] = array(
        'node' => $id,
        'label' => $entity_type['label'],
        'group' =>$settings['group'],
        'shape' => $settings['shape'],
      );
    }
  }

  // Get edges data
  foreach (field_info_fields() as $field_name => $field) {
    if($field['type'] === 'entityreference') {
      foreach ($field['bundles'] as $bundle) {
        foreach ($bundle as $key => $type) {
          foreach ($field['settings']['handler_settings']['target_bundles'] as $target_bundle) {
           $edges[] = array(
              'from' => $type,
              'to' => $target_bundle,
              'label' => $field_name,
            );
          }
        }
      }
    }
  }

  // Create DOT data from nodes
  foreach ($nodes as $key => $node) {
    $output .= DOT_node($node['node']);
  }

  // Create DOT data from edges
  foreach ($edges as $key => $edge) {
    $output .= DOT_Ref($edge['from'], $edge['to']);
  }

  return theme('anatomy', array('data' => $output));
}


/**
 *  Create DOT ready nodes
 *
 * @param string $node
 *   The unique id of the DOT node
 * @param string $label
 *   (optional) Label to be shown on the node
 *
 * @return string
 *   A sting with DOT ready data with information about the node
 */
function DOT_node($node, $label = ''){
  return $node. ";\n";
}

/**
 *  Connect to nodes.
 *
 * @param string $from
 *   The unique id of the DOT node from where the reference should point
 * @param string $to
 *   The unique id of the DOT node to where the reference should point
 * @param array $label
 *   (optional) Attributes for the reference
 *
 * @return string
 *   A sting with DOT ready data with information about the reference
 */
function DOT_Ref($from, $to, $attributes = array()) {
  return $from . ' -> ' . $to . ";\n";
}

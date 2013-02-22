<?php
/**
 * @file
 * gi_content_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gi_content_types_ctools_plugin_api() {
  return array("version" => "1");
}

/**
 * Implements hook_node_info().
 */
function gi_content_types_node_info() {
  $items = array(
    'github_blob' => array(
      'name' => t('Github Blob'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'github_commit' => array(
      'name' => t('Github Commit'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'github_image' => array(
      'name' => t('Github Image'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'github_repo' => array(
      'name' => t('Github Repo'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Repo Display Name'),
      'help' => t('Not used for anything other than a label in lists.'),
    ),
    'github_tree' => array(
      'name' => t('Github Tree'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

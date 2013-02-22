<?php
/**
 * @file
 * gi_content_types.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function gi_content_types_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|github_blob|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'github_blob';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|github_blob|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|github_blob|teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'github_blob';
  $ds_fieldsetting->view_mode = 'teaser';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h4',
        'class' => '',
      ),
    ),
  );
  $export['node|github_blob|teaser'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|github_commit|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'github_commit';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|github_commit|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|github_tree|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'github_tree';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|github_tree|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|github_tree|teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'github_tree';
  $ds_fieldsetting->view_mode = 'teaser';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h4',
        'class' => '',
      ),
    ),
  );
  $export['node|github_tree|teaser'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function gi_content_types_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|github_blob|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'github_blob';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_repo_path',
        1 => 'title',
        2 => 'body',
        3 => 'field_image',
        4 => 'field_file',
      ),
    ),
    'fields' => array(
      'field_repo_path' => 'ds_content',
      'title' => 'ds_content',
      'body' => 'ds_content',
      'field_image' => 'ds_content',
      'field_file' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|github_blob|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|github_blob|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'github_blob';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|github_blob|teaser'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|github_commit|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'github_commit';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_commit_message',
        2 => 'field_tree',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_commit_message' => 'ds_content',
      'field_tree' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|github_commit|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|github_tree|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'github_tree';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_repo_path',
        2 => 'field_limbs',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_repo_path' => 'ds_content',
      'field_limbs' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|github_tree|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|github_tree|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'github_tree';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|github_tree|teaser'] = $ds_layout;

  return $export;
}

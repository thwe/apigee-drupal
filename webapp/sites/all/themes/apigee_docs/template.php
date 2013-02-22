<?php

/**
 * Preprocess for page.tpl.php
 */
function apigee_docs_preprocess_page(&$vars) {
  // Set proper active item in the top menu. We base on the path prefix for top
  // three menu items /enterprise, /usergrid, /apigee_api
  $copy = $active = $_GET['q'];

  $parts = explode('/', request_path(), 2);
  $prefix = $parts[0];

  if ($prefix == 'enterprise') {
    $active = 'enterprise/enterprise_home';
  }
  elseif ($prefix == 'usergrid') {
    $active = 'app_services';
  }
  elseif ($prefix == 'apigee_api' || $prefix == 'api') {
    $active = 'apigee_api';
  }

  $main_menu = variable_get('menu_main_links_source', 'main-menu');

  if ($active !== $copy) {
    menu_tree_set_path($main_menu, $active);
  }

  $vars['main_menu'] = menu_navigation_links($main_menu, 0);
  $vars['secondary_menu'] = menu_navigation_links($main_menu, 1);
  $master_container_class = array();
  // Add first element of secondary menu as "Overview link".
  if (!empty($vars['secondary_menu'])) {
    $master_container_class[] = 'master-container-secondary-menu';
  }

  if (!empty($vars['page']['breadcrumb'])) {
    $master_container_class[] = 'master-container-breadcrumb';
  }

  $vars['master_container_class'] = implode(' ', $master_container_class);

  // Add custom CSS files.
  $path = current_path();
  $css_filename = preg_replace('/[\s\W]+/', '_', $path); // Strip all non alphanumerical chars.
  if (file_exists(DRUPAL_ROOT . '/' . drupal_get_path('theme', 'apigee_docs') . '/css/' . $css_filename . '.css')) {
    drupal_add_css(drupal_get_path('theme', 'apigee_docs') . '/css/' . $css_filename . '.css', array('weight' => 100, 'group' => CSS_THEME));
  }
  // Add custom Javascript files.
  $js_filename = $css_filename; // Strip all non alphanumerical chars.
  if (file_exists(DRUPAL_ROOT . '/' . drupal_get_path('theme', 'apigee_docs') . '/js/' . $js_filename . '.js')) {
    drupal_add_js(drupal_get_path('theme', 'apigee_docs') . '/js/' . $js_filename . '.js', array('weight' => 100, 'group' => CSS_THEME));
  }
}

/**
 * Preprocess for region.tpl.php
 */
function apigee_docs_preprocess_region(&$variables, $hook) {
  if ($variables['region'] == "sidebar_second") {
    // Remove "well" class from second sidebar.
    array_pop($variables['classes_array']);
  }
}

/**
 * Implements hook_menu_breadcrumb_alter().
 *
 * Remove breadcrumb current item.
 */
function apigee_docs_menu_breadcrumb_alter(&$active_trail, $item) {
  foreach ($active_trail as $key => $active_trail_item) {
    if ($active_trail_item['link_path'] == $item['href']) {
      unset($active_trail[$key]);
    }
  }
}

/**
 * Override of theme_breadcrumb().
 */
function apigee_docs_breadcrumb($variables) {

	// Hide breadcrumbs for Api reference content type.
	if ($node = menu_get_object()) {
		if ($node->type == 'api_reference') {
			return array();
		}
	}

  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Adding the title of the current page to the breadcrumb.
    $breadcrumb[] = drupal_get_title();

    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    return '<div class="breadcrumb">' . implode(' &nbsp;>&nbsp; ', $breadcrumb) . '</div>';
  }
}

/**
 * Implements hook_js_alter().
 */
function apigee_docs_js_alter(&$javascript) {
  foreach ($javascript as &$script) {
    // Modify default inserted js by accordion_menu to add event on accordion
    // creation. We show the block and trigger javascript to
    // add float functionality.
    if ($script['type'] == 'inline' && strpos($script['data'], 'accordion') !== FALSE) {
      $script['data'] = str_replace('accordion({', 'accordion({ create: function(event, ui) { jQuery(this).parent().show(); Drupal.apigeeStructureBlock(); },', $script['data']);
    }
  }
}

function apigee_docs_preprocess_rate_template_yesno(&$variables){
  $variables['title_prefix'] = '<strong class="rate-yesno-title">Was this helpful? </strong>';
  unset($variables['info']);
  $variables['buttons'][0] = preg_replace('/(?<=<\/a>)\d+/', '', $variables['buttons'][0]);
  $variables['buttons'][1] = preg_replace('/(?<=<\/a>)\d+/', '', $variables['buttons'][1]);

  $class_yes = $class_no = 'class="btn rate-button rate-yesno-btn"';
  if ($variables['results']['user_vote'] == $variables['links'][0]['text']) {
    $class_yes = 'class="btn rate-button rate-yesno-btn rate-yesno-clicked"';
  }
  if ($variables['results']['user_vote'] == $variables['links'][1]['text']) {
    $class_no = 'class="btn rate-button rate-yesno-btn rate-yesno-clicked"';
  }
  $variables['buttons'][0] = preg_replace('/class="[^"]*"/', $class_yes, $variables['buttons'][0]);
  $variables['buttons'][1] = preg_replace('/class="[^"]*"/', $class_no, $variables['buttons'][1]);
}

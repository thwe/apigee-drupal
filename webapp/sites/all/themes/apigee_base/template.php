<?php

$theme_path = drupal_get_path('theme', 'apigee_base');
include_once($theme_path . '/includes/apigee_base.inc');
include_once($theme_path . '/includes/modules/theme.inc');
include_once($theme_path . '/includes/modules/form.inc');
include_once($theme_path . '/includes/modules/menu.inc');
include_once($theme_path . '/includes/modules/views.inc');

/**
 * hook_theme()
 */
function apigee_base_theme() {
  return array(
    'apigee_base_links' => array(
      'variables' => array('links' => array(), 'attributes' => array(), 'heading' => NULL),
    ),
    'apigee_base_btn_dropdown' => array(
      'variables' => array('links' => array(), 'attributes' => array(), 'type' => NULL),
    ),
  );
}

/**
 * Preprocess variables for html.tpl.php
 *
 * @see system_elements()
 * @see html.tpl.php
 */
function apigee_base_preprocess_html(&$variables) {
   // Try to load the library, if the apigee_base_ui module is in use.
  if (module_exists('apigee_base_ui')) {
    $library = libraries_load('apigee_base', 'minified');
  }
}

/**
 * Override theme_breadrumb().
 *
 */
function apigee_base_breadcrumb($variables) {
  if (!theme_get_setting('toggle_breadcrumbs')) {
    return;
  }


  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Adding the title of the current page to the breadcrumb.
    $breadcrumb[] = drupal_get_title();

    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $output .= '<div class="breadcrumb">' . implode(' &nbsp;/&nbsp; ', $breadcrumb) . '</div>';
    return $output;
  }
}

/**
 * Preprocess variables for region.tpl.php
 *
 * @see region.tpl.php
 */
function apigee_base_preprocess_region(&$variables, $hook) {
  if ($variables['region'] == 'content') {
    $variables['theme_hook_suggestions'][] = 'region__no_wrapper';
  }

  if ($variables['region'] == "sidebar_first") {
    $variables['classes_array'][] = 'well';
  }

  if ($variables['region'] == "sidebar_second") {
    $variables['classes_array'][] = 'well';
  }
}

/**
 * Preprocess variables for node.tpl.php
 *
 * @see node.tpl.php
 */
function apigee_base_preprocess_node(&$variables) {
  if ($variables['teaser']) {
    $variables['classes_array'][] = 'row-fluid';
  }

  $author = $variables['name'];
  $time_ago_short = format_interval((time() - $variables['created']) , 1) . t(' ago');
  $time_ago_long = format_interval((time() - $variables['created']) , 2) . t(' ago');

  // Add some date variables
  if ($variables['type'] = 'blog') {
    if ($variables['uid'] != 0){
      $variables['posted'] = 'Posted by ' . $author . '&nbsp;|&nbsp;about&nbsp;' . $time_ago_short;
    }
    else{
      $variables['posted'] = 'Posted ' . $time_ago_short;
    }
    $variables['submitted_day'] = format_date($variables['node']->created, 'custom', 'j');
    $variables['submitted_month'] = format_date($variables['node']->created, 'custom', 'M');
  }

  if ($variables['type'] == 'forum') {
    $variables['submitted'] = 'Topic created by: ' . $author . '&nbsp;&nbsp;' . $time_ago_long;
  }
}

/**
 * Preprocess variables for comment.tpl.php
 *
 * @see node.tpl.php
 */
function apigee_devconnect_preprocess_comment(&$variables) {

  // Comment Submitted Variables
  $variables['comment_author'] = $variables['elements']['#comment']->uid;
  $author_details = user_load(array('uid'=>$variables['comment_author']));
  $variables['author_first_name'] = $author_details->field_first_name['und'][0]['safe_value'];
  $variables['author_last_name'] = $author_details->field_last_name['und'][0]['safe_value'];
  $variables['author_email'] = $author_details->mail;
  $variables['submitted'] = $variables['author_first_name'] . '&nbsp;' . $variables['author_last_name'] . '&nbsp;|&nbsp;' . '<a href="mailto:' . $variables['author_email'] . '">' . $variables['author_email'] . '</a>';
}

/**
 * Preprocess variables for block.tpl.php
 *
 * @see block.tpl.php
 */
function apigee_base_preprocess_block(&$variables, $hook) {
  $variables['title_attributes_array']['class'][] = 'block-title';
}


/**
 * Preprocess variables for page.tpl.php
 *
 * @see page.tpl.php
 */
function apigee_base_preprocess_page(&$variables) {

  $variables['user_reg_setting'] = variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL);

  if (module_exists('apachesolr')) {
    // todo: $searchTerm is undefined, so this parameter will always be empty
    $search = drupal_get_form('search_form', NULL, (isset($searchTerm) ? $searchTerm : ''));
    $search['basic']['keys']['#size'] = 20;
    $search['basic']['keys']['#title'] = '';
    unset($search['#attributes']);
    //$search['#action'] = base_path() . 'search/site'; // breaks apachesolr searching
    $search_form = drupal_render($search);
    $find = array('type="submit"', 'type="text"');
    $replace = array('type="hidden"', 'type="search" placeholder="search" autocapitalize="off" autocorrect="off"');
    $vars['search_form'] = str_replace($find, $replace, $search_form);
  }

  // Add information about the number of sidebars.
  if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    $variables['columns'] = 3;
  }
  elseif (!empty($variables['page']['sidebar_first'])) {
    $variables['columns'] = 2;
  }
  elseif (!empty($variables['page']['sidebar_second'])) {
    $variables['columns'] = 2;
  }
  else {
    $variables['columns'] = 1;
  }

  // Custom Search
  $variables['search'] = FALSE;
  if (theme_get_setting('toggle_search') && module_exists('search')) {
    $variables['search'] = drupal_get_form('search_form');
  }

  // Primary nav
  $variables['primary_nav'] = FALSE;
  if ($variables['main_menu']) {
    // Build links
    $tree = menu_tree_page_data(variable_get('menu_main_links_source', 'main-menu'));
    $variables['main_menu'] = apigee_base_menu_navigation_links($tree);

    // Build list
    $variables['primary_nav'] = theme('apigee_base_links', array(
      'links' => $variables['main_menu'],
      'attributes' => array(
        'id' => 'main-menu',
        'class' => array('nav'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    ));
  }

  // Make sure the menu module is in use before setting menu vars.
  if (module_exists('menu')) {
    // Primary nav
    $variables['primary_nav'] = FALSE;
    if ($variables['main_menu']) {
      // Build links
      $tree = menu_tree_page_data(variable_get('menu_main_links_source', 'main-menu'));
      $variables['main_menu'] = apigee_base_menu_navigation_links($tree);

      // Build list
      $variables['primary_nav'] = theme('apigee_base_links', array(
        'links' => $variables['main_menu'],
        'attributes' => array(
          'id' => 'main-menu',
          'class' => array('nav'),
        ),
        'heading' => array(
          'text' => t('Main menu'),
          'level' => 'h2',
          'class' => array('element-invisible'),
        ),
      ));
    }

    // Secondary nav
    $variables['secondary_nav'] = FALSE;
    if ($variables['secondary_menu']) {
      $secondary_menu = menu_load(variable_get('menu_secondary_links_source', 'user-menu'));

      // Build links
      $tree = menu_tree_page_data($secondary_menu['menu_name']);
      $variables['secondary_menu'] = apigee_base_menu_navigation_links($tree);

      // Build list
      $variables['secondary_nav'] = theme('apigee_base_btn_dropdown', array(
        'links' => $variables['secondary_menu'],
        'label' => $secondary_menu['title'],
        'type' => 'success',
        'attributes' => array(
          'id' => 'user-menu',
          'class' => array('pull-right'),
        ),
        'heading' => array(
          'text' => t('Secondary menu'),
          'level' => 'h2',
          'class' => array('element-invisible'),
        ),
      ));
    }

    // Replace tabs with dropw down version
    $variables['tabs']['#primary'] = _apigee_base_local_tasks($variables['tabs']['#primary']);
  }
}

/**
 * Returns the correct span class for a region
 */
function _apigee_base_content_span($columns = 1) {
  $class = FALSE;

  switch ($columns) {
    case 1:
      $class = 'span24';
      break;
    case 2:
      $class = 'span18';
      break;
    case 3:
      $class = 'span12';
      break;
  }

  return $class;
}

/**
 * Returns HTML for a query pager. Override of theme_pager().
 *
 * Overridden to change some class names. Bootstrap uses some of the same
 * classes for different types of elements, and offers other classes are used
 * for pagers. In particular, the 'pager' class (used in core) is for rounded
 * buttons, while Bootstrap uses the 'pagination' class for multi-button pagers
 * like these.
 *
 * Also format the current page number as a link so that it will be themed like
 * the other links around it.
 *
 * @param $vars
 *   An associative array containing:
 *   - tags: An array of labels for the controls in the pager.
 *   - element: An optional integer to distinguish between multiple pagers on
 *     one page.
 *   - parameters: An associative array of query string parameters to append to
 *     the pager links.
 *   - quantity: The number of pages in the list.
 *
 * @ingroup themeable
 */
function apigee_base_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('« first')), 'element' => $element, 'parameters' => $parameters));
  $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t('next ›')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('last »')), 'element' => $element, 'parameters' => $parameters));

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => array('pager-first'),
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array('prev'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('active'), // Add the active class
            'data' => l($i, '#', array('fragment' => '', 'external' => TRUE)),
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
          );
        }
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array('next'),
        'data' => $li_next,
      );
    }
    if ($li_last) {
      $items[] = array(
        'class' => array('pager-last'),
        'data' => $li_last,
      );
    }

    return '<div class="pagination">' . theme('item_list', array(
      'items' => $items,
      // pager class is used for rounded, bubbly boxes in Bootstrap
      //'attributes' => array('class' => array('pager')),
    )) . '</div>';
  }
}

/**
 * Implementation of hook_preprocess().
 *
 * As early as possible in the theming process, check for apachesolr search URL,
 * and redirect to site search instead (apachesolr will still run the search).
 *
 * @param $vars
 * @param $hook
 */
function apigee_base_preprocess($vars, $hook) {
  static $checked_url = FALSE;
  if (!$checked_url) {
    $args = arg();
    if (count($args) == 3 && $args[0] == 'search' && $args[1] == 'apachesolr_search') {
      drupal_goto('search/site/' . urlencode($args[2]));
    }
    $checked_url = TRUE;
  }
}

function apigee_base_form_search_form_alter(&$form, &$form_state) {
  $form['#attributes']['class'][] = 'navbar-search';
  $form['#attributes']['class'][] = 'pull-right';
  $form['basic']['keys']['#title'] = '';
  $form['basic']['keys']['#attributes']['class'][] = 'search-query';
  $form['basic']['keys']['#attributes']['class'][] = 'span2';
  $form['basic']['keys']['#attributes']['placeholder'] = t('Search');

  $form['basic']['submit']['#value'] = t('Search');
  $form['basic']['submit']['#attributes']['style'] = 'display:none';

  $default_search = variable_get('search_default_module', 'site');
  if ($default_search == 'apachesolr_search') {
    $default_search = 'site';
  }

  if ($default_search == 'site') {
    unset($form['basic']['#type']);
    unset($form['basic']['#attributes']);
    $form += $form['basic'];
    unset($form['basic']);
    unset($form['action']);
    $form['#submit'] = array('apigee_base_search_form_submit');
  }
}

function apigee_base_search_form_submit($form, &$form_state) {
  if (!empty($form_state['values']['keys'])) {
    $default_search = variable_get('search_default_module', 'site');
    if ($default_search == 'apachesolr_search') {
      $default_search = 'site';
    }
    $form_state['redirect'] = 'search/' . $default_search . '/' . $form_state['values']['keys'];
  }
}


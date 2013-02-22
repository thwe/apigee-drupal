<?php
/**
 * @file
 * Default theme implementation to display list of developer apps.
 *
 * Available variables:
 * $user - fully-populated user object (stdClass)
 * $application_count - number of applications registered to the user
 * $applications - array of arrays, each of which has the following keys:
 *  - app_name
 *  - callback_url
 *  - app_keys
 *  - delete_url
 */
?>
<?php
  // Set Title
  drupal_set_title('My Apps');

  // Build Breadcrumbs
  $breadcrumb = array();
  $breadcrumb[] = l('Home', '<front>');

  // Set Breadcrumbs
  drupal_set_breadcrumb($breadcrumb);

?>
<?php print l('Add a new app', 'user/' . $user->uid . '/apps/add', array('attributes' => array('class' => array('add-app')))); ?>

<form class="form-stacked">

<?php if ($application_count) : ?>

<h2>These are your apps!</h2>
<h3>Add more, edit or delete them as you like.</h3>
<hr>

<?php
  foreach ($applications as $app) {
    print '<div class="app-content"><h4 class="app-title">' . l($app['app_name'], 'user/' . $user->uid . '/app-detail/' . $app['app_name']) . '</h4>';
    if ($app['attributes']['Description']) {
      print '<div class="app-desc">' . check_plain($app['attributes']['Description']) . '</div>';
    }
    print '</div>';

    print '<div class="app-delete">';
    print '<button class="btn primary action button-processed" title="Delete App" data-url="' . $app['delete_url'] . '"></button>';
    print '</div>';
    print '<br><hr>';
  }
?>
<?php else: ?>
	<h2>Looks like you don’t have any apps</h2>
  <h3>Get started by adding one.</h3>
<?php endif; ?>
</form>

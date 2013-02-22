<?php

/**
 * undocumented function
 *
 * @return void
 * @author Tom Stovall
 **/
function gi_settings_form() {
	
	module_load_include("module", "ctools", "ctools");
    // Include the CTools tools that we need.
    ctools_include('ajax');
    ctools_include('modal');

    // Add CTools' javascript to the page.
    ctools_modal_add_js();

	drupal_add_js(drupal_get_path("module", "gi")."/gi.admin.js");
	
	$form = array(
		"#type" => "form",
		"#attributes" => array(
	      "id" => "gi_settings_form",
	    ),
	);
	
	
	
	return $form;
}


<?php

function gi_commit_list() {

  $query = new EntityFieldQuery;
  $result = $query
	->entityCondition('entity_type', 'node')
	->propertyCondition('type', 'github_repo')
	->execute();

  if (!empty($result['node'])) {
    $repos = array_keys($result['node']);
  }
  else {
    $repos = array();
  }


  $toReturn = "";
	if (count($repos) >= 1 ){
		foreach ($repos as $weight => $nid) {
	    $repo = new GIGithubRepo(array("nid" => $nid));
	    $toReturn .= drupal_render(drupal_get_form("gi_commit_list_form", $repo));
	  }
	} else {
		$toReturn = "<p>You currently don't have any repos to import. Would you like to <a href='".base_path()."node/add/github-repo?destination=admin/content/gi'>Add One</a>?</p>";
	}



 /* if (user_access("administer github importer") && module_exists('ctools')) {
    $form['actions']['add_repo'] = array(
      "#type" => "button",
      "#value" => t("Add New Repo"),
      "#attributes" => array(
        "class" => array("btn"),
        "onclick" => "document.location.href = '" . base_path() . "node/add/github-repo?destination=admin/content/gi'; return (false);",
      ),
    );
  } */

  return $toReturn;
}

function gi_commit_list_submit($form, $form_state) {
  $repo = new GIGithubRepo(array("nid" => $form_state['values']['nid']));
  $toReturn = array();
  foreach ($form_state['values']['commits'] as $key => $sha) {
    if ($sha != FALSE) {
      // grab commit info, translate it to a node object
      $commit = $repo->getCommit($sha);
      if ($commit->nid) {
        $toReturn[] = "Commit Imported::<b>{$commit->title}</b> (NID:$commit->nid)";
      }
    }
  }
  drupal_set_message("This(these) commit(s) have been imported.<br>Their Tree(s) will begin importing when the next cron runs.</p><ul><li>" . implode("</li><li>", $toReturn) . "</li></ul>", "notice");
  drupal_goto("admin/content/node");
}

function gi_commit_list_form($form, $form_state) {
  $repo = $form_state['build_info']['args'][0];
  $form = array(
    "#type" => "form",
    "#attributes" => array(
      "id" => "gi_commit_list_form_" . $repo->nid,
      "class" => array("gi_commit_list_form"),
    ),
  );
  $fieldset = array(
    "#type" => "fieldset",
    "#title" => $repo->node->title,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $header = array(
    "title" => array("data" => t("Commit Message")),
    "commiter" => array("data" => t("Committer")),
    "date" => array("data" => t("Date")),
  );
  $options = array();
  foreach ($repo->commitList as $key => $row) {
    $options[$row['sha']] = array(
      "title" => check_plain($row['commit']['message']),
      "commiter" => $row['commit']['author']['name'],
      "date" => $row['commit']['author']['date'],
    );
  }
  $fieldset['commits'] = array(
    "#type" => "tableselect",
    "#header" => $header,
    "#options" => $options,
    "#empty" => t("No Info Available"),
  );
  $form[$repo->user . "-" . $repo->repo] = $fieldset;
  $form['nid'] = array(
    "#type" => "hidden",
    "#value" => $repo->nid,
  );
  $form['actions'] = array("#type" => "actions");
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Import Commit(s)"),
    '#weight' => 10,
    '#submit' => array("gi_commit_list_submit"),
  );
  return $form;
}

function gi_import_list_form() {
	  $path = drupal_get_path("module", "gi");
	  drupal_add_js($path . "/js/gi.js");
	  drupal_add_css($path . "/css/gi.css");
	$trees = _gi_get_unimported_trees();
	
	if (count($trees)) {
		return _gi_get_edit_tree_list(node_load_multiple($trees, null, true));
	} else {
		return "<h4>Nothing to be imported</h4>";
	}
 
}


function gi_import_now_ajax($node) {
	

	
	if (is_object($node)) {
		$tree = new GIGithubTree(array("nid" => $node->nid));
		$tree->import();
		
	}

	echo gi_import_list_form();
	exit();
}

function _gi_get_edit_tree_list($trees) {
	$rows = array();
    $headers = array(
	    "title" => array("data" => t("Tree Name")),
		"progress" => array("data" => t("Import Progress"))
	  );
	  foreach ($trees as $tree) {
	    $rows[] = array(
	    	"data" => array(
	    		"title" => check_plain($tree->title),
				"progress" => "<progress value=0 max=100 style='display:none;'></progress>"
	    	),
	        "data-nid" => $tree->nid
	    );
	  }
	  
	
	return theme("table", array("attributes" => array("id" => "gi_import_now_list"), "header" => $header, "rows" => $rows));
}


function _gi_get_unimported_trees() {
	$query = new EntityFieldQuery;
  
	$result =  $query
		->entityCondition('entity_type', 'node')
		->propertyCondition('type', 'github_tree')
		->fieldCondition('field_imported', "value", 0, "=")
		->execute();

	if (count($result['node'])) {		
    	return array_keys($result['node']);
  	}
	else return array();
}


function theme_gi_tree_list($trees) {
	
  $path = drupal_get_path("module", "gi");
  drupal_add_js($path . "/js/gi.js");
  drupal_add_css($path . "/css/gi.css");

  if (is_array($trees)) {
	$nodes = node_load_multiple($trees);
  }
  foreach ($nodes as $nid => $node) {
	$rows[] = array("data" => array("<h2>".$node->title."</h2>"), "data-nid" => $nid);
  }
  return theme("table", array("rows" => $rows, "attributes" => array("class" => array("gi-import-now"))));
  
}



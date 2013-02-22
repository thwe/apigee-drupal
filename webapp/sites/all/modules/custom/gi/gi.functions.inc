<?php
/**
 * make json call and return data results
 *
 * @param string $action 
 * @return array or false
 * @author stovak
 */
function gi_call($action) {
  $response = drupal_http_request($action, array(
      CURLOPT_SSL_VERIFYPEER => FALSE,
      CURLOPT_RETURNTRANSFER => TRUE,
      CURLOPT_HTTPHEADER => array(
        "Accept: application/json; charset=utf-8",
        "Content-Type: application/json; charset=utf-8",
      ),
    )
  );	
  if (in_array($response->code, array(200, 201, 202, 203, 204, 205, 206))) {
    return drupal_json_decode($response->data);
  }
  else {
    watchdog("gi", __FUNCTION__, array("response" => $response));
    return FALSE;
  }
}
/**
 * Add entry to tree parent referencing node
 *
 * @param string $nid 
 * @param string $pnid 
 * @return void
 * @author stovak
 */

function _gi_add_parent($nid, $pnid) {
  $count = db_query("select count(*) from field_revision_field_limbs where bundle = 'github_tree' and entity_type = 'node' and entity_id = :pnid and field_limbs_nid = :nid", array("nid" => $nid, "pnid" => $pnid))->fetchField();
  if ($count == 0) {
    $parent = node_load($pnid);
    $parent->field_limbs["und"][] = array("nid" => $node->nid);
    node_save($parent);
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 *  Node lookup by sha
 *
 * @param string $ref
 *
 * @return void
 * @author stovak
 */
function _gi_find_node_by_sha($ref) {
  $nodes  = array();
  $query  = new EntityFieldQuery;
  $result = $query->entityCondition('entity_type', 'node')->propertyCondition('type', 'github_' . $ref->type)->propertyCondition('sha', $ref->sha)->execute();

  if (!empty($result['node'])) {
    $nodes = node_load_multiple(array_keys($result['node']));
  }
  if (count($nodes)) {
    return array_shift($nodes);
  }
  else {
    return (object)array(
      "type" => 'github_' . $ref->type,
      "sha" => $ref->sha,
      "title" => $ref->path,
    );
  }
}

/**
 * Translate json to commit node
 *
 * @param string $commit
 *
 * @return node object ready to save
 * @author stovak
 */
function _gi_json_to_node_data_commit($commit) {
  return (object)array(
    "type" => "github_commit",
    "title" => substr($commit['message'], 0, 100),
	"language" => LANGUAGE_NONE,
    "sha" => $commit['sha'],
    "field_tree_url" => array(LANGUAGE_NONE => array(array("url" => $commit['tree']['url']))),
    "field_tree_sha" => array(LANGUAGE_NONE => array(array("value" => $commit['tree']['sha']))),
    "field_commit_message" => array(LANGUAGE_NONE => array(array("value" => $commit['message']))),
  );
}

/**
 * Translate json to tree node
 *
 * @param string $tree
 * @param string $path
 *
 * @return node object ready to save
 * @author stovak
 */
function _gi_json_to_node_data_tree($tree, $path) {
  return (object)array(
    "type" => "github_tree",
	"language" => LANGUAGE_NONE,
    "title" => $path,
    "sha" => $tree['sha'],
    "field_tree_url" => array(LANGUAGE_NONE => array(array("url" => $tree['url']))),
  );
}

/**
 * translate json to blob node
 *
 * @return void
 * @author stovak
 **/
function _gi_json_to_node_data_blob($blob, $path) {

  return (object)array(
    "type" => "github_blob",
 	"language" => LANGUAGE_NONE,
   "title" => $path,
    "sha" => $blob['sha'],
    "field_tree_url" => array(LANGUAGE_NONE => array(array("url" => $blob['tree']['url']))),
    "body" => array(
      LANGUAGE_NONE => array(
        array(
          'value' => base64_decode($blob['content']),
          'format' => "plain_text",
        ),
      ),
    ),
  );
}


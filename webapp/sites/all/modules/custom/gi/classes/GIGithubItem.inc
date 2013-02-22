<?php
class GIGithubItem {

/**
 *  node ID of the imported object
 *
 * @var string
 */

public $node;

/**
 *  response data converted to array
 *
 * @var array
 */

public $itemData;

/**
 *  whether or not to write results to watchdog table
 *
 * @var string
 */

public $debug;

/**
 * make json call and return data results
 *
 * @param string $action
 *
 * @return array or false
 * @author stovak
 */

public $__lastResponse; function __construct($action = "", $debug = FALSE) {
  $this->debug = $debug;
  $this->itemData = $this->__callRemoteAction($action);
  }

  /**
   * REST call to remote URL. If no URL supplied, use item default url
   *
   * @param string $action
   * @param string $method
   * @param string $post_vars
   *
   * @return void
   * @author Tom Stovall
   */
  function __callRemoteAction($action = NULL, $method = "GET", $post_vars = array()) {
    if ($action == NULL) {
      $action = $this->url;
    }
    $this->__lastResponse = drupal_http_request($action, array(
        "headers" => array(
		  "accept" => "application/json; charset=utf-8",
		  "Content-Type" => "application/json; charset=utf-8"
        ),
        "method" => $method,
		"data" => http_build_query($post_vars)
      )
    );
    if (in_array($this->__lastResponse->code, array(200, 201, 202, 203, 204, 205, 206))) {
      return drupal_json_decode($this->__lastResponse->data);
    }
    else {
      if ($this->debug) {
        watchdog("gi", __FUNCTION__, array("response" => $this->__lastResponse));
      }
      return FALSE;
    }
  }

  /**
   * Add entry to tree parent referencing node
   *
   * @param string $nid  (node)
   * @param string $pnid (parent)
   *
   * @return void
   * @author stovak
   */
  function _add_parent($nid, $pnid) {
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
  function _find_by_sha() {
    $query = new EntityFieldQuery;
    $result = $query
		->entityCondition('entity_type', 'node')
		->propertyCondition('type', 'github_' . $this->type)
		->propertyCondition('sha', $this->sha)
		->execute();


    if (!empty($result['node'])) {
      $this->nid = array_shift(array_keys($result['node']));
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * set node id if duplicate repo path is found
   *
   * @return void
   * @author Tom Stovall
   **/
  function _find_by_repo_path() {
    $source = 	db_select('url_alias', "u")
			->fields("u", array("alias", "source"))
			->condition("u.alias", "node/".$this->path)
			->execute()
			->fetchObject()
			->source;
    if (!empty($source)) {
      $this->nid = (int)str_replace("node/", "", $source);
      return TRUE;
    } else {
      return FALSE;
    }
  }

  /**
   * Save this object as a node
   *
   * @param string $commit
   *
   * @return node object ready to save
   * @author stovak
   */
  function __toNode() {
    // attempt to find an existing node by SHA and Repo Location
    if ($this->_find_by_sha() || $this->_find_by_repo_path()) {
      $this->revision = TRUE;
    }
    node_save($this->node);
  }

  /**
   * copies array values to their corresponding item property
   *
   * @param string $arr
   *
   * @return void
   * @author Tom Stovall
   */
  function _array_to_item_properties($arr) {
    foreach ($arr as $key => $arg) {
      $this->__set($key, $arg);
    }
  }

  function __get($name) {
    if (is_array($this->node->{$name}) && !empty($this->node->{$name}[LANGUAGE_NONE][0])) {
      return array_shift(array_values($this->node->{$name}[LANGUAGE_NONE][0]));
    }
    elseif ($name == "path") {
	    if (is_array($this->node->path)) {
			return $this->node->path->alias;
		} elseif($this->node->nid) {
			return db_select('url_alias', "u")
				->fields("u", array("alias", "source"))
				->condition("u.source", "node/".$this->node->nid)
				->execute()
				->fetchObject()
				->alias;
		} else {
			return false;
		}
    }
    else return $this->node->{$name};
  }

  function __set($name, $value) {
	if (!is_object($this->node)) {
      $this->node = new stdClass();
    }
	switch ($name) {
		
		case "path":
				$this->node->path = array(
				  	"pathauto" => false,
				    "alias" => strtolower($value)
				  );
			break;
		
		case "nid":
		 		if ((int)$value !== 0) {
					$this->node->nid = $value;
				}
			break;
			
		case "field_url":
		case "field_tree_url":
				$this->node->{$name}[LANGUAGE_NONE][]["url"] = $value;
			break;
		
		
		default:
			if (substr($name, 0, 5) == "field") {
		      if (!is_array($this->node->{$name})) {
		        $this->node->{$name} = array();
		      }
		     
		     $this->node->{$name}[LANGUAGE_NONE][]['value'] = $value;
		    }
		    else $this->node->{$name} = $value;
		  }
		
	}
	

    



}


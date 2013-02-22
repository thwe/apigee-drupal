<?php
class GIGithubCommit extends GIGithubItem {


  public $tree; 

  function __construct($action) {
	global $user;
    parent::__construct($action);

    $this->_array_to_item_properties(array(
      "type" => "github_commit",
      "language" => LANGUAGE_NONE,
      "is_new" => true,
      "title" => substr($this->itemData['message'], 0, 100),
      "sha" => $this->itemData['sha'],
	  "uid" => $user->uid,
      "field_tree_url" => $this->itemData['tree']['url'],
      "field_tree_sha" => $this->itemData['tree']['sha'],
      "field_commit_message" => $this->itemData['message'],
    ));

    if ($this->itemData != NULL) {
      $this->itemData['tree']['title'] = "Commit Root: ".$this->sha;
	  $aURL = explode("/", str_replace("https://api.github.com/", "", $this->itemData['url']));
      $this->itemData['tree']['path'] = "repos/".$aURL[1]."/".$aURL[2];
	  $this->itemData['tree']['uid'] = $this->uid;

      $this->tree = new GIGithubTree($this->itemData['tree']);
      $this->node->field_tree = array(LANGUAGE_NONE => array(array("nid" => $this->tree->nid)));
    }
	$this->__toNode();
  }

  function __toNode() {
    return node_save($this->node);
  }
}


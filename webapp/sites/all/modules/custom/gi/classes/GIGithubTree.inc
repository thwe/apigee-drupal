<?php



class GIGithubTree extends GIGithubItem {
	
	public $fileList = array();
	public $importedNodes = array();
	
	function __construct($args) {
		global $user;
		if (array_key_exists("nid", $args)) {
			$this->node = node_load($args['nid'], null, true);
			$this->nid = $args['nid'];
			parent::__construct($this->field_tree_url);
			if (is_array($this->itemData['tree'])) {
				$this->fileList = $this->itemData['tree'];
			}
			if (!is_array($this->field_limbs)){
				$this->field_limbs = array();
			}
		} else {
			$this->_array_to_item_properties($args);
			parent::__construct();
			$this->__toNode();
		}
	}
	
	function __toNode() {
		$this->node->type = "github_tree";
		$this->node->language = LANGUAGE_NONE;
		$this->field_tree_url = $this->url;
		if (!is_array($this->node->path)){
			$this->node->path = array(
				"pathauto" => false,
				"alias" => $this->node->path
			);
		}
		
		node_save($this->node);
		return $this->nid;
	}
	
	function import() {
		if (substr($this->title, 0, 11) != "Commit Root") {
			$base_repo_path = $this->path."/".$this->title;
		} else {
			$base_repo_path = $this->path;
		}
		foreach($this->fileList as $key => $item) {
			if ( substr($item['path'], 0, 1) == "." ) {
				unset($this->fileList[$key]);
				continue;
			}
			$item['title'] = $item['path'];
			$item['path'] = $base_repo_path. "/".$item['title'];
			$item['uid'] = $this->uid;
			$className = "GIGithub".ucfirst($item['type']);			
			$this->importedNodes[$item['sha']] = new $className($item);
			$this->node->field_limbs[LANGUAGE_NONE][]["nid"] = $this->importedNodes[$item['sha']]->nid;
		}
		
		$this->node->field_imported = array(LANGUAGE_NONE => array(array("value" => 1)));
		node_save($this->node);
	}
	
}
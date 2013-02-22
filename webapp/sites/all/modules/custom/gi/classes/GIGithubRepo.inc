<?php

define("GITHUB_API_ENDPOINT", "https://api.github.com/repos");


class GIGithubRepo extends GIGithubItem {
	
	var $commitList = array();
	var $user;
	var $repo;	
	var $node;
	var $url;
	var $importedCommits = array();
	/**
	 *  constructor
	 *
	 * @author Tom Stovall
	 * either supply an array with User/Repo or a NID.
	 * User/Repo combination creates new node
	 * nid retrieves existing node
	 */
	
	function __construct() {
		$args = array_shift(func_get_args());
		$this->_array_to_item_properties($args);
		if ($this->nid) {
			$this->node = node_load($this->nid, null, true);
			$this->__fromNode();
		} 
		$this->commitList = $this->__callRemoteAction( $this->url . "/commits", "GET");
	}
	
	function __fromNode() {
		foreach (array("user", "repo") as $thisProp) {
			$nodeProp = "field_".$thisProp;
			$this->$thisProp = array_shift(array_values($this->node->{$nodeProp}[LANGUAGE_NONE][0]));
		}
		$this->url = GITHUB_API_ENDPOINT ."/". $this->user ."/". $this->repo;
	}
	
	function getRepoInfo() {
		return $this->__callRemoteAction();
	}
	
	function getCommit($sha) {
		$this->importedCommits[$sha] = new GIGithubCommit($this->url."/git/commits/".$sha);
		if (empty($this->node->field_commits)) {
			$this->node->field_commits = array(LANGUAGE_NONE => array(array("nid" => $this->importedCommits[$sha]->node->nid)));
		} else {
			$this->node->field_commits[LANGUAGE_NONE][] = array("nid" => $this->importedCommits[$sha]->node->nid);
		}
		node_save($this->node);
		return $this->importedCommits[$sha];
	}
	
}
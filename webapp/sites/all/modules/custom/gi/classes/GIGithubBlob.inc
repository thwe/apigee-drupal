<?php
class GIGithubBlob extends GIGithubItem {
function __construct($args) {
  if (array_key_exists("nid", $args)) {
    $this->node = node_load($args['nid'], NULL, TRUE);
    }
    else {
	  $this->_array_to_item_properties($args);
      $this->type = "github_blob";
      $this->language = LANGUAGE_NONE;
      $this->is_new = TRUE;
      parent::__construct($args['url']);
      $this->handleContent($args);
	  $this->__toNode();
    }
  }


  function handleContent($args) {

    $extension = array_pop(explode(".", $args['path']));
    switch ($extension) {
      case "ico":
      case "jpg":
      case "png":
      case "gif":
        $file = file_save_data(base64_decode($this->itemData['content']), "public://" . $args['title']);
        $this->node->field_image = array(LANGUAGE_NONE => array(array("fid" => $file->fid)));
        break;


	  case "inv":
		// do nothing with the content
		break;
        

      case "html":
			$d = new DOMDocument();
		    $d->formatOutput = TRUE;
		    @$d->loadHTML(base64_decode($this->itemData['content']));
		    $xpathsearch = new DOMXPath($d);
			$body = $xpathsearch->query("/html/body")->item(0);
			$text = str_replace(array("<body>", "</body>"), "", $d->saveXML($body));
	        $this->node->body = array(
	          LANGUAGE_NONE => array(
	            array(
	              'value' => base64_decode($text),
	              'format' => "full_html",
	            ),
	          ),
	        );
        break;

      case "rst":
        $this->node->body = array(
          LANGUAGE_NONE => array(
            array(
              'value' => base64_decode($this->itemData['content']),
              'format' => "rst",
            ),
          ),
        );
        break;

      case "md":
        $this->node->body = array(
          LANGUAGE_NONE => array(
            array(
              'value' => base64_decode($this->itemData['content']),
              'format' => "markdown",
            ),
          ),
        );
        break;

      default:
        $this->node->body = array(
          LANGUAGE_NONE => array(
            array(
              'value' => base64_decode($this->itemData['content']),
              'format' => "plain_text",
            ),
          ),
        );
    }
  }
}


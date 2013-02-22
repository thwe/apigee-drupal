<?php
/**
 * @file
 * devconnect_footer.features.node_export_features.inc
 */

/**
 * Implements hook_node_export_features_default().
 */
function devconnect_footer_node_export_features_default() {
  $node_export = array(
  'code_string' => 'array(
  array(
    \'vid\' => \'178\',
    \'uid\' => \'7\',
    \'title\' => \'Privacy Policy\',
    \'log\' => \'\',
    \'status\' => \'1\',
    \'comment\' => \'1\',
    \'promote\' => \'0\',
    \'sticky\' => \'0\',
    \'sha\' => NULL,
    \'vuuid\' => \'2d64f09e-9f6c-cc64-c151-501933578827\',
    \'ds_switch\' => \'\',
    \'nid\' => \'178\',
    \'type\' => \'page\',
    \'language\' => \'und\',
    \'created\' => \'1328763802\',
    \'changed\' => \'1333750789\',
    \'tnid\' => \'0\',
    \'translate\' => \'0\',
    \'uuid\' => \'42114b41-f7b8-a9e4-25f9-9f25bb486c65\',
    \'revision_timestamp\' => \'1333750789\',
    \'revision_uid\' => \'2\',
    \'body\' => array(
      \'und\' => array(
        \'0\' => array(
          \'value\' => \'<h3>Editing your Privacy Policy.</h3><ul style="font-size: 10px; font-weight: normal;"><li>Log in to your portal as a user with admin or content creation privileges.</li><li>Navigate to the Privacy Policy page</li><li>Using the Edit Tab you can edit the content of this page.</li></ul><p style="font-size: 10px; font-weight: normal;">&nbsp;</p><p style="font-size: 10px; font-weight: normal;"><strong>Alternate Method:</strong></p><ul style="font-size: 10px; font-weight: normal;"><li>Log in to your portal as a user with admin or content creation privileges.</li><li>Select Content from the black Drupal menu at the top of the page.</li><li>Select the&nbsp;<em>Privacy Policy</em>&nbsp;page from the list and select edit.</li><li>Make your changes and save the page.</li></ul>\',
          \'summary\' => \'\',
          \'format\' => \'filtered_html\',
          \'safe_value\' => \'<h3>Editing your Privacy Policy.</h3>
<ul><li>Log in to your portal as a user with admin or content creation privileges.</li>
<li>Navigate to the Privacy Policy page</li>
<li>Using the Edit Tab you can edit the content of this page.</li>
</ul><p> </p>
<p><strong>Alternate Method:</strong></p>
<ul><li>Log in to your portal as a user with admin or content creation privileges.</li>
<li>Select Content from the black Drupal menu at the top of the page.</li>
<li>Select the <em>Privacy Policy</em> page from the list and select edit.</li>
<li>Make your changes and save the page.</li>
</ul>\',
          \'safe_summary\' => \'\',
        ),
      ),
    ),
    \'rdf_mapping\' => array(
      \'rdftype\' => array(
        \'0\' => \'foaf:Document\',
      ),
      \'title\' => array(
        \'predicates\' => array(
          \'0\' => \'dc:title\',
        ),
      ),
      \'created\' => array(
        \'predicates\' => array(
          \'0\' => \'dc:date\',
          \'1\' => \'dc:created\',
        ),
        \'datatype\' => \'xsd:dateTime\',
        \'callback\' => \'date_iso8601\',
      ),
      \'changed\' => array(
        \'predicates\' => array(
          \'0\' => \'dc:modified\',
        ),
        \'datatype\' => \'xsd:dateTime\',
        \'callback\' => \'date_iso8601\',
      ),
      \'body\' => array(
        \'predicates\' => array(
          \'0\' => \'content:encoded\',
        ),
      ),
      \'uid\' => array(
        \'predicates\' => array(
          \'0\' => \'sioc:has_creator\',
        ),
        \'type\' => \'rel\',
      ),
      \'name\' => array(
        \'predicates\' => array(
          \'0\' => \'foaf:name\',
        ),
      ),
      \'comment_count\' => array(
        \'predicates\' => array(
          \'0\' => \'sioc:num_replies\',
        ),
        \'datatype\' => \'xsd:integer\',
      ),
      \'last_activity\' => array(
        \'predicates\' => array(
          \'0\' => \'sioc:last_activity_date\',
        ),
        \'datatype\' => \'xsd:dateTime\',
        \'callback\' => \'date_iso8601\',
      ),
    ),
    \'cid\' => \'0\',
    \'last_comment_timestamp\' => \'1328763802\',
    \'last_comment_name\' => NULL,
    \'last_comment_uid\' => \'7\',
    \'comment_count\' => \'0\',
    \'name\' => \'sathish\',
    \'picture\' => \'0\',
    \'data\' => \'b:0;\',
    \'path\' => array(
      \'pid\' => \'114\',
      \'source\' => \'node/178\',
      \'alias\' => \'basic-page/privacy-policy\',
      \'language\' => \'und\',
    ),
    \'menu\' => array(
      \'link_title\' => \'\',
      \'mlid\' => 0,
      \'plid\' => 0,
      \'menu_name\' => \'main-menu\',
      \'weight\' => 0,
      \'options\' => array(),
      \'module\' => \'menu\',
      \'expanded\' => 0,
      \'hidden\' => 0,
      \'has_children\' => 0,
      \'customized\' => 0,
      \'parent_depth_limit\' => 8,
      \'description\' => \'\',
      \'enabled\' => 1,
    ),
    \'node_export_drupal_version\' => \'7\',
    \'#_export_node_encode_object\' => \'1\',
  ),
    array(
    \'vid\' => \'180\',
    \'uid\' => \'7\',
    \'title\' => \'Contact us\',
    \'log\' => \'\',
    \'status\' => \'1\',
    \'comment\' => \'1\',
    \'promote\' => \'0\',
    \'sticky\' => \'0\',
    \'sha\' => NULL,
    \'vuuid\' => \'f0efdbf0-3dbc-f924-01bb-b22d699c27e6\',
    \'ds_switch\' => \'\',
    \'nid\' => \'180\',
    \'type\' => \'page\',
    \'language\' => \'und\',
    \'created\' => \'1328800153\',
    \'changed\' => \'1333750842\',
    \'tnid\' => \'0\',
    \'translate\' => \'0\',
    \'uuid\' => \'66e66b46-8383-2404-019d-a08822b566b7\',
    \'revision_timestamp\' => \'1333750842\',
    \'revision_uid\' => \'2\',
    \'body\' => array(
      \'und\' => array(
        \'0\' => array(
          \'value\' => \'<h3>Editing your Contact Us Page.</h3><ul><li>Log in to your portal as a user with admin or content creation privileges.</li><li>Navigate to the Contact Us page</li><li>Using the Edit Tab you can edit the content of this page.</li></ul><p>&nbsp;</p><p><strong>Alternate Method:</strong></p><ul><li>Log in to your portal as a user with admin or content creation privileges.</li><li>Select Content from the black Drupal menu at the top of the page.</li><li>Select the&nbsp;<em>Contact Us</em>&nbsp;page from the list and select edit.</li><li>Make your changes and save the page.</li></ul>\',
          \'summary\' => \'\',
          \'format\' => \'filtered_html\',
          \'safe_value\' => \'<h3>Editing your Contact Us Page.</h3>
<ul><li>Log in to your portal as a user with admin or content creation privileges.</li>
<li>Navigate to the Contact Us page</li>
<li>Using the Edit Tab you can edit the content of this page.</li>
</ul><p> </p>
<p><strong>Alternate Method:</strong></p>
<ul><li>Log in to your portal as a user with admin or content creation privileges.</li>
<li>Select Content from the black Drupal menu at the top of the page.</li>
<li>Select the <em>Contact Us</em> page from the list and select edit.</li>
<li>Make your changes and save the page.</li>
</ul>\',
          \'safe_summary\' => \'\',
        ),
      ),
    ),
    \'rdf_mapping\' => array(
      \'rdftype\' => array(
        \'0\' => \'foaf:Document\',
      ),
      \'title\' => array(
        \'predicates\' => array(
          \'0\' => \'dc:title\',
        ),
      ),
      \'created\' => array(
        \'predicates\' => array(
          \'0\' => \'dc:date\',
          \'1\' => \'dc:created\',
        ),
        \'datatype\' => \'xsd:dateTime\',
        \'callback\' => \'date_iso8601\',
      ),
      \'changed\' => array(
        \'predicates\' => array(
          \'0\' => \'dc:modified\',
        ),
        \'datatype\' => \'xsd:dateTime\',
        \'callback\' => \'date_iso8601\',
      ),
      \'body\' => array(
        \'predicates\' => array(
          \'0\' => \'content:encoded\',
        ),
      ),
      \'uid\' => array(
        \'predicates\' => array(
          \'0\' => \'sioc:has_creator\',
        ),
        \'type\' => \'rel\',
      ),
      \'name\' => array(
        \'predicates\' => array(
          \'0\' => \'foaf:name\',
        ),
      ),
      \'comment_count\' => array(
        \'predicates\' => array(
          \'0\' => \'sioc:num_replies\',
        ),
        \'datatype\' => \'xsd:integer\',
      ),
      \'last_activity\' => array(
        \'predicates\' => array(
          \'0\' => \'sioc:last_activity_date\',
        ),
        \'datatype\' => \'xsd:dateTime\',
        \'callback\' => \'date_iso8601\',
      ),
    ),
    \'cid\' => \'0\',
    \'last_comment_timestamp\' => \'1328800153\',
    \'last_comment_name\' => NULL,
    \'last_comment_uid\' => \'7\',
    \'comment_count\' => \'0\',
    \'name\' => \'sathish\',
    \'picture\' => \'0\',
    \'data\' => \'b:0;\',
    \'path\' => array(
      \'pid\' => \'116\',
      \'source\' => \'node/180\',
      \'alias\' => \'basic-page/contact-us\',
      \'language\' => \'und\',
    ),
    \'menu\' => array(
      \'link_title\' => \'\',
      \'mlid\' => 0,
      \'plid\' => 0,
      \'menu_name\' => \'main-menu\',
      \'weight\' => 0,
      \'options\' => array(),
      \'module\' => \'menu\',
      \'expanded\' => 0,
      \'hidden\' => 0,
      \'has_children\' => 0,
      \'customized\' => 0,
      \'parent_depth_limit\' => 8,
      \'description\' => \'\',
      \'enabled\' => 1,
    ),
    \'node_export_drupal_version\' => \'7\',
    \'#_export_node_encode_object\' => \'1\',
  ),
    array(
    \'vid\' => \'179\',
    \'uid\' => \'7\',
    \'title\' => \'Terms of Use\',
    \'log\' => \'\',
    \'status\' => \'1\',
    \'comment\' => \'1\',
    \'promote\' => \'0\',
    \'sticky\' => \'0\',
    \'sha\' => NULL,
    \'vuuid\' => \'e82604a6-7d93-b744-4586-cb0a3a905b90\',
    \'ds_switch\' => \'\',
    \'nid\' => \'179\',
    \'type\' => \'page\',
    \'language\' => \'und\',
    \'created\' => \'1328763867\',
    \'changed\' => \'1333750732\',
    \'tnid\' => \'0\',
    \'translate\' => \'0\',
    \'uuid\' => \'8203be7f-fc2f-7264-7d25-e6594592f089\',
    \'revision_timestamp\' => \'1333750732\',
    \'revision_uid\' => \'2\',
    \'body\' => array(
      \'und\' => array(
        \'0\' => array(
          \'value\' => \'<h3>Editing your Terms of Use.</h3><ul><li>Log in to your portal as a user with admin or content creation privileges.</li><li>Navigate to the Terms of Use page</li><li>Using the Edit Tab you can edit the content of this page.</li></ul><p>&nbsp;</p><p><strong>Alternate Method:</strong></p><ul><li>Log in to your portal as a user with admin or content creation privileges.</li><li>Select Content from the black Drupal menu at the top of the page.</li><li>Select the <em>Terms of Use</em> page from the list and select edit.</li><li>Make your changes and save the page.</li></ul><p>&nbsp;</p>\',
          \'summary\' => \'\',
          \'format\' => \'filtered_html\',
          \'safe_value\' => \'<h3>Editing your Terms of Use.</h3>
<ul><li>Log in to your portal as a user with admin or content creation privileges.</li>
<li>Navigate to the Terms of Use page</li>
<li>Using the Edit Tab you can edit the content of this page.</li>
</ul><p> </p>
<p><strong>Alternate Method:</strong></p>
<ul><li>Log in to your portal as a user with admin or content creation privileges.</li>
<li>Select Content from the black Drupal menu at the top of the page.</li>
<li>Select the <em>Terms of Use</em> page from the list and select edit.</li>
<li>Make your changes and save the page.</li>
</ul><p> </p>
\',
          \'safe_summary\' => \'\',
        ),
      ),
    ),
    \'rdf_mapping\' => array(
      \'rdftype\' => array(
        \'0\' => \'foaf:Document\',
      ),
      \'title\' => array(
        \'predicates\' => array(
          \'0\' => \'dc:title\',
        ),
      ),
      \'created\' => array(
        \'predicates\' => array(
          \'0\' => \'dc:date\',
          \'1\' => \'dc:created\',
        ),
        \'datatype\' => \'xsd:dateTime\',
        \'callback\' => \'date_iso8601\',
      ),
      \'changed\' => array(
        \'predicates\' => array(
          \'0\' => \'dc:modified\',
        ),
        \'datatype\' => \'xsd:dateTime\',
        \'callback\' => \'date_iso8601\',
      ),
      \'body\' => array(
        \'predicates\' => array(
          \'0\' => \'content:encoded\',
        ),
      ),
      \'uid\' => array(
        \'predicates\' => array(
          \'0\' => \'sioc:has_creator\',
        ),
        \'type\' => \'rel\',
      ),
      \'name\' => array(
        \'predicates\' => array(
          \'0\' => \'foaf:name\',
        ),
      ),
      \'comment_count\' => array(
        \'predicates\' => array(
          \'0\' => \'sioc:num_replies\',
        ),
        \'datatype\' => \'xsd:integer\',
      ),
      \'last_activity\' => array(
        \'predicates\' => array(
          \'0\' => \'sioc:last_activity_date\',
        ),
        \'datatype\' => \'xsd:dateTime\',
        \'callback\' => \'date_iso8601\',
      ),
    ),
    \'cid\' => \'0\',
    \'last_comment_timestamp\' => \'1328763867\',
    \'last_comment_name\' => NULL,
    \'last_comment_uid\' => \'7\',
    \'comment_count\' => \'0\',
    \'name\' => \'sathish\',
    \'picture\' => \'0\',
    \'data\' => \'b:0;\',
    \'path\' => array(
      \'pid\' => \'115\',
      \'source\' => \'node/179\',
      \'alias\' => \'basic-page/terms-use\',
      \'language\' => \'und\',
    ),
    \'menu\' => array(
      \'link_title\' => \'\',
      \'mlid\' => 0,
      \'plid\' => 0,
      \'menu_name\' => \'main-menu\',
      \'weight\' => 0,
      \'options\' => array(),
      \'module\' => \'menu\',
      \'expanded\' => 0,
      \'hidden\' => 0,
      \'has_children\' => 0,
      \'customized\' => 0,
      \'parent_depth_limit\' => 8,
      \'description\' => \'\',
      \'enabled\' => 1,
    ),
    \'node_export_drupal_version\' => \'7\',
    \'#_export_node_encode_object\' => \'1\',
  ),
)',
);
  return $node_export;
}

#Github Import

This module will import a Github Repo into a Drupal website and maintain hierarchy and association with the imported limbs. Multiple commits will be imported and new revisions of nodes will be created when the repo is updated.

#Installation

1.	Drop the module into sites/all/modules/contrib
1. 	Navigate to admin/content/node. There will be a new tab "github importer". Click on the tab.
1.	Add your first "repo" content object. Private Repos aren't supported yet but are coming.
1.	The Commit list will have checkboxes to import commit trees. Once the commit tree is chosen,
	it will be imported when the next cron cycle runs.
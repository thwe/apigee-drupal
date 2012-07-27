core = 7.x
api = 2

;core
projects[drupal][type] = "core"
projects[drupal][download][type] = "git"
projects[drupal][download][tag] = "7.14"
projects[drupal][download][url] = "http://git.drupal.org/project/drupal.git"

;Contrib projects
projects[admin_menu][subdir] = "contrib"
projects[apachesolr][subdir] = "contrib"
projects[apachesolr_autocomplete][subdir] = "contrib"
projects[backup_migrate][subdir] = "contrib"
projects[bean][subdir] = "contrib"
projects[bean][patch][] = "http://drupal.org/files/bean-extra-field-support-1534722-2.patch"
projects[block_class][subdir] = "contrib"
projects[ckeditor][subdir] = "contrib"
projects[content_access][subdir] = "contrib"
projects[context][subdir] = "contrib"
projects[cpn][subdir] = "contrib"
projects[ctools][subdir] = "contrib"
projects[devel][subdir] = 'contrib'
projects[diff][subdir] = 'contrib'
projects[drupad][subdir] = 'contrib'
projects[ds][subdir] = "contrib"
projects[entity][subdir] = "contrib"
projects[entity_view_mode][subdir] = "contrib"
projects[features][subdir] = 'contrib'
projects[feeds][subdir] = "contrib"
projects[feeds_tamper][subdir] = "contrib"
projects[feeds_xpathparser][subdir] = "contrib"
projects[field_group][subdir] = 'contrib'
projects[fivestar][subdir] = 'contrib'
projects[google_analytics][subdir] = 'contrib'
projects[google_analytics_reports][subdir] = 'contrib'
projects[imce][subdir] = 'contrib'
projects[imce_wysiwyg][subdir] = 'contrib'
projects[job_scheduler][subdir] = "contrib"
projects[jquery_update][subdir] = 'contrib'
projects[libraries][subdir] = "contrib"
projects[link][subdir] = "contrib"
projects[link_node][subdir] = "contrib"
projects[metatag][subdir] = "contrib"
projects[node_export][subdir] = 'contrib'
projects[pathauto][subdir] = "contrib"
projects[rules][subdir] = "contrib"
projects[smart_trim][subdir] = "contrib"
projects[token][subdir] = "contrib"
projects[views][subdir] = "contrib"
projects[views_infinite_scroll][subdir] = 'contrib'
projects[views_slideshow][subdir] = "contrib"
projects[webform][subdir] = "contrib"
projects[workbench][subdir] = "contrib"
projects[wysiwyg][subdir] = "contrib"

; apigee base theme
projects[apigee_base][type] = "theme"
projects[apigee_base][download][type] = 'git'
projects[apigee_base][download][url] = "git@github.com:apigee/apigee_drupal_base_theme.git"

; apigee marketing theme
projects[apigee_mktg][type] = "theme"
projects[apigee_mktg][download][type] = 'git'
projects[apigee_mktg][download][url] = "git@github.com:apigee/apigee_drupal_mktg_theme"

; development seed's admin theme
projects[tao][type]=theme
projects[rubik][type]=theme

; apigee SSO module
projects[apigee_sso][type] = module
projects[apigee_sso][subdir] = custom
projects[apigee_sso][download][type] = 'git'
projects[apigee_sso][download][url] = "git@github.com:apigee/apigee_drupal_sso.git"

; Libraries
; ------------------------------------------------------------------
; unfortunately, we can't link directly to a /download/latest
; for some and the URL's will need to be updated
; by hand when security updates are posted

libraries[jquery_cycle][download][type] = "get"
libraries[jquery_cycle][download][url] = "http://www.malsup.com/jquery/cycle/release/jquery.cycle.zip?v2.86"
libraries[jquery_cycle][directory_name] = "jquery.cycle"
libraries[jquery_cycle][destination] = "libraries"

libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://mktg-dev.apigee.com/libraries/ckeditor_3.6.2.tar.gz"
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][destination] = "libraries"

libraries[codemirror][download][type] = "get"
libraries[codemirror][download][url] = "http://codemirror.net/codemirror.zip"
libraries[codemirror][directory_name] = "codemirror"
libraries[codemirror][destination] = "libraries"

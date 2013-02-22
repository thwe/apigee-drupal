(function($){
	Drupal.behaviors.gi_import_now = {
		id: "gi_import_now",
		attach: function(context) {
			$("#gi_import_now_list tr:first-child progress").show().attr("value", 10);
			$("#gi_import_now_list").parent().load(this.getURL(context), function() {
				
				Drupal.attachBehaviors($("#gi_import_now_list").parent(), Drupal.settings);
				
			});
		},
		detach: function(context) {
			
		},
		getURL: function(context) {
			return Drupal.settings.basePath + "admin/content/gi/now/ajax/" +
				$("#gi_import_now_list tr:first-child").attr("data-nid");
		}
		
		
	}
	
	
})(jQuery)
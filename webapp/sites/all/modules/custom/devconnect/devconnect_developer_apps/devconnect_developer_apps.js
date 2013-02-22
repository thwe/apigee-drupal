(function($) {
	Drupal.behaviors.devconnect_org = {
		attach: function(context) {
    	$("form.form-stacked button.btn.primary.action:not(button-processed)").click(function(evt) {
				evt.stopPropagation();
				document.location.href=Drupal.settings.basePath+jQuery(this).attr('data-url');
				return false;
			}).addClass("button-processed");

			// jQuery Select
			$('select#api_product').selectList();
		},
		detach: function(context) {
		}
	}
})(jQuery);

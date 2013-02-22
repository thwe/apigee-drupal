(function ($) {
  Drupal.behaviors.apigeeDocs = {
    attach: function (context, settings) {
      if ($('.sub-nav').length) {
        $('html, body').height($(document).height() - 80);
      }
      else {
        $('html, body').height($(document).height() - 55);
      }
    }
  };

/**
 * Overrid TOC js so Back to Top buttons scroll back to the top of the page.
 */
  Drupal.tocFilterScrollToOnClick = function() {
    // Make sure links still has hash.
    if (!this.hash || this.hash == '#') {
      return true;
    }

    // Make sure the href is pointing to an anchor link on this page.
    var href = this.href.replace(/#[^#]*$/, '');
    var url = window.location.toString();
    if (href && url.indexOf(href) === -1) {
      return true;
    }

    // Find hash target.
    var $a = $('a[name=' + this.hash.substring(1) + ']');

    // Make hash target is on the current page.
    if (!$a.length) {
      return true;
    }

    // Scroll to hash target
    var duration = Drupal.settings.toc_filter_smooth_scroll_duration || 'medium';
    // Changed code start
    if ($a.href == '#top') {
      $('body,html').animate({scrollTop:0}, 1200, 'easeOutQuart');
    }
    else {
      $('html, body').animate({scrollTop: $a.offset().top - 100}, duration);
    }
    // Changed code end
    return false;
  }

  /**
   * Floating accordion block on the sidebar.
   */
  Drupal.apigeeStructureBlock = function() {
    $('.block-accordion-menu').once('apigeeStructureBlock', function(){
      var $block = $('.block-accordion-menu');
      // Save current top position of the block;
      var $topOffset = $block.offset().top - $(window).scrollTop();
      var $topOffsetFixed = 120;

      // Triggered on scroll event.
      $(window).scroll(function() {
        if ($('#admin-menu').length == 0) {
          $topOffsetFixed = 90;
        }

        var $windowScrollTop = $(window).scrollTop();

        if ($topOffset - $windowScrollTop > $topOffsetFixed) {
          $block.css('top', $topOffset - $windowScrollTop);
        }
        else {
          $block.css('top', $topOffsetFixed);
        }
      });
    });
    // Trigger scroll event manually to set the position without scrolling.
    $(window).trigger('scroll');
  };

})(jQuery);

<div class="panel-display apigee-threecol clearfix row" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <div class="region-main-content right-border span18">
      <div class="region-main-content">
      <?php if ($content['top']): ?>
        <div class="panel-panel panel-col-top">
          <div class="inside"><?php print $content['top']; ?></div>
        </div>
      <?php endif ?>

      <div class="center-wrapper">
        <div class="panel-panel panel-col-first">
          <div class="inside"><?php print $content['left']; ?></div>
        </div>

        <div class="panel-panel panel-col">
          <div class="inside"><?php print $content['middle']; ?></div>
        </div>

        <div class="panel-panel panel-col-last">
          <div class="inside"><?php print $content['right']; ?></div>
        </div>
      </div>

      <?php if ($content['bottom']): ?>
        <div class="panel-panel panel-col-bottom">
          <div class="inside"><?php print $content['bottom']; ?></div>
        </div>
      <?php endif ?>
    </div>
  </div>

  <div class="main-sidebar-wrapper span4 offset1">
    <?php if ($content['sidebar']): ?>
      <div class="panel-panel panel-sidebar">
        <div class="inside"><?php print $content['sidebar']; ?></div>
      </div>
    <?php endif ?>
  </div>
</div>

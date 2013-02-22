<a name="top"></a>
<?php print render($page['header']); ?>

<div class="master-container <?php print $master_container_class; ?>">
  <div class="main-container">
    <?php print render($page['breadcrumb']); ?>

    <?php if ($title): ?>
    <section class="page-header page-header-title">
      <!-- Title -->
      <div class="container">
        <div class="row">
          <div class="span24">
            <?php print render($title_prefix); ?>
            <h1><?php print $title; ?></h1>
            <?php print render($title_suffix); ?>
          </div>
        </div>
      </div>
    </section>
    <?php endif; ?>

    <!-- Main content -->
    <div class="page-content">
      <div class="container">
        <?php print $messages; ?>
        <?php if ($page['help']): ?>
          <div class="well"><?php print render($page['help']); ?></div>
        <?php endif; ?>
        <?php if ($action_links): ?>
          <ul class="action-links"><?php print render($action_links); ?></ul>
        <?php endif; ?>

        <div class="row">
          <!-- Left Sidebar  -->
          <?php if ($page['sidebar_first']): ?>
            <aside class="span6" role="complementary">
              <?php print render($page['sidebar_first']); ?>
            </aside>
          <?php endif; ?>

          <!-- Main Body  -->
          <section class="<?php print _apigee_base_content_span($columns);?> region-main-content <?php if ($page['sidebar_second']) { print "right-border"; } ?>">
            <div class="region-main-content-wrapper">
              <?php if ($page['highlighted']): ?>
                <div class="highlighted hero-unit"><?php print render($page['highlighted']); ?></div>
              <?php endif; ?>
              <?php if ($tabs): ?>
                <?php print render($tabs); ?>
              <?php endif; ?>
              <a id="main-content"></a>
              <?php print render($page['content']); ?>
            </div>
          </section>

          <!-- Right Sidebar  -->
          <?php if ($page['sidebar_second']): ?>
            <aside class="span5" role="complementary">
              <?php print render($page['sidebar_second']); ?>
            </aside>  <!-- /#sidebar-second -->
          <?php endif; ?>

        </div>
      </div>
    </div>
  </div>
</div>

<!-- Bottom region with menu -->
<div class="footer-container">
  <?php print render($page['bottom']); ?>

  <!-- Footer with copyright statement -->
  <?php print render($page['footer']); ?>
</div>

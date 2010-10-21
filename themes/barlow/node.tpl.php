<div id="node-<?php print $nid ?>" class="node<?php print ($sticky && $page == 0) ? " sticky" : ""; ?><?php print ($page == 0) ? " teaser" : " "; ?><?php print ' ' . ($node->type); ?><?php print ($submitted && !$page) ? " cal" : ""?>">
<?php print $picture ?>
<?php if ($page == 0) { ?>
  <?php if ($submitted) { ?>
  <div class="calendar"><div>
  <span class="month"><?php print format_date($created, 'custom', 'M') ?></span>
  <span class="day"><?php print format_date($created, 'custom', 'd') ?></span>
  <span class="time"><?php print format_date($created, 'custom', 'H:i') ?></span>
  </div></div>
  <?php } ?>
  <h2 class="title"><a href="<?php print $node_url ?>"><?php print $title ?></a></h2>
  <?php if ($author || $terms) { ?>
    <div class="submitted">
    <?php if ($author) { ?>
      <span class="author"><?php print $author ?></span>
    <?php } ?>
    <?php if ($terms) { ?>
      <span class="taxonomy"><?php print $terms ?></span>
    <?php } ?>
    </div>
  <?php } ?>
<?php } ?>
<div class="content"><?php print $content ?></div>
<?php if ($links && $page == 0){ ?>
  <div class="links">&raquo; <?php print $links ?></div>
<?php } ?>
<?php if ($page) { ?>
  <div class="meta">
 <?php if ($submitted) { ?>
  <div class="submitted"><?php print $submitted ?></div>
 <?php } ?>
 <?php if ($terms) { ?>
   <div class="taxonomy"><?php print $terms ?></div>
 <?php } ?>
 <?php if ($links){ ?>
   <div class="links">&raquo; <?php print $links ?></div>
 <?php } ?>
 </div>
<?php } ?>
</div>

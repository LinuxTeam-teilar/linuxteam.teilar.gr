<div id="comment-<?php print $id; ?>" class="comment<?php print ($comment->new) ? ' comment-new' : '' ?><?php print ($comment->uid != 1) ? ' comment-node-author' : '' ?> clear-block">
<?php if ($comment->new) { ?>
  <a id="new"></a>
  <span class="new"><?php print $new ?></span>
<?php } ?>
<div class="id"><a href="#comment-<?php print $id; ?>" ><?php print $id ?></a></div>
<h3 class="title author"><?php print $author; ?>:</h3>
  <?php print $picture ?>
  <div class="content"><?php print $content ?></div>
  <?php if ($signature): ?>
    <div class="user-signature clear-block">
      <?php print $signature ?>
    </div>
  <?php endif; ?>
  <?php if ($picture) { ?>
    <br class="clear" />
  <?php } ?>
  <div class="submitted"><?php print format_date($comment->timestamp, 'small') ?></div>
  <?php print $links ?>
</div>

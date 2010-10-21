<?php
// $Id: gallery-assist-pager.tpl.php,v 1.0 2009/11/19 16:11:12 jcmc Exp $
/** 
 * Example of template for the gallery container floated left and with separator line.
 * 
 * You can add extra css formating at here in the two folowing variants or in the tamplate.php
 * <style>
 *  <!-- your styles here -->
 * }
 * </style>
 * 
 * <link type="text/css" rel="stylesheet" media="all" href="/path/to/gallery-assist-pager.css" />
 */

  // Check or this template works and you can see them. When not please refresh your cache.
  drupal_set_message(t('THE TEMPLATE "gallery-assist-pager.tpl.php" WORKS. YOU CAN REMOVE THIS LINE', array()));
?>

<link type="text/css" rel="stylesheet" media="all" href="/themes/garland/gallery-assist-pager.css" />

<div id="ga-pager-box" class="pager-<?php print $extras['pager_position']; ?> clear-block next-line" style="<?php print $extras['pager_style']; ?>">
  <?php print $links; ?>
</div>



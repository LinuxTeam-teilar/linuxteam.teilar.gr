<?php
// $Id: gallery-assist-display.tpl.php,v 1.0 2009/11/19 16:11:12 jcmc Exp $
/** 
 * Example of template for the gallery container floated left and with separator line.
 * 
 * You can add extra css formating at here in the two folowing variants or through the tamplate.php
 * <style>
 *  <!-- your styles here -->
 * }
 * </style>
 * 
 * <link type="text/css" rel="stylesheet" media="all" href="/path/to/gallery-assist-display.css" />
 */

  // Check or this template works and you can see them. When not please refresh your cache.
  drupal_set_message(t('THE TEMPLATE "gallery-assist-display.tpl.php" WORKS. YOU CAN REMOVE THIS LINE', array()));
?>

<link type="text/css" rel="stylesheet" media="all" href="/themes/garland/gallery-assist-display.css" />

<div id="gallery-container" class="<?php print $item->nodetype; ?> gallery-container <?php print $conf['op']; ?> clear-block" <?php print $conf['my_attr']; ?> >
<?php
  if ($conf['pager_position'] == 'top' || $conf['pager_position'] == 'both') {
    print $pager;
  }
  
  print $boxes;

  if ($conf['pager_position'] == 'bottom' || $conf['pager_position'] == 'both') {
    print $pager;
  }
  
  $conf['pager_position'] == 'top' || $conf['pager_position'] == 'both' ? $pager : '';
?>
</div>


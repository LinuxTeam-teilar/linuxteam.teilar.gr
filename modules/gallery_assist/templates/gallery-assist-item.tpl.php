<?php
// $Id: gallery-assist-item.tpl.php,v 1.0 2009/11/19 16:11:12 jcmc Exp $
/** 
 * Example of template for the gallery item container.
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
  drupal_set_message(t('THE TEMPLATE "gallery-assist-item.tpl.php" WORKS. YOU CAN REMOVE THIS LINE', array()));
?>

<?php dsm($item->download_path); ?>

<a title="Download original image." href="<?php print $item->download_path; ?>">download</a>

<div class="clear-block">
 
 <div id="node-<?php print $item->nid; ?>" class="node">
   
   <span class="submitted"><?php print $item->submitted; ?></span>
    
    <div class="clear-block"><?php print $item->links; ?></div>
      
      <div class="content clear-block">
      
      <!-- Print the pager acord settings. -->
      <?php if ($item->top == 1 || $item->top == 3) { ?>
        
        <div id="ga-pager" class="'. $item->nodetype .' ga-pager clear-block"><?php print $item->pager; ?></div>
      
      <?php } ?>

      <!-- Print the item image. -->
      <div id="ga-image-display" class="'. $item->nodetype .' ga-image-display" style="max-width:<?php print $item->preview_size; ?>px; max-height:<?php print $item->preview_size; ?>px;<?php print $item->extra_styles . $item->img_extra_styles; ?>">
        
        <?php print $item->img; ?>
      
      </div>
    
    <!-- Print the pager acord settings. -->
    <?php if ($item->top == 0 || $item->top == 3) { ?>
      
      <div id="ga-pager" class="<?php print $item->nodetype; ?> ga-pager clear-block"><?php print $item->pager; ?></div>
    
    <? } ?>
    
    <!-- Information from Author or copyright. -->
    <?php if (!empty($item->copyright)) { ?>
      
      <div id="gallery-item-copyright" class="<?php print $item->nodetype; ?> gallery-item-copyright" style="max-width:<?php print $item->preview_size; ?>px;<?php print $item->extra_styles; ?>">&copy; <?php print $item->copyright; ?></div>
    
    <? } ?>
    
     <!-- Title of the item (image). You can use the if condition as by copyright. -->
     <div id="gallery-item-caption-title" class="<?php print $item->nodetype; ?> gallery-item-caption-title" style="max-width:<?php print $item->preview_size; ?>px;<?php print $item->extra_styles; ?>"><?php print $item->ptitle; ?></div>
     
     <!-- Gallery item description. You can use the if condition as by copyright. -->
     <div id="gallery-item-caption-text" class="<?php print $item->nodetype; ?> gallery-item-caption-text" style="max-width:<?php print $item->preview_size; ?>px;<?php print $item->extra_styles; ?>"><?php print $item->pdescription; ?></div>
   
   </div>
 
 </div>

</div>


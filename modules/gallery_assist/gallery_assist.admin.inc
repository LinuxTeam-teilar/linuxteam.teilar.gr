<?php
// $Id: gallery_assist.admin.inc,v 1.9 2009/12/03 14:17:26 jcmc Exp $

/**
 * @file
 * Drupal content type with gallery functionality. Administration page.
 * 
 */

/**
 * Settings form
 */ 
function gallery_assist_settings($form_state, $type = 'gallery_assist', $type_name = '') {

  global $base_path;
  drupal_add_css(drupal_get_path('module', 'gallery_assist') .'/css/gallery_assist.css', 'module', 'all', FALSE);

  $form = array();

  $assigned = variable_get('gallery_assist_'. $type, 0) == 1 ? ' ('. t('enabled') .')' : ' ('. t('disabled') .')';

  $fieldname[$type] = $type == 'gallery_assist' ? t('Gallery Assist') : t('Gallery Assist on @typename', array('@typename' => $type_name));

  $settings_type = variable_get('gallery_assist_'. $type .'_data', FALSE);

  if (variable_get('gallery_assist_use_imagecache', 0) == 1) {
    $settings_ic = variable_get('gallery_assist_'. $type .'_ic_data', FALSE);
  }

  $settings = is_array($settings_ic) ? array_merge($settings_type, $settings_ic) : $settings_type;

  $form['gallery_assist_'. $type .'_settings'][$type] = array(
    '#type' => 'fieldset',
    '#title' => $fieldname[$type],
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => $type == 'gallery_assist' ? 0 : 1,
    '#weight' => 0,
  );

  if (module_exists('imagecache') && variable_get('gallery_assist_use_imagecache', 0) == 1) {
    $form['gallery_assist_'. $type .'_settings'][$type] += _gallery_assist_get_ic_settings_form($type, $settings);
  }
  else {
    $form['gallery_assist_'. $type .'_settings'][$type] += _gallery_assist_sizes_settings_form($type, $settings);
  }

  // Layout.
  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layout'),
    '#collapsible' => TRUE,
    //'#collapsed' => TRUE,
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_items_per_row'] = array(
    '#type' => 'select',
    '#title' => t('Thumbnails per row'),
    '#options' => drupal_map_assoc(array('unlimited', 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)),
    '#default_value' => $settings['items_per_row'],
    '#prefix' => '<div class="gallery-assist-settings-left">',
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_rows_per_page'] = array(
    '#title' => t('Rows per page'),
    '#default_value' => $settings['rows_per_page'],
    '#type' => 'select',
    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6)),
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_title_substr'] = array(
    '#title' => t('Cut item title text for display'),
    '#default_value' => $settings['title_substr'],
    '#type' => 'textfield',
    '#size' => 10,
    '#suffix' => '</div>',
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_item_margin'] = array(
    '#type' => 'select',
    '#title' => t('Items margin'),
    '#options' => drupal_map_assoc(array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20)),
    '#default_value' => $settings['item_margin'],
    '#prefix' => '<div class="gallery-assist-settings-left">',
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_item_padding'] = array(
    '#type' => 'select',
    '#title' => t('Items padding'),
    '#options' => drupal_map_assoc(array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20)),
    '#default_value' => $settings['item_padding'],
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_item_border'] = array(
    '#type' => 'select',
    '#title' => t('Items border'),
    '#options' => drupal_map_assoc(array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)),
    '#default_value' => $settings['item_border'],
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_item_border_color'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#class' => 'farbtastic-picker',
    '#title' => t('Items border color'),
    '#default_value' => $settings['item_border_color'],
    '#suffix' => '</div>',
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_show_backlink'] = array(
    '#type' => 'select',
    '#title' => t('Back link'),
    '#options' => array(0 => t('off'), 1 => t('on')),
    '#default_value' => $settings['show_backlink'],
    '#prefix' => '<div class="gallery-assist-settings-left">',
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_show_title'] = array(
    '#type' => 'select',
    '#title' => t('Display titles'),
    '#options' => array(0 => t('off'), 1 => t('on')),
    '#default_value' => $settings['show_title'] ? $settings['show_title'] : 0,
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_show_toggle'] = array(
    '#type' => 'select',
    '#title' => t('Title links toggle'),
    '#options' => array(0 => t('off'), 1 => t('on')),
    '#default_value' => $settings['show_toggle'],
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_position_toggle'] = array(
    '#type' => 'select',
    '#title' => t('Title links position'),
    '#options' => array(0 => t('before body'), 1 => t('after body')),
    '#default_value' => $settings['position_toggle'],
    '#suffix' => '</div>',
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_ga_align'] = array(
    '#type' => 'select',
    '#title' => t('Teaser container align'),
    '#options' => array('none' => 'none', 'left' => 'left', 'center' => 'center', 'right' => 'right'),
    '#default_value' => $settings['layout']['ga_align'],
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_gap_align'] = array(
    '#type' => 'select',
    '#title' => t('Page container align'),
    '#options' => array('none' => 'none', 'left' => 'left', 'center' => 'center', 'right' => 'right'),
    '#default_value' => $settings['layout']['gap_align'],
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_t_ga_float'] = array(
    '#type' => 'select',
    '#title' => t('Teaser container float'),
    '#options' => array('none' => t('none'), 'left' => t('left'),'right'  => t('right')),
    '#default_value' => $settings['layout']['t_ga_float'],
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_layout']['gallery_assist_'. $type .'_p_ga_float'] = array(
    '#type' => 'select',
    '#title' => t('Page container float'),
    '#options' => array('none' => t('none'), 'left' => t('left'),'right'  => t('right')),
    '#default_value' => $settings['layout']['p_ga_float'],
  );

  // Pager.
  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_pager'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pager'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_pager']['gallery_assist_'. $type .'_pager_symbol'] = array(
    '#title' => t('Type'),
    '#default_value' => $settings['pager_symbol'],
    '#type' => 'select',
    '#options' => array('0' => t('Numeric'), '1' => t('Icons')),
    '#prefix' => '<div class="gallery-assist-settings-left">',
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_pager']['gallery_assist_'. $type .'_pager_layout'] = array(
    '#title' => t('Layout'),
    '#default_value' => $settings['pager_layout'],
    '#type' => 'select',
    '#options' => gallery_assist_pager_options(),
    '#suffix' => '</div>',
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_pager']['gallery_assist_'. $type .'_pager_position'] = array(
    '#title' => t('Position'),
    '#default_value' => $settings['pager_position'],
    '#type' => 'select',
    '#options' => array('top' => t('top'), 'bottom' => t('bottom'), 'both' => t('both')),
    '#prefix' => '<div class="gallery-assist-settings-left">',
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_pager']['gallery_assist_'. $type .'_pager_visibles'] = array(
    '#title' => t('Quantity of visible links'),
    '#default_value' => $settings['pager_visibles'],
    '#type' => 'textfield',
    '#size' => 10,
    '#suffix' => '</div>',
  );

  $form['gallery_assist_'. $type .'_settings'][$type]['gallery_assist_'. $type .'_change'] = array(
    '#type' => 'hidden',
    '#value' => TRUE,
  );

  $form['submit']['save'] = array(
    '#type' => 'submit',
    '#name' => 'save',
    '#value' => t('Save'),
  );
  
  $form['gallery_assist_'. $type .'_settings']['#suffix'] = '<div style="text-align: right;">'. gallery_assist_copyright() .'</div>';
  $form['#submit'][] = 'gallery_assist_settings_submit';
  
  return $form;
}

function _gallery_assist_assigments_form() {
  $form = array();

  // Choose list for assigments.
  $types = node_get_types();
  unset($types['gallery_assist']);
  foreach ($types as $typ => $v) {
    $default_value = variable_get('gallery_assist_'. $v->type, 0);

    $form['gallery_assist_assigments']['gallery_assist_'. $v->type] = array(
      '#type' => 'checkbox',
      '#title' => $v->name,
      '#default_value' => $default_value,
    );

    $form['gallery_assist_assigments']['gallery_assist_'. $v->type .'_changed'] = array(
      '#type' => 'hidden',
      '#value' => $default_value,
    );
  }

  return $form;
}

function gallery_assist_settings_extras() {
  global $user;
  $import_path = file_directory_path() .'/u'. $user->uid .'/import';
  $dscan1 = file_scan_directory($import_path, '.', array(), 0, FALSE);
  $paths1 = array_keys($dscan1);

  $form = array();
  $form['gallery_assist_extras'] = array(
    '#type' => 'fieldset',
    '#title' => t('Gallery Assist Extras'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  //
  $form['gallery_assist_extras']['gallery_assist_upload_conf'] = array(
    '#type' => 'fieldset',
    '#title' => t('Upload proccess'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Better only for experts.'),
    '#weight' => -50,
  );
  $form['gallery_assist_extras']['gallery_assist_upload_conf']['gallery_assist_upload_method'] = array(
    '#type' => 'select',
    '#title' => t('Files save method'),
    '#default_value' => variable_get('gallery_assist_upload_method', 1),
    '#options' => array( 0 => t('Rename files'), 1 => t('Replace files')),
    '#description' => 'If you choose "Replace files" existing files will be replaced by uploading files through the new file with the same name.<br>If you choose "Rename files" new files with same name as existing files will be renamed with a counter at the end.',
    '#prefix' => '<div class="gallery-assist-settings-left">',
    '#suffix' => '</div>',
  );
  /*
  $form['gallery_assist_extras']['gallery_assist_upload_conf']['gallery_assist_upload_name_filter'] = array(
    '#type' => 'select',
    '#title' => t('Files name filter'),
    '#default_value' => variable_get('gallery_assist_upload_name_filter', 1),
    '#options' => array(0 => t('none'), 1 => t('only alpha numeric'), 2 => t('alpha numeric & white spaces')),
    '#description' => t('The filter "only alpha numeric" removes all symbols, except alphanumeric characters from the file name. The filter "alpha numeric & white spaces" removes all symbols, except alphanumeric characters and white spaces from the file name.'),
    '#prefix' => '<div class="gallery-assist-settings-left">',
    '#suffix' => '</div>',
  );*/

  // Assigments
  if (user_access('administer gallery_assist')) {
    $form['gallery_assist_extras']['gallery_assist_assigments'] = array(
      '#type' => 'fieldset',
      '#title' => t('Assigments'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#weight' => -50,
      '#description' => t('Assign the gallery functionality to other content types.'),
    );

    $form['gallery_assist_extras']['gallery_assist_assigments'] += _gallery_assist_assigments_form();

  }

  if (module_exists('imce')) {
    $form['gallery_assist_extras']['gallery_assist_import_directories'] = array(
      '#type' => 'radios',
      //'#title' => '',
      '#options' => $paths1,
    );
  }

  $form['submit']['save'] = array(
    '#type' => 'submit',
    '#name' => 'save',
    '#value' => t('Save'),
  );

  $form['gallery_assist_extras']['#suffix'] = '<div style="text-align: right;">'. gallery_assist_copyright() .'</div>';
  $form['#submit'][] = 'gallery_assist_nodetypes_submit';

  return $form;
}

function gallery_assist_pager_options() {
  // Get gallery_assist_pager layouts.
  $pager_path_theme = drupal_get_path('theme', variable_get('theme_default', FALSE)) .'/ga_pager';
  $scan['theme'] = file_scan_directory($pager_path_theme, '.', $nomask = array('.', '..', 'README.txt'), 0, FALSE);
  $pager_options = array('default' => 'default');

  foreach ($scan as $dscan) { 

    foreach ($dscan as $p => $d) {
      if (!is_file($d->basename)) {
        $pager_options[$d->basename] = $d->basename;
      }
    }

  }

  return $pager_options;
}

/**
 * Separate 
 */
function _gallery_assist_sizes_settings_form($type, $settings = array()) {

  $form = array();
  // Upload.
  $form['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_sizes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sizes'),
    '#collapsible' => TRUE,
    //'#collapsed' => TRUE,
  );

  $form['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_upload'] = array(
    '#type' => 'fieldset',
    '#title' => t('Upload'),
    //'#collapsible' => TRUE,
    //'#collapsed' => TRUE,
  );

  $form['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_upload']['gallery_assist_'. $type .'_upload_thm'] = array(
    '#type' => 'textfield',
    '#title' => t('Thumbnail upload size'),
    '#size' => 5,
    '#default_value' =>  $settings['upload_thm'],
    '#prefix' => '<div class="gallery-assist-settings-left">',
    '#suffix' => '</div>',
  );

  $form['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_upload']['gallery_assist_'. $type .'_upload_prev'] = array(
    '#type' => 'textfield',
    '#title' => t('Preview upload size'),
    '#size' => 5,
    '#default_value' => $settings['upload_prev'],
    '#prefix' => '<div class="gallery-assist-settings-left">',
    '#suffix' => '</div>',
  );

  // Layout.
  $form['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_lsizes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display'),
    //'#collapsible' => TRUE,
    //'#collapsed' => TRUE,
  );

  if ($settings['thumbnail_size'] == '' && $settings['thumbnail_size'] == 0) {
    $settings['thumbnail_size'] = $settings['thumbnail_size'] = 100;
  }

  $form['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_lsizes']['gallery_assist_'. $type .'_thumbnail_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Thumbnail display size'),
    '#size' => 5,
    '#default_value' => $settings['thumbnail_size'],
    '#prefix' => '<div class="gallery-assist-settings-left">',
  );

  $form['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_lsizes']['gallery_assist_'. $type .'_preview_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Preview display size'),
    '#size' => 5,
    '#default_value' => $settings['preview_size'],
    '#suffix' => '</div>',
  );

  $form['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_lsizes']['gallery_assist_'. $type .'_thumbnail_size_plus'] = array(
    '#type' => 'textfield',
    '#title' => t('Extra thumbnail custom size'),
    '#size' => 5,
    '#default_value' => $settings['thumbnail_size_plus'],
    '#description' => 'Extend the width of thumbnails needed for layout.',
    '#prefix' => '<div class="gallery-assist-settings-left">',
    '#suffix' => '</div>',
  );

  return $form;
}

function _gallery_assist_get_ic_settings_form($type, $settings) {
  $form = array();

  // Upload.
  $form['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_sizes'] = array(
    '#type' => 'fieldset',
    '#title' => t('ImagaCache presets'),
    '#collapsible' => TRUE,
    //'#collapsed' => TRUE,
  );

  $presets = imagecache_presets();
  foreach ($presets as $presetid => $value) {
    $options[$presetid] = $value['presetname'];
  }

  $form['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_thm_presetid'] = array(
    '#type' => 'select',
    '#title' => t('Thumbnail preset'),
    '#default_value' => $settings['thm_presetid'],
    '#options' => $options,
    '#description' => t('Current used setting: @thm_presetname', array('@thm_presetname' => $settings['prev_presetname'])),
  );

  $form['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_sizes']['gallery_assist_'. $type .'_prev_presetid'] = array(
    '#type' => 'select',
    '#title' => t('Preview preset'),
    '#default_value' => $settings['prev_presetid'],
    '#options' => $options,
    '#description' => t('Current used setting: @prev_presetname', array('@prev_presetname' => $settings['prev_presetname'])),
  );

  return $form;
}

function gallery_assist_copyright() {
  return t('Module developed by <a target="_blank" href="@ga_creator_link">Juan Morejón</a> from the <a target="_blank" href="@qtg_link">Quiptime Group</a>', array(
    '@ga_creator_link' => url('http://simple.puntolatinoclub.de'), 
    '@qtg_link' => url('http://www.quiptime.com'),
  ));
}


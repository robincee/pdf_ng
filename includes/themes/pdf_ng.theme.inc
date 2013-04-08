<?php

/**
 * @file
 * pdf_ng/includes/themes/pdf_ng.theme.inc
 *
 * Theme and preprocess functions for the PDF NG module.
 */

/**
 * Preprocess function for theme('pdf_ng_image').
 */
function pdf_ng_preprocess_pdf_ng_image(&$variables) {
    drupal_add_css(drupal_get_path('module', 'pdf_ng') . '/pdf_ng.css');
  // Do not display the name for the 'square_thumbnail', we use
  // this mode in the media browser and node_edit form.
  $file_object = file_uri_to_object($variables['uri']);
  if ($variables['options']['image_style'] != 'media_thumbnail') {
    $variables['title'] = check_plain($file_object->filename);
  }
  // Create an image with correct style.
  $pdf_ng_thumb = theme('image_style', array('style_name' => $variables['options']['image_style'], 'path' => $variables['uri'] . '.png'));
  $file_url = file_create_url($variables['uri']);
  $variables['url'] = $GLOBALS['base_url'] . '/' . libraries_get_path('pdf.js') . '/web/viewer.html?file=' . $file_url;
  // If this image needs to be linked to the PDF without any fancy stuff.
  if (!empty($variables['options']['link_to']) && $variables['options']['link_to']) {
    if ($variables['options']['new_window']) {
      if (!empty($variables['title'])) { $variables['title'] = l($variables['title'], $variables['url'], array('html' => TRUE, 'attributes' => array('target' => '_blank'))); }
      $variables['output'] = l($pdf_ng_thumb, $variables['url'], array('html' => TRUE, 'attributes' => array('target' => '_blank')));
    }
    else {
      if (!empty($variables['title'])) { $variables['title'] = l($variables['title'], $variables['url'], array('html' => TRUE)); }
      $variables['output'] = l($pdf_ng_thumb, $variables['url'], array('html' => TRUE));
    }
  }
  else {
    $variables['output'] = $pdf_ng_thumb;
  }
}

/**
 * Preprocess function for theme('pdf_ng_document').
 */
function pdf_ng_preprocess_pdf_ng_document(&$variables) {
  // TODO: This should actually be a separate module.
  if ($variables['options']['enforce_pdfjs'] != true) {
    drupal_add_js(dirname(__FILE__) . '/acrobat_detection.js');
  }
  $file_object = file_uri_to_object($variables['uri']);
  $file_url = file_create_url($variables['uri']);
  // Add some options as their own template variables.
  foreach (array('width', 'height') as $theme_var) {
    $variables[$theme_var] = $variables['options'][$theme_var];
  }
  $variables['title'] = check_plain($file_object->filename);
  $variables['url'] = $GLOBALS['base_url'] . '/' . libraries_get_path('pdf.js') . '/web/viewer.html?file=' . $file_url;
  $variables['file_url'] = $file_url;
}

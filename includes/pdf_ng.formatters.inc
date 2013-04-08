<?php

/**
 * @file
 * Formatter functions for the PDF NG module.
 */

/**
 * Implements hook_file_formatter_info().
 */
function pdf_ng_file_formatter_info() {
  $formatters['pdf_ng_document'] = array(
    'label' => t('PDF document'),
    'file types' => array('document'),
    'default settings' => array(),
    'view callback' => 'pdf_ng_file_formatter_document_view',
    'settings callback' => 'pdf_ng_file_formatter_document_settings',
  );
  foreach (pdf_ng_variable_default() as $setting => $value) {
    $formatters['pdf_ng_document']['default settings'][$setting] = pdf_ng_variable_get($setting);
  }
  $formatters['pdf_ng_image'] = array(
    'label' => t('PDF thumbnail'),
    'file types' => array('document'),
    'default settings' => array(
      'image_style' => '',
    ),
    'view callback' => 'pdf_ng_file_formatter_image_view',
    'settings callback' => 'pdf_ng_file_formatter_image_settings',
  );
  foreach (pdf_ng_image_variable_default() as $image_setting => $image_value) {
    $formatters['pdf_ng_image']['default settings'][$image_setting] = pdf_ng_image_variable_get($image_setting);
  }
  return $formatters;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function pdf_ng_file_formatter_document_view($file, $display, $langcode) {
  // TODO: still have to figure out what to do with wysiwyg.
  if ($file->type == 'document' && $file->filemime == 'application/pdf' && empty($file->override['wysiwyg'])) {
    $element = array(
      '#theme' => 'pdf_ng_document',
      '#uri' => $file->uri,
      '#options' => array(),
    );
    $display['settings']['attributes'] = array();
    foreach (pdf_ng_variable_default() as $setting => $default_value) {
      $element['#options'][$setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function pdf_ng_file_formatter_document_settings($form, &$form_state, $settings) {
  $element = array();
  $element['enforce_pdfjs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enforce PDF.js'),
    '#default_value' => $settings['enforce_pdfjs'],
    '#description' => t("If unchecked, pdf.js will only be loaded when users don not have a PDF reader installed (except for Safari with default OSX Preview, because it can't be detected via javascript)."),
  );
  return $element;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function pdf_ng_file_formatter_image_view($file, $display, $langcode) {
  // Create thumbnails that do not exist yet. (this can kill your server).
  if (!file_exists(drupal_realpath($file->uri) . '.png')) {
    pdf_ng_process_file($file);
  }
  if ($file->filemime == 'application/pdf') {
    $element = array(
      '#theme' => 'pdf_ng_image',
      '#uri' => $file->uri,
      '#options' => array('image_style' => $display['settings']['image_style']),
    );
    $display['settings']['attributes'] = array();
    foreach (pdf_ng_image_variable_default() as $setting => $default_value) {
      $element['#options'][$setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function pdf_ng_file_formatter_image_settings($form, &$form_state, $settings) {
  $element = array();
  $element['image_style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#options' => image_style_options(FALSE),
    '#default_value' => $settings['image_style'],
    '#empty_option' => t('None (original image)'),
  );
  $element['show_name'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show name'),
    '#default_value' => $settings['show_name'],
    '#description' => t("If checked, the file name will be displayed above the thumbnail."),
  );
  $element['link_to'] = array(
    '#type' => 'checkbox',
    '#title' => t('Link to'),
    '#default_value' => $settings['link_to'],
    '#description' => t("If checked, the thumbnail will link to the PDF file."),
  );
  $element['new_window'] = array(
    '#type' => 'checkbox',
    '#title' => t('New window'),
    '#default_value' => $settings['new_window'],
    '#description' => t("If checked, the linked thumbnail will open in a new tab/window."),
  );
  return $element;
}

/**
 * Implements hook_file_default_displays().
 */
function pdf_ng_file_default_displays() {
  $default_displays = array();
  $default_document_settings = array(
    'default' => '',
    'preview' => 'media_thumbnail',
    'teaser' => '',
  );
  foreach ($default_document_settings as $view_mode => $settings) {
    $display_name = 'document__' . $view_mode . '__pdf_ng_document';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 1,
      'settings' => $settings,
    );
  }
  $default_image_styles = array(
    'default' => 'square_thumbnail',
    'preview' => 'media_thumbnail',
    'teaser' => 'medium',
  );
  foreach ($default_image_styles as $view_mode => $image_style) {
    $display_name = 'document__' . $view_mode . '__pdf_ng_image';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 2,
      'settings' => array('image_style' => $image_style, 'new_window' => TRUE, 'link_to' => TRUE),
    );
  }
  return $default_displays;
}

<?php

/**
 * @file pdf_ng/includes/pdf_ng.variables.inc
 * Variable defaults for the PDF NG module.
 */

/**
 * Define constants.
 */

/**
 * The variable namespace for pdf.
 */
define('PDF_NG_NAMESPACE', 'pdf_ng__');

/**
 * The variable namespace for pdf image.
 */
define('PDF_NG_IMAGE_NAMESPACE', 'pdf_ng_image__');

/**
 * The variable namespace for pdf link.
 */
define('PDF_NG_LINK_NAMESPACE', 'pdf_ng_link__');

/**
 * Wrapper for variable_get() using the PDF variable registry.
 */
function pdf_ng_variable_get($name, $default = NULL) {
  if (!isset($default)) {
    $default = pdf_ng_variable_default($name);
  }
  $variable_name = PDF_NG_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 * Wrapper for variable_set() using the PDF variable registry.
 */
function pdf_ng_variable_set($name, $value) {
  $variable_name = PDF_NG_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() using the PDF variable registry.
 */
function pdf_ng_variable_del($name) {
  $variable_name = PDF_NG_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the PDF namespace.
 */
function pdf_ng_variable_default($name = NULL) {
  static $defaults;
  if (!isset($defaults)) {
    $defaults = array(
      'enforce_pdfjs' => TRUE,
      'width' => '900px',
      'height' => '700px',
    );
  }
  if (!isset($name)) {
    return $defaults;
  }
  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

/**
 * Return the fully namespace variable name.
 */
function pdf_ng_variable_name($name) {
  return PDF_NG_NAMESPACE . $name;
}

/**
 * Wrapper for variable_get() using the PDF variable registry.
 */
function pdf_ng_image_variable_get($name, $default = NULL) {
  if (!isset($default)) {
    $default = pdf_ng_image_variable_default($name);
  }
  $variable_name = PDF_NG_IMAGE_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 * Wrapper for variable_set() using the PDF image variable registry.
 */
function pdf_ng_image_variable_set($name, $value) {
  $variable_name = PDF_NG_IMAGE_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() using the PDF image variable registry.
 */
function pdf_ng_image_variable_del($name) {
  $variable_name = PDF_NG_IMAGE_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the PDF image namespace.
 */
function pdf_ng_image_variable_default($name = NULL) {
  static $defaults;
  if (!isset($defaults)) {
    $defaults = array(
      'new_window' => FALSE,
      'link_to' => FALSE,
      'show_name' => TRUE,
    );
  }
  if (!isset($name)) {
    return $defaults;
  }
  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

/**
 * Return the fully namespace variable name.
 */
function pdf_ng_image_variable_name($name) {
  return PDF_NG_IMAGE_NAMESPACE . $name;
}

/**
 * Wrapper for variable_get() using the PDF variable registry.
 */
function pdf_ng_link_variable_get($name, $default = NULL) {
  if (!isset($default)) {
    $default = pdf_ng_link_variable_default($name);
  }
  $variable_name = PDF_NG_LINK_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 * Wrapper for variable_set() using the PDF image variable registry.
 */
function pdf_ng_link_variable_set($name, $value) {
  $variable_name = PDF_NG_LINK_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() using the PDF image variable registry.
 */
function pdf_ng_link_variable_del($name) {
  $variable_name = PDF_NG_LINK_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the PDF image namespace.
 */
function pdf_ng_link_variable_default($name = NULL) {
  static $defaults;
  if (!isset($defaults)) {
    $defaults = array(
      'new_window' => FALSE,
    );
  }
  if (!isset($name)) {
    return $defaults;
  }
  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

/**
 * Return the fully namespace variable name.
 */
function pdf_ng_link_variable_name($name) {
  return PDF_NG_LINK_NAMESPACE . $name;
}

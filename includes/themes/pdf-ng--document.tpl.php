<?php

/**
 * @file pdf_ng/includes/themes/pdf-ng--document.tpl.php
 *
 * Template file for theme('pdf_ng_document').
 */

?>
<div class="<?php print $classes; ?> pdf-ng-document-<?php print $id; ?>">
  <iframe class="pdf-ng" <?php print $api_id_attribute; ?>width="<?php print $width; ?>" height="<?php print $height; ?>" title="<?php print $title; ?>" src="<?php print $url; ?>" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen><?php print $file_url; ?></iframe>
</div>

<?php

/**
 * @file pdf_ng/includes/themes/pdf-ng--image.tpl.php
 *
 * Template file for theme('pdf_ng_image').
 */

if (!empty($title)): ?>
<div class="pdf-ng-image-title pdf-ng-image-title-<?php print $id; ?>"><?php echo $title; ?></div>
<?php endif; ?>
<div class="<?php print $classes; ?> pdf-ng-image-<?php print $id; ?>">
  <?php print $output; ?>
</div>

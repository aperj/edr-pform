<?php

/**
 * This isn't a true Drupal block template, but it can be used within a block.
 *
 * Variables of interest:
 *
 * $author - the raw author object from Open Library
 * $name - The author's name, usually a link to their Open Library page (depending on theme function arguments)
 * $image - Themed author image
 */
 //dsm($author);
?>
<div class="openlibrary-author-block">
<?php if ($image): ?>
<div class="openlibrary-cover"><?php print $image; ?></div>
<?php endif; ?>
<div class="openlibrary-content">
<dl>
<dt>Name:</dt><dd><?php print $name; ?></dd>
<?php if ($author->birth_date): ?>
<dt>Born:</dt><dd><?php print $author->birth_date; ?></dd>
<?php endif; ?>

</dl>
</div>

</div><!-- .openlibrary-edition-block -->

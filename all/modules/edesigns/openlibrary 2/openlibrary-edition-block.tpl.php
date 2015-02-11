<?php

/**
 * This isn't a true Drupal block template, but it can be used within a block.
 *
 * Variables of interest:
 *
 * $edition - the raw edition object from Open Library
 * $title - The title of the book, usually a link to the Open Library page (depending on theme function arguments)
 * $cover - Themed cover image
 * $authors - Themed list of authors, linking back to Open Library (or elsewhere, depending on theme function arguments)
 */
 //dsm($edition);
?>
<div class="openlibrary-edition-block">
<?php if ($cover): ?>
<div class="openlibrary-cover"><?php print $cover; ?></div>
<?php endif; ?>
<div class="openlibrary-content">
<dl>
<dt>Title:</dt><dd><?php print $title; ?></dd>
<dt>Authors:</dt><dd><?php print $authors; ?></dd>
<?php if ($edition->edition_name): ?>
<dt>Edition:</dt><dd><?php print $edition->edition_name; ?></dd>
<?php endif; ?>
<?php if ($edition->publish_date): ?>
<dt>Date Published:</dt><dd><?php print $edition->publish_date; ?></dd>
<?php endif; ?>

<?php if (count($edition->publishers)): ?>
<dt>Publishers:</dt><dd>
<?php print implode('<br />', $edition->publishers); ?>
</dd>
<?php endif; ?>


<?php if (count($edition->genres)): ?>
<dt>Genres:</dt><dd>
<?php print implode('<br />', $edition->genres); ?>
</dd>
<?php endif; ?>

</dl>
</div>

</div><!-- .openlibrary-edition-block -->

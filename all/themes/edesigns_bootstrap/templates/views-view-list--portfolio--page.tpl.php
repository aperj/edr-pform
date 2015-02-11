<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */

//print 'RRRROW'; return;
?>

<div class="portfolio">
<div class="row">
  <?php print '<ul  class="portfolio-img">'; ?>
    <?php foreach ($rows as $id => $row): ?>
      <li class="span3" data-type="web-design" data-id="p-1" >
      	<div class="work">
      		<?php print $row; ?>
      	</div>
     </li>
    <?php endforeach; ?>
  <?php print $list_type_suffix; ?>
</div>
</div>







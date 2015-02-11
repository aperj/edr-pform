<?php

/**
 * @file
 * Theme functions for openlibrary.module.
 */

/**
 * Open Library API
 * Copyright 2009 Matthew Davidson.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * Convenience theme function that fetches the edition and displays it in one of a number of possible formats.
 *
 * For more control, you may want to call the theme functions that this function calls.
 *
 * @param $id
 *   A string identifier. This must be a string, even if it's all numeric digits.
 *
 * @param $type
 *   The type of identifier. Accepts same values as the $type argument in openlibrary_get_edition().
 *
 * @param $style
 *   An output style. Possible values:
 *     - 'title': Title only, linking to Open Library page.
 *     - 'block': Book cover, and a lot of other info in a block-like format.
 */
function theme_openlibrary_edition($id, $id_type = 'isbn', $style = 'title') {
  $id_type = $id_type ? $id_type : 'isbn';
  $style = $style ? $style : 'title';
  drupal_add_css(drupal_get_path('module', 'openlibrary') .'/openlibrary.css', 'module');
  
  $edition = openlibrary_get_edition($id, $id_type);
  
  if (!$edition) {
    return t('Edition %id_type not found: %id', array('%id_type' => $id_type, '%id' => $id));
  }
  
  switch ($style) {
    case 'title':
      $output = theme('openlibrary_edition_title', $edition);
      break;
    case 'block':
      $output = theme('openlibrary_edition_block', $edition);
      break;
  }
  
  return $output;
}


/**
 * Displays the title of an edition.
 *
 * @param $edition
 *   An Open Library edition object
 *
 * @param $link
 *   TRUE if the title should be a link 
 */
function theme_openlibrary_edition_title($edition, $link = TRUE) {
  drupal_add_css(drupal_get_path('module', 'openlibrary') .'/openlibrary.css', 'module');
  
  if ($link) {
    return l($edition->title, OPENLIBRARY_RESTFUL_API_ROOT . $edition->key);
  }
  else {
    return $edition->title;
  }
}

function template_preprocess_openlibrary_edition_block(&$variables) {
  drupal_add_css(drupal_get_path('module', 'openlibrary') .'/openlibrary.css', 'module');

  $variables['olid'] = openlibrary_olid_from_key($variables['edition']->key);
  if ($variables['show_cover']) {
    $variables['cover'] = theme('openlibrary_edition_cover', $variables['edition']);
  }
  $variables['title'] = theme('openlibrary_edition_title', $variables['edition'], $variables['link']);
  
  $authors = array();
  foreach ($variables['edition']->authors as $author) {
    $authors[] = theme('openlibrary_author', openlibrary_olid_from_key($author->key));
  }
  $variables['authors'] = implode(', ', $authors);
}


/**
 * Displays an edition cover.
 *
 * @param $edition
 *   An Open Library edition object
 *
 * @param $size
 *   'S', 'M', or 'L'. See http://openlibrary.org/dev/docs/api/covers
 *
 * @param $link
 *   TRUE if the title should be a link 
 */
function theme_openlibrary_edition_cover($edition, $size = 'M', $link = TRUE) {
  drupal_add_css(drupal_get_path('module', 'openlibrary') .'/openlibrary.css', 'module');
  
  $url = openlibrary_get_cover(openlibrary_olid_from_key($edition->key));
  if (!$url) {
    return;
  }
  
  //TODO: imagecache.module integration
  
  $attributes = array('class' => 'openlibrary-size-'. $size);
  // Caution: need $getsize to be false until at least D7. See http://drupal.org/node/238681
  $img = theme('image', $url, $variables['edition']->title .' cover', '', $attributes, FALSE);
  
  if ($link) {
    $options = array('html' => TRUE);
    return l($img, OPENLIBRARY_RESTFUL_API_ROOT . $edition->key, $options);
  }
  else {
    return $img;
  }
}



/**
 * Convenience theme function that fetches author info and displays it in one of a number of possible formats.
 *
 * For more control, you may want to call the theme functions that this function calls.
 *
 * @param $olid
 *   The author's OLID
 *
 * @param $style
 *   An output style. Possible values:
 *     - 'name': Author's name only, linking to Open Library page.
 *     - 'block': Image and a lot of other info in a block-like format.
 */
function theme_openlibrary_author($olid, $style = 'name') {
  $style = $style ? $style : 'name';
  drupal_add_css(drupal_get_path('module', 'openlibrary') .'/openlibrary.css', 'module');
  
  $author = openlibrary_get_author($olid);
  
  if (!$author) {
    return t('Author not found: ') .':'. $olid;
  }
  
  switch ($style) {
    case 'name':
      $output = theme('openlibrary_author_name', $author);
      break;
    case 'block':
      $output = theme('openlibrary_author_block', $author);
      break;
  }
  
  return $output;
}


/**
 * Displays the name of an author.
 *
 * @param $author
 *   An Open Library author object
 *
 * @param $link
 *   TRUE if the title should be a link 
 */
function theme_openlibrary_author_name($author, $link = TRUE) {
  drupal_add_css(drupal_get_path('module', 'openlibrary') .'/openlibrary.css', 'module');
  
  if ($link) {
    return l($author->name, OPENLIBRARY_RESTFUL_API_ROOT . $author->key);
  }
  else {
    return $author->name;
  }
}

function template_preprocess_openlibrary_author_block(&$variables) {
  drupal_add_css(drupal_get_path('module', 'openlibrary') .'/openlibrary.css', 'module');

  $variables['olid'] = openlibrary_olid_from_key($variables['author']->key);
  if ($variables['show_image']) {
    $variables['image'] = theme('openlibrary_author_image', $variables['author']);
  }
  $variables['name'] = theme('openlibrary_author_name', $variables['author'], $variables['link']);
}


/**
 * Displays an author image.
 *
 * @param $author
 *   An Open Library author object
 *
 * @param $size
 *   'S', 'M', or 'L'. See http://openlibrary.org/dev/docs/api/covers
 *
 * @param $link
 *   TRUE if the title should be a link 
 */
function theme_openlibrary_author_image($author, $size = 'M', $link = TRUE) {
  drupal_add_css(drupal_get_path('module', 'openlibrary') .'/openlibrary.css', 'module');
  
  $url = openlibrary_get_cover(openlibrary_olid_from_key($author->key), 'olid', 'a');
  if (!$url) {
    return;
  }
  
  //TODO: imagecache.module integration
  
  $attributes = array('class' => 'openlibrary-size-'. $size);
  // Caution: need $getsize to be false until at least D7. See http://drupal.org/node/238681
  $img = theme('image', $url, $variables['author']->name .' image', '', $attributes, FALSE);
  
  if ($link) {
    $options = array('html' => TRUE);
    return l($img, OPENLIBRARY_RESTFUL_API_ROOT . $author->key, $options);
  }
  else {
    return $img;
  }
}





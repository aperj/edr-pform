<?php
/**
 * @file
 * Primarily Drupal hooks and global API functions to manipulate views.
 *
 * This is the main module file for Views. The main entry points into
 * this module are views_page() and views_block(), where it handles
 * incoming page and block requests.
 */

/**
 * Advertise the current views api version
 */
function views_api_version() {
  return '3.0';
}

/**
 * Implements hook_forms().
 *
 * To provide distinct form IDs for Views forms, the View name and
 * specific display name are appended to the base ID,
 * views_form_views_form. When such a form is built or submitted, this
 * function will return the proper callback function to use for the given form.
 */
function views_forms($form_id, $args) {
  if (strpos($form_id, 'views_form_') === 0) {
    return array(
      $form_id => array(
        'callback' => 'views_form',
      ),
    );
  }
}

/**
 * Returns a form ID for a Views form using the name and display of the View.
 */
function views_form_id($view) {
  $parts = array(
    'views_form',
    $view->name,
    $view->current_display,
  );

  return implode('_', $parts);
}

/**
 * Views will not load plugins advertising a version older than this.
 */
function views_api_minimum_version() {
  return '2';
}

/**
 * Implement hook_theme(). Register views theming functions.
 */
function views_theme($existing, $type, $theme, $path) {
  $path = drupal_get_path('module', 'views');
  ctools_include('theme', 'views', 'theme');

  // Some quasi clever array merging here.
  $base = array(
    'file' => 'theme.inc',
    'path' => $path . '/theme',
  );

  // Our extra version of pager from pager.inc
  $hooks['views_mini_pager'] = $base + array(
    'variables' => array('tags' => array(), 'quantity' => 10, 'element' => 0, 'parameters' => array()),
    'pattern' => 'views_mini_pager__',
  );

  $variables = array(
    // For displays, we pass in a dummy array as the first parameter, since
    // $view is an object but the core contextual_preprocess() function only
    // attaches contextual links when the primary theme argument is an array.
    'display' => array('view_array' => array(), 'view' => NULL),
    'style' => array('view' => NULL, 'options' => NULL, 'rows' => NULL, 'title' => NULL),
    'row' => array('view' => NULL, 'options' => NULL, 'row' => NULL, 'field_alias' => NULL),
    'exposed_form' => array('view' => NULL, 'options' => NULL),
    'pager' => array(
      'view' => NULL, 'options' => NULL,
      'tags' => array(), 'quantity' => 10, 'element' => 0, 'parameters' => array()
    ),
  );

  // Default view themes
  $hooks['views_view_field'] = $base + array(
    'pattern' => 'views_view_field__',
    'variables' => array('view' => NULL, 'field' => NULL, 'row' => NULL),
  );
  $hooks['views_view_grouping'] = $base + array(
    'pattern' => 'views_view_grouping__',
    'variables' => array('view' => NULL, 'grouping' => NULL, 'grouping_level' => NULL, 'rows' => NULL, 'title' => NULL),
  );

  $plugins = views_fetch_plugin_data();

  // Register theme functions for all style plugins
  foreach ($plugins as $type => $info) {
    foreach ($info as $plugin => $def) {
      if (isset($def['theme']) && (!isset($def['register theme']) || !empty($def['register theme']))) {
        $hooks[$def['theme']] = array(
          'pattern' => $def['theme'] . '__',
          'file' => $def['theme file'],
          'path' => $def['theme path'],
          'variables' => $variables[$type],
        );

        $include = DRUPAL_ROOT . '/' . $def['theme path'] . '/' . $def['theme file'];
        if (file_exists($include)) {
          require_once $include;
        }

        if (!function_exists('theme_' . $def['theme'])) {
          $hooks[$def['theme']]['template'] = drupal_clean_css_identifier($def['theme']);
        }
      }
      if (isset($def['additional themes'])) {
        foreach ($def['additional themes'] as $theme => $theme_type) {
          if (empty($theme_type)) {
            $theme = $theme_type;
            $theme_type = $type;
          }

          $hooks[$theme] = array(
            'pattern' => $theme . '__',
            'file' => $def['theme file'],
            'path' => $def['theme path'],
            'variables' => $variables[$theme_type],
          );

          if (!function_exists('theme_' . $theme)) {
            $hooks[$theme]['template'] = drupal_clean_css_identifier($theme);
          }
        }
      }
    }
  }

  $hooks['views_form_views_form'] = $base + array(
    'render element' => 'form',
  );

  $hooks['views_exposed_form'] = $base + array(
    'template' => 'views-exposed-form',
    'pattern' => 'views_exposed_form__',
    'render element' => 'form',
  );

  $hooks['views_more'] = $base + array(
    'template' => 'views-more',
    'pattern' => 'views_more__',
    'variables' => array('more_url' => NULL, 'link_text' => 'more', 'view' => NULL),
  );

  // Add theme suggestions which are part of modules.
  foreach (views_get_module_apis() as $info) {
    if (isset($info['template path'])) {
      $hooks += _views_find_module_templates($hooks, $info['template path']);
    }
  }
  return $hooks;
}

/**
 * Scans a directory of a module for template files.
 *
 * @param $cache
 *   The existing cache of theme hooks to test against.
 * @param $path
 *   The path to search.
 *
 * @see drupal_find_theme_templates
 */
function _views_find_module_templates($cache, $path) {
  $templates = array();
  $regex = '/' . '\.tpl\.php' . '$' . '/';

  // Because drupal_system_listing works the way it does, we check for real
  // templates separately from checking for patterns.
  $files = drupal_system_listing($regex, $path, 'name', 0);
  foreach ($files as $template => $file) {
    // Chop off the remaining extensions if there are any. $template already
    // has the rightmost extension removed, but there might still be more,
    // such as with .tpl.php, which still has .tpl in $template at this point.
    if (($pos = strpos($template, '.')) !== FALSE) {
      $template = substr($template, 0, $pos);
    }
    // Transform - in filenames to _ to match function naming scheme
    // for the purposes of searching.
    $hook = strtr($template, '-', '_');
    if (isset($cache[$hook])) {
      $templates[$hook] = array(
        'template' => $template,
        'path' => dirname($file->filename),
        'includes' => isset($cache[$hook]['includes']) ? $cache[$hook]['includes'] : NULL,
      );
    }
    // Ensure that the pattern is maintained from base themes to its sub-themes.
    // Each sub-theme will have their templates scanned so the pattern must be
    // held for subsequent runs.
    if (isset($cache[$hook]['pattern'])) {
      $templates[$hook]['pattern'] = $cache[$hook]['pattern'];
    }
  }

  $patterns = array_keys($files);

  foreach ($cache as $hook => $info) {
    if (!empty($info['pattern'])) {
      // Transform _ in pattern to - to match file naming scheme
      // for the purposes of searching.
      $pattern = strtr($info['pattern'], '_', '-');

      $matches = preg_grep('/^'. $pattern .'/', $patterns);
      if ($matches) {
        foreach ($matches as $match) {
          $file = substr($match, 0, strpos($match, '.'));
          // Put the underscores back in for the hook name and register this pattern.
          $templates[strtr($file, '-', '_')] = array(
            'template' => $file,
            'path' => dirname($files[$match]->uri),
            'variables' => isset($info['variables']) ? $info['variables'] : NULL,
            'render element' => isset($info['render element']) ? $info['render element'] : NULL,
            'base hook' => $hook,
            'includes' => isset($info['includes']) ? $info['includes'] : NULL,
          );
        }
      }
    }
  }

  return $templates;
}

/**
 * A theme preprocess function to automatically allow view-based node
 * templates if called from a view.
 *
 * The 'modules/node.views.inc' file is a better place for this, but
 * we haven't got a chance to load that file before Drupal builds the
 * node portion of the theme registry.
 */
function views_preprocess_node(&$vars) {
  // The 'view' attribute of the node is added in views_preprocess_node()
  if (!empty($vars['node']->view) && !empty($vars['node']->view->name)) {
    $vars['view'] = $vars['node']->view;
    $vars['theme_hook_suggestions'][] = 'node__view__' . $vars['node']->view->name;
    if (!empty($vars['node']->view->current_display)) {
      $vars['theme_hook_suggestions'][] = 'node__view__' . $vars['node']->view->name . '__' . $vars['node']->view->current_display;

      // If a node is being rendered in a view, and the view does not have a path,
      // prevent drupal from accidentally setting the $page variable:
      if ($vars['page'] && $vars['view_mode'] == 'full' && !$vars['view']->display_handler->has_path()) {
        $vars['page'] = FALSE;
      }
    }
  }

  // Allow to alter comments and links based on the settings in the row plugin.
  if (!empty($vars['view']->style_plugin->row_plugin) && get_class($vars['view']->style_plugin->row_plugin) == 'views_plugin_row_node_view') {
    node_row_node_view_preprocess_node($vars);
  }
}

/**
 * A theme preprocess function to automatically allow view-based node
 * templates if called from a view.
 */
function views_preprocess_comment(&$vars) {
  // The 'view' attribute of the node is added in template_preprocess_views_view_row_comment()
  if (!empty($vars['node']->view) && !empty($vars['node']->view->name)) {
    $vars['view'] = &$vars['node']->view;
    $vars['theme_hook_suggestions'][] = 'comment__view__' . $vars['node']->view->name;
    if (!empty($vars['node']->view->current_display)) {
      $vars['theme_hook_suggestions'][] = 'comment__view__' . $vars['node']->view->name . '__' . $vars['node']->view->current_display;
    }
  }
}

/*
 * Implement hook_permission().
 */
function views_permission() {
  return array(
    'administer views' => array(
      'title' => t('Administer views'),
      'description' => t('Access the views administration pages.'),
    ),
    'access all views' => array(
      'title' => t('Bypass views access control'),
      'description' => t('Bypass access control when accessing views.'),
    ),
  );
}

/**
 * Implement hook_menu().
 */
function views_menu() {
  // Any event which causes a menu_rebuild could potentially mean that the
  // Views data is updated -- module changes, profile changes, etc.
  views_invalidate_cache();
  $items = array();
  $items['views/ajax'] = array(
    'title' => 'Views',
    'page callback' => 'views_ajax',
    'theme callback' => 'ajax_base_page_theme',
    'delivery callback' => 'ajax_deliver',
    'access callback' => TRUE,
    'description' => 'Ajax callback for view loading.',
    'type' => MENU_CALLBACK,
    'file' => 'includes/ajax.inc',
  );
  // Path is not admin/structure/views due to menu complications with the wildcards from
  // the generic ajax callback.
  $items['admin/views/ajax/autocomplete/user'] = array(
    'page callback' => 'views_ajax_autocomplete_user',
    'theme callback' => 'ajax_base_page_theme',
    'access callback' => 'user_access',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
    'file' => 'includes/ajax.inc',
  );
  // Define another taxonomy autocomplete because the default one of drupal
  // does not support a vid a argument anymore
  $items['admin/views/ajax/autocomplete/taxonomy'] = array(
    'page callback' => 'views_ajax_autocomplete_taxonomy',
    'theme callback' => 'ajax_base_page_theme',
    'access callback' => 'user_access',
    'access arguments' => array('access content'),
    'type' => MENU_CALLBACK,
    'file' => 'includes/ajax.inc',
  );
  return $items;
}

/**
 * Implement hook_menu_alter().
 */
function views_menu_alter(&$callbacks) {
  $our_paths = array();
  $views = views_get_applicable_views('uses hook menu');
  foreach ($views as $data) {
    list($view, $display_id) = $data;
    $result = $view->execute_hook_menu($display_id, $callbacks);
    if (is_array($result)) {
      // The menu system doesn't support having two otherwise
      // identical paths with different placeholders.  So we
      // want to remove the existing items from the menu whose
      // paths would conflict with ours.

      // First, we must find any existing menu items that may
      // conflict.  We use a regular expression because we don't
      // know what placeholders they might use.  Note that we
      // first construct the regex itself by replacing %views_arg
      // in the display path, then we use this constructed regex
      // (which will be something like '#^(foo/%[^/]*/bar)$#') to
      // search through the existing paths.
      $regex = '#^(' . preg_replace('#%views_arg#', '%[^/]*', implode('|', array_keys($result))) . ')$#';
      $matches = preg_grep($regex, array_keys($callbacks));

      // Remove any conflicting items that were found.
      foreach ($matches as $path) {
        // Don't remove the paths we just added!
        if (!isset($our_paths[$path])) {
          unset($callbacks[$path]);
        }
      }
      foreach ($result as $path => $item) {
        if (!isset($callbacks[$path])) {
          // Add a new item, possibly replacing (and thus effectively
          // overriding) one that we removed above.
          $callbacks[$path] = $item;
        }
        else {
          // This item already exists, so it must be one that we added.
          // We change the various callback arguments to pass an array
          // of possible display IDs instead of a single ID.
          $callbacks[$path]['page arguments'][1] = (array)$callbacks[$path]['page arguments'][1];
          $callbacks[$path]['page arguments'][1][] = $display_id;
          $callbacks[$path]['access arguments'][] = $item['access arguments'][0];
          $callbacks[$path]['load arguments'][1] = (array)$callbacks[$path]['load arguments'][1];
          $callbacks[$path]['load arguments'][1][] = $display_id;
        }
        $our_paths[$path] = TRUE;
      }
    }
  }

  // Save memory: Destroy those views.
  foreach ($views as $data) {
    list($view, $display_id) = $data;
    $view->destroy();
  }
}

/**
 * Helper function for menu loading. This will automatically be
 * called in order to 'load' a views argument; primarily it
 * will be used to perform validation.
 *
 * @param $value
 *   The actual value passed.
 * @param $name
 *   The name of the view. This needs to be specified in the 'load function'
 *   of the menu entry.
 * @param $display_id
 *   The display id that will be loaded for this menu item.
 * @param $index
 *   The menu argument index. This counts from 1.
 */
function views_arg_load($value, $name, $display_id, $index) {
  static $views = array();

  // Make sure we haven't already loaded this views argument for a similar menu
  // item elsewhere.
  $key = $name . ':' . $display_id . ':' . $value . ':' . $index;
  if (isset($views[$key])) {
    return $views[$key];
  }

  if ($view = views_get_view($name)) {
    $view->set_display($display_id);
    $view->init_handlers();

    $ids = array_keys($view->argument);

    $indexes = array();
    $path = explode('/', $view->get_path());

    foreach ($path as $id => $piece) {
      if ($piece == '%' && !empty($ids)) {
        $indexes[$id] = array_shift($ids);
      }
    }

    if (isset($indexes[$index])) {
      if (isset($view->argument[$indexes[$index]])) {
        $arg = $view->argument[$indexes[$index]]->validate_argument($value) ? $value : FALSE;
        $view->destroy();

        // Store the output in case we load this same menu item again.
        $views[$key] = $arg;
        return $arg;
      }
    }
    $view->destroy();
  }
}

/**
 * Page callback entry point; requires a view and a display id, then
 * passes control to the display handler.
 */
function views_page() {
  $args = func_get_args();
  $name = array_shift($args);
  $display_id = array_shift($args);

  // Load the view and render it.
  if ($view = views_get_view($name)) {
    return $view->execute_display($display_id, $args);
  }

  // Fallback; if we get here no view was found or handler was not valid.
  return drupal_not_found();
}

/**
 * Implements hook_page_alter().
 */
function views_page_alter(&$page) {
  // If the main content of this page contains a view, attach its contextual
  // links to the overall page array. This allows them to be rendered directly
  // next to the page title.
  $view = views_get_page_view();
  if (!empty($view)) {
    // If a module is still putting in the display like we used to, catch that.
    if (is_subclass_of($view, 'views_plugin_display')) {
      $view = $view->view;
    }

    views_add_contextual_links($page, 'page', $view, $view->current_display);
  }
}

/**
 * Implements MODULE_preprocess_HOOK().
 */
function views_preprocess_html(&$variables) {
  // If the page contains a view as its main content, contextual links may have
  // been attached to the page as a whole; for example, by views_page_alter().
  // This allows them to be associated with the page and rendered by default
  // next to the page title (which we want). However, it also causes the
  // Contextual Links module to treat the wrapper for the entire page (i.e.,
  // the <body> tag) as the HTML element that these contextual links are
  // associated with. This we don't want; for better visual highlighting, we
  // prefer a smaller region to be chosen. The region we prefer differs from
  // theme to theme and depends on the details of the theme's markup in
  // page.tpl.php, so we can only find it using JavaScript. We therefore remove
  // the "contextual-links-region" class from the <body> tag here and add
  // JavaScript that will insert it back in the correct place.
  if (!empty($variables['page']['#views_contextual_links_info'])) {
    $key = array_search('contextual-links-region', $variables['classes_array']);
    if ($key !== FALSE) {
      unset($variables['classes_array'][$key]);
      // Add the JavaScript, with a group and weight such that it will run
      // before modules/contextual/contextual.js.
      drupal_add_js(drupal_get_path('module', 'views') . '/js/views-contextual.js', array('group' => JS_LIBRARY, 'weight' => -1));
    }
  }
}

/**
 * Implements hook_contextual_links_view_alter().
 */
function views_contextual_links_view_alter(&$element, $items) {
  // If we are rendering views-related contextual links attached to the overall
  // page array, add a class to the list of contextual links. This will be used
  // by the JavaScript added in views_preprocess_html().
  if (!empty($element['#element']['#views_contextual_links_info']) && !empty($element['#element']['#type']) && $element['#element']['#type'] == 'page') {
    $element['#attributes']['class'][] = 'views-contextual-links-page';
  }
}

/**
 * Implement hook_block_info().
 */
function views_block_info() {
  // Try to avoid instantiating all the views just to get the blocks info.
  views_include('cache');
  $cache = views_cache_get('views_block_items', TRUE);
  if ($cache && is_array($cache->data)) {
    return $cache->data;
  }

  $items = array();
  $views = views_get_all_views();
  foreach ($views as $view) {
    // disabled views get nothing.
    if (!empty($view->disabled)) {
      continue;
    }

    $view->init_display();
    foreach ($view->display as $display_id => $display) {

      if (isset($display->handler) && !empty($display->handler->definition['uses hook block'])) {
        $result = $display->handler->execute_hook_block_list();
        if (is_array($result)) {
          $items = array_merge($items, $result);
        }
      }

      if (isset($display->handler) && $display->handler->get_option('exposed_block')) {
        $result = $display->handler->get_special_blocks();
        if (is_array($result)) {
          $items = array_merge($items, $result);
        }
      }
    }
  }

  // block.module has a delta length limit of 32, but our deltas can
  // unfortunately be longer because view names can be 32 and display IDs
  // can also be 32. So for very long deltas, change to md5 hashes.
  $hashes = array();

  // get the keys because we're modifying the array and we don't want to
  // confuse PHP too much.
  $keys = array_keys($items);
  foreach ($keys as $delta) {
    if (strlen($delta) >= 32) {
      $hash = md5($delta);
      $hashes[$hash] = $delta;
      $items[$hash] = $items[$delta];
      unset($items[$delta]);
    }
  }

  // Only save hashes if they have changed.
  $old_hashes = variable_get('views_block_hashes', array());
  if ($hashes != $old_hashes) {
    variable_set('views_block_hashes', $hashes);
  }
  // Save memory: Destroy those views.
  foreach ($views as $view) {
    $view->destroy();
  }

  views_cache_set('views_block_items', $items, TRUE);

  return $items;
}

/**
 * Implement hook_block_view().
 */
function views_block_view($delta) {
  $start = microtime(TRUE);
  // if this is 32, this should be an md5 hash.
  if (strlen($delta) == 32) {
    $hashes = variable_get('views_block_hashes', array());
    if (!empty($hashes[$delta])) {
      $delta = $hashes[$delta];
    }
  }

  // This indicates it's a special one.
  if (substr($delta, 0, 1) == '-') {
    list($nothing, $type, $name, $display_id) = explode('-', $delta);
    // Put the - back on.
    $type = '-' . $type;
    if ($view = views_get_view($name)) {
      if ($view->access($display_id)) {
        $view->set_display($display_id);
        if (isset($view->display_handler)) {
          $output = $view->display_handler->view_special_blocks($type);
          // Before returning the block output, convert it to a renderable
          // array with contextual links.
          views_add_block_contextual_links($output, $view, $display_id, 'special_block_' . $type);
          $view->destroy();
          return $output;
        }
      }
      $view->destroy();
    }
  }

  // If the delta doesn't contain valid data return nothing.
  $explode = explode('-', $delta);
  if (count($explode) != 2) {
    return;
  }
  list($name, $display_id) = $explode;
  // Load the view
  if ($view = views_get_view($name)) {
    if ($view->access($display_id)) {
      $output = $view->execute_display($display_id);
      // Before returning the block output, convert it to a renderable array
      // with contextual links.
      views_add_block_contextual_links($output, $view, $display_id);
      $view->destroy();
      return $output;
    }
    $view->destroy();
  }
}

/**
 * Converts Views block content to a renderable array with contextual links.
 *
 * @param $block
 *   An array representing the block, with the same structure as the return
 *   value of hook_block_view(). This will be modified so as to force
 *   $block['content'] to be a renderable array, containing the optional
 *   '#contextual_links' property (if there are any contextual links associated
 *   with the block).
 * @param $view
 *   The view that was used to generate the block content.
 * @param $display_id
 *   The ID of the display within the view that was used to generate the block
 *   content.
 * @param $block_type
 *   The type of the block. If it's block it's a regular views display,
 *   but 'special_block_-exp' exist as well.
 */
function views_add_block_contextual_links(&$block, $view, $display_id, $block_type = 'block') {
  // Do not add contextual links to an empty block.
  if (!empty($block['content'])) {
    // Contextual links only work on blocks whose content is a renderable
    // array, so if the block contains a string of already-rendered markup,
    // convert it to an array.
    if (is_string($block['content'])) {
      $block['content'] = array('#markup' => $block['content']);
    }
    // Add the contextual links.
    views_add_contextual_links($block['content'], $block_type, $view, $display_id);
  }
}

/**
 * Adds contextual links associated with a view display to a renderable array.
 *
 * This function should be called when a view is being rendered in a particular
 * location and you want to attach the appropriate contextual links (e.g.,
 * links for editing the view) to it.
 *
 * The function operates by checking the view's display plugin to see if it has
 * defined any contextual links that are intended to be displayed in the
 * requested location; if so, it attaches them. The contextual links intended
 * for a particular location are defined by the 'contextual links' and
 * 'contextual links locations' properties in hook_views_plugins() and
 * hook_views_plugins_alter(); as a result, these hook implementations have
 * full control over where and how contextual links are rendered for each
 * display.
 *
 * In addition to attaching the contextual links to the passed-in array (via
 * the standard #contextual_links property), this function also attaches
 * additional information via the #views_contextual_links_info property. This
 * stores an array whose keys are the names of each module that provided
 * views-related contextual links (same as the keys of the #contextual_links
 * array itself) and whose values are themselves arrays whose keys ('location',
 * 'view_name', and 'view_display_id') store the location, name of the view,
 * and display ID that were passed in to this function. This allows you to
 * access information about the contextual links and how they were generated in
 * a variety of contexts where you might be manipulating the renderable array
 * later on (for example, alter hooks which run later during the same page
 * request).
 *
 * @param $render_element
 *   The renderable array to which contextual links will be added. This array
 *   should be suitable for passing in to drupal_render() and will normally
 *   contain a representation of the view display whose contextual links are
 *   being requested.
 * @param $location
 *   The location in which the calling function intends to render the view and
 *   its contextual links. The core system supports three options for this
 *   parameter:
 *   - 'block': Used when rendering a block which contains a view. This
 *     retrieves any contextual links intended to be attached to the block
 *     itself.
 *   - 'page': Used when rendering the main content of a page which contains a
 *     view. This retrieves any contextual links intended to be attached to the
 *     page itself (for example, links which are displayed directly next to the
 *     page title).
 *   - 'view': Used when rendering the view itself, in any context. This
 *     retrieves any contextual links intended to be attached directly to the
 *     view.
 *   If you are rendering a view and its contextual links in another location,
 *   you can pass in a different value for this parameter. However, you will
 *   also need to use hook_views_plugins() or hook_views_plugins_alter() to
 *   declare, via the 'contextual links locations' array key, which view
 *   displays support having their contextual links rendered in the location
 *   you have defined.
 * @param $view
 *   The view whose contextual links will be added.
 * @param $display_id
 *   The ID of the display within $view whose contextual links will be added.
 *
 * @see hook_views_plugins()
 * @see views_block_view()
 * @see views_page_alter()
 * @see template_preprocess_views_view()
 */
function views_add_contextual_links(&$render_element, $location, $view, $display_id) {
  // Do not do anything if the view is configured to hide its administrative
  // links.
  if (empty($view->hide_admin_links)) {
    // Also do not do anything if the display plugin has not defined any
    // contextual links that are intended to be displayed in the requested
    // location.
    $plugin = views_fetch_plugin_data('display', $view->display[$display_id]->display_plugin);
    // If contextual links locations are not set, provide a sane default. (To
    // avoid displaying any contextual links at all, a display plugin can still
    // set 'contextual links locations' to, e.g., an empty array.)
    $plugin += array('contextual links locations' => array('view'));
    // On exposed_forms blocks contextual links should always be visible.
    $plugin['contextual links locations'][] = 'special_block_-exp';
    $has_links = !empty($plugin['contextual links']) && !empty($plugin['contextual links locations']);
    if ($has_links && in_array($location, $plugin['contextual links locations'])) {
      foreach ($plugin['contextual links'] as $module => $link) {
        $args = array();
        $valid = TRUE;
        if (!empty($link['argument properties'])) {
          foreach ($link['argument properties'] as $property) {
            // If the plugin is trying to create an invalid contextual link
            // (for example, "path/to/{$view->property}", where $view->property
            // does not exist), we cannot construct the link, so we skip it.
            if (!property_exists($view, $property)) {
              $valid = FALSE;
              break;
            }
            else {
              $args[] = $view->{$property};
            }
          }
        }
        // If the link was valid, attach information about it to the renderable
        // array.
        if ($valid) {
          $render_element['#contextual_links'][$module] = array($link['parent path'], $args);
          $render_element['#views_contextual_links_info'][$module] = array(
            'location' => $location,
            'view' => $view,
            'view_name' => $view->name,
            'view_display_id' => $display_id,
          );
        }
      }
    }
  }
}

/**
 * Returns an array of language names.
 *
 * This is a one to one copy of locale_language_list because we can't rely on enabled locale module.
 *
 * @param $field
 *   'name' => names in current language, localized
 *   'native' => native names
 * @param $all
 *   Boolean to return all languages or only enabled ones
 *
 * @see locale_language_list
 */
function views_language_list($field = 'name', $all = FALSE) {
  if ($all) {
    $languages = language_list();
  }
  else {
    $languages = language_list('enabled');
    $languages = $languages[1];
  }
  $list = array();
  foreach ($languages as $language) {
    $list[$language->language] = ($field == 'name') ? t($language->name) : $language->$field;
  }
  return $list;
}

/**
 * Implements hook_flush_caches().
 */
function views_flush_caches() {
  return array('cache_views', 'cache_views_data');
}

/**
 * Implements hook_field_create_instance.
 */
function views_field_create_instance($instance) {
  cache_clear_all('*', 'cache_views', TRUE);
  cache_clear_all('*', 'cache_views_data', TRUE);
}

/**
 * Implements hook_field_update_instance.
 */
function views_field_update_instance($instance, $prior_instance) {
  cache_clear_all('*', 'cache_views', TRUE);
  cache_clear_all('*', 'cache_views_data', TRUE);
}

/**
 * Implements hook_field_delete_instance.
 */
function views_field_delete_instance($instance) {
  cache_clear_all('*', 'cache_views', TRUE);
  cache_clear_all('*', 'cache_views_data', TRUE);
}

/**
 * Invalidate the views cache, forcing a rebuild on the next grab of table data.
 */
function views_invalidate_cache() {
  cache_clear_all('*', 'cache_views', TRUE);
}

/**
 * Access callback to determine if the user can import Views.
 *
 * View imports require an additional access check because they are PHP
 * code and PHP is more locked down than administer views.
 */
function views_import_access() {
  return user_access('administer views') && user_access('use PHP for settings');
}

/**
 * Determine if the logged in user has access to a view.
 *
 * This function should only be called from a menu hook or some other
 * embedded source. Each argument is the result of a call to
 * views_plugin_access::get_access_callback() which is then used
 * to determine if that display is accessible. If *any* argument
 * is accessible, then the view is accessible.
 */
function views_access() {
  $args = func_get_args();
  foreach ($args as $arg) {
    if ($arg === TRUE) {
      return TRUE;
    }

    if (!is_array($arg)) {
      continue;
    }

    list($callback, $arguments) = $arg;
    $arguments = $arguments ? $arguments : array();
    // Bring dynamic arguments to the access callback.
    foreach ($arguments as $key => $value) {
      if (is_int($value) && isset($args[$value])) {
        $arguments[$key] = $args[$value];
      }
    }
    if (function_exists($callback) && call_user_func_array($callback, $arguments)) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
 * Access callback for the views_plugin_access_perm access plugin.
 *
 * Determine if the specified user has access to a view on the basis of
 * permissions. If the $account argument is omitted, the current user
 * is used.
 */
function views_check_perm($perm, $account = NULL) {
  return user_access($perm, $account) || user_access('access all views', $account);
}

/**
 * Access callback for the views_plugin_access_role access plugin.

 * Determine if the specified user has access to a view on the basis of any of
 * the requested roles. If the $account argument is omitted, the current user
 * is used.
 */
function views_check_roles($rids, $account = NULL) {
  global $user;
  $account = isset($account) ? $account : $user;
  $roles = array_keys($account->roles);
  $roles[] = $account->uid ? DRUPAL_AUTHENTICATED_RID : DRUPAL_ANONYMOUS_RID;
  return user_access('access all views', $account) || array_intersect(array_filter($rids), $roles);
}
// ------------------------------------------------------------------
// Functions to help identify views that are running or ran

/**
 * Set the current 'page view' that is being displayed so that it is easy
 * for other modules or the theme to identify.
 */
function &views_set_page_view($view = NULL) {
  static $cache = NULL;
  if (isset($view)) {
    $cache = $view;
  }

  return $cache;
}

/**
 * Find out what, if any, page view is currently in use. Please note that
 * this returns a reference, so be careful! You can unintentionally modify the
 * $view object.
 *
 * @return view
 *   A fully formed, empty $view object.
 */
function &views_get_page_view() {
  return views_set_page_view();
}

/**
 * Set the current 'current view' that is being built/rendered so that it is
 * easy for other modules or items in drupal_eval to identify
 *
 * @return view
 */
function &views_set_current_view($view = NULL) {
  static $cache = NULL;
  if (isset($view)) {
    $cache = $view;
  }

  return $cache;
}

/**
 * Find out what, if any, current view is currently in use. Please note that
 * this returns a reference, so be careful! You can unintentionally modify the
 * $view object.
 *
 * @return view
 */
function &views_get_current_view() {
  return views_set_current_view();
}

// ------------------------------------------------------------------
// Include file helpers

/**
 * Include views .inc files as necessary.
 */
function views_include($file) {
  ctools_include($file, 'views');
}

/**
 * Load views files on behalf of modules.
 */
function views_module_include($api, $reset = FALSE) {
  if ($reset) {
    $cache = &drupal_static('ctools_plugin_api_info');
    if (isset($cache['views']['views'])) {
      unset($cache['views']['views']);
    }
  }
  ctools_include('plugins');
  return ctools_plugin_api_include('views', $api, views_api_minimum_version(), views_api_version());
}

/**
 * Get a list of modules that support the current views API.
 */
function views_get_module_apis($api = 'views', $reset = FALSE) {
  if ($reset) {
    $cache = &drupal_static('ctools_plugin_api_info');
    if (isset($cache['views']['views'])) {
      unset($cache['views']['views']);
    }
  }
  ctools_include('plugins');
  return ctools_plugin_api_info('views', $api, views_api_minimum_version(), views_api_version());
}

/**
 * Include views .css files.
 */
function views_add_css($file) {
  // We set preprocess to FALSE because we are adding the files conditionally,
  // and we don't want to generate duplicate cache files.
  // TODO: at some point investigate adding some files unconditionally and
  // allowing preprocess.
  drupal_add_css(drupal_get_path('module', 'views') . "/css/$file.css", array('preprocess' => FALSE));
}

/**
 * Include views .js files.
 */
function views_add_js($file) {
  // If javascript has been disabled by the user, never add js files.
  if (variable_get('views_no_javascript', FALSE)) {
    return;
  }
  static $base = TRUE, $ajax = TRUE;
  if ($base) {
    drupal_add_js(drupal_get_path('module', 'views') . "/js/base.js");
    $base = FALSE;
  }
  if ($ajax && in_array($file, array('ajax', 'ajax_view'))) {
    drupal_add_library('system', 'drupal.ajax');
    drupal_add_library('system', 'jquery.form');
    $ajax = FALSE;
  }
  ctools_add_js($file, 'views');
}

/**
 * Load views files on behalf of modules.
 */
function views_include_handlers($re
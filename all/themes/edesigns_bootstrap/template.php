<?php /* template.php */

function edesigns_bootstrap_process_page(&$vars) {
  $page = $vars['page']; //print 'yo'; exit;
  // Render and clean up navbar search form.
  $vars['navbar_search'] = drupal_render($vars['navbar_search']);
  $vars['navbar_search'] = strip_tags($vars['navbar_search'], '<form><input>');
}

function edesigns_bootstrap_preprocess_page(&$vars) {
  /* for portfolio */
  //if (current_path() == 'portfolio') {
    drupal_add_js(drupal_get_path('theme', 'edesigns_bootstrap') . '/prettyPhoto/js/jquery.prettyPhoto.js');
    drupal_add_css(drupal_get_path('theme', 'edesigns_bootstrap') . '/andia-style.css' );
    drupal_add_css(drupal_get_path('theme', 'edesigns_bootstrap') . '/prettyPhoto/css/prettyPhoto.css' );
  //} 

    if (drupal_is_front_page()) {
      //drupal_add_js(drupal_get_path('theme', 'edesigns_bootstrap') . '/js/jquery.parallax-1.1.3.js');
      //drupal_add_js(drupal_get_path('theme', 'edesigns_bootstrap') . '/js/bootstrap-scrollspy.js');
      //drupal_add_js(drupal_get_path('theme', 'edesigns_bootstrap') . '/js/bootstrap-collapse.js');
      //drupal_add_js(drupal_get_path('theme', 'edesigns_bootstrap') . '/js/jquery.localscroll-1.2.7-min.js');
      //drupal_add_js(drupal_get_path('theme', 'edesigns_bootstrap') . '/js/jquery.scrollTo-1.4.2-min.js');
      drupal_add_js(drupal_get_path('module', 'edesigns') . '/js/edesigns_scroll.js');

    }
   

	// Build navbar search form.
  $vars['navbar_search'] = FALSE;
  if (module_exists('search')) {
    $vars['navbar_search'] = drupal_get_form('_tweme_navbar_search_form');
    // Add custom classes.
    $vars['navbar_search']['#attributes']['class'][] = 'navbar-search-elastic';
    $vars['navbar_search']['#attributes']['class'][] = 'pull-right';
    $vars['navbar_search']['#attributes']['class'][] = 'hidden-phone';
    //print_r($vars['navbar_search']);
  }

}
/**
 * Helper function: returns a navbar search form.
 */
function _tweme_navbar_search_form($form, &$form_state) {
  $form = search_form($form, $form_state);
  // Set additional attributes.
  $form['#attributes']['class'][] = 'navbar-search';
  $form['basic']['keys']['#title'] = '';
  $form['basic']['keys']['#attributes']['class'][] = 'search-query';
  $form['basic']['keys']['#attributes']['placeholder'] = t('Search');

  // Unset unnecessary data and attributes.
  unset($form['basic']['submit']);
  unset($form['basic']['#type']);
  unset($form['basic']['#attributes']);

  return $form;
}

function edesigns_bootstrap_item_list99(&$variables) {
  // my custom stuff done to theme_item_list 
  return 'test';
}


?>

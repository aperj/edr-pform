<?php
/**
 * @file
 * portfolio_view.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function portfolio_view_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['blog-recent'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'recent',
    'module' => 'blog',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'edesigns_bootstrap' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'edesigns_bootstrap',
        'weight' => '-8',
      ),
      'seven' => array(
        'region' => 'dashboard_inactive',
        'status' => '1',
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '1',
  );

  $export['edesigns-edesigns_poweredby'] = array(
    'cache' => '1',
    'custom' => '0',
    'delta' => 'edesigns_poweredby',
    'module' => 'edesigns',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'edesigns_bootstrap' => array(
        'region' => 'footer',
        'status' => '1',
        'theme' => 'edesigns_bootstrap',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['search-form'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'form',
    'module' => 'search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bartik',
        'weight' => '-1',
      ),
      'bootstrap' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '-1',
      ),
      'edesigns_bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'edesigns_bootstrap',
        'weight' => '-1',
      ),
      'seven' => array(
        'region' => 'dashboard_sidebar',
        'status' => '1',
        'theme' => 'seven',
        'weight' => '-10',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['user-login'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'login',
    'module' => 'user',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => 'sidebar_first',
        'status' => '1',
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'edesigns_bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'edesigns_bootstrap',
        'weight' => '0',
      ),
      'seven' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'seven',
        'weight' => '10',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['views-portfolio-block_1'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'portfolio-block_1',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => '0',
      ),
      'bootstrap' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap',
        'weight' => '0',
      ),
      'edesigns_bootstrap' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'edesigns_bootstrap',
        'weight' => '-9',
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  return $export;
}

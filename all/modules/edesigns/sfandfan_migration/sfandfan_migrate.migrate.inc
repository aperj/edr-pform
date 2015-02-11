<?php
function migrate_sfandfan_migration_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'xyz' => array(
        'title' => t('XYZ Migrations'),
      ),
    ),
    'migrations' => array(
      'XyzUser' => array(
        'class_name' => 'MigrateXyzUserMigration',
        'group_name' => 'xyz',
      ),
      'XyzArticle' => array(
        'class_name' => 'MigrateXyzArticleMigration',
        'group_name' => 'xyz',
      ),
    ),
  );
  return $api;
}
?>


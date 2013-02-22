<?php

// Plugin definition
$plugin = array(
  'title' => t('Apigee three column'),
  'category' => t('Columns: 3'),
//  'icon' => 'threecol_33_34_33.png',
  'theme' => 'apigee_threecol',
  'css' => 'apigee_threecol.css',
  'regions' => array(
    'top' => t('Top'),
    'left' => t('Left side'),
    'middle' => t('Middle column'),
    'right' => t('Right side'),
    'bottom' => t('Bottom'),
    'sidebar' => t('Sidebar'),
   ),
);

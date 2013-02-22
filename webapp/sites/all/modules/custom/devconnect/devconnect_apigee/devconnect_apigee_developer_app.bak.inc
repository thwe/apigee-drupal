<?php

module_load_include('inc', 'devconnect_apigee', 'devconnect_apigee');

class DevConnectApigeeDeveloperApp extends DevConnectApigee {

  private $private_access_values;

  public function __construct(&$user) {
    parent::__construct();
    $this->baseURI = $this->endpoint . '/organizations/' . $this->org . '/developers/' . $user->mail . '/apps';
    $this->private_access_values = array('internal', 'private');
  }

  public function Validate($app) {
    return self::call($this->baseURI . '/' . rawurlencode($app));
  }

  public function Create($values) {
    return self::call($this->baseURI, 'POST', self::translateFormValuesToPayloadArray($values));
  }

  public function Delete($app) {
    return self::call($this->baseURI . '/' . rawurlencode($app), 'DELETE');
  }

  public function Update($app, $values) {
    return self::call($this->baseURI . '/' . rawurlencode($app), 'POST', self::translateFormValuesToPayloadArray($values));
  }

  public function GetList() {
    return self::call($this->baseURI);
  }

  public function GetListDetail() {
    return self::call($this->baseURI, 'GET', array('expand' => 'true'));
  }

  public function GetInfo($app) {
    $info = self::call($this->baseURI . '/' . rawurlencode($app));
    $info['data']['parsed_attributes'] = self::parse_attributes($info['data']);
    return $info;
  }

  public function GetAPIProductDetail($apiproduct, $hide_private = TRUE) {
    static $api_products;
    if (!isset($api_products)) {
      $api_products = array();
    }
    if (!isset($api_products[$apiproduct])) {
      try {
        $results = self::call($this->endpoint . '/organizations/' . $this->org . '/apiproducts/' . $apiproduct);
      } catch (Exception $e) {
        watchdog('devconnect_apigee_developer_app', $e->getMessage(), array(), WATCHDOG_ERROR);
        return array();
      }
      $info = $results['data'];

      $attributes = self::parse_attributes($info);
      $info['parsed_attributes'] = $attributes;
      if (isset($attributes['access']) && in_array($attributes['access'], $this->private_access_values)) {
        drupal_set_message(t('This API product is not publicly available.'), 'error');
        if ($hide_private) {
          watchdog('devconnect_apigee_developer_app', 'Trying to get detail on private apiproduct ' . $apiproduct);
        }
        $info['hidden'] = TRUE;
      }
      else {
        $info['hidden'] = FALSE;
      }
      $api_products[$apiproduct] = $info;
    }
    $info = $api_products[$apiproduct];
    if ($hide_private && $info['hidden']) {
      return array();
    }
    return $info;
  }

  /**
   * Returns list of all API Products, formatted for display on app create/edit page.
   *
   * This was originally in devconnect_apigee_org.inc but since that file has gone away, it was moved here.
   *
   * @return array
   */
  public function GetAPIProductsOptions() {
    // need expanded view to get displayName and access.
    $results = self::call($this->endpoint . '/organizations/' . $this->org . '/apiproducts', 'GET', array('expand' => 'true'));
    $options = array();
    foreach ($results['data']['apiProduct'] as $product) {
      $attributes = self::parse_attributes($product);
      // Omit API products whose access (if set) marks it as private/internal
      if (!isset($attributes['access']) || !in_array($attributes['access'], $this->private_access_values)) {
        $key = 'prod-' . $product['name'];
        $options[$key] = $product['displayName'];
      }
    }
    return $options;
  }

  private static function translateFormValuesToPayloadArray($values) {
    $api_products = array();
    if (isset($values['api_product'])) {
      if (is_array($values['api_product'])) {
        foreach ($values['api_product'] as $key => $value) {
          if ($value) {
            $api_products[] = str_replace('prod-', '', $key);
          }
        }
      }
      else {
        // Allow customized sites to declare api_product as non-multiple.
        // This results in a scalar value rather than an array.
        $api_products[] = str_replace('prod-', '', $values['api_product']);
      }
    }
    $payload = array(
      'accessType' => $values['access_type'],
      'apiProducts' => $api_products,
      'callbackUrl' => $values['callback_url'],
      'name' => $values['machine_name']
    );

    $attributes = array();
    foreach($values as $key => $value) {
      if (substr($key, 0, 10) == 'attribute_') {
        $attributes[] = array(
          'name' => substr($key, 10),
          'value' => $value
        );
      }
    }
    if (count($attributes) > 0) {
      $payload['attributes'] = $attributes;
    }

    return $payload;
  }
}


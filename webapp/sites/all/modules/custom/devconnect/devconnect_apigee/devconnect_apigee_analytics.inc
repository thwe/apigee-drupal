<?php

/**
 * @file
 *  Class to query the Apigee analytics API. All accesses are reads (GET).
 * @author Daniel Johnson <djohnson@apigee.com>
 */

module_load_include('inc', 'devconnect_apigee', 'devconnect_apigee');

class DevConnectApigeeAnalyticsParameterException extends Exception {}

class DevConnectApigeeAnalytics extends DevConnectApigee {

  private $environment;

  /**
   * Class constructor.
   *
   * @param string $environment
   * @param int $api_version
   */
  public function __construct($environment = NULL) {
    //parent::__construct();
    // TODO FIXME
    $this->org = 'enterprisestickers';
    $this->endpoint = 'https://api.enterprise.apigee.com/v1';
    $this->curl_auth = "djohnson@apigee.com:We+Love+APIs";

    if (!isset($environment)) {
      $environment = '*';
    }
    $this->setEnvironment($environment);
  }

  public function getEnvironments() {
    // TODO: query for actual environments, save in Drupal var
    return array('test', 'prod');
  }

  public function getEnvironment() {
    return $this->environment;
  }
  public function setEnvironment($env) {
    if ($env != '*' && !in_array($env, $this->getEnvironments())) {
      throw new DevConnectApigeeAnalyticsParameterException('Invalid environment "' . $env . '".');
    }
    $this->environment = $env;
    $this->baseURI = $this->endpoint . '/organizations/' . $this->org . '/environments/' . $env . '/stats/';
  }

  public function getDeveloperAppByName($appname, $metric, $time_start, $time_end, $time_unit, $sort_by, $sort_order = 'ASC') {
    $params = $this->validate_parameters('apps', $metric, $time_start, $time_end, $time_unit, $sort_by, $sort_order);
    $params['filter'] = '(developer_app eq \'' . urlencode($appname) . '\')';

    return self::call($this->baseURI . 'apps', 'GET', $params, $this->curl_auth);
  }

  /**
   * Returns a keyed array of metrics allowable for a given call type. Array keys are machine names
   * and values are human-readable names.
   *
   * @param string $call_type
   * @return array
   */
  public static function getMetrics($call_type) {
    switch ($call_type) {
      case 'apis':
        $metrics = array(
          'message_count' => t('Message Count'),
          'message_count-first24hrs' => t('Message Count - First 24 Hours'),
          'message_count-second24hrs' => t('Message Count - Second 24 Hours'),
          'error_count' => t('Error Count'),
          'error_count-first24hrs' => t('Error Count - First 24 Hours'),
          'total_response_time' => t('Total Response Time'),
          'max_response_time' => t('Maximum Response Time'),
          'min_response_time' => t('Minimum Response Time'),
          'data_exchange_size' => t('Data Exchange Size'),
          'end_point_response_time' => t('Endpoint Response Time')
        );
        break;
      case 'apps':
        $metrics = array(
          'message_count' => t('Message Count'),
          'message_count-first24hrs' => t('Message Count - First 24 Hours'),
          'message_count-second24hrs' => t('Message Count - Second 24 Hours'),
          'error_count' => t('Error Count'),
          'error_count-first24hrs' => t('Error Count - First 24 Hours'),
          'user_count' => t('User Count'),
          'user_count-first24hrs' => t('User Count - First 24 Hours'),
          'total_response_time' => t('Total Response Time'),
          'max_response_time' => t('Maximum Response Time'),
          'min_response_time' => t('Minimum Response Time'),
          'end_point_response_time' => t('Endpoint Response Time')
        );
        break;
      case 'devs':
        $metrics = array(
          'message_count' => t('Message Count'),
          'message_count-first24hrs' => t('Message Count - First 24 Hours'),
          'message_count-second24hrs' => t('Message Count - Second 24 Hours'),
          'error_count' => t('Error Count'),
          'error_count-first24hrs' => t('Error Count - First 24 Hours'),
          'app_count' => t('App Count'),
          'app_count-first24hrs' => t('App Count - First 24 Hours'),
          'user_count' => t('User Count'),
          'user_count-first24hrs' => t('User Count - First 24 Hours')
        );
        break;
      case 'traffic':
        $metrics = array(
          'message_count' => t('Message Count'),
          'message_count-first24hrs' => t('Message Count - First 24 Hours'),
          'message_count-second24hrs' => t('Message Count - Second 24 Hours'),
        );
        break;
      case 'envs':
        $metrics = array(
          'message_count' => t('Message Count'),
          'message_count-first24hrs' => t('Message Count - First 24 Hours'),
          'message_count-second24hrs' => t('Message Count - Second 24 Hours'),
          'error_count' => t('Error Count'),
          'error_count-first24hrs' => t('Error Count - First 24 Hours'),
          'api_count' => t('API Count')
        );
        break;
      case 'apiproducts':
        $metrics = array(
          'message_count' => t('Message Count'),
          'message_count-first24hrs' => t('Message Count - First 24 Hours'),
          'message_count-second24hrs' => t('Message Count - Second 24 Hours'),
          'app_count' => t('App Count'),
          'app_count-first24hrs' => t('App Count - First 24 Hours'),
          'developer_count' => t('Developer Count'),
          'developer_count-first24hrs' => t('Developer Count - First 24 Hours')
        );
        break;
      default:
        $metrics = array();
        break;
    }
    return $metrics;
  }

  /**
   * Returns a keyed array of allowable time units. Array keys are machine names
   * and values are human-readable names.
   *
   * @return array
   */
  public static function getTimeUnits() {
    return array(
      'second' => t('Second'),
      'minute' => t('Minute'),
      'hour' => t('Hour'),
      'day' => t('Day'),
      'week' => t('Week'),
      'month' => t('Month'),
      'quarter' => t('Quarter'),
      'year' => t('Year'),
      // The rest of these are just silly.
      /*
      'decade' => t('Decade'),
      'century' => t('Century'),
      'millennium' => t('Millenium')
      */
    );
  }

  /**
   * Validates common parameters for analytics API calls, and bundles them
   * into an appropriately-structured array to be passed into an HTTP call.
   *
   * @param string $call_type
   * @param string $metric
   * @param string $time_start
   * @param string $time_end
   * @param string $time_unit
   * @param string $sort_by
   * @param string $sort_order
   * @return array
   * @throws DevConnectApigeeAnalyticsParameterException
   */
  private function validate_parameters($call_type, $metric, $time_start, $time_end, $time_unit, $sort_by, $sort_order) {
    $metric_items = preg_split('!\s*,\s*!', $metric);
    if (count($metric_items) == 0) {
      throw new DevConnectApigeeAnalyticsParameterException('Missing metric.');
    }
    $valid_metrics = array_keys(self::getMetrics($call_type));
    foreach ($metric_items as $metric_item) {
      if (!in_array($metric_item, $valid_metrics)) {
        throw new DevConnectApigeeAnalyticsParameterException('Invalid metric.');
      }
    }
    $sort_by_items = preg_split('!\s*,\s*!', $sort_by);
    if (count($sort_by_items) == 0) {
      throw new DevConnectApigeeAnalyticsParameterException('Missing sort-by metric');
    }
    foreach ($sort_by_items as $sort_by_item) {
      if (!in_array($sort_by_item, $valid_metrics)) {
        throw new DevConnectApigeeAnalyticsParameterException('Invalid sort-by metric.');
      }
    }
    if (!in_array($time_unit, array_keys(self::getTimeUnits()))) {
      throw new DevConnectApigeeAnalyticsParameterException('Invalid time unit.');
    }
    $sort_order = strtoupper($sort_order);
    if ($sort_order != 'ASC' && $sort_order != 'DESC') {
      throw new DevConnectApigeeAnalyticsParameterException('Invalid sort order.');
    }
    $time_range = self::parse_time($time_start) . '~' . self::parse_time($time_end);
    $payload = array(
      'timeRange' => $time_range,
      'timeUnit' => $time_unit,
      'sortby' => join(',', $sort_by_items),
      'sort' => $sort_order,
      '_optimized' => 'js',
      'select' => join(',', $metric_items),
    );

    return $payload;
  }

  /**
   * Parses an incoming time string or Unix timestamp into an internally-acceptable time format.
   *
   * If the time input cannot be parsed, an exception is thrown.
   *
   * @static
   * @param string|int $time
   * @return string
   * @throws DevConnectApigeeAnalyticsParameterException
   */
  private static function parse_time($time) {
    $int_time = FALSE;
    if (is_int($time)) {
      $int_time = $time;
    }
    if (preg_match('!^([0-9]{1,2})/([0-9]{1,2})/([0-9]{4}) ([0-9]{2}):([0-9]{2})$!', $time, $matches)) {
      list (, $m, $d, $y, $h, $i) = $matches;
      if ($m >= 0 && $m <= 12 && $d >= 1 && $d <= 31 && $h >= 0 && $h <= 12 && $i >= 0 && $i <= 59) {
        $int_time = mktime($h, $i, 0, $m, $d, $y);
      }
    }
    if ($int_time === FALSE) {
      $int_time = @strtotime($time);
    }
    if ($int_time === FALSE) {
      throw new DevConnectApigeeAnalyticsParameterException('Invalid time format.');
    }
    return date('m/d/Y H:i', $int_time);
  }

}


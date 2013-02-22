<?php
class DevConnectApigee {
  protected $baseURI;
  protected $endpoint;
  protected $curl_auth;
  public $org;
  // stolen from drupal's common.inc file
  public static $responses = array(
    100 => 'Continue',
    101 => 'Switching Protocols',
    200 => 'OK',
    201 => 'Created',
    202 => 'Accepted',
    203 => 'Non-Authoritative Information',
    204 => 'No Content',
    205 => 'Reset Content',
    206 => 'Partial Content',
    300 => 'Multiple Choices',
    301 => 'Moved Permanently',
    302 => 'Found',
    303 => 'See Other',
    304 => 'Not Modified',
    305 => 'Use Proxy',
    307 => 'Temporary Redirect',
    400 => 'Bad Request',
    401 => 'Unauthorized',
    402 => 'Payment Required',
    403 => 'Forbidden',
    404 => 'Not Found',
    405 => 'Method Not Allowed',
    406 => 'Not Acceptable',
    407 => 'Proxy Authentication Required',
    408 => 'Request Time-out',
    409 => 'Conflict',
    410 => 'Gone',
    411 => 'Length Required',
    412 => 'Precondition Failed',
    413 => 'Request Entity Too Large',
    414 => 'Request-URI Too Large',
    415 => 'Unsupported Media Type',
    416 => 'Requested range not satisfiable',
    417 => 'Expectation Failed',
    500 => 'Internal Server Error',
    501 => 'Not Implemented',
    502 => 'Bad Gateway',
    503 => 'Service Unavailable',
    504 => 'Gateway Time-out',
    505 => 'HTTP Version not supported',
  );

  public function __construct($vars = array()) {
    $this->org = variable_get('devconnect_org', DEVCONNECT_APIGEE_DEFAULT_ORG);
    $this->endpoint = variable_get('devconnect_endpoint', DEVCONNECT_APIGEE_DEFAULT_ENDPOINT);
    $this->curl_auth = devconnect_apigee_get_curl_auth();
  }


  protected static function call($url, $method = "GET", $payload = array(), $curl_auth = NULL) {
    //header('Content-Type: text/plain'); print "URL: $url\n"; print_r(debug_backtrace()); die();
    $response = array();
    $response_code = 0;

    if (!isset($curl_auth)) {
      $curl_auth = devconnect_apigee_get_curl_auth();
    }
    // Hide the password for logging
    list($masked_auth) = explode(':', $curl_auth, 2);
    $masked_auth .= ':[encrypted]';

    $opts = array(
      CURLOPT_SSL_VERIFYPEER => FALSE,
      CURLOPT_RETURNTRANSFER => TRUE,
      CURLOPT_URL => $url,
      CURLOPT_HTTPHEADER => array(
        "Accept: application/json; charset=utf-8",
      ),
      CURLOPT_HTTPAUTH => variable_get("devconnect_authtype", CURLAUTH_BASIC),
      CURLOPT_USERPWD => $curl_auth,
    );

    switch (strtoupper($method)) {
      case "GET":
        $opts[CURLOPT_HTTPGET] = TRUE;
        if (count($payload) > 0) {
          $opts[CURLOPT_URL] .= "?" . http_build_query($payload);
        }
        //print $opts[CURLOPT_URL] . '<br>'; // FIXME
        break;

      case "POST":
        $opts[CURLOPT_POST] = TRUE;
        $opts[CURLOPT_POSTFIELDS] = json_encode($payload);
        $opts[CURLOPT_HTTPHEADER][] = "Content-Type: application/json; charset=utf-8";
        break;

      case "PUT":
        $opts[CURLOPT_PUT] = TRUE;
        $opts[CURLOPT_INFILE] = file_get_contents($payload['infile']);
        $opts[CURLOPT_INFILESIZE] = filesize($payload['infile']);
        break;

      default:
        $opts[CURLOPT_CUSTOMREQUEST] = $method;
        break;
    }
    //print_r($opts);
    try {
      $ch = curl_init();
      curl_setopt_array($ch, $opts);
      $response['raw'] = curl_exec($ch);
      $opts[CURLOPT_USERPWD] = $masked_auth;
      $response['opts'] = $opts;

      $response_code = curl_getinfo($ch, CURLINFO_HTTP_CODE);
      curl_close($ch);
      $response_message = self::$responses[$response_code];
      $response_class = floor($response_code / 100);
      if ($response_class > 2) {
        throw new Exception('Connection with the Apigee endpoint failed with the following status: ' . $response_code . ' ' . $response_message . '.');
      }

      if (strpos($response['raw'], "<?xml") === 0) {
        $response['data'] = new SimpleXMLElement($response['raw']);
        if ($response['data']->Code == 'rest.SchemaValidationFailure') {
          $message = $response['data']->Message;
          if (!strlen($message)) {
            $message = 'An error occurred while processing this request';
          }
          throw new Exception($message);
        }
      }
      else {
        $response['data'] = @json_decode($response['raw'], TRUE);
      }
      $response['code'] = $response_code;
      $response['code_status'] = $response_message;
      $response['code_class'] = $response_class;
      //if (!user_access("administer organization settings")) {
      //  $opts[CURLOPT_USERPWD] = "*****************************";
      //}
    } catch (Exception $e) {
      $error_message = $e->getMessage();
      watchdog(get_class(), "$method//message: $error_message");
      $response['exception'] = $error_message;
      if ($response_code) {
        $response['code'] = $response_code;
        $response['code_status'] = $response_message;
        $response['code_class'] = $response_class;
      }
    }

    watchdog(get_class(), $method . "//RESPONSE: " . print_r($response, TRUE));
    return $response;
  }

  protected static function parse_attributes($item) {
    $attributes = array();
    if (!empty($item['attributes'])) {
      foreach ($item['attributes'] as $attr) {
        $attributes[$attr['name']] = $attr['value'];
      }
    }
    return $attributes;
  }
}


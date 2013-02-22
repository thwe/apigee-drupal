<?php

module_load_include('inc', 'devconnect_apigee', 'devconnect_apigee');

class DevConnectApigeeDeveloper extends DevConnectApigee {

  /**
   * Indicates whether this class instance represents a pre-existing user.
   *
   * @var bool
   */
  private $existingUser = FALSE;

  /**
   * Workaround for R16.5 KMS bug:
   * If we update a Developer without sending a fully-populated apps array,
   * the developer -> apps relationship is lost. This is a KMS bug. When it is
   * fixed, the following const should be set to FALSE.
   */
  const REQUIRE_DEVELOPER_LOAD_BEFORE_UPDATE = TRUE;

  /**
   * Class constructor.
   *
   * @param string $orig
   */
  public function __construct($orig = '') {
    parent::__construct();
    $this->baseURI = $this->endpoint . '/organizations/' . $this->org . '/developers';
    if (strlen(trim($orig)) > 0) {
      $this->baseURI .= '/' . $orig;
      $this->existingUser = TRUE;
    }
  }

  /**
   * Validates that the given user exists by attempting to load the user.
   *
   * @return array|bool
   */
  public function Validate() {
    if ($this->existingUser) {
      return self::call($this->baseURI);
    }
    else {
      return FALSE;
    }
  }

  /**
   * Attempts to create a user if all required values are present
   *
   * @param object $account
   *    A user object
   * @return array|bool
   */
  public function Create($account) {
    if ($this->CheckForRequiredValues($account)) {
      $payload = self::ConvertDrupalAccountToPayloadArray($account);
      return self::call($this->baseURI, 'POST', $payload);
    }
    else {
      return FALSE;
    }
  }

  /**
   * Attempts to update an existing user in KMS.
   *
   * @see self::REQUIRE_DEVELOPER_LOAD_BEFORE_UPDATE
   *
   * @param object $account
   *    A user object
   * @return array
   */
  public function Update($account) {
    $payload = self::ConvertDrupalAccountToPayloadArray($account);
    if (self::REQUIRE_DEVELOPER_LOAD_BEFORE_UPDATE && $this->existingUser) {
      try {
        $developer = self::call($this->baseURI);
        $payload['apps'] = $developer['data']['apps'];
      }
      catch (Exception $e) {
        watchdog('devconnect_apigee_developer.inc', $e->getMessage(), WATCHDOG_ERROR);
      }
    }
    return self::call($this->baseURI, 'POST', $payload);
  }

  /**
   * Attempts to delete a user from KMS.
   *
   * @return array|bool
   */
  public function Delete() {
    if ($this->existingUser) {
      return self::call($this->baseURI, 'DELETE');
    }
    else {
      return FALSE;
    }
  }

  /**
   * Validates that user has a somewhat valid-looking email.
   *
   * If the user's first and last name entity fields are unset, updates them
   * based on the email address. This is strictly for KMS use, and no
   * entity_save is performed on the $account.
   *
   * @param object $account
   * @return bool
   */
  public function CheckForRequiredValues(&$account) {
    if (property_exists($account, 'mail') && (strpos($account->mail, '@'))) {
      $name = explode('@', $account->mail, 2);
      if (!isset($account->field_first_name[LANGUAGE_NONE][0]['value'])) {
        $account->field_first_name[LANGUAGE_NONE][0]['value'] = $name[0];
      }
      if (!isset($account->field_last_name[LANGUAGE_NONE][0]['value'])) {
        $account->field_last_name[LANGUAGE_NONE][0]['value'] = $name[1];
      }
      return TRUE;
    }
    else {
      return FALSE;
    }

  }

  /**
   * Takes a user object (with first/last name entity fields) and converts
   * it into an appropriately-structured PHP array suitable for JSON calls to
   * KMS.
   *
   * @static
   * @param object $account
   * @return array
   */
  private static function ConvertDrupalAccountToPayloadArray($account) {
    // Note that since R16.5 we do not pass password.
    $payload = array(
      'email' => $account->mail,
      'firstName' => $account->field_first_name[LANGUAGE_NONE][0]['value'],
      'lastName' => $account->field_last_name[LANGUAGE_NONE][0]['value'],
      'userName' => $account->name,
      'status' => ($account->status ? 'active' : 'inactive'),
      'attributes' => array()
    );

    $vars = get_object_vars($account);
    foreach ($vars as $key => $value) {
      if (substr($key, 0, 10) == 'attribute_') {
        $payload['attributes'][] = array(
          'name' => substr($key, 10),
          'value' => $value
        );
      }
    }

    return $payload;
  }
}


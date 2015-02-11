<?php

/**
 * @file
 * Provides Microsoft Translator plugin controller.
 *
 * Check @link http://msdn.microsoft.com/en-us/library/dd576287.aspx Microsoft
 * Translator @endlink. Note that we are using HTTP API.
 */

/**
 * Microsoft translator plugin controller.
 */
class TMGMTMicrosoftTranslatorPluginController extends TMGMTDefaultTranslatorPluginController {

  /**
   * Translation service URL.
   *
   * @var string
   */
  protected $translatorUrl = 'http://api.microsofttranslator.com/v2/Http.svc';

  /**
   * Authentication service URL.
   *
   * @var string
   */
  protected $authUrl = 'https://datamarket.accesscontrol.windows.net/v2/OAuth2-13/';

  /**
   * Maximum supported characters.
   *
   * @var int
   */
  protected $maxCharacters = 10000;

  /**
   * Overrides TMGMTDefaultTranslatorPluginController::isAvailable().
   */
  public function isAvailable(TMGMTTranslator $translator) {
    if ($translator->getSetting('clientid') && $translator->getSetting('clientsecret')) {
      return TRUE;
    }
    // Backwards compatibility for the old api key.
    if ($translator->getSetting('api')) {
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Overrides TMGMTDefaultTranslatorPluginController::canTranslate().
   */
  public function canTranslate(TMGMTTranslator $translator, TMGMTJob $job) {
    if (!parent::canTranslate($translator, $job)) {
      return FALSE;
    }
    foreach (array_filter(tmgmt_flatten_data($job->getData()), '_tmgmt_filter_data') as $value) {
      // If one of the texts in this job exceeds the max character count the job
      // can't be translated.
      if (drupal_strlen($value['#text']) > $this->maxCharacters) {
        return FALSE;
      }
    }
    return TRUE;
  }

  /**
   * Implements TMGMTTranslatorPluginControllerInterface::requestTranslation().
   */
  public function requestTranslation(TMGMTJob $job) {
    // Pull the source data array through the job and flatten it.
    $data = array_filter(tmgmt_flatten_data($job->getData()), '_tmgmt_filter_data');
    $translation = array();
    foreach ($data as $key => $value) {
      // Query the translator API.
      $result = $this->doRequest($job->getTranslator(), 'Translate', array(
        'from' => $job->source_language,
        'to' => $job->target_language,
        'contentType' => 'text/plain',
        'text' => $value['#text'],
      ), array(
        'headers' => array(
          'Content-Type' => 'text/plain',
        ),
      ));
      // Check the result code for possible errors.
      switch ($result->code) {
        case 200:
          // Lets use DOMDocument for now because this service enables us to
          // send an array of translation sources, and we will probably use
          // this soon.
          $dom = new DOMDocument;
          $dom->loadXML($result->data);
          $items = $dom->getElementsByTagName('string');
          $translation[$key]['#text'] = $items->item(0)->nodeValue;
          break;
        case 400:
          $job->rejected('Rejected by Microsoft Translator: !error', array('!error' => $result->data), 'error');
          return;
        default:
          $job->rejected('Unknown error from Microsoft Translator: !error', array('!error' => $result->data), 'error');
          return;
      }
    }
    // The translation job has been successfully submitted.
    $job->submitted('The translation job has been submitted.');
    // Save the translated data through the job.
    $job->addTranslatedData(tmgmt_unflatten_data($translation));
  }

  /**
   * Overrides TMGMTDefaultTranslatorPluginController::getSupportedTargetLanguages().
   */
  public function getSupportedTargetLanguages(TMGMTTranslator $translator, $source_language) {
    $languages = array();
    $request = $this->doRequest($translator, 'GetLanguagesForTranslate');
    if ($request->code == 200) {
      $dom = new DOMDocument;
      $dom->loadXML($request->data);
      foreach ($dom->getElementsByTagName('string') as $item) {
        $languages[$item->nodeValue] = $item->nodeValue;
      }
    }
    // Microsoft translator reports chinese language codes with their old names.
    // Replace them with the offical identifiers.
    if (isset($languages['zh-CHS'])) {
      unset($languages['zh-CHS']);
      $languages['zh-hans'] = 'zh-hans';
    }
    if (isset($languages['zh-CHT'])) {
      unset($languages['zh-CHT']);
      $languages['zh-hant'] = 'zh-hant';
    }
    // Check if the source language is available.
    if (array_key_exists($source_language, $languages)) {
      unset($languages[$source_language]);
      return $languages;
    }
    return array();
  }

  /**
   * Overrides TMGMTDefaultTranslatorPluginController::hasCheckoutSettings().
   */
  public function hasCheckoutSettings(TMGMTJob $job) {
    return FALSE;
  }

  /**
   * Execute a request against the Microsoft API.
   *
   * @param TMGMTTranslator $translator
   *   The translator entity to get the settings from.
   * @param $path
   *   The path that should be appended to the base uri, e.g. Translate or
   *   GetLanguagesForTranslate.
   * @param $query
   *   (Optional) Array of GET query arguments.
   * @param $options
   *   (Optional) Array of additional options passed to drupal_http_request().
   *
   * @return
   *   The response object returned by drupal_http_request().
   */
  protected function doRequest(TMGMTTranslator $translator, $path, array $query = array(), array $options = array()) {
    // fubhy, can you please stop removing this setting? This is used for the
    // tests. Thanks.
    // Answer: Okay. Will try to keep my cool :D...
    $custom_url = $translator->getSetting('url');
    $url = ($custom_url ? $custom_url : $this->translatorUrl) . '/' . $path;
    $testtokenurl = FALSE;
    if ($custom_url) {
      $testtokenurl = $custom_url . '/GetToken';
    }
    // The new Api uses 2 new parameters and access token.
    $clientid = $translator->getSetting('clientid');
    if (!empty($clientid)) {
      $clientsecret = $translator->getSetting('clientsecret');
      $tokenRequest = $this->getToken($clientid, $clientsecret, $testtokenurl);
      $token = json_decode($tokenRequest->data);
      if (isset($token->error)) {
        watchdog('tmgmt_microsoft', 'Could not get Microsoft token. Error: @error', array('@error' => $token->error_description), WATCHDOG_ERROR);
        return $tokenRequest;
      }
      $options['headers']['Authorization'] = 'Bearer ' . $token->access_token;
    }
    else {
      // @todo remove this parameter and logic around once it is officially
      // deprecated.
      // Legacy api parameter.
      // Add the appId to the query arguments and build the query string.
      $query = array('appId' => $translator->getSetting('api')) + $query;
    }
    $url = url($url, array('query' => $query));
    return drupal_http_request($url, $options);
  }

  /**
   * Get the access token.
   *
   * @param $clientID
   *   Application client ID.
   * @param $clientSecret
   *   Application client secret string.
   *
   * @return
   *   The response object returned by drupal_http_request().
   */
  protected function getToken($clientID, $clientSecret, $testurl = FALSE) {
 

        $grantType = 'client_credentials';
        $scopeUrl = 'http://api.microsofttranslator.com';
        $clientID = 'drewtranslate';
        $clientSecret = 'rkplHXg0TgeBYGcGJ6WYl7ihv2DP38b4JzccF5ty53Y';
        $authUrl = 'https://datamarket.accesscontrol.windows.net/v2/OAuth2-13/';

        $token = $this->my_getTokensNEW($grantType, $scopeUrl, $clientID, $clientSecret, $authUrl);
        print ' Token: ' . $token;
exit;








   $request = &drupal_static(__FUNCTION__);
    if (!isset($request[$clientID][$clientSecret])) {
      // Create the request array.
      $paramArr = array(
        'grant_type' => 'client_credentials',
        'scope' => 'http://api.microsofttranslator.com',
        'client_id' => 'drewtranslate',
        'client_secret' => 'rkplHXg0TgeBYGcGJ6WYl7ihv2DP38b4JzccF5ty53Y', //$clientSecret,
      );
      $headers = array('Content-Type' => 'application/x-www-form-urlencoded');
      $options = array(
        'headers' => $headers,
        'method' => 'POST',
        'data' => http_build_query($paramArr),
      );
      $url = 'https://datamarket.accesscontrol.windows.net/v2/OAuth2-13/'; //$this->authUrl;
      if ($testurl) {
        $url = $testurl;
      }
      //$request[$clientID][$clientSecret] = drupal_http_request($url, $options);
    
//$res=$this->my_getTokens($paramArr['grant_type'], $paramArr['scope'], $paramArr['client_id'], $paramArr['client_secret'], $url);	
//print_r($res); exit;



       $grantType = 'client_credentials';
        $scopeUrl = 'http://api.microsofttranslator.com';
        $clientID = 'drewtranslate';
        $clientSecret = 'rkplHXg0TgeBYGcGJ6WYl7ihv2DP38b4JzccF5ty53Y';
        $authUrl = 'https://datamarket.accesscontrol.windows.net/v2/OAuth2-13/';


        $token = $this->my_getTokensOLD($grantType, $scopeUrl, $clientID, $clientSecret, $authUrl);;
        print ' Token: ' . $token; exit;




}
    return $request[$clientID][$clientSecret];
  }


/*
     * @param string $grantType    Grant type.
     * @param string $scopeUrl     Application Scope URL.
     * @param string $clientID     Application client ID.
     * @param string $clientSecret Application client ID.
     * @param string $authUrl      Oauth Url.
     *
     * @return string.
     */
function my_getTokensNEW($grantType, $scopeUrl, $clientID, $clientSecret, $authUrl){
        try {
            //Initialize the Curl Session.
            $ch = curl_init();
            //Create the request Array.
            $paramArr = array (
                 'grant_type1'    => $grantType,
                 'scope1'         => $scopeUrl,
                 'client_id1'     => $clientID,
                 'client_secret1' => $clientSecret,
		'scope' => $scopeUrl
            );
            //Create an Http Query.//
            $paramArr = http_build_query($paramArr,",'&'");
            

            //Set the Curl URL.
            curl_setopt($ch, CURLOPT_URL, $authUrl);
            //Set HTTP POST Request.
            curl_setopt($ch, CURLOPT_POST, TRUE);
            //Set data to POST in HTTP "POST" Operation.
            curl_setopt($ch, CURLOPT_POSTFIELDS, $paramArr);
            //CURLOPT_RETURNTRANSFER- TRUE to return the transfer as a string of the return value of curl_exec().
            curl_setopt ($ch, CURLOPT_RETURNTRANSFER, TRUE);
            //CURLOPT_SSL_VERIFYPEER- Set FALSE to stop cURL from verifying the peer's certificate.
            curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
            //Execute the  cURL session.
$strResponse = curl_exec($ch);
//print $strResponse;


            //Get the Error Code returned by Curl.
            $curlErrno = curl_errno($ch);
            if($curlErrno){
                $curlError = curl_error($ch);
                throw new Exception($curlError);
            }
            //Close the Curl Session.
            curl_close($ch);
            //Decode the returned JSON string.
            $objResponse = json_decode($strResponse);
//print '<pre>'; print_r($objResponse); print '</pre>';
            if (isset($objResponse->error)){
                throw new Exception($objResponse->error_description);
            }
            return $objResponse->access_token;
        } catch (Exception $e) {
            echo "Exception-".$e->getMessage();
        }
    }







    function my_getTokens($grantType, $scopeUrl, $clientID, $clientSecret, $authUrl){
        try {
            //Initialize the Curl Session.
            $ch = curl_init();
            //Create the request Array.
            $paramArr = array (
                 'grant_type'    => $grantType,
                 'scope'         => $scopeUrl,
                 'client_id'     => $clientID,
                 'client_secret' => $clientSecret
            );
            //Create an Http Query.//
            $paramArr = http_build_query($paramArr);
            //Set the Curl URL.
            curl_setopt($ch, CURLOPT_URL, $authUrl);
            //Set HTTP POST Request.
            curl_setopt($ch, CURLOPT_POST, TRUE);
            //Set data to POST in HTTP "POST" Operation.
            curl_setopt($ch, CURLOPT_POSTFIELDS, $paramArr);
            //CURLOPT_RETURNTRANSFER- TRUE to return the transfer as a string of the return value of curl_exec().
            curl_setopt ($ch, CURLOPT_RETURNTRANSFER, TRUE);
            //CURLOPT_SSL_VERIFYPEER- Set FALSE to stop cURL from verifying the peer's certificate.
            curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
            //Execute the  cURL session.
$strResponse = curl_exec($ch);
//print $strResponse;

            //Get the Error Code returned by Curl.
            $curlErrno = curl_errno($ch);
            if($curlErrno){
                $curlError = curl_error($ch);
                throw new Exception($curlError);
            }
            //Close the Curl Session.
            curl_close($ch);
            //Decode the returned JSON string.
            $objResponse = json_decode($strResponse);
//print '<pre>'; print_r($objResponse); print '</pre>';
            if (isset($objResponse->error)){
                throw new Exception($objResponse->error_description);
            }
            return $objResponse->access_token;
        } catch (Exception $e) {
            echo "Exception-".$e->getMessage();
        }
    }





     /*
     * @param string $grantType    Grant type.
     * @param string $scopeUrl     Application Scope URL.
     * @param string $clientID     Application client ID.
     * @param string $clientSecret Application client ID.
     * @param string $authUrl      Oauth Url.
     *
     * @return string.
     */

    function my_getTokensOLD($grantType, $scopeUrl, $clientID, $clientSecret, $authUrl){
        try {
            //Initialize the Curl Session.
            $ch = curl_init();
            //Create the request Array.
            $paramArr = array (
                 'grant_type'    => $grantType,
                 'scope'         => $scopeUrl,
                 'client_id'     => $clientID,
                 'client_secret' => $clientSecret
            );

            //Create an Http Query.//
            $paramArr = http_build_query($paramArr);
//print '<pre>'; print_r($paramArr); print '</pre>'; exit;
            //Set the Curl URL.
            curl_setopt($ch, CURLOPT_URL, $authUrl);
            //Set HTTP POST Request.
            curl_setopt($ch, CURLOPT_POST, TRUE);
            //Set data to POST in HTTP "POST" Operation.
            curl_setopt($ch, CURLOPT_POSTFIELDS, $paramArr);
            //CURLOPT_RETURNTRANSFER- TRUE to return the transfer as a string of the return value of curl_exec().
            curl_setopt ($ch, CURLOPT_RETURNTRANSFER, TRUE);
            //CURLOPT_SSL_VERIFYPEER- Set FALSE to stop cURL from verifying the peer's certificate.
            curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
            //Execute the  cURL session.
            $strResponse = curl_exec($ch);
            //Get the Error Code returned by Curl.
            $curlErrno = curl_errno($ch);
            if($curlErrno){
                $curlError = curl_error($ch);
                throw new Exception($curlError);
            }
            //Close the Curl Session.
            curl_close($ch);
            //Decode the returned JSON string.
            $objResponse = json_decode($strResponse);
            if ($objResponse->error){
                throw new Exception($objResponse->error_description);
            }
            return $objResponse->access_token;
        } catch (Exception $e) {
            echo "Exception-".$e->getMessage();
        }
    }
}


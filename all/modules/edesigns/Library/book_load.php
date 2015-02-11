<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


 /*
 $fields = array("publisherID","company_name","address_1","address_2","city","state","country","country_id","postal_code","first_name","last_name","phone","email",
                "paypal_email","check_name","username","password","active","email");

    $role_name = 'Account Owner';
    $roles = user_roles(TRUE);
    $rid = array_search($role_name, $roles);
    $new_role[$rid] = $role_name;

    $profile_vars = array();


$row = 0;
if (($handle = fopen("platform_users.csv", "r")) !== FALSE) {
    while (($data = fgetcsv($handle, 2000, ",")) !== FALSE) {
        if ($row==0) { $row++; continue; }

        // create new user 
        $account = new stdClass();
        $account->is_new = true;
        $newUserData = array();

        $num = count($data);
        //echo "<p> $num fields in line $row: <br /></p>\n";
        $row++;
        for ($c=0; $c < $num; $c++) {
            switch ($fields[$c]) {
               case "publisherID": // userref
                   $newUserData['publisher_id'][LANGUAGE_NONE][0]['value'] = $data[$c];
                   break;
               case "company_name": // publisher_company_profile: field_company_name
                   $profile_vars['field_company_name'] = $data[$c];
                    break;
                case "address_1": // publisher_company_profile: field_mailing_address1
                    $profile_vars['field_mailing_address1'] = $data[$c];
                    break;
                case "address_2": // publisher_company_profile: field_mailing_address2
                    $profile_vars['field_mailing_address2'] = $data[$c];
                    break;
                case "city": // publisher_company_profile: field_city
                    $profile_vars['field_city'] = $data[$c];
                    break;
                case "state": // publisher_company_profile: field_mailing_state
                    $profile_vars['field_state'] = $data[$c];
                    break;
                case "country": // publisher_company_profile: field_country
                    $profile_vars['field_country3'] = $data[$c];
                    break;
                case "country_id": // ??
                    break;
                case "postal_code": // publisher_company_profile: field_postal_code
                    $profile_vars['field_postal_code'] = $data[$c];
                    break;
                case "first_name": // publisher_company_profile: field_contact_name
                    $profile_vars['field_contact_name'] = $data[$c];
                    break;
                case "last_name": // publisher_company_profile: field_contact_name
                    $profile_vars['field_contact_name'] = $data[$c];
                    break;
                case "phone": // publisher_company_profile: field_contact_phone
                    $profile_vars['field_contact_phone'] = $data[$c];
                    break;
                case "email": // publisher_company_profile: field_contact_email
                    $newUserData['field_publisher_contact_email'][LANGUAGE_NONE][0]['value'] = $data[$c];
                    $newUserData['mail'] = $data[$c];
                    $newUserData['init'] = $data[$c];
                    $profile_vars['field_contact_email'] = $data[$c];
                    break;
                case "paypal_email":  // publisher_payment_information: field_payment_preference (checked if paying by paypal)
                    break;

                case "check_name"; // publisher_payment_information: field_preference_check
                    break;
                case "username":  // user: name
                    $newUserData['name'] = $data[$c];
                    break;
                case "password":  // user: pass
                    $newUserData['pass'] = 'test'; //$data[$c];
                    break;
                case "active":  // user: active
                    $newUserData['status'] = $data[$c];
                    break;
            }


            //echo $data[$c] . ' , ';  //. "<br />\n";

        }


        $newUserData['roles'] = $new_role  ;
        $newUserData['timezone'] = variable_get('date_default_timezone', '');
        //$newUserData['technorati_user_type'][LANGUAGE_NONE][0]['value'] = 'publisher';

        $new_user = user_save($account, $newUserData);

        $profile = profile_create(array('user' => $new_user, 'type' => 'publisher_company_profile'));
        $profile->field_company_name[LANGUAGE_NONE][0]['value'] = $profile_vars['field_company_name'];
        $profile->field_mailing_address1[LANGUAGE_NONE][0]['value'] = $profile_vars['field_mailing_address1'];
        $profile->field_mailing_address2[LANGUAGE_NONE][0]['value'] = $profile_vars['field_mailing_address2'];
        $profile->field_city[LANGUAGE_NONE][0]['value'] = $profile_vars['field_city'];
        $profile->field_state[LANGUAGE_NONE][0]['value'] = $profile_vars['field_state'];
        $profile->field_postal_code[LANGUAGE_NONE][0]['value'] = $profile_vars['field_postal_code'];
        $profile->field_country3[LANGUAGE_NONE][0]['value'] = $profile_vars['field_country3'];

        $profile->field_contact_name[LANGUAGE_NONE][0]['value'] = $profile_vars['field_contact_name'];
        $profile->field_contact_email[LANGUAGE_NONE][0]['value'] = $profile_vars['field_contact_email'];
        $profile->field_contact_title[LANGUAGE_NONE][0]['value'] = $profile_vars['field_contact_title'];
        $profile->field_contact_phone[LANGUAGE_NONE][0]['value'] = $profile_vars['field_contact_phone'];

        profile2_save($profile);

        //print_r($profile);
        //print_r($newUserData); exit;
        print ' Saved profile: ' . $profile->field_company_name[LANGUAGE_NONE][0]['value'];
        nl();
        //if ($row > 5) break;
    }
    fclose($handle);
}

      function nl() {
           echo "\r\n";
       }
       */
?>

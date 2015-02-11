<?php

  /*
  * the initial function used to import the first 120 items
  */
    function sfandfan_importSpreadsheet() {     return '';
       $fields = array('Type','Subtype','ISBN','Author','Last','Item Title','Collection Title','URL','Source',
                      'Thumbnail URL','Published','Description','Awards','Tags','Related');

        $row = 0;
        $numSaved = 0;
        if (($handle = fopen("sites/all/modules/edesigns/sfandfan/Fantasy.csv", "r")) !== FALSE) {
            while (($data = fgetcsv($handle, 2000, ",")) !== FALSE) {
              //print ' data : ' . _prepost($data) . '<br>';
                if ($row==0) { $row++; continue; }

                // create new book
                $book = new stdClass();
                $book->type = 'book';
                $book->is_new = true;
                $num = count($data);

                $row++;
                for ($c=0; $c < $num; $c++) {
                    switch ($fields[$c]) {
                       case "ISBN":
                            if (isset($data[$c]) && $data[$c]!='') {
                              /*
                              * check for duplicate
                              */

                              $book->field_amazon_id[LANGUAGE_NONE][0]['asin'] = $data[$c];
                              if ( $data[5] != '') $book->title = $data[5];
                              node_save($book);
                              print ' saving: ' . $book->field_amazon_id[LANGUAGE_NONE][0]['asin'] . ' ' . $book->title . '<br>';
                              //_prepost($book);
                              $numSaved++;
                            }
                            break;
                    }
                }


            }
        }
       print '<br>' . ' Total Saved: ' . $numSaved;
    }
    /*
    * utility
    */
 function sfandfan_loadAll($type) {
            $query = new EntityFieldQuery();
            $query->entityCondition('entity_type', 'node')
                            ->entityCondition('bundle', $type);
                            //->addMetaData('account', user_load(1)); // run the query as user 1

            return  $query->execute();

        }


?>
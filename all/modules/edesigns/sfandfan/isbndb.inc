<?php

define('ISBNDB_KEY', 'YWH8HTAF');




function sfandfan_download_isbndb_book_content() {
    include_once drupal_get_path('module', 'user') . '/user.module';
    global $user;
   
    if ($user->uid!=1) return ;
    //echo phpinfo(); exit;
    // Getting a resource from an Open Library ID:
    //_prepost(openlibrary_get_content('/b/OL23226198M'));
    //_prepost(openlibrary_get_content('/subjects/science_fiction.json?details=true'));
    //$data = drupal_http_request($cmd_subject);
    //_prepost($data);  
    
    /* isbndb.com
     * 
     */
    $key = 'YWH8HTAF';
    // http://isbndb.com/api/subjects.xml?access_key=YWH8HTAF&index1=name&value1=science%20fiction
    // http://isbndb.com/docs/api/51-books.html
    // list of subjects: http://isbndb.com/search-all.html?kw=science+fiction
    $subject_id = 'science_fiction_fantasy_general';
    $page_number = 30; 
    while (true) {
        print ' <br>PAGE: ' . $page_number . '<br><br>';
        $cmd_subject = 'http://isbndb.com/api/books.xml?access_key='.$key.'&page_number='.$page_number.'&results=texts,authors&index1=subject_id&value1='.$subject_id;
    
    
        /* TEST1 */    
            // http://isbndb.com/docs/api/51-books.html
            // http://webhole.net/2009/08/25/get-book-info-from-isbn/
        $response=simplexml_load_file($cmd_subject);
        // check if we got at least one result
        if($response->BookList['total_results']>0){ // [total_results], [page_size] => 10, [page_number] => 1, [shown_results] => 10

            // assign each book to $book
            foreach($response->BookList->BookData as $book)
            {
                //if ($book['isbn'] != '1427809321') continue;
                ///* three books, same author (ursula k leguin)
                // 1571130349, 089370105X, 0786714085
                
                /* skip this if we already have this content */
                if (sfandfan_find_content('sf_book', (string)$book->Title)) {
                    echo ' skipping: ' . $book->Title . '<br>';
                    continue;
                }
                
                echo '<br>****** response ******<br>';
                echo "Short Title: {$book->Title}<br/>
                Long Title: {$book->TitleLong}<br/>
                Author(s): {$book->AuthorsText}<br />
                Publisher: {$book->PublisherText}<br/>
                ISBN10: {$book['isbn']}<br/>
                ISBN13: {$book['isbn13']}<br/>
                Edition Information: {$book->Details['edition_info']}<br/>
                Language: {$book->Details['language']}<br/>
                Physical Description: {$book->Details['physical_description_text']}
                ";
                
                
             /* create and update a book rec */
                $sf_book = entity_create('node', array('type' => 'sf_book'));
                $sf_book->title = $book->Title;
                $sf_book->field_description[LANGUAGE_NONE][0]['value'] = $book->Summary;
                $sf_book->field_isbndb_book_id[LANGUAGE_NONE][0]['value'] = $book['book_id'];
                $sf_book->field_isbn[LANGUAGE_NONE][0]['value'] = $book['isbn'];
                $sf_book->field_isbn13[LANGUAGE_NONE][0]['value'] = $book['isbn13'];
                //$sf_book->field_description ;
                //$sf_book->field_author ;
    
        
                //_prepost($book); exit;
                foreach ($book->Authors as $author) {

                    $i=0;
                    $author_ids = array();
                    while ($author->Person[$i]) {
                        $sf_author=sfandfan_create_author((string)$author->Person[$i++]);
                        $sf_book->field_author[LANGUAGE_NONE][$i]['target_id'] = $sf_author->nid;
                     }

                }
                $isbn = $sf_book->field_isbn[LANGUAGE_NONE][0]['value'];
                $sf_book->field_thumbnail_url[LANGUAGE_NONE][0]['value'] = 'http://covers.librarything.com/devkey/'.LIBRARYTHING_KEY.'/small/isbn/'. $isbn ;
                $sf_book->field_medium_url[LANGUAGE_NONE][0]['value'] = 'http://covers.librarything.com/devkey/'.LIBRARYTHING_KEY.'/small/isbn/'. $isbn ;
                $sf_book->field_large_url[LANGUAGE_NONE][0]['value'] = 'http://covers.openlibrary.org/b/isbn/'.$isbn .'-L.jpg';;
                entity_save('node', $sf_book);    // break;
         
                
            }
        }
    
        
       if (++$page_number>100) break;
    }
    //_prepost($response);    
    
/*
 * return from TEST1
SimpleXMLElement Object
(
    [@attributes] => Array
        (
            [server_time] => 2012-05-13T03:10:55Z
        )

    [BookList] => SimpleXMLElement Object
        (
            [@attributes] => Array
                (
                    [total_results] => 6847
                    [page_size] => 10
                    [page_number] => 1
                    [shown_results] => 10
                )

            [BookData] => Array
                (
                    [0] => SimpleXMLElement Object
                        (
                            [@attributes] => Array
                                (
                                    [book_id] => the_youngblood_project
                                    [isbn] => 155369211X
                                    [isbn13] => 9781553692119
                                )

                            [Title] => The Youngblood Project
                            [TitleLong] => SimpleXMLElement Object
                                (
                                )

                            [AuthorsText] => Bruce Kost, 
                            [PublisherText] => Trafford Publishing
                            [Details] => SimpleXMLElement Object
                                (
                                    [@attributes] => Array
                                        (
                                            [change_time] => 2009-02-20T20:38:32Z
                                            [price_time] => 2010-09-01T01:56:02Z
                                            [edition_info] => Paperback; 2002-07-04
                                            [language] => 
                                            [physical_description_text] => 5.5"x8.5"x0.7"; 0.7 lb; 274 pages
                                            [lcc_number] => 
                                            [dewey_decimal_normalized] => 813
                                            [dewey_decimal] => 813
                                        )

                                )

                        )

                    [1] => SimpleXMLElement Object
                        (
                            [@attributes] => Array
                                (
                                    [book_id] => inquisitor
                                    [isbn] => 1852838353
                                    [isbn13] => 9781852838355
                                )

 * 
 */


}





?>

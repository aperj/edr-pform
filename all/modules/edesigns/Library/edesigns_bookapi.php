<?php

/*
 * 
 *   Objects defined in this file:

        edesigns_bookProvider {}
        edesigns_bookapi {}
        isbndb_bookProvider extends edesigns_bookProvider {}
        librarything_bookProvider extends edesigns_bookProvider {}
        openlibrary_bookProvider extends edesigns_bookProvider {}
        edesigns_book{}
        edesigns_book_cover{}
        edesigns_author {}
        edesigns_publisher {}
 *
 * 
 */
// class ActionsConfigurationTestCase extends DrclassupalWebTestCase {
class edesigns_bookapi {
  //protected function checkCacheExists($cid, $var, $bin = NULL) { 
   
}

class edesigns_bookProvider {
    public   $DRY_RUN = false;
    protected   $name ; // openlibrary, librarything, isbndb
    //protected   $cover_base_url ;
    protected   $base_url;
    protected   $key;
    protected   $cover_url;
    public      $response;
    public      $last_command;
    public      $last_page;
    public      $books;         /* array of edesigns_book objects from last query
    
    
    /*
    * if author already exists, update. otherwise create
    */
    function create_author($name) {
        //print ' CREATING: ' . $name . '<br>';

        // http://drupal.org/node/1343708    
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'node')
                        ->entityCondition('bundle', 'sf-author')
                        //->fieldCondition('title', 'value', 'name', '=')
                        ->propertyCondition('title', $name)
                        ->addMetaData('account', user_load(1)); // run the query as user 1

        $result = $query->execute();
        if (isset($result['node'])) {
            foreach ($result['node'] as $id => $node) {
                return $node;            
            }
        }    

        $sf_author = entity_create('node', array('type' => 'sf_author'));
        $sf_author->title = $name;
    // _prepost($sf_author); exit;
        if (!$this->DRY_RUN) entity_save('node', $sf_author);
        print ' saved author: ' . $sf_author->title . "\r\n";
        return $sf_author;

    }
    /*
    * 
    */
    function find_content($type, $title, $isbn) {

        // http://drupal.org/node/1343708    
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'node')
                        ->entityCondition('bundle', $type)  // sf-author
                        ->fieldCondition('field_isbn', 'value', $isbn, '=')
                        //->propertyCondition('title', $title)
                        ->addMetaData('account', user_load(1)); // run the query as user 1

        $result = $query->execute();
        if (isset($result['node'])) {
            foreach ($result['node'] as $id => $node) { 
                print 'found!!!!: ' . $title; 
                return $node;            
            }
        } 
        print ' Content not found: ' .$title . ' isbn: ' . $isbn . "\r\n"; //exit;
        return null;
    }
    
    
    
}

/*
 * 
 */
class isbndb_bookProvider extends edesigns_bookProvider {
    protected $name = 'isbndb';
    protected $key = 'YWH8HTAF';
    protected $base_url;
    protected $cover_url;
    
    //public $general_Category = 'science_fiction_fantasy_general';
    
    function __construct() {
       //print "In BaseClass constructor\n";
        $this->base_url = 'http://isbndb.com/api/books.xml?access_key='.$this->key;
        $this->books = array();
        if ($this->DRY_RUN) print ' DRY RUN ';
        print $base_url;
    }    
    
    public function download_book_content($subject, $page_start) {
        $key = 'YWH8HTAF';
        $subject_id = $subject; //'science_fiction_fantasy_general';
        $page_number = $page_start;
       
        print "\r\nPAGE: " . $page_number . "\r\n";
        $cmd_subject = $this->base_url . '&page_number='.$page_number.'&results=texts,authors&index1=subject_id&value1='.$subject_id;
        //print "\r\n" . $cmd_subject . "\r\n"; exit;
        $this->last_command = $cmd_subject;
        $this->last_page = $page_number;

        $this->response=simplexml_load_file($cmd_subject);
        // check if we got at least one result
        print "\r\ngot response for page:: " . $page_number . "\r\n";

        $this->parseResults();
        
        //print_r($this->books); exit;

    }
    
    function checkRemoteFile($url)
    {
        $size = getimagesize($url);   
        if ($size[0]>10) return true; else return false;
    }
    
 
    function parseResults() {
        $lthing = new librarything_bookProvider();
        $openlib = new openlibrary_bookProvider();

        if($this->response->BookList['total_results']>0){ // [total_results], [page_size] => 10, [page_number] => 1, [shown_results] => 10

            // 
            foreach($this->response->BookList->BookData as $book)
            {
                $bk = new edesigns_book();
                $bk->load_from_isbndb($book);
                /* we have two sources for covers:
                    * 1. librarything and 2. openlibrary
                    * we prefer openlibrary cover for large and librarything for small and medium, however
                    * if the preferred provider doesn't have an image then choose the non-preferred if the
                    * image exists
                    */     //print_r($bk); 
                $isbn = $book->isbn;
                
                $default_large_img = $openlib->large_img_url((string)$bk->isbn);
                $secondary_large_img = $lthing->large_img_url((string)$bk->isbn);
                //print ' secondary: ' . $secondary_large_img . "\r\n";
                $large_img = ''; 
                if ($this->checkRemoteFile($default_large_img)) { $large_img = $default_large_img;  }
                else {
                    if ($this->checkRemoteFile($secondary_large_img)) { $large_img = $secondary_large_img;  }
                }
                if (strlen($large_img)==0) print ' NO Large, ';

                $default_small_img = $lthing->small_img_url((string)$bk->isbn);
                $secondary_small_img = $openlib->small_img_url((string)$bk->isbn);
                $small_img = ''; 
                if ($this->checkRemoteFile($default_small_img)) { $small_img = $default_small_img; }
                else {
                    if ($this->checkRemoteFile($secondary_small_img)) { $small_img = $secondary_small_img;  }
                }
                if (strlen($small_img)==0) print ' NO Small, ';

                $default_medium_img = $lthing->medium_img_url((string)$bk->isbn);
                $secondary_medium_img = $openlib->medium_img_url((string)$book->isbn);
                $medium_img = ''; 
                if ($this->checkRemoteFile($default_medium_img)) { $medium_img = $default_medium_img; }
                else {
                    if ($this->checkRemoteFile($secondary_medium_img)) { $medium_img = $secondary_medium_img;  }
                }
                if (strlen($medium_img)==0) print ' NO Medium, ';



                $bk->set_cover($small_img, $medium_img, $large_img);
//print_r($book); print ' isbn: ' ; print_r((string)$bk->isbn); exit;
                /* skip this if we already have this content */
                if ($this->find_content('sf_book', (string)$book->Title, (string)$bk->isbn)) {
                    echo ' skipping: ' . "\r\n";
                    $bk->already_exists = true;
                    continue;
                }
                $bk->already_exists = false;
                print "Adding: " . (string)$book->Title . "\r\n";
    // print_r($bk->description); //exit;
                $this->books[] = $bk;

            }
        }

        
    }

        function parseResults1() {
            if($this->response->BookList['total_results']>0){ // [total_results], [page_size] => 10, [page_number] => 1, [shown_results] => 10

                // assign each book to $book
                foreach($this->response->BookList->BookData as $book)
                {
                    //if ($book['isbn'] != '1427809321') continue;
                    ///* three books, same author (ursula k leguin)
                    // 1571130349, 089370105X, 0786714085

                    /* skip this if we already have this content */
                    if ($this->find_content('sf_book', (string)$book->Title)) {
                        echo ' skipping: ' . $book->Title . "/r/n";
                        continue;
                    }

                    echo '/r/n****** response ******/r/n';
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
                            $sf_author=$this->create_author((string)$author->Person[$i++]); // parent??
                            $sf_book->field_author[LANGUAGE_NONE][$i]['target_id'] = $sf_author->nid;
                        }

                    }
                    $isbn = $sf_book->field_isbn[LANGUAGE_NONE][0]['value'];
                    $sf_book->field_thumbnail_url[LANGUAGE_NONE][0]['value'] = 'http://covers.librarything.com/devkey/'.LIBRARYTHING_KEY.'/small/isbn/'. $isbn ;
                    $sf_book->field_medium_url[LANGUAGE_NONE][0]['value'] = 'http://covers.librarything.com/devkey/'.LIBRARYTHING_KEY.'/small/isbn/'. $isbn ;
                    $sf_book->field_large_url[LANGUAGE_NONE][0]['value'] = 'http://covers.openlibrary.org/b/isbn/'.$isbn .'-L.jpg';;
                    if (!$this->DRY_RUN) entity_save('node', $sf_book);    


                }
            }

        
    }

}
class librarything_bookProvider extends edesigns_bookProvider {
    protected $name = 'librarything';
    protected $key = '14e8ba9bf7f7860b13fb58ba60146228';
    protected $base_url;
    protected $cover_url;

    function __construct() {
       //print "In BaseClass constructor\n";
        $this->cover_url = 'http://covers.librarything.com/devkey/'.$this->key; //.'/medium/isbn/'.$isbn; //0545010225';
    }  
    
    public function large_img_url($isbn) {
       return $this->cover_url.'/large/isbn/'. $isbn ;
        
    }
    public function medium_img_url($isbn) {
       return $this->cover_url.'/medium/isbn/'. $isbn ;
        
    }
    public function small_img_url($isbn) {
       return $this->cover_url.'/small/isbn/'. $isbn ;
    }
    
    
}
class openlibrary_bookProvider extends edesigns_bookProvider {
    protected $name = 'openlibrary';
    protected $key = '14e8ba9bf7f7860b13fb58ba60146228';
    protected $base_url;
    protected $cover_url;

    function __construct() {
       //print "In BaseClass constructor\n";
        $this->cover_url = 'http://covers.openlibrary.org/b/isbn/'; //.'/medium/isbn/'.$isbn; //0545010225';
    }    
    public function large_img_url($isbn) {
       return $this->cover_url.$isbn .'-L.jpg';
        
    }
    public function medium_img_url($isbn) {
       return $this->cover_url.$isbn .'-M.jpg';
        
    }
    public function small_img_url($isbn) {
       return $this->cover_url.$isbn .'-S.jpg';
    }
    
    
}
/*
 * 
 */
class edesigns_book {
    public $isbn ;
    public $isbn13;
    
    public $title;
    public $titlelong;
    public $publisher;
    public $author;
    public $description;
    public $edition;
    public $language;
    
    //public $librarything_large_image;
    //public $librarything_small_image;
    //public $librarything_medium_image;
    
    //public $openlibrary_large_image;
    //public $openlibrary_small_image;
    //public $openlibrary_medium_image;
    
    public $already_exists;
    public $cover;  // edesigns_book_cover
    
    function __construct() {  
        $this->cover = new edesigns_book_cover();
    }      
    
    public function load_from_isbndb($book_data) {
        $this->title = $book_data->Title;
        $this->titlelong = $book_data->TitleLong;
        $this->isbn = $book_data['isbn'];
        $this->isbn13 = $book_data['isbn13'];


        $this->publisher = $book_data->PublisherText;
    // public $bk->author = $book->AuthorText;
        $this->description = $book_data->Summary;   
        $this->edition = $book->Details['edition_info'];
        $this->language - $book->language;
        
        //print_r($book_data);
    }
    
    public function set_cover($small, $medium, $large) {
        $this->cover->small = $small;
        $this->cover->medium = $medium;
        $this->cover->large = $large;
        
    }
    
    public function dump() {
        /*
    
        echo '<br>****** response ******<br>';
        echo "Short Title: {$this->title}<br/>
        Long Title: {$this->titlelong}<br/>
        Author(s): {$this->AuthorsText}<br />
        Publisher: {$this->PublisherText}<br/>
        ISBN10: {$this->isbn'<br/>
        ISBN13: {$this->isbn13'<br/>
        Edition Information: $this->edition\r\n
        Language: $this->language\r\n
        Physical Description: {$this->description\r\n
        ";
       */ 
    }
    
    
}

class edesigns_book_cover {
    public $small;
    public $medium;
    public $large;

    function __construct() {
        $this->small = array();
        $this->medium = array();
        $this->large = array();
    }

}
class edesigns_author {
    public $name;
    public $website;
}

class edesigns_publisher {
    public $name;
    public $address;
}





?>

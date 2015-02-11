<header id="navbar" role="banner" class="navbar navbar-fixed-top">
  <div class="navbar-inner">
    <div class="container">
      <!-- .btn-navbar is used as the toggle for collapsed navbar content -->
      <a class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse">
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </a>

      <?php if ($logo): ?>
        <a class="logo pull-left" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a>
      <?php endif; ?>

      <?php if ($site_name): ?>
        <h1 id="site-name">
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" class="brand"><?php print $site_name; ?></a>
        </h1>
      <?php endif; ?>
<!--
      <?php if ($primary_nav || $secondary_nav || !empty($page['navigation'])): ?>
        <div class="nav-collapse">
          <nav role="navigation">
            <?php if ($primary_nav): ?>
              <?php print render($primary_nav); ?>
            <?php endif; ?>
            <?php if (!empty($page['navigation'])): ?>
              <?php print render($page['navigation']); ?>
            <?php endif; ?>
            <?php if ($secondary_nav): ?>
              <?php print render($secondary_nav); ?>
            <?php endif; ?>
          </nav>
        </div>
      <?php endif; ?>
      -->

                    <ul id="navi" class="nav">
                        <li><a href="#pane-1"  class="scroll">Home</a></li>
                        <li><a href="#pane-2"  class="scroll">Articles</a></li>
                        <li><a href="#pane-3"  class="scroll">Portfolio</a></li>
                        <li><a href="#pane-4"  class="scroll">Contact</a></li>
                    </ul>      

      <?php if ($navbar_search): ?><?php print $navbar_search ?><?php endif ?>
      
    </div>
  </div>
</header>

<div class="container">

  <header role="banner" id="page-header">
    <?php if ( $site_slogan ): ?>
      <p class="lead"><?php print $site_slogan; ?></p>
    <?php endif; ?>

    <?php print render($page['header']); ?>
  </header> <!-- /#header -->

  <div class="row">

    <?php if ($page['sidebar_first']): ?>
      <aside class="span3" role="complementary">
        <?php print render($page['sidebar_first']); ?>
      </aside>  <!-- /#sidebar-first -->
    <?php endif; ?>  

    <section class="<?php print _bootstrap_content_span($columns); ?>">  
      <?php if ($page['highlighted']): ?>
        <div class="highlighted hero-unit"><?php print render($page['highlighted']); ?></div>
      <?php endif; ?>
      <?php if ($breadcrumb): print $breadcrumb; endif;?>
      <a id="main-content"></a>
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h1 class="page-header"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php print $messages; ?>
      <?php if ($tabs): ?>
        <?php print render($tabs); ?>
      <?php endif; ?>
      <?php if ($page['help']): ?> 
        <div class="well"><?php print render($page['help']); ?></div>
      <?php endif; ?>
      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>

      <?php  /*print render($page['content']);*/ ?>

      		<div id="pane-1">
      		    <div class="box">
      		        <div class="hbox-element">
      			        <h1>EdmondDesigns</h1>

      			        <div  style='width: 350px'>
      			            <p><i class="icon-ok-sign icon-4x"> </i>Full lifecycle development</p>
				            <p><i class="icon-ok-sign icon-4x"> </i>Front end and back end technologies</p>
				            <p><i class="icon-ok-sign icon-4x"> </i>Hosting and support</p>
				        </div>
				    </div>
				    <div id="icon-slides" class="hbox-element" >
				        <iframe style="width: 650px; height: 400px; border: none" src="/sites/all/themes/edesigns_bootstrap/edge_icons/icon-list.html"></iframe>
				    </div>
				</div>
				<div>
				    <ul style="list-style-type: disc; list-style: disc; " class="box">
				        <li class="hbox-element" >PHP</li>
				        <li class="hbox-element" >Drupal</li>
				        <li class="hbox-element">Adobe Edge</li>
				        <li class="hbox-element">GIT</li>
				        <li class="hbox-element">HTML5</li>
                        <li class="hbox-element">CSS3</li>
                        <li class="hbox-element">Android</li>
                        <li class="hbox-element">IOS</li>
                    </ul>
                </div>
			</div>

    		<div id="pane-2"> 
      			<h1>Recent Articles</h1>
      			<p><?php echo views_embed_view('recent_content', 'block');?></p>
      			<p><a href="/archive/201302"><i class="icon-arrow-right icon-4x"></i>See all articles</a></p>
			</div>			

     		<div id="pane-3"> <!-- portfolio -->
      			<h1>Portfolio</h1>
      			<p>
      				<?php echo views_embed_view('portfolio', 'block_1');?>
			</p>
			<p><a href="/portfolio"><i class="icon-arrow-right icon-4x"></i>Goto portfolio page</a></p>			

		</div>

    <div id="pane-4">
      			<h1>Get in touch</h1>
      			<p>EdmondDesigns</p>
				<p>San Francisco, Ca.</p>
				<p>drew AT edmonddesigns dot com</p>
				<p>(415) 570-1469</p>
        <p id="badges"><img src="<?php echo path_to_theme() . '/images/badges_sm1.png'?>"/></p>
		</div>			
     


    </section>

    <?php if ($page['sidebar_second']): ?>
      <aside class="span3" role="complementary">
        <?php print render($page['sidebar_second']); ?>
      </aside>  <!-- /#sidebar-second -->
    <?php endif; ?>

  </div>
  <footer class="footer container">
    <?php print render($page['footer']); ?>
  </footer>

<script>
	jQuery.noConflict();
	(function ($) {
		$(".scroll").click(function(event){		
			
			event.preventDefault();
			$('html,body').animate({scrollTop:$(this.hash).offset().top}, 500);
		});

		

	})(jQuery);
</script>



</div>

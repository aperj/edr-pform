/***********************
* Adobe Edge Animate Composition Actions
*
* Edit this file with caution, being careful to preserve 
* function signatures and comments starting with 'Edge' to maintain the 
* ability to interact with these actions from within Adobe Edge Animate
*
***********************/
(function($, Edge, compId){
var Composition = Edge.Composition, Symbol = Edge.Symbol; // aliases for commonly used Edge classes

   //Edge symbol: 'stage'
   (function(symbolName) {
      
      
      Symbol.bindTriggerAction(compId, symbolName, "Default Timeline", 3000, function(sym, e) {
         sym.stop();
         
         setTimeout(function() {
         sym.play("fadeout");
         }, 8000);

      });
      //Edge binding end

      Symbol.bindTriggerAction(compId, symbolName, "Default Timeline", 6000, function(sym, e) {
         sym.stop();
         
         setTimeout(function() {
         sym.play("fadein");
         }, 4000);

      });
      //Edge binding end

   })("stage");
   //Edge symbol end:'stage'

   //=========================================================
   
   //Edge symbol: 'git'
   (function(symbolName) {   
   
   })("git");
   //Edge symbol end:'git'

   //=========================================================
   
   //Edge symbol: 'nodejs'
   (function(symbolName) {   
   
      Symbol.bindTriggerAction(compId, symbolName, "Default Timeline", 6000, function(sym, e) {
         sym.stop();
         setTimeout(function() {
           sym.play("shrink");
         }, 5000);

      });
      //Edge binding end

      Symbol.bindTriggerAction(compId, symbolName, "Default Timeline", 10000, function(sym, e) {
         sym.stop();
         setTimeout(function() {
           sym.play("grow");
         }, 5000);

      });
      //Edge binding end

      Symbol.bindTriggerAction(compId, symbolName, "Default Timeline", 14000, function(sym, e) {
         sym.stop();
         setTimeout(function() {
           sym.play("fadeout");
         }, 6000);

      });
      //Edge binding end

      Symbol.bindTriggerAction(compId, symbolName, "Default Timeline", 25000, function(sym, e) {
         sym.stop();
         setTimeout(function() {
           sym.play("slideup");
         }, 4000);

      });
      //Edge binding end

   })("nodejs");
   //Edge symbol end:'nodejs'

   //=========================================================
   
   //Edge symbol: 'html5'
   (function(symbolName) {   
   
      Symbol.bindTriggerAction(compId, symbolName, "Default Timeline", 402, function(sym, e) {
         //get the value of a Symbol variable
         var numShakes = sym.getVariable("numShakes");
         if (numShakes<2) {
           // repeat without pause
           sym.setVariable("numShakes",numShakes+1);
           sym.play("start");
         } else {
         	setTimeout(function() {
         		sym.play("start");
         	}, 1000);
         	sym.setVariable("numShakes",0);
         }
         
         

      });
      //Edge binding end

      Symbol.bindTriggerAction(compId, symbolName, "Default Timeline", 0, function(sym, e) {
         //set the value of a Symbol variable
         sym.setVariable("numShakes",0);

      });
      //Edge binding end

   })("html5");
   //Edge symbol end:'html5'

   //=========================================================
   
   //Edge symbol: 'edge'
   (function(symbolName) {   
   
      Symbol.bindTriggerAction(compId, symbolName, "Default Timeline", 2000, function(sym, e) {
         sym.stop();
         setTimeout(function() {
           sym.play("fadedown");
         }, 8000);

      });
      //Edge binding end

      Symbol.bindTriggerAction(compId, symbolName, "Default Timeline", 4000, function(sym, e) {
         sym.stop();
         setTimeout(function() {
           sym.play("fadeup");
         }, 4000);

      });
      //Edge binding end

   })("edge");
   //Edge symbol end:'edge'

})(jQuery, AdobeEdge, "EDGE-355148062");
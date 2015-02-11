/**
 * Adobe Edge: symbol definitions
 */
(function($, Edge, compId){
//images folder
var im='images/';

var fonts = {};


var resources = [
];
var symbols = {
"stage": {
   version: "1.5.0",
   minimumCompatibleVersion: "1.5.0",
   build: "1.5.0.217",
   baseState: "Base State",
   initialState: "Base State",
   gpuAccelerate: false,
   resizeInstances: false,
   content: {
         dom: [
         {
            id:'badges_slice_01',
            type:'image',
            rect:['14px','5px','100px','95px','auto','auto'],
            fill:["rgba(0,0,0,0)",im+"badges_slice_01.gif",'0px','0px']
         },
         {
            id:'drupal',
            type:'rect',
            rect:['122','5','auto','auto','auto','auto']
         },
         {
            id:'html5',
            type:'rect',
            rect:['22','109','auto','auto','auto','auto']
         },
         {
            id:'edge2',
            type:'rect',
            rect:['256','-1','auto','auto','auto','auto']
         },
         {
            id:'css3',
            type:'image',
            rect:['470px','18px','128px','82px','auto','auto'],
            fill:["rgba(0,0,0,0)",im+"css3.png",'0px','0px']
         },
         {
            id:'nodejs3',
            type:'rect',
            rect:['14','235','auto','auto','auto','auto']
         },
         {
            id:'git3',
            type:'rect',
            rect:['133','121','auto','auto','auto','auto']
         }],
         symbolInstances: [
         {
            id:'html5',
            symbolName:'html5'
         },
         {
            id:'edge2',
            symbolName:'edge'
         },
         {
            id:'drupal',
            symbolName:'drupal'
         },
         {
            id:'nodejs3',
            symbolName:'nodejs'
         },
         {
            id:'git3',
            symbolName:'git'
         }
         ]
      },
   states: {
      "Base State": {
         "${_badges_slice_01}": [
            ["style", "left", '14px'],
            ["style", "top", '5px']
         ],
         "${_html5}": [
            ["style", "left", '359px'],
            ["style", "top", '7px']
         ],
         "${_edge2}": [
            ["style", "top", '26px'],
            ["style", "left", '205px']
         ],
         "${_git3}": [
            ["style", "top", '7px'],
            ["style", "opacity", '0'],
            ["style", "left", '275px']
         ],
         "${_nodejs3}": [
            ["style", "top", '106px']
         ],
         "${_Stage}": [
            ["color", "background-color", 'rgba(253,253,253,0.00)'],
            ["style", "width", '550px'],
            ["style", "height", '250px'],
            ["style", "overflow", 'hidden']
         ],
         "${_drupal}": [
            ["style", "left", '93px']
         ],
         "${_css3}": [
            ["style", "top", '16px'],
            ["transform", "scaleY", '0.7'],
            ["style", "height", '82px'],
            ["transform", "scaleX", '0.7'],
            ["style", "left", '429px'],
            ["style", "width", '128px']
         ]
      }
   },
   timelines: {
      "Default Timeline": {
         fromState: "Base State",
         toState: "",
         duration: 11143,
         autoPlay: true,
         labels: {
            "fadein": 1000,
            "fadeout": 4000
         },
         timeline: [
            { id: "eid144", tween: [ "transform", "${_css3}", "scaleX", '0.7', { fromValue: '0.7'}], position: 0, duration: 0, easing: "easeInOutQuad" },
            { id: "eid25", tween: [ "style", "${_git3}", "opacity", '1', { fromValue: '0.000000'}], position: 1000, duration: 2000 },
            { id: "eid28", tween: [ "style", "${_git3}", "opacity", '0', { fromValue: '1'}], position: 4000, duration: 2000 },
            { id: "eid146", tween: [ "style", "${_css3}", "left", '429px', { fromValue: '429px'}], position: 0, duration: 0, easing: "easeInOutQuad" },
            { id: "eid163", tween: [ "style", "${_css3}", "left", '440px', { fromValue: '429px'}], position: 11143, duration: 0, easing: "easeInOutQuad" },
            { id: "eid145", tween: [ "transform", "${_css3}", "scaleY", '0.7', { fromValue: '0.7'}], position: 0, duration: 0, easing: "easeInOutQuad" },
            { id: "eid147", tween: [ "style", "${_css3}", "top", '16px', { fromValue: '16px'}], position: 0, duration: 0, easing: "easeInOutQuad" },
            { id: "eid162", tween: [ "style", "${_css3}", "top", '12px', { fromValue: '16px'}], position: 11143, duration: 0, easing: "easeInOutQuad" },
            { id: "eid142", tween: [ "style", "${_html5}", "top", '7px', { fromValue: '7px'}], position: 0, duration: 0, easing: "easeInOutQuad" },
            { id: "eid133", tween: [ "style", "${_edge2}", "top", '26px', { fromValue: '26px'}], position: 132, duration: 0, easing: "easeInOutQuad" },
            { id: "eid141", tween: [ "style", "${_html5}", "left", '359px', { fromValue: '359px'}], position: 0, duration: 0, easing: "easeInOutQuad" },
            { id: "eid135", tween: [ "style", "${_drupal}", "left", '93px', { fromValue: '93px'}], position: 132, duration: 0, easing: "easeInOutQuad" },
            { id: "eid136", tween: [ "style", "${_edge2}", "left", '205px', { fromValue: '205px'}], position: 132, duration: 0, easing: "easeInOutQuad" }         ]
      }
   }
},
"git": {
   version: "1.5.0",
   minimumCompatibleVersion: "1.5.0",
   build: "1.5.0.217",
   baseState: "Base State",
   initialState: "Base State",
   gpuAccelerate: false,
   resizeInstances: false,
   content: {
   dom: [
   {
      id: 'badges_slice_04',
      type: 'image',
      rect: ['0px','0px','100px','95px','auto','auto'],
      fill: ['rgba(0,0,0,0)','images/badges_slice_04.gif','0px','0px']
   }],
   symbolInstances: [
   ]
   },
   states: {
      "Base State": {
         "${symbolSelector}": [
            ["style", "height", '95px'],
            ["style", "width", '100px']
         ],
         "${_badges_slice_04}": [
            ["style", "top", '0px'],
            ["style", "left", '0px']
         ]
      }
   },
   timelines: {
      "Default Timeline": {
         fromState: "Base State",
         toState: "",
         duration: 0,
         autoPlay: true,
         timeline: [
         ]
      }
   }
},
"nodejs": {
   version: "1.5.0",
   minimumCompatibleVersion: "1.5.0",
   build: "1.5.0.217",
   baseState: "Base State",
   initialState: "Base State",
   gpuAccelerate: false,
   resizeInstances: false,
   content: {
   dom: [
   {
      id: 'lamp2',
      type: 'rect',
      rect: ['595','89','auto','auto','auto','auto']
   },
   {
      id: 'nodejs',
      type: 'image',
      rect: ['0px','-14px','520px','129px','auto','auto'],
      fill: ['rgba(0,0,0,0)','images/nodejs.png','0px','0px']
   }],
   symbolInstances: [
   {
      id: 'lamp2',
      symbolName: 'lamp'
   }   ]
   },
   states: {
      "Base State": {
         "${_lamp2}": [
            ["style", "left", '544px'],
            ["style", "top", '10px']
         ],
         "${_nodejs}": [
            ["style", "top", '144px'],
            ["style", "height", '129px'],
            ["style", "opacity", '1'],
            ["style", "left", '0px'],
            ["style", "width", '520px']
         ],
         "${symbolSelector}": [
            ["style", "height", '178px'],
            ["style", "width", '520px']
         ]
      }
   },
   timelines: {
      "Default Timeline": {
         fromState: "Base State",
         toState: "",
         duration: 25000,
         autoPlay: true,
         labels: {
            "slideup": 3024,
            "shrink": 7000,
            "grow": 11000,
            "fadeout": 15000
         },
         timeline: [
            { id: "eid167", tween: [ "style", "${_lamp2}", "top", '10px', { fromValue: '10px'}], position: 0, duration: 0, easing: "easeInOutQuad" },
            { id: "eid151", tween: [ "style", "${_nodejs}", "width", '520px', { fromValue: '520px'}], position: 3021, duration: 0, easing: "easeInOutQuad" },
            { id: "eid160", tween: [ "style", "${_nodejs}", "width", '275px', { fromValue: '520px'}], position: 7000, duration: 3000, easing: "easeInOutQuad" },
            { id: "eid161", tween: [ "style", "${_nodejs}", "width", '520px', { fromValue: '275px'}], position: 11000, duration: 3000, easing: "easeInOutQuad" },
            { id: "eid42", tween: [ "style", "${_nodejs}", "top", '-14px', { fromValue: '144px'}], position: 3024, duration: 2976, easing: "easeOutBounce" },
            { id: "eid150", tween: [ "style", "${_nodejs}", "top", '-14px', { fromValue: '-14px'}], position: 25000, duration: 0, easing: "easeInOutQuad" },
            { id: "eid166", tween: [ "style", "${_lamp2}", "left", '544px', { fromValue: '544px'}], position: 0, duration: 0, easing: "easeInOutQuad" },
            { id: "eid172", tween: [ "style", "${_lamp2}", "left", '305px', { fromValue: '544px'}], position: 7000, duration: 3000, easing: "easeInOutQuad" },
            { id: "eid175", tween: [ "style", "${_lamp2}", "left", '551px', { fromValue: '305px'}], position: 11000, duration: 3000, easing: "easeInOutQuad" },
            { id: "eid92", tween: [ "style", "${_nodejs}", "opacity", '0', { fromValue: '1'}], position: 15000, duration: 10000, easing: "easeInOutQuad" }         ]
      }
   }
},
"html5": {
   version: "1.5.0",
   minimumCompatibleVersion: "1.5.0",
   build: "1.5.0.217",
   baseState: "Base State",
   initialState: "Base State",
   gpuAccelerate: false,
   resizeInstances: false,
   content: {
   dom: [
   {
      id: 'badges_slice_03',
      type: 'image',
      rect: ['0px','0px','100px','95px','auto','auto'],
      fill: ['rgba(0,0,0,0)','images/badges_slice_03.gif','0px','0px']
   }],
   symbolInstances: [
   ]
   },
   states: {
      "Base State": {
         "${_badges_slice_03}": [
            ["style", "top", '0px'],
            ["style", "left", '0px'],
            ["transform", "rotateZ", '0deg']
         ],
         "${symbolSelector}": [
            ["style", "height", '95px'],
            ["style", "width", '100px']
         ]
      }
   },
   timelines: {
      "Default Timeline": {
         fromState: "Base State",
         toState: "",
         duration: 401.7421875,
         autoPlay: true,
         labels: {
            "start": 130
         },
         timeline: [
            { id: "eid50", tween: [ "transform", "${_badges_slice_03}", "rotateZ", '10deg', { fromValue: '0deg'}], position: 130, duration: 69 },
            { id: "eid46", tween: [ "transform", "${_badges_slice_03}", "rotateZ", '0deg', { fromValue: '10deg'}], position: 199, duration: 104 },
            { id: "eid48", tween: [ "transform", "${_badges_slice_03}", "rotateZ", '-5deg', { fromValue: '0deg'}], position: 303, duration: 99 }         ]
      }
   }
},
"edge": {
   version: "1.5.0",
   minimumCompatibleVersion: "1.5.0",
   build: "1.5.0.217",
   baseState: "Base State",
   initialState: "Base State",
   gpuAccelerate: false,
   resizeInstances: false,
   content: {
   dom: [
   {
      id: 'edge',
      type: 'image',
      rect: ['0px','0px','256px','256px','auto','auto'],
      fill: ['rgba(0,0,0,0)','images/edge.png','0px','0px']
   }],
   symbolInstances: [
   ]
   },
   states: {
      "Base State": {
         "${_edge}": [
            ["style", "top", '-98px'],
            ["transform", "scaleY", '0.2'],
            ["style", "left", '-98px'],
            ["transform", "scaleX", '0.2']
         ],
         "${symbolSelector}": [
            ["style", "height", '60px'],
            ["style", "overflow", 'hidden'],
            ["style", "width", '60px']
         ]
      }
   },
   timelines: {
      "Default Timeline": {
         fromState: "Base State",
         toState: "",
         duration: 4000,
         autoPlay: true,
         labels: {
            "fadeup": 1000,
            "fadedown": 3000
         },
         timeline: [
            { id: "eid57", tween: [ "transform", "${_edge}", "scaleX", '0.7', { fromValue: '0.2'}], position: 1000, duration: 1000, easing: "easeInOutQuad" },
            { id: "eid82", tween: [ "transform", "${_edge}", "scaleX", '0.2', { fromValue: '0.7'}], position: 3000, duration: 1000, easing: "easeInOutQuad" },
            { id: "eid127", tween: [ "style", "${_edge}", "top", '-98px', { fromValue: '-98px'}], position: 1000, duration: 0, easing: "easeInOutQuad" },
            { id: "eid58", tween: [ "transform", "${_edge}", "scaleY", '0.7', { fromValue: '0.2'}], position: 1000, duration: 1000, easing: "easeInOutQuad" },
            { id: "eid83", tween: [ "transform", "${_edge}", "scaleY", '0.2', { fromValue: '0.7'}], position: 3000, duration: 1000, easing: "easeInOutQuad" },
            { id: "eid126", tween: [ "style", "${_edge}", "left", '-98px', { fromValue: '-98px'}], position: 1000, duration: 0, easing: "easeInOutQuad" }         ]
      }
   }
},
"drupal": {
   version: "1.5.0",
   minimumCompatibleVersion: "1.5.0",
   build: "1.5.0.217",
   baseState: "Base State",
   initialState: "Base State",
   gpuAccelerate: false,
   resizeInstances: false,
   content: {
   dom: [
   {
      id: 'badges_slice_02',
      type: 'image',
      rect: ['0px','0px','101px','95px','auto','auto'],
      fill: ['rgba(0,0,0,0)','images/badges_slice_02.gif','0px','0px']
   }],
   symbolInstances: [
   ]
   },
   states: {
      "Base State": {
         "${_badges_slice_02}": [
            ["style", "top", '0px'],
            ["style", "left", '0px'],
            ["transform", "rotateZ", '0deg']
         ],
         "${symbolSelector}": [
            ["style", "height", '95px'],
            ["style", "width", '101px']
         ]
      }
   },
   timelines: {
      "Default Timeline": {
         fromState: "Base State",
         toState: "",
         duration: 17000,
         autoPlay: true,
         labels: {
            "rotate": 15000
         },
         timeline: [
            { id: "eid95", tween: [ "transform", "${_badges_slice_02}", "rotateZ", '360deg', { fromValue: '0deg'}], position: 15000, duration: 2000, easing: "easeInOutQuad" }         ]
      }
   }
},
"lamp": {
   version: "1.5.0",
   minimumCompatibleVersion: "1.5.0",
   build: "1.5.0.217",
   baseState: "Base State",
   initialState: "Base State",
   gpuAccelerate: false,
   resizeInstances: false,
   content: {
   dom: [
   {
      id: 'lamp22',
      type: 'image',
      rect: ['0px','0px','200px','124px','auto','auto'],
      fill: ['rgba(0,0,0,0)','images/lamp2.png','0px','0px']
   }],
   symbolInstances: [
   ]
   },
   states: {
      "Base State": {
         "${_lamp22}": [
            ["style", "left", '0px'],
            ["style", "top", '0px']
         ],
         "${symbolSelector}": [
            ["style", "height", '124px'],
            ["style", "width", '200px']
         ]
      }
   },
   timelines: {
      "Default Timeline": {
         fromState: "Base State",
         toState: "",
         duration: 0,
         autoPlay: false,
         timeline: [
            { id: "eid164", tween: [ "style", "${_lamp22}", "left", '0px', { fromValue: '0px'}], position: 0, duration: 0, easing: "easeInOutQuad" },
            { id: "eid165", tween: [ "style", "${_lamp22}", "top", '0px', { fromValue: '0px'}], position: 0, duration: 0, easing: "easeInOutQuad" }         ]
      }
   }
}
};


Edge.registerCompositionDefn(compId, symbols, fonts, resources);

/**
 * Adobe Edge DOM Ready Event Handler
 */
$(window).ready(function() {
     Edge.launchComposition(compId);
});
})(jQuery, AdobeEdge, "EDGE-355148062");

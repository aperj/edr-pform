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
            id:'badges_slice_02',
            type:'image',
            rect:['122px','5px','101px','95px','auto','auto'],
            fill:["rgba(0,0,0,0)",im+"badges_slice_02.gif",'0px','0px']
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
            rect:['550px','102px','128px','82px','auto','auto'],
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
            id:'nodejs3',
            symbolName:'nodejs'
         },
         {
            id:'edge2',
            symbolName:'edge'
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
         "${_badges_slice_02}": [
            ["style", "top", '5px'],
            ["style", "left", '122px']
         ],
         "${_git3}": [
            ["style", "top", '100px'],
            ["style", "opacity", '0']
         ],
         "${_nodejs3}": [
            ["style", "top", '244px']
         ],
         "${_Stage}": [
            ["color", "background-color", 'rgba(253,253,253,0.00)'],
            ["style", "width", '550px'],
            ["style", "height", '400px'],
            ["style", "overflow", 'hidden']
         ],
         "${_css3}": [
            ["style", "top", '102px'],
            ["style", "height", '82px'],
            ["style", "left", '550px'],
            ["style", "width", '128px']
         ]
      }
   },
   timelines: {
      "Default Timeline": {
         fromState: "Base State",
         toState: "",
         duration: 6000,
         autoPlay: true,
         labels: {
            "fadein": 1000,
            "fadeout": 4000
         },
         timeline: [
            { id: "eid29", tween: [ "style", "${_git3}", "top", '100px', { fromValue: '100px'}], position: 3024, duration: 0 },
            { id: "eid39", tween: [ "style", "${_nodejs3}", "top", '244px', { fromValue: '244px'}], position: 3024, duration: 0 },
            { id: "eid25", tween: [ "style", "${_git3}", "opacity", '1', { fromValue: '0.000000'}], position: 1000, duration: 2000 },
            { id: "eid28", tween: [ "style", "${_git3}", "opacity", '0', { fromValue: '1'}], position: 4000, duration: 2000 }         ]
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
      id: 'nodejs',
      type: 'image',
      rect: ['0px','-14px','520px','129px','auto','auto'],
      fill: ['rgba(0,0,0,0)','images/nodejs.png','0px','0px']
   }],
   symbolInstances: [
   ]
   },
   states: {
      "Base State": {
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
            { id: "eid42", tween: [ "style", "${_nodejs}", "top", '-14px', { fromValue: '144px'}], position: 3024, duration: 2976, easing: "easeOutBounce" },
            { id: "eid92", tween: [ "style", "${_nodejs}", "opacity", '0', { fromValue: '1'}], position: 15000, duration: 10000, easing: "easeInOutQuad" },
            { id: "eid86", tween: [ "style", "${_nodejs}", "width", '275px', { fromValue: '520px'}], position: 7000, duration: 3000, easing: "easeInOutQuad" },
            { id: "eid89", tween: [ "style", "${_nodejs}", "width", '520px', { fromValue: '275px'}], position: 11000, duration: 3000, easing: "easeInOutQuad" }         ]
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
            ["style", "top", '0px'],
            ["transform", "scaleY", '0.2'],
            ["style", "left", '0px'],
            ["transform", "scaleX", '0.2']
         ],
         "${symbolSelector}": [
            ["style", "height", '256px'],
            ["style", "width", '256px']
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
            { id: "eid57", tween: [ "transform", "${_edge}", "scaleX", '1', { fromValue: '0.2'}], position: 1000, duration: 1000, easing: "easeInOutQuad" },
            { id: "eid82", tween: [ "transform", "${_edge}", "scaleX", '0.2', { fromValue: '1'}], position: 3000, duration: 1000, easing: "easeInOutQuad" },
            { id: "eid58", tween: [ "transform", "${_edge}", "scaleY", '1', { fromValue: '0.2'}], position: 1000, duration: 1000, easing: "easeInOutQuad" },
            { id: "eid83", tween: [ "transform", "${_edge}", "scaleY", '0.2', { fromValue: '1'}], position: 3000, duration: 1000, easing: "easeInOutQuad" }         ]
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

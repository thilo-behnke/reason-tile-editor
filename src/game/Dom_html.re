/*type svgElement;*/
type imageElement;

type canvasRenderingContext2D;

type canvasElement;

type performanceObj;
type imageObj;

[@bs.val] external document : Dom.document = "";

[@bs.val] external window : Dom.window = "";

[@bs.send] [@bs.send]
/*external createSvg:*/
/*(Dom.document, Dom.eventTarget_like(Dom._node(Dom._document(Dom._baseClass))), string) => svgElement =*/
/*"createElementNS";*/
external createImg : (Dom.document, [@bs.as "img"] _) => imageElement =
  "createElement";

[@bs.val] external requestAnimationFrame : (float => unit) => unit = "";

[@bs.return null_to_opt] [@bs.send]
external getElementById : (Dom.document, string) => option(Dom.element) = "";

[@bs.send]
external addEventListener :
  (Dom.document, string, Dom.event_like('a) => bool, bool) => unit =
  "";

type domElement = {. "id": string};
[@bs.send]
external elementsFromPoint :
  (Dom.document, int, int) => Js.Array.t(domElement) =
  "";

[@bs.send]
external addEventListenerImg :
  (imageElement, string, Dom.event_like('a) => bool, bool) => unit =
  "addEventListener";

[@bs.val] external performance : performanceObj = "";
[@bs.send] external performanceNow : performanceObj => float = "now";

[@bs.new] external createImg : (int, int) => imageObj = "Image";

/* unsafe casts */
external imageObjToJsObj : imageObj => Js.t({..}) = "%identity";
external imageElementToJsObj : imageElement => Js.t({..}) = "%identity";
/*external svgElementToJsObj: svgElement => Js.t({..}) = "%identity";*/

external canvasRenderingContext2DToJsObj :
  canvasRenderingContext2D => Js.t({..}) =
  "%identity";

external canvasElementToJsObj : canvasElement => Js.t({..}) = "%identity";

external keyboardEventToJsObj : Dom.keyboardEvent => Js.t({..}) = "%identity";

external elementToCanvasElement : Dom.element => canvasElement = "%identity";
external elementToJsObj : Dom.element => Js.t({..}) = "%identity";

external windowToJsObj : Dom.window => Js.t({..}) = "%identity";

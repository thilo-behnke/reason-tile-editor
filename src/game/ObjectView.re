open General;
open GameObject;

let component = pureComp("ObjectView");

let make =
    (
      ~id: int,
      ~gameObj: GameObject.obj,
      ~isBeingDragged: bool,
      ~updatePos: pixPos => unit,
      ~selectObj: pixPos => unit,
      _children,
    ) => {
  ...component,
  render: _ =>
    <div
      className=(GameObject.get_style(gameObj, isBeingDragged))
      onClick=ReactEvent.Mouse.stopPropagation
      onMouseDown=(
        e => {
          let nE = ReactEvent.Synthetic.nativeEvent(e);
          ReactEvent.Mouse.stopPropagation(e);
          selectObj((nE##offsetX, nE##offsetY));
        }
      )
      onMouseMove=(
        e =>
          isBeingDragged ?
            updatePos((
              ReactEvent.Mouse.pageX(e),
              ReactEvent.Mouse.pageY(e),
            )) :
            ()
      )>
      (ReasonReact.string(GameObject.get_rep(gameObj, id)))
    </div>,
};

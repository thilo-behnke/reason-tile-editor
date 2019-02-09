open Trash;
let component = ReasonReact.statelessComponent("TrashView");

let make = (_children, ~active) => {
  ...component,
  render: _ =>
    /* TODO: use domelement.elementFromPoint => https://www.quirksmode.org/dom/w3c_cssom.html#documentview */
    <div className=(Trash.get_style(active)) id="trash">
      (ReasonReact.string("Trash"))
    </div>,
};

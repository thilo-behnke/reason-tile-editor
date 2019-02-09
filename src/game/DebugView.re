let component = ReasonReact.statelessComponent("Debug");

let make = (~selectedObj, _children) => {
  ...component,
  render: self => <div> (ReasonReact.string("Debug")) </div>,
};

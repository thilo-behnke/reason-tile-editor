open Tile;

type retainedProps = {
  tile: Tile.tile,
  active: bool,
};
let component = ReasonReact.statelessComponentWithRetainedProps("TileView");

let make = (~tile, ~onClick=_ => (), ~active=false, _children) => {
  ...component,
  retainedProps: {
    tile,
    active,
  },
  shouldUpdate: ({oldSelf, newSelf}) =>
    oldSelf.retainedProps.tile !== newSelf.retainedProps.tile
    || oldSelf.retainedProps.active !== newSelf.retainedProps.active,
  render: _ =>
    <button onClick className=(Tile.get_style(tile, active))>
      (ReasonReact.string(Tile.get_rep(tile)))
    </button>,
};

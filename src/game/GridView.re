open General;
open Tile;
open Grid;

let component = pureComp("GridView");

let make = (~grid: StGrid.grid, ~setTile, _children) => {
  ...component,
  render: self =>
    <div>
      (_children |> ReasonReact.array)
      <div className=(StGrid.get_style(grid))>
        (
          StGrid.get_tiles(grid)
          |> List.map((t: Tile.tile) =>
               <TileView onClick=(e => setTile(Tile.get_pos(t))) tile=t />
             )
          |> Array.of_list
          |> ReasonReact.array
        )
      </div>
    </div>,
};

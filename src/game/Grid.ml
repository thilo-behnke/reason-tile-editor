include Utils
open General
open Tile
open Css

module type Grid  =
  sig
    type props
    type grid
    val create : (int* int) -> grid
    val set_tile : grid -> Tile.tile -> grid
    val get_tile : grid -> gridPos -> Tile.tile
    val get_tiles : grid -> Tile.tile list
    (* val add_obj : grid -> (string* string* string) -> (float* float) -> grid
     * val rem_obj : grid -> obj -> grid *)
    val get_style: grid -> string
  end
module StGrid : Grid =
  struct
    type props = {
      rows: int;
      cols: int;
      obj_counter: int;}
    type grid = (Tile.tile list* props)
    let create (cols,rows) =
      (let g =
         (List.map (fun i  -> Tile.create ((i mod cols), (i / rows)) "empty")) @@
           (EList.range @@ (cols * rows)) in
       (g, { rows = rows; cols = cols; obj_counter = 0 }) : grid)
    let set_tile (g,props) (pos,tt) =
      let g' =
        List.map
          (fun ((pos',_) as t)  -> if pos = pos' then (pos, tt) else t) g in
      (g', props)
    let get_tile ((g,_) : grid) pos =
      let t = List.find (fun (pos',_)  -> pos = pos') g in t
    let get_tiles (g,_) = g
    (* let add_obj ((g,objs,props) : grid) obj pixPos =
     *   (let { obj_counter } = props in
     *    (g, ((Object.create obj_counter obj pixPos) :: objs), props) : 
     *   grid)
     * let rem_obj (g,objs,props) obj =
     *   let id = Object.get_id obj in
     *   let objs' = List.filter (fun o  -> (Object.get_id o) <> id) objs in
     *   (g, objs', props) *)
    let get_style ((_,props): grid) =
      let {cols; rows} = props in
      style
        [gridRow 2 5;
        gridColumn 1 10;
        display grid;
        paddingTop(`px(50));
        gridTemplateRows [`repeat ((`num rows), (`fr 1.))];
        gridTemplateColumns [`repeat ((`num cols), (`fr 1.))]]
  end 

open Css
open General


module Tile =
struct
  type tileType =
    | Empty
    | Ground
    | Rock
    | Air
  type tile = (gridPos* tileType)
  let create (col, row) t =
    let tt = match t with
    | "ground" -> Ground
    | "rock" -> Rock
    | "air" -> Air
    | _ -> Empty in ((col, row), tt)
  let update (col, row) = function
    | Some(tt) -> (col, row), tt
    | None -> (col, row), Empty
  let has_type t (_, tt) = match t with
    | Some(tt') -> tt = tt'
    | None -> false 
  let get_pos (p, _) = p
  let get_type = function | Some(_, tt) -> Some(tt) | None -> None
  let get_rep ((_,_),t) =
      match t with
      | Empty  -> (("empty")[@reason.raw_literal "empty"])
      | Ground  -> (("ground")[@reason.raw_literal "ground"])
      | Rock  -> (("rock")[@reason.raw_literal "rock"])
      | Air  -> (("air")[@reason.raw_literal "air"])
  let get_style t active =
    let c = match t with | (_,Empty ) -> `auto | _ -> `pointer in
    let s_border = if active then border (`px 3) `solid (`rgba (244, 0, 0, 1.)) else border (`px 1) `solid (`rgba (127, 63, 191, 1.)) in
    let bc =
      match t with
      | (_,Empty ) -> `rgba (255, 255, 255, 1.0)
      | (_,Ground ) -> `rgba (187, 91, 46, 1.0)
      | _ -> `rgba (46, 84, 187, 1.0) in
    style
      [cursor c;
       backgroundColor bc;
       height (`px 50);
       width (`px 50);
       s_border]  end

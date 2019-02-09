open Css
open Tile
include Utils

type obj_attrs = {strs: string list; augs: string list; emos: string list}
let load_tileset () = [Tile.create (0, 0) "grass"; Tile.create (0, 1) "ground"; Tile.create (0, 2) "rock"]
let load_object_attrs (): obj_attrs =
  {strs = ["mouse"]; augs = ["boots"; "wings"; "springs"; "jetpack"; "hook"]; emos= ["indifferent"; "fearful"; "aggressive"]}

module Header = struct
  type userType =
    | Free
    | Premium
  type user =
    | LoggedIn of (string * userType)
    | Guest
  type header = user * (Tile.tile list) * obj_attrs
  let create (un,pw) = Guest, load_tileset (), load_object_attrs ()
  let get_tiles (u, t, _) = t
  let get_user_rep (u, _, _) = match u with 
    | Guest -> "Guest User"
    | LoggedIn(nick, Free) -> "Hi, " ^ nick ^ " (free)"
    | LoggedIn(nick, Premium) -> "Hi, " ^ nick ^ " <star>"
  let get_obj_attrs (_,_,oa) = oa
  let get_style _ = style[display `flex;]
end

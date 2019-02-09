open Css

module Trash = struct
  let get_style active = if active then style[backgroundColor (`rgba(255, 0, 0, 1.0))] else style[backgroundColor (`rgba(255, 255, 255, 1.0))]
  end

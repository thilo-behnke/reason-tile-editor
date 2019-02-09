open General
open Css
open Utils
type pixPos = (int* int)
module type GameObject  =
  sig
    type props
    type obj
    val create : int -> (string* string* string) -> pixPos -> obj
    val update_pos : obj -> pixPos -> obj
    val get_id : obj -> int
  end
module GameObject =
  struct
    type props = {
      str: structure;
      aug: augmentation;
      emo: emotion;}
    type obj = (pixPos*props)
    let create (s,a,e) pos =
      let str =
        match s with
        | (("player")[@reason.raw_literal "player"]) -> Player
        | _ -> Mouse in
      let aug =
        match a with
        | (("wings")[@reason.raw_literal "wings"]) -> Wings
        | (("spring")[@reason.raw_literal "spring"]) -> Spring
        | (("jetpack")[@reason.raw_literal "jetpack"]) -> Jetpack
        | (("hook")[@reason.raw_literal "hook"]) -> Hook
        | _ -> Boots in
      let emo =
        match e with
        | (("fearful")[@reason.raw_literal "fearful"]) -> Fearful
        | (("aggressive")[@reason.raw_literal "aggressive"]) -> Aggressive
        | _ -> Indifferent in
      (pos, { str; aug; emo })
    let update_pos (_,t) pos' = (pos', t)
    let update_str ({ aug; emo },t) str = ({ str; aug; emo }, t)
    let get_pos (pos,_) = pos
    let add_to_pos (x',y') ((x,y),props) = ((x+x', y+y'),props)
    let set_pos pos (_,props) = (pos,props)
    let get_style ((x,y),_) isActive = 
      let box_shadow = if isActive then boxShadow (`rgba (0, 0, 0, 0.75)) ~x:(`px 10) ~y:(`px 10) ~blur:(`px 5) else boxShadow (`rgba (0, 0, 0, 0.5)) ~x:(`px 5) ~y:(`px 5) ~blur:(`px 10) in
      let z_index = if isActive then zIndex(120) else zIndex(100) in
      style
        [cursor(`pointer);
        width (`px 100);
        height (`px 100);
        position `absolute;
        box_shadow;
        transition "box-shadow" ~duration:(300) ~timingFunction: `easeInOut;
        border (`px 1) `solid (`rgba(0, 0, 0, 1.));
        z_index;
        top (`px y);
        left (`px x);
        backgroundColor(`rgba (244, 0, 0, 1.))]
    let get_rep ((x, y),{str;aug;emo}) id =
      let s_str = match str with | Player -> "player" | _ -> "mouse" in
      let s_aug = match aug with | Wings -> "wings" | Spring -> "spring" | Jetpack -> "jetpack" | Hook -> "hook" | _ -> "boots" in
      let s_emo = match emo with | Fearful -> "fearful" | Aggressive -> "aggressive" | _ -> "indifferent" in
      "Pos: " ^ string_of_int(x) ^ "," ^ string_of_int(y) ^ " / " ^ s_str ^ ", " ^ (s_aug) ^ ", " ^ (s_emo) ^ " (" ^ string_of_int(id) ^ ") \n Drag Me!"
  end
module ObjectList =
  struct
    type objList = (int * GameObject.obj) list * int
    let create () = [] , 1
    let add_obj (l,c) obj = (c, obj) :: l,c+1
    let get_obj (l,c) id = List.find (fun (id',_) -> id = id') l,c
    let upd_obj (l,c) id f : objList = let l' = List.filter (fun (id',_) -> id <> id') l in
      let _,obj = List.find (fun (id',_) -> id' = id) l in
      (id,f obj)::l',c
    let rem_obj (l,c) id = List.filter (fun (id',_) -> id <> id') l,c
    let get_obj_list (l,_) = l
    let move_to_frond (l,c) id = let t, f = EList.partition (fun (id',_) -> id' = id) l in
      List.append t f, c
  end

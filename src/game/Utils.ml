module Utils =
  struct
    let add a b = a + b
    let inc i = i + 1
    let dec i = i - 1
    let div a b = a / b
    let double i = i * 2
    let incDouble i = (inc i) |> double
    let sub a b = a - b
    let sum a b = a + b
  end
module MyString =
  struct
    let append s s' = s ^ s'
    let explode s =
      let rec inner acc s' =
        match String.length s' with
        | 0 -> acc
        | n ->
            let c = s'.[0] in
            let ss = String.sub s' 1 (n - 1) in inner (c :: acc) ss in
      List.rev @@ (inner [] s)
  end
module EList =
  struct
    include List
    let rec map f = function | [] -> [] | x::xs -> (f x) :: (map f xs)
    let rec forEach f = function | [] -> () | x::xs -> (f x; forEach f xs)
    let forEachi f l =
      let rec inner i =
        function | [] -> () | x::xs -> (f x i; inner (i + 1) xs) in
      inner 0 l
    let range n =
      let rec inner acc i =
        match i < n with | true  -> inner (i :: acc) (i + 1) | false  -> acc in
      inner [] 0
    let rec find_opt pred =
      function
      | [] -> None
      | x::xs -> if pred x then Some x else find_opt pred xs
    let reducei f arr =
      let rec inner acc i =
        function | [] -> acc | x::xs -> inner (f acc i x) (i + 1) xs in
      inner [] 0 arr
    let partition pred l =
      let truthy = List.filter (fun x -> pred x) l in
      let falsy = List.filter (fun x -> not(pred x)) l in truthy, falsy
  end
let (|>) x f = f x
let (<|) f x = x f

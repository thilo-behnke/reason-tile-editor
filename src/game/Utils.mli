module Utils: sig
    val add: int -> int -> int
    val inc: int -> int
    val dec: int -> int
    val div: int -> int -> int
    val double: int -> int
    val incDouble: int -> int
    val sub: int -> int -> int
    val sum: int -> int -> int
end

module MyString: sig
    val append: string -> string -> string
    val explode: string -> char list
end

module EList: sig
    val map: ('a -> 'b) -> 'a list -> 'b list
    val forEach: ('a -> unit) -> 'a list -> unit
    val forEachi: ('a -> int -> unit) -> 'a list -> unit
    val range: int -> int list
    val find_opt: ('a -> bool) -> 'a list -> 'a option
    val reducei: ('b list -> int -> 'a -> 'b list) -> 'a list -> 'b list
    val partition: ('a -> bool) -> 'a list -> 'a list * 'a list
    end

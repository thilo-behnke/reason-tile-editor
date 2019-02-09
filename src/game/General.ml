type structure =
  | Player
  | Mouse
  | Unknown
type augmentation =
  | Boots
  | Wings
  | Spring
  | Jetpack
  | Hook
type emotion =
  | Indifferent
  | Fearful
  | Aggressive

type renderInf = {cls: string; rep: string}

type gridPos = (int* int)

let arr = ReasonReact.array
let stateComp = ReasonReact.reducerComponent
let pureComp = ReasonReact.statelessComponent

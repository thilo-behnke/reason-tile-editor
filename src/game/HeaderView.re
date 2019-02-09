open General;
open Header;
open Tile;
open GameObject;
open Styles;

type headerActions =
  | SelectStructure(string)
  | SelectAugmentation(string)
  | SelectEmotion(string);

type headerState = {
  str: string,
  aug: string,
  emo: string,
};

let component = ReasonReact.reducerComponent("HeaderView");

let createObj = (str, aug, emo) =>
  GameObject.create((str, aug, emo), (200, 200));

let make =
    (
      ~header: Header.header,
      ~selectedTile: option(Tile.tile),
      ~setActive: option(Tile.tile) => unit,
      ~trashActive: bool,
      ~addObj: GameObject.obj => unit,
      _children,
    ) => {
  ...component,
  initialState: () => {str: "mouse", aug: "boots", emo: "fearful"},
  reducer: (action: headerActions, state: headerState) =>
    switch (action) {
    | SelectStructure(str) => ReasonReact.Update({...state, str})
    | SelectAugmentation(aug) => ReasonReact.Update({...state, aug})
    | SelectEmotion(emo) => ReasonReact.Update({...state, emo})
    | _ => ReasonReact.Update(state)
    },
  render: ({state, send}) =>
    <div id="header" className=Styles.header>
      <div className=(Header.get_style(header))>
        (
          List.map(
            (t: Tile.tile) =>
              <TileView
                active=(
                  switch (selectedTile) {
                  | Some(a) => a == t
                  | None => false
                  }
                )
                tile=t
                onClick=(_ => setActive(Some(t)))
              />,
            Header.get_tiles(header),
          )
          |> Array.of_list
          |> arr
        )
      </div>
      <button onClick=(e => ())>
        (ReasonReact.string(Header.get_user_rep(header)))
      </button>
      <div>
        {
          let {strs, augs, emos} = Header.get_obj_attrs(header);
          <div>
            <select
              onChange=(
                e =>
                  send(
                    SelectStructure(
                      ReactEvent.Synthetic.nativeEvent(e)##target##value,
                    ),
                  )
              )>
              (
                List.map(
                  s => <option value=s> (ReasonReact.string(s)) </option>,
                  strs,
                )
                |> Array.of_list
                |> ReasonReact.array
              )
            </select>
            <select
              onChange=(
                e =>
                  send(
                    SelectAugmentation(
                      ReactEvent.Synthetic.nativeEvent(e)##target##value,
                    ),
                  )
              )>
              (
                List.map(
                  s => <option value=s> (ReasonReact.string(s)) </option>,
                  augs,
                )
                |> Array.of_list
                |> ReasonReact.array
              )
            </select>
            <select
              onChange=(
                e =>
                  send(
                    SelectEmotion(
                      ReactEvent.Synthetic.nativeEvent(e)##value,
                    ),
                  )
              )>
              (
                List.map(
                  s => <option value=s> (ReasonReact.string(s)) </option>,
                  emos,
                )
                |> Array.of_list
                |> ReasonReact.array
              )
            </select>
            <button
              onClick=(
                _ => createObj(state.str, state.aug, state.emo) |> addObj
              )>
              (ReasonReact.string("create"))
            </button>
          </div>;
        }
      </div>
      <TrashView active=trashActive />
    </div>,
};

include Grid;
open Tile;
open Header;
open GameObject;
include Styles;

module GetHello = [%graphql {|
     query {hello}
     |}];
module GetHelloQuery = ReasonApollo.CreateQuery(GetHello);

type gridProps = {
  rows: int,
  cols: int,
};

type editorActions =
  | LogInUser(string, string)
  | SetActiveTile(option(Tile.tile))
  | UpdateTile(gridPos)
  | DragObj(pixPos)
  | SelectObj(int, pixPos)
  | UnselectObj(unit)
  | AddObj(GameObject.obj)
  | DeleteSelectedObj(unit);
type dragObj = {
  id: int,
  dragPos: pixPos,
};

type state = {
  divRef: ref(option(Dom.element)),
  header: Header.header,
  grid: StGrid.grid,
  objs: ObjectList.objList,
  selectedTile: option(Tile.tile),
  selectedObj: option(dragObj),
  trashActive: bool,
};

let setRef = (theRef, {ReasonReact.state}) =>
  state.divRef := Js.Nullable.toOption(theRef);

let component = ReasonReact.reducerComponent("Editor");

let make = _children => {
  ...component,
  initialState: () => {
    divRef: ref(None),
    header: Header.create(("", "")),
    grid: StGrid.create((50, 20)),
    objs: ObjectList.create(),
    selectedTile: None,
    selectedObj: None,
    trashActive: false,
  },
  reducer: (action: editorActions, state) =>
    switch (action) {
    | SetActiveTile(t) => ReasonReact.Update({...state, selectedTile: t})
    | UpdateTile(pos) =>
      ReasonReact.Update({
        ...state,
        grid:
          StGrid.set_tile(
            state.grid,
            Tile.update(pos, Tile.get_type(state.selectedTile)),
          ),
      })
    | DragObj(pos) =>
      let (objs, trashActive) =
        switch (state.selectedObj) {
        | None => (state.objs, false)
        | Some({id, dragPos}) =>
          let (x, y) = pos;
          let (x', y') = dragPos;
          let trash =
            Dom_html.elementsFromPoint(Dom_html.document, x, y)
            |> Array.to_list
            |> List.exists(e => e##id == "header");
          let pos' = (x - x', y - y');
          (
            ObjectList.upd_obj(state.objs, id, GameObject.set_pos(pos')),
            trash,
          );
        };
      ReasonReact.Update({...state, objs, trashActive});
    | SelectObj(id, dragPos) =>
      ReasonReact.Update({
        ...state,
        selectedObj: Some({id, dragPos}),
        objs: ObjectList.move_to_frond(state.objs, id),
      })
    | UnselectObj () => ReasonReact.Update({...state, selectedObj: None})
    | AddObj(obj) =>
      ReasonReact.Update({
        ...state,
        objs: ObjectList.add_obj(state.objs, obj),
      })
    | DeleteSelectedObj () =>
      switch (state.selectedObj) {
      | None => ReasonReact.Update(state)
      | Some({id, _}) =>
        ReasonReact.Update({
          ...state,
          selectedObj: None,
          objs: ObjectList.rem_obj(state.objs, id),
          trashActive: false,
        })
      }
    | _ => ReasonReact.Update(state)
    },
  render: ({state, send, handle}) =>
    <div
      ref=(handle(setRef))
      className=Styles.app_grid
      onMouseMove=(
        e =>
          send(
            DragObj((ReactEvent.Mouse.pageX(e), ReactEvent.Mouse.pageY(e))),
          )
      )
      onMouseUp=(
        _ =>
          state.trashActive ? send(DeleteSelectedObj()) : send(UnselectObj())
      )>
      <HeaderView
        header=state.header
        selectedTile=state.selectedTile
        setActive=(t => send(SetActiveTile(t)))
        trashActive=state.trashActive
        addObj=(obj => send(AddObj(obj)))
      />
      <GridView grid=state.grid setTile=(pos => send(UpdateTile(pos)))>
        (
          ObjectList.get_obj_list(state.objs)
          |> List.rev
          |> List.map(((id', obj)) =>
               <ObjectView
                 id=id'
                 gameObj=obj
                 isBeingDragged=(
                   switch (state.selectedObj) {
                   | None => false
                   | Some({id}) => id == id'
                   }
                 )
                 updatePos=(pos => send(DragObj(pos)))
                 selectObj=(pos => send(SelectObj(id', pos)))
               />
             )
          |> Array.of_list
          |> ReasonReact.array
        )
      </GridView>
      {
        let helloQuery = GetHello.make();
        <GetHelloQuery variables=helloQuery##variables>
          ...(
               ({result}) =>
                 switch (result) {
                 | Loading => <div> (ReasonReact.string("loading")) </div>
                 | Error(error) =>
                   <div> (ReasonReact.string(error##message)) </div>
                 | Data(response) =>
                   <div>
                     (
                       ReasonReact.string(
                         switch (response##hello) {
                         | None => "no data"
                         | Some(data) => data
                         },
                       )
                     )
                   </div>
                 }
             )
        </GetHelloQuery>;
      }
    </div>,
};

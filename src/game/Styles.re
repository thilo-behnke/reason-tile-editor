include General;
module Styles = {
  open Css;
  let app_grid = style([display(grid), gridTemplateColumns([`fr(5.)])]);
  let header =
    style([
      gridRow(1, 1),
      gridColumn(1, 5),
      backgroundColor(`rgba((255, 255, 255, 1.0))),
      position(fixed),
      left(zero),
      top(zero),
      width(`percent(100.)),
      height(`px(150)),
      borderBottom(`px(1), `solid, `rgba((0, 0, 0, 1.))),
      display(grid),
      gridTemplateColumns([`fr(5.), `fr(1.)]),
      zIndex(11),
    ]);
};

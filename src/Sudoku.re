module State = {
  type t = {
    cells: Grid.t,
    validCount: int,
  };

  let init = (): t => {
    let cells = Array.range(0, 9 * 9 - 1)->Array.map(Cell.empty);
    let validCount = Grid.validCount(cells);
    {cells, validCount};
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state: State.t, msg) =>
        switch (msg) {
        | Msg.Change(index, value) =>
          let cells = Grid.fill(state.cells, value, index);
          let cells = Grid.validate(cells);
          let validCount = Grid.validCount(cells);
          {cells, validCount};
        | Msg.NewGame => state
        },
      State.init(),
    );

  <div className="grid">
    {state.cells
     ->Array.mapWithIndex((i, cell) =>
         <Cell
           cell
           key={i->string_of_int}
           change={value => dispatch(Msg.Change(i, value))}
         />
       )
     ->React.array}
  </div>;
};

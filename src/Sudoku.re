module State = {
  type t = {
    cells: Grid.t,
    validCount: int,
  };

  let init = (): t => {
    let cells =
      Array.range(0, 9 * 9 - 1)
      ->Array.map(Cell.empty)
      ->Grid.fillStatic(0, 2)
      ->Grid.fillStatic(1, 1)
      ->Grid.fillStatic(2, 5)
      ->Grid.fillStatic(3, 8)
      ->Grid.fillStatic(5, 3)
      ->Grid.fillStatic(8, 9)
      ->Grid.fillStatic(9, 6)
      ->Grid.fillStatic(11, 4)
      ->Grid.fillStatic(13, 5)
      ->Grid.fillStatic(15, 3)
      ->Grid.fillStatic(17, 1)
      ->Grid.fillStatic(20, 7)
      ->Grid.fillStatic(21, 1)
      ->Grid.fillStatic(22, 6)
      ->Grid.fillStatic(25, 2)
      ->Grid.fillStatic(28, 5)
      ->Grid.fillStatic(31, 1)
      ->Grid.fillStatic(33, 7)
      ->Grid.fillStatic(34, 9)
      ->Grid.fillStatic(38, 8)
      ->Grid.fillStatic(39, 3)
      ->Grid.fillStatic(40, 9)
      ->Grid.fillStatic(42, 2)
      ->Grid.fillStatic(45, 4)
      ->Grid.fillStatic(48, 5)
      ->Grid.fillStatic(50, 8)
      ->Grid.fillStatic(55, 9)
      ->Grid.fillStatic(57, 2)
      ->Grid.fillStatic(58, 8)
      ->Grid.fillStatic(59, 5)
      ->Grid.fillStatic(63, 8)
      ->Grid.fillStatic(65, 6)
      ->Grid.fillStatic(66, 7)
      ->Grid.fillStatic(67, 3)
      ->Grid.fillStatic(68, 9)
      ->Grid.fillStatic(69, 5)
      ->Grid.fillStatic(70, 1)
      ->Grid.fillStatic(71, 2)
      ->Grid.fillStatic(73, 2)
      ->Grid.fillStatic(76, 4)
      ->Grid.fillStatic(78, 9)
      ->Grid.validate;
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
          let cells = state.cells->Grid.fill(index, value)->Grid.validate;
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

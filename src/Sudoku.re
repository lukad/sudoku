[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state: State.t, msg) =>
        switch (msg) {
        | Msg.Change(index, value) =>
          let cells = state.cells->Grid.fill(index, value)->Grid.validate;
          let validCount = Grid.validCount(cells);
          let status = validCount == 81 ? State.Won : state.status;
          {...state, cells, validCount, status};
        | Msg.NewGame => State.init()
        | Tick when State.isTicking(state) => {
            ...state,
            ticks: state.ticks + 1,
          }
        | Tick => state
        },
      State.init(),
    );

  React.useEffect0(() => {
    let timerId = Js.Global.setInterval(() => dispatch(Msg.Tick), 1000);
    Some(() => Js.Global.clearInterval(timerId));
  });

  <>
    <Controls dispatch status={state.status} ticks={state.ticks} />
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
    </div>
  </>;
};

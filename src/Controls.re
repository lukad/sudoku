let (%%) = (a, b) => (a / b, a mod b);

[@react.component]
let make = (~dispatch: Msg.t => unit, ~status: State.status, ~ticks: int) => {
  let (hours, n) = ticks %% 3600;
  let (minutes, seconds) = n %% 60;

  <div className="controls">
    <button
      onClick={_ => dispatch(Msg.NewGame)}
      disabled={status == State.Generating}>
      "New Game"->React.string
    </button>
    <div className="time">
      {Printf.sprintf("%02d:%02d:%02d", hours, minutes, seconds)->React.string}
    </div>
  </div>;
};

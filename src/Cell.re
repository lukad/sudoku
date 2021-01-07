type t = {
  id: int,
  valid: bool,
  fill,
}

and fill =
  | Empty
  | Filled(int)
  | Static(int);

let empty = (id): t => {id, fill: Empty, valid: true};

let isStatic = cell =>
  switch (cell.fill) {
  | Static(_) => true
  | _ => false
  };

let getValue = cell =>
  switch (cell.fill) {
  | Static(v)
  | Filled(v) => Some(v)
  | Empty => None
  };

[@react.component]
let make = (~cell: t, ~change: option(int) => unit) => {
  let handleChange = e => {
    ReactEvent.Form.target(e)##value
    ->Option.flatMap(Js.String.match([%re "/[1-9]*([1-9])/"]))
    ->Option.flatMap(matches => matches[Array.length(matches) - 1])
    ->Option.map(int_of_string)
    ->change;
  };

  <div
    className=Cn.(
      "cell" + "static"->on(isStatic(cell)) + "invalid"->on(!cell.valid)
    )>
    <div className=Cn.("fill")>
      <div className="value">
        {switch (cell.fill) {
         | Static(value) => value->string_of_int->React.string
         | _ =>
           <input
             type_="text"
             value={cell->getValue->Option.mapWithDefault("", string_of_int)}
             onChange=handleChange
             pattern="\d*"
           />
         }}
      </div>
    </div>
  </div>;
};

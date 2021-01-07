type t = array(Cell.t);

let update = (f: Cell.t => Cell.t, index: int, tiles: t) =>
  Array.mapWithIndex(tiles, (i, cell) =>
    if (i == index) {
      f(cell);
    } else {
      cell;
    }
  );

let setValue = (value: option(int)) =>
  update(cell =>
    switch (value) {
    | Some(v) => {...cell, fill: Cell.Filled(v)}
    | None => {...cell, fill: Cell.Empty}
    }
  );

let validate = (grid: t) => {
  Array.map(
    grid,
    cell => {
      let invalid =
        grid
        ->Array.keep(other => other->Cell.getValue->Option.isSome)
        ->Array.keep(other => {Cell.getValue(cell) == Cell.getValue(other)})
        ->Array.length
        > 1;
      {...cell, valid: !invalid};
    },
  );
};

let validCount = (grid: t) =>
  grid
  ->Array.keep(cell => cell.valid && cell->Cell.getValue->Option.isSome)
  ->Array.length;

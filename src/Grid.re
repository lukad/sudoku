type t = array(Cell.t);
type pos = (int, int);

let indexToPos = index => (index / 9, index mod 9);
let posToIndex = ((x, y): pos) => y * 9 + x;

let cellAtPos = (grid: t, pos) => grid[posToIndex(pos)];

let update = (grid: t, f: Cell.t => Cell.t, index: int) =>
  Array.mapWithIndex(grid, (i, cell) =>
    if (i == index) {
      f(cell);
    } else {
      cell;
    }
  );

let fill = (grid: t, value: option(int)) =>
  grid->update(cell =>
    switch (value) {
    | Some(v) => {...cell, fill: Cell.Filled(v)}
    | None => {...cell, fill: Cell.Empty}
    }
  );

let fillStatic = (grid: t, value: int) =>
  grid->update(cell => {...cell, fill: Cell.Static(value)});

let region = (grid: t, (x, y)) => {
  let (x, y) = (x * 3, y * 3);
  [|
    (x, y),
    (x + 1, y),
    (x + 2, y),
    (x, y + 1),
    (x + 1, y + 1),
    (x + 2, y + 1),
    (x, y + 2),
    (x + 1, y + 2),
    (x + 2, y + 2),
  |]
  ->Array.map(cellAtPos(grid))
  ->Array.keep(Option.isSome)
  ->Array.map(Option.getUnsafe);
};

let row = (grid: t, y) => Array.slice(grid, ~offset=9 * y, ~len=9);

let column = (grid: t, x) => {
  Array.range(0, 8)
  ->Array.map(y => cellAtPos(grid, (x, y)))
  ->Array.keep(Option.isSome)
  ->Array.map(Option.getUnsafe);
};

let filled = (grid: t) =>
  Array.keep(grid, cell => cell->Cell.getValue->Option.isSome);

let duplicates = (grid: t) => {
  let grid = filled(grid);
  grid
  ->Array.keep(cell =>
      Array.getBy(grid, other =>
        Cell.getValue(cell) == Cell.getValue(other) && cell.id != other.id
      )
      ->Option.isSome
    )
  ->Array.map(cell => cell.id);
};

let invalidIds = (grid: t) =>
  [|
    Array.range(0, 8)->Array.map(y => y |> row(grid) |> duplicates),
    Array.range(0, 8)->Array.map(x => x |> column(grid) |> duplicates),
    Array.range(0, 2)
    ->Array.map(x =>
        Array.range(0, 2)
        ->Array.map(y => region(grid, (x, y))->duplicates)
        ->Array.concatMany
      ),
  |]
  ->Array.concatMany
  ->Array.concatMany;

let validate = (grid: t) => {
  let invalids = invalidIds(grid);
  Array.map(grid, cell =>
    switch (Array.getBy(invalids, id => id == cell.id)) {
    | Some(_) => {...cell, valid: false}
    | None => {...cell, valid: true}
    }
  );
};

let validCount = (grid: t) =>
  grid
  ->Array.keep(cell => cell.valid && cell->Cell.getValue->Option.isSome)
  ->Array.length;

ReactDOMRe.renderToElementWithId(<Sudoku />, "app");

type parcelModule;
type hot;
[@bs.val] external parcelModule: parcelModule = "module";
[@bs.get] external hot: parcelModule => Js.nullable(hot) = "hot";
[@bs.send.pipe: hot] external accept: unit => unit = "accept";

switch (parcelModule |> hot |> Js.Nullable.toOption) {
| Some(h) => h |> accept()
| _ => ()
};

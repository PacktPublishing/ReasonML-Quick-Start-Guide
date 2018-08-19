let component = ReasonReact.statelessComponent("Page2");

let make = _children => {
  ...component,
  render: _self => <h1> (ReasonReact.string("Page2")) </h1>,
};

let component = ReasonReact.statelessComponent("Page3");

let make = _children => {
  ...component,
  render: _self => <h1> (ReasonReact.string("Page3")) </h1>,
};

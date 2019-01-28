let component = ReasonReact.statelessComponent("Page1");

let make = _children => {
  ...component,
  render: _self => <h1> {ReasonReact.string("Page1")} </h1>,
};

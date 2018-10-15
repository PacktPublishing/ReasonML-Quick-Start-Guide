let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self => <div> (ReasonReact.string("hello world")) </div>,
};

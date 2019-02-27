let component = ReasonReact.statelessComponent("Home");

let make = _children => {
  ...component,
  render: _self =>
    <Title center=true underline=true> {ReasonReact.string("Page1")} </Title>,
};

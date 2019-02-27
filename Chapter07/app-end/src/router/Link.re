let component = ReasonReact.statelessComponent("Link");
let make = (~href, ~className="", children) => {
  ...component,
  render: self =>
    <a
      href
      className
      onClick={
        self.handle((event, _self) => {
          ReactEvent.Mouse.preventDefault(event);
          ReasonReact.Router.push(href);
        })
      }>
      ...children
    </a>,
};

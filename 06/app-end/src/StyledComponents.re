[@bs.module "styled-components"] [@bs.scope "default"]
external h1: (array(string), array('a)) => ReasonReact.reactClass = "h1";

module Title = {
  let title =
    h1(
      [|
        "text-align: ",
        "; text-decoration: ",
        "; color: white; background-color: coral;",
      |],
      [|
        props => props##center ? "center" : "left",
        props => props##underline ? "underline" : "none",
      |],
    );

  let title = [%bs.raw
    {|
     require("styled-components").default.h1`
       text-align: ${props => props.center ? "center" : "left"};
       text-decoration: ${props => props.underline ? "underline" : "none"};
       color: white;
       background-color: coral;
     `
   |}
  ];

  [@bs.deriving abstract]
  type jsProps = {
    center: bool,
    underline: bool,
  };
  let make = (~center=false, ~underline=false, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=title,
      ~props=jsProps(~center, ~underline),
      children,
    );
};

%bs.raw
{|const styled = require("styled-components").default|};

let title = [%bs.raw
  {|
     styled.h1`
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

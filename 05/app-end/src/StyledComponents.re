[@bs.module "styled-components"] external styled: Js.t('a) = "default";

module H1 = {
  let h1: array(string) => ReasonReact.reactClass = styled##h1;
  let make = (~css, ~props, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=h1([|css|]),
      ~props=Js.Dict.fromList(Belt.List.map(props, a => (a, ""))),
      children,
    );
};

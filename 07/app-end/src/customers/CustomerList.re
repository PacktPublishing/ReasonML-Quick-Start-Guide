let component = ReasonReact.statelessComponent("CustomerList");

let customers =
  DataPureReason.(parse(getItem("customers")))->Belt.List.fromArray;

module Styles = {
  open Css;

  let list =
    style([
      listStyleType(none),
      padding(zero),
      margin2(~v=px(50), ~h=auto),
      width(px(700)),
      selector(
        "li",
        [
          backgroundColor(rgba(150, 123, 182, 0.1)),
          margin2(~v=px(15), ~h=zero),
          selector(
            "a",
            [
              display(flexBox),
              flexWrap(wrap),
              textDecoration(none),
              padding(px(20)),
              selector(
                "p",
                [
                  flex(1),
                  flexBasis(pct(50.)),
                  margin(zero),
                  color(black),
                ],
              ),
            ],
          ),
        ],
      ),
    ]);
};

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <ul className=Styles.list>
        {
          ReasonReact.array(
            Belt.List.map(customers, customer =>
              <li key={string_of_int(customer.id)}>
                <Link href={"/customers/" ++ string_of_int(customer.id)}>
                  <p> {ReasonReact.string(customer.name)} </p>
                  <p> {ReasonReact.string(customer.address.street)} </p>
                  <p> {ReasonReact.string(customer.phone)} </p>
                  <p> {ReasonReact.string(customer.email)} </p>
                </Link>
              </li>
            )
            ->Belt.List.toArray,
          )
        }
      </ul>
    </div>,
};

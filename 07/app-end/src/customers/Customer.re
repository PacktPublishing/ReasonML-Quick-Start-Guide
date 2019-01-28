[@bs.val] external pathname: string = "window.location.pathname";

type mode =
  | Create
  | Update;

type state = {
  mode,
  customer: CustomerType.t,
};

type action =
  | Save(ReactEvent.Form.t);

let component = ReasonReact.reducerComponent("Customer");

module Styles = {
  open Css;

  let form =
    style([
      width(pct(100.)),
      maxWidth(px(800)),
      margin2(~v=px(10), ~h=auto),
      selector(
        "label",
        [
          display(block),
          margin2(~v=px(20), ~h=zero),
          selector(
            "input",
            [
              fontSize(px(14)),
              lineHeight(px(40)),
              display(block),
              width(pct(100.)),
              height(px(40)),
              padding(px(10)),
              boxSizing(borderBox),
            ],
          ),
        ],
      ),
      selector(
        "input[type=submit]",
        [
          display(block),
          width(px(200)),
          height(px(40)),
          backgroundColor(firebrick),
          borderStyle(none),
          cursor(`pointer),
          color(white),
        ],
      ),
    ]);
};

let customers = DataPureReason.(parse(getItem("customers")));

let getId = pathname =>
  try (Js.String.replaceByRe([%bs.re "/\\D/g"], "", pathname)->int_of_string) {
  | _ => (-1)
  };

let getCustomer = customers => {
  let id = getId(pathname);
  customers |> Js.Array.find(customer => customer.CustomerType.id == id);
};

let getDefault = customers: CustomerType.t => {
  id: Belt.Array.length(customers) + 1,
  name: "",
  address: {
    street: "",
    city: "",
    state: "",
    zip: "",
  },
  phone: "",
  email: "",
};

let make = _children => {
  ...component,
  initialState: () => {
    let mode = Js.String.includes("create", pathname) ? Create : Update;
    {
      mode,
      customer:
        switch (mode) {
        | Create => getDefault(customers)
        | Update =>
          Belt.Option.getWithDefault(
            getCustomer(customers),
            getDefault(customers),
          )
        },
    };
  },
  reducer: (action, state) =>
    switch (action) {
    | Save(event) =>
      let getInputValue: string => string = [%raw
        (selector => "return document.querySelector(selector).value")
      ];
      ReactEvent.Form.preventDefault(event);
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          customer: {
            id: state.customer.id,
            name: getInputValue("input[name=name]"),
            address: {
              street: getInputValue("input[name=street]"),
              city: getInputValue("input[name=city]"),
              state: getInputValue("input[name=state]"),
              zip: getInputValue("input[name=zip]"),
            },
            phone: getInputValue("input[name=phone]"),
            email: getInputValue("input[name=email]"),
          },
        },
        (
          self => {
            let customers =
              switch (self.state.mode) {
              | Create =>
                Belt.Array.concat(customers, [|self.state.customer|])
              | Update =>
                Belt.Array.setExn(
                  customers,
                  Js.Array.findIndex(
                    customer =>
                      customer.CustomerType.id == self.state.customer.id,
                    customers,
                  ),
                  self.state.customer,
                );
                customers;
              };

            let json = customers->Belt.List.fromArray->DataPureReason.toJson;
            DataPureReason.setItem("customers", json);
          }
        ),
      );
    },
  render: self =>
    <form
      className=Styles.form
      onSubmit={
        event => {
          ReactEvent.Form.persist(event);
          self.send(Save(event));
        }
      }>
      <label>
        {ReasonReact.string("Name")}
        <input
          type_="text"
          defaultValue={self.state.customer.name}
          name="name"
        />
      </label>
      <label>
        {ReasonReact.string("Street Address")}
        <input
          type_="text"
          defaultValue={self.state.customer.address.street}
          name="street"
        />
      </label>
      <label>
        {ReasonReact.string("City")}
        <input
          type_="text"
          defaultValue={self.state.customer.address.city}
          name="city"
        />
      </label>
      <label>
        {ReasonReact.string("State")}
        <input
          type_="text"
          defaultValue={self.state.customer.address.state}
          name="state"
        />
      </label>
      <label>
        {ReasonReact.string("Zip")}
        <input
          type_="text"
          defaultValue={self.state.customer.address.zip}
          name="zip"
        />
      </label>
      <label>
        {ReasonReact.string("Phone")}
        <input
          type_="text"
          defaultValue={self.state.customer.phone}
          name="phone"
        />
      </label>
      <label>
        {ReasonReact.string("Email")}
        <input
          type_="text"
          defaultValue={self.state.customer.email}
          name="email"
        />
      </label>
      <input
        type_="submit"
        value={
          switch (self.state.mode) {
          | Create => "Create"
          | Update => "Update"
          }
        }
      />
    </form>,
};

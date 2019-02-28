[@bs.val] [@bs.scope "localStorage"] external getItem: string => string = "";
[@bs.val] [@bs.scope "localStorage"]
external setItem: (string, string) => unit = "";

let addressDecoder = json =>
  Json.Decode.(
    (
      {
        street: json |> field("street", string),
        city: json |> field("city", string),
        state: json |> field("state", string),
        zip: json |> field("zip", string),
      }: CustomerType.address
    )
  );

let customerDecoder = json =>
  Json.Decode.(
    (
      {
        id: json |> field("id", int),
        name: json |> field("name", string),
        address: json |> field("address", addressDecoder),
        phone: json |> field("phone", string),
        email: json |> field("email", string),
      }: CustomerType.t
    )
  );

let parse = json =>
  json |> Json.parseOrRaise |> Json.Decode.array(customerDecoder);

let toJson = (customers: array(CustomerType.t)) =>
  customers->Belt.Array.map(customer =>
    Json.Encode.(
      object_([
        ("id", int(customer.id)),
        ("name", string(customer.name)),
        (
          "address",
          object_([
            ("street", string(customer.address.street)),
            ("city", string(customer.address.city)),
            ("state", string(customer.address.state)),
            ("zip", string(customer.address.zip)),
          ]),
        ),
        ("phone", string(customer.phone)),
        ("email", string(customer.email)),
      ])
    )
  )
  |> Json.Encode.jsonArray
  |> Json.stringify;

[@bs.val] [@bs.scope "localStorage"] external getItem: string => string = "";
[@bs.val] [@bs.scope "localStorage"]
external setItem: (string, string) => unit = "";

let parseCustomer = json =>
  switch (Js.Json.classify(json)) {
  | Js.Json.JSONObject(json) => (
      {
        id:
          switch (Js.Dict.get(json, "id")) {
          | Some(id) =>
            switch (Js.Json.classify(id)) {
            | Js.Json.JSONNumber(id) => int_of_float(id)
            | _ => failwith("Field 'id' should be a number")
            }
          | None => failwith("Missing field: id")
          },
        name:
          switch (Js.Dict.get(json, "name")) {
          | Some(name) =>
            switch (Js.Json.classify(name)) {
            | Js.Json.JSONString(name) => name
            | _ => failwith("Field 'name' should be a string")
            }
          | None => failwith("Missing field: name")
          },
        address:
          switch (Js.Dict.get(json, "address")) {
          | Some(address) =>
            switch (Js.Json.classify(address)) {
            | Js.Json.JSONObject(address) => {
                street:
                  switch (Js.Dict.get(address, "street")) {
                  | Some(street) =>
                    switch (Js.Json.classify(street)) {
                    | Js.Json.JSONString(street) => street
                    | _ => failwith("Field 'street' should be a string")
                    }
                  | None => failwith("Missing field: street")
                  },
                city:
                  switch (Js.Dict.get(address, "city")) {
                  | Some(city) =>
                    switch (Js.Json.classify(city)) {
                    | Js.Json.JSONString(city) => city
                    | _ => failwith("Field 'city' should be a string")
                    }
                  | None => failwith("Missing field: city")
                  },
                state:
                  switch (Js.Dict.get(address, "state")) {
                  | Some(state) =>
                    switch (Js.Json.classify(state)) {
                    | Js.Json.JSONString(state) => state
                    | _ => failwith("Field 'state' should be a string")
                    }
                  | None => failwith("Missing field: state")
                  },
                zip:
                  switch (Js.Dict.get(address, "zip")) {
                  | Some(zip) =>
                    switch (Js.Json.classify(zip)) {
                    | Js.Json.JSONString(zip) => zip
                    | _ => failwith("Field 'zip' should be a string")
                    }
                  | None => failwith("Missing field: zip")
                  },
              }
            | _ => failwith("Field 'address' should be a object")
            }
          | None => failwith("Missing field: address")
          },
        phone:
          switch (Js.Dict.get(json, "phone")) {
          | Some(phone) =>
            switch (Js.Json.classify(phone)) {
            | Js.Json.JSONString(phone) => phone
            | _ => failwith("Field 'phone' should be a string")
            }
          | None => failwith("Missing field: phone")
          },
        email:
          switch (Js.Dict.get(json, "email")) {
          | Some(email) =>
            switch (Js.Json.classify(email)) {
            | Js.Json.JSONString(email) => email
            | _ => failwith("Field 'email' should be a string")
            }
          | None => failwith("Missing field: email")
          },
      }: CustomerType.t
    )
  | _ => failwith("Expected an object")
  };

let parseCustomers = json =>
  switch (Js.Json.classify(json)) {
  | Js.Json.JSONArray(array) =>
    Belt.Array.map(array, customer => parseCustomer(customer))
  | _ => failwith("Expected an array")
  };

let parse = string => {
  let json =
    try (Js.Json.parseExn(string)) {
    | _ => failwith("Error parsing JSON string")
    };
  Js.log(json);
  parseCustomers(json);
};

let customerToJson = (customer: CustomerType.t) => {
  let id = customer.id;
  let name = customer.name;
  let street = customer.address.street;
  let city = customer.address.city;
  let state = customer.address.state;
  let zip = customer.address.zip;
  let phone = customer.phone;
  let email = customer.email;

  {j|
    {
      "id": $id,
      "name": "$name",
      "address": {
        "street": "$street",
        "city": "$city",
        "state": "$state",
        "zip": "$zip"
      },
      "phone": "$phone",
      "email": "$email"
    }
  |j};
};

let toJson = (customers: array(CustomerType.t)) =>
  Belt.Array.map(customers, customer => customerToJson(customer))
  ->Belt.Array.reduce("[", (acc, customer) => acc ++ customer ++ ",")
  ->Js.String.replaceByRe([%bs.re "/,$/"], "", _)
  ++ "]"
     ->Js.String.split("/n", _)
     ->Js.Array.map(line => Js.String.trim(line), _)
     ->Js.Array.joinWith("", _);

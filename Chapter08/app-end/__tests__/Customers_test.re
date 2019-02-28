open Jest;

describe("Customer", () =>
  Expect.(
    test("can create a customer", () => {
      let customers: array(CustomerType.t) = [|
        {
          id: 1,
          name: "Irita Camsey",
          address: {
            street: "69 Ryan Parkway",
            city: "Kansas City",
            state: "MO",
            zip: "00494",
          },
          phone: "8169271752",
          email: "icamsey0@over-blog.com",
        },
        {
          id: 2,
          name: "Luise Grayson",
          address: {
            street: "2756 Gale Trail",
            city: "Jacksonville",
            state: "FL",
            zip: "23566",
          },
          phone: "9044985243",
          email: "lgrayson1@netlog.com",
        },
        {
          id: 3,
          name: "Derick Whitelaw",
          address: {
            street: "45 Southridge Par",
            city: "Lexington",
            state: "KY",
            zip: "08037",
          },
          phone: "4079634850",
          email: "dwhitelaw2@fema.gov",
        },
      |];
      let customer: CustomerType.t =
        Customer.getCustomerById(customers, 2) |> Belt.Option.getExn;
      expect((customer.id, customer.name)) |> toEqual((2, "Luise Grayson"));
    })
  )
);

type t('a) = {
  name: string,
  email: string,
  date: Js.Date.t,
  total: float,
};

type discounted;
type undiscounted;

type discount =
  | Ten
  | Fifteen
  | Twenty;

let make = (~name, ~email, ~date, ~total) => {name, email, date, total};

let discount = (~invoice, ~discount) => {
  ...invoice,
  total:
    invoice.total
    *. (
      switch (discount) {
      | Ten => 0.9
      | Fifteen => 0.85
      | Twenty => 0.8
      }
    ),
};

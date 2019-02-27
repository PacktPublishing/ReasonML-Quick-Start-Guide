type t('a);

type discounted;
type undiscounted;

type discount =
  | Ten
  | Fifteen
  | Twenty;

let make:
  (~name: string, ~email: string, ~date: Js.Date.t, ~total: float) =>
  t(undiscounted);

let discount:
  (~invoice: t(undiscounted), ~discount: discount) => t(discounted);

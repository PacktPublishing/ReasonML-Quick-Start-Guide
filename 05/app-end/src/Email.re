let invoice =
  Invoice.make(
    ~name="Raphael",
    ~email="persianturtle@gmail.com",
    ~date=Js.Date.make(),
    ~total=15.0,
  );
let invoice = Invoice.(discount(~invoice, ~discount=Ten));

let send: Invoice.t('a) => unit =
  invoice =>
    /* send invoice email */
    Js.log(invoice);

send(invoice);

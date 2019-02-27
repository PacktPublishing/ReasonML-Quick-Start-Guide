type address = {
  street: string,
  city: string,
  state: string,
  zip: string,
};

type t = {
  id: int,
  name: string,
  address,
  phone: string,
  email: string,
};

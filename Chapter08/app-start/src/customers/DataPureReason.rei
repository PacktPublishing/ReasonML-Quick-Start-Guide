[@bs.val] [@bs.scope "localStorage"] external getItem: string => string = "";
[@bs.val] [@bs.scope "localStorage"]
external setItem: (string, string) => unit = "";

let parse: string => array(CustomerType.t);
let toJson: array(CustomerType.t) => string;

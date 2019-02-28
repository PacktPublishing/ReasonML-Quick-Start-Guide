let component = ReasonReact.statelessComponent("NavLink");
let make = (~href, children) => {
  ...component,
  render: _self =>
    <Router.WithRouter>
      ...{
           (~currentRoute) =>
             <Link href className={currentRoute.href == href ? "active" : ""}>
               ...children
             </Link>
         }
    </Router.WithRouter>,
};

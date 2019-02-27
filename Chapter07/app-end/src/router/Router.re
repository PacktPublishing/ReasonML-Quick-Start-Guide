type route = {
  href: string,
  title: string,
  component: ReasonReact.reactElement,
};

let routes = [
  {href: "/", title: "Home", component: <Home />},
  {href: "/customers", title: "Customer List", component: <CustomerList />},
  {
    href: "/customers/create",
    title: "Create Customer",
    component: <Customer />,
  },
  {href: "/customers/:id", title: "Update Customer", component: <Customer />},
  {href: "/page2", title: "Page2", component: <Page2 />},
  {href: "/page3", title: "Page3", component: <Page3 />},
];

let hrefToPath = href => href |> Js.String.split("/") |> Belt.List.fromArray;

let pathToHref = path =>
  Belt.List.reduce(path, "", (acc, p) => acc ++ "/" ++ p);

let urlToRoute = (url: ReasonReact.Router.url) =>
  switch (
    Belt.List.getBy(
      routes,
      route => {
        let regex =
          Js.String.replaceByRe([%bs.re "/[:*]\w+/g"], "[^\/]+", route.href)
          ++ "$";
        switch (
          Js.String.match(Js.Re.fromString(regex), pathToHref(url.path))
        ) {
        | None => false
        | Some(_match) => true
        };
      },
    )
  ) {
  | None => Belt.List.headExn(routes)
  | Some(route) => route
  };

module WithRouter = {
  type state = route;
  type action =
    | ChangeRoute(route);
  let component = ReasonReact.reducerComponent("WithRouter");
  let make = children => {
    ...component,
    didMount: self => {
      let watcherID =
        ReasonReact.Router.watchUrl(url =>
          self.send(ChangeRoute(urlToRoute(url)))
        );
      ();
      self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
    },
    initialState: () =>
      urlToRoute(ReasonReact.Router.dangerouslyGetInitialUrl()),
    reducer: (action, _state) =>
      switch (action) {
      | ChangeRoute(route) => ReasonReact.Update(route)
      },
    render: self => children(~currentRoute=self.state),
  };
};

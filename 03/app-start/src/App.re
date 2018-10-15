[@bs.val] external require: string => string = "";

require("../../../src/App.scss");

type state = {isOpen: bool};

type action =
  | ToggleMenu(bool);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {isOpen: false},
  reducer: (action, _state) =>
    switch (action) {
    | ToggleMenu(isOpen) => ReasonReact.Update({isOpen: isOpen})
    },
  render: self =>
    <div
      className={"App" ++ (self.state.isOpen ? " overlay" : "")}
      onClick={
        _event =>
          if (self.state.isOpen) {
            self.send(ToggleMenu(false));
          }
      }>
      <header>
        <a
          onClick={
            event => {
              ReactEvent.Mouse.stopPropagation(event);
              self.send(ToggleMenu(true));
            }
          }>
          <img src={require("../../../src/img/icon/hamburger.svg")} />
        </a>
        <h1> {ReasonReact.string("Home")} </h1>
      </header>
      <nav
        className={self.state.isOpen ? "active" : ""}
        onClick={event => ReactEvent.Mouse.stopPropagation(event)}>
        <header>
          <a onClick={_event => self.send(ToggleMenu(false))}>
            <img src={require("../../../src/img/icon/arrow.svg")} />
            {ReasonReact.string("Home")}
          </a>
        </header>
        <label> {ReasonReact.string("home")} </label>
        <ul> <li> <a> {ReasonReact.string("Home")} </a> </li> </ul>
        <label> {ReasonReact.string("pages")} </label>
        <ul>
          <li> <a> {ReasonReact.string("Page1")} </a> </li>
          <li> <a> {ReasonReact.string("Page2")} </a> </li>
          <li> <a> {ReasonReact.string("Page3")} </a> </li>
        </ul>
      </nav>
      <main> ReasonReact.null </main>
    </div>,
};

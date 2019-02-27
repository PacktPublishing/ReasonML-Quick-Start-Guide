[@bs.val] external require: string => string = "";
[@bs.val] [@bs.scope "performance"] external now: unit => float = "";

type touches = {
  first: option((float, float)),
  last: option((float, float)),
};

type state = {
  isOpen: bool,
  touches,
  width: ref(float),
};

type action =
  | ToggleMenu(bool)
  | TouchStart(float)
  | TouchMove(float)
  | TouchEnd;

let component = ReasonReact.reducerComponent("App");

module Styles = {
  open Css;

  let app =
    style([
      minHeight(vh(100.)),
      after([
        contentRule(""),
        transitions([
          `transition("opacity 450ms cubic-bezier(0.23, 1, 0.32, 1)"),
          `transition("transform 0ms cubic-bezier(0.23, 1, 0.32, 1) 450ms"),
        ]),
        position(fixed),
        top(zero),
        right(zero),
        bottom(zero),
        left(zero),
        backgroundColor(rgba(0, 0, 0, 0.33)),
        transform(translateX(pct(-100.))),
        opacity(0.),
        zIndex(1),
      ]),
      selector(
        "&.overlay",
        [
          after([
            `transition("opacity 450ms cubic-bezier(0.23, 1, 0.32, 1)"),
            transform(translateX(zero)),
            opacity(1.),
          ]),
        ],
      ),
      selector(
        "> header",
        [
          display(flexBox),
          alignItems(center),
          height(px(60)),
          backgroundColor(dodgerblue),
          color(white),
          boxShadows([
            `shadow("0 4px 5px 0 rgba(15, 74, 133, 0.14)"),
            `shadow("0 2px 9px 1px rgba(15, 74, 133, 0.12)"),
            `shadow("0 4px 2px -2px rgba(15, 74, 133, 0.2)"),
          ]),
          selector(
            "> a",
            [
              display(flexBox),
              alignItems(center),
              width(px(32)),
              height(pct(100.)),
              padding2(~v=zero, ~h=px(10)),
              cursor(`pointer),
              selector("> img", [width(pct(100.)), height(pct(100.))]),
            ],
          ),
          selector(
            "> h1",
            [fontSize(px(26)), lineHeight(px(26)), marginLeft(px(10))],
          ),
        ],
      ),
      selector(
        "> nav",
        [
          `transition("transform 450ms cubic-bezier(0.23, 1, 0.32, 1)"),
          position(absolute),
          top(zero),
          left(zero),
          transform(translateX(`calc((`sub, pct(-100.), px(10))))),
          height(vh(100.)),
          backgroundColor(white),
          boxShadows([
            `shadow("rgba(0, 0, 0, 0.16) 0px 3px 10px"),
            `shadow("rgba(0, 0, 0, 0.23) 0px 3px 10px"),
          ]),
          overflow(auto),
          zIndex(2),
          selector("&.active", [transform(translateX(zero))]),
          selector(
            "> label",
            [
              fontWeight(normal),
              fontSize(px(12)),
              lineHeight(px(24)),
              textTransform(uppercase),
              display(block),
              backgroundColor(rgba(0, 0, 0, 0.32)),
              color(white),
              padding2(~v=zero, ~h=px(15)),
            ],
          ),
          selector(
            "> header",
            [
              position(relative),
              backgroundColor(lavender),
              height(px(150)),
              margin(zero),
              selector(
                "> a",
                [
                  fontSize(px(24)),
                  lineHeight(px(24)),
                  position(absolute),
                  top(zero),
                  left(zero),
                  display(flexBox),
                  alignItems(center),
                  height(px(40)),
                  padding2(~v=px(10), ~h=px(20)),
                  selector(
                    "> img",
                    [
                      width(px(20)),
                      height(px(20)),
                      marginRight(px(20)),
                    ],
                  ),
                ],
              ),
            ],
          ),
          selector(
            "> ul",
            [
              margin(zero),
              padding(zero),
              listStyleType(none),
              selector(
                "> li",
                [
                  position(relative),
                  borderBottom(px(1), solid, rgba(0, 0, 0, 0.06)),
                  after([
                    unsafe("content", "url('./img/icon/chevron.svg')"),
                    position(absolute),
                    top(zero),
                    right(px(15)),
                    bottom(zero),
                    margin(auto),
                    width(px(15)),
                    height(px(15)),
                  ]),
                  selector(
                    "> a",
                    [
                      `transition(
                        "background-color 450ms cubic-bezier(0.23, 1, 0.32, 1)",
                      ),
                      fontSize(px(18)),
                      lineHeight(px(54)),
                      textDecoration(none),
                      display(block),
                      padding2(~v=zero, ~h=px(15)),
                      color(black),
                      selector(
                        "&.active",
                        [backgroundColor(hex("e9e9e9"))],
                      ),
                    ],
                  ),
                  selector("> img", [width(px(15)), height(px(15))]),
                ],
              ),
            ],
          ),
          media("(max-width: 767px)", [width(vw(85.))]),
          media("(min-width: 768px)", [width(px(300))]),
        ],
      ),
    ]);
};

let make = (~currentRoute: Router.route, _children) => {
  ...component,
  initialState: () => {
    isOpen: false,
    touches: {
      first: None,
      last: None,
    },
    width: ref(0.0),
  },
  willReceiveProps: self => {...self.state, isOpen: false},
  reducer: (action, state) =>
    switch (action) {
    | ToggleMenu(isOpen) => ReasonReact.Update({...state, isOpen})
    | TouchStart(clientX) =>
      if (state.isOpen) {
        ReasonReact.Update({
          ...state,
          touches: {
            first: Some((clientX, now())),
            last: None,
          },
        });
      } else {
        ReasonReact.NoUpdate;
      }
    | TouchMove(clientX) =>
      if (state.isOpen) {
        ReasonReact.Update({
          ...state,
          touches: {
            ...state.touches,
            last: Some((clientX, now())),
          },
        });
      } else {
        ReasonReact.NoUpdate;
      }
    | TouchEnd =>
      if (state.isOpen) {
        let (x, t) =
          Belt.Option.getWithDefault(state.touches.first, (0.0, 0.0));
        let (x', t') =
          Belt.Option.getWithDefault(state.touches.last, (0.0, 0.0));
        let velocity = (x' -. x) /. (t' -. t);
        let state = {
          ...state,
          touches: {
            first: None,
            last: None,
          },
        };
        if (velocity < (-0.3) || x' < state.width^ /. 2.0) {
          ReasonReact.UpdateWithSideEffects(
            state,
            (self => self.send(ToggleMenu(false))),
          );
        } else {
          ReasonReact.Update(state);
        };
      } else {
        ReasonReact.NoUpdate;
      }
    },
  render: self =>
    <div
      className={"App " ++ Styles.app ++ (self.state.isOpen ? " overlay" : "")}
      onClick={
        _event =>
          if (self.state.isOpen) {
            self.send(ToggleMenu(false));
          }
      }
      onTouchStart={
        event =>
          self.send(
            TouchStart(
              ReactEvent.Touch.changedTouches(event)##item(0)##clientX,
            ),
          )
      }
      onTouchMove={
        event =>
          self.send(
            TouchMove(
              ReactEvent.Touch.changedTouches(event)##item(0)##clientX,
            ),
          )
      }
      onTouchEnd={_event => self.send(TouchEnd)}>
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
        <h1> {ReasonReact.string(currentRoute.title)} </h1>
      </header>
      <nav
        className={self.state.isOpen ? "active" : ""}
        onClick={event => ReactEvent.Mouse.stopPropagation(event)}
        style={
          switch (self.state.touches) {
          | {first: Some((x, _)), last: Some((x', _))} =>
            ReactDOMRe.Style.make(
              ~transform=
                "translateX("
                ++ string_of_float(x' -. x > 0.0 ? 0.0 : x' -. x)
                ++ "0px)",
              ~transition="none",
              (),
            )
          | _ => ReactDOMRe.Style.make()
          }
        }
        ref={
          self.handle((ref, self) =>
            self.state.width :=
              (
                switch (Js.Nullable.toOption(ref)) {
                | None => 0.0
                | Some(r) => ReactDOMRe.domElementToObj(r)##clientWidth
                }
              )
          )
        }>
        <header>
          <a onClick={_event => self.send(ToggleMenu(false))}>
            <img src={require("../../../src/img/icon/arrow.svg")} />
            {ReasonReact.string(currentRoute.title)}
          </a>
        </header>
        <label> {ReasonReact.string("home")} </label>
        <ul>
          <li>
            <NavLink href="/"> {ReasonReact.string("Home")} </NavLink>
          </li>
        </ul>
        <label> {ReasonReact.string("pages")} </label>
        <ul>
          <li>
            <NavLink href="/customers">
              {ReasonReact.string("Customers")}
            </NavLink>
          </li>
          <li>
            <NavLink href="/page2"> {ReasonReact.string("Page2")} </NavLink>
          </li>
          <li>
            <NavLink href="/page3"> {ReasonReact.string("Page3")} </NavLink>
          </li>
        </ul>
      </nav>
      <main>
        ReactTransitionGroup.(
          <TransitionGroup>
            <CSSTransition
              key={currentRoute.title}
              _in=true
              timeout=900
              classNames="routeTransition">
              {currentRoute.component}
            </CSSTransition>
          </TransitionGroup>
        )
      </main>
    </div>,
};

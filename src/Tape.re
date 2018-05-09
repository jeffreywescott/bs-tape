type error = Js.Nullable.t({. "message": string});

type assertInterface = {
  plan: int => unit,
  endTest: unit => unit,
  endTestIfNoErr: bool => unit,
  fail: string => unit,
  pass: string => unit,
  timeoutAfter: int => unit,
  skip: string => unit,
  ok: (~message: string=?, bool) => unit,
  notOk: (~message: string=?, bool) => unit,
  error: (~message: string=?, error) => unit,
  equalStr: (~message: string=?, string, string) => unit,
  equalInt: (~message: string=?, int, int) => unit,
  equalFloat: (~message: string=?, float, float) => unit,
  comment: string => unit,
  test: (string, assertInterface => unit) => unit,
};

[@bs.module "tape"]
external _test : (string, assertInterface => unit) => unit = "test";

[@bs.send] external _plan : (assertInterface, int) => unit = "plan";

[@bs.send] external _end : (assertInterface, bool) => unit = "end";

[@bs.send] external _fail : (assertInterface, string) => unit = "fail";

[@bs.send] external _pass : (assertInterface, string) => unit = "pass";

[@bs.send]
external _timeoutAfter : (assertInterface, int) => unit = "timeoutAfter";

[@bs.send] external _skip : (assertInterface, string) => unit = "skip";

[@bs.send]
external _ok : (assertInterface, bool, Js.Nullable.t(string)) => unit = "ok";

[@bs.send]
external _notOk : (assertInterface, bool, Js.Nullable.t(string)) => unit =
  "notOk";

[@bs.send]
external _error : (assertInterface, error, Js.Nullable.t(string)) => unit =
  "error";

[@bs.send]
external _equalStr :
  (assertInterface, string, string, Js.Nullable.t(string)) => unit =
  "equal";

[@bs.send]
external _equalInt :
  (assertInterface, int, int, Js.Nullable.t(string)) => unit =
  "equal";

[@bs.send]
external _equalFloat :
  (assertInterface, float, float, Js.Nullable.t(string)) => unit =
  "equal";

[@bs.send] external _comment : (assertInterface, string) => unit = "comment";

[@bs.send]
external _subtest : (assertInterface, string, assertInterface => unit) => unit =
  "test";

[@bs.module "tape"] [@bs.scope "test"]
external _testOnly : (string, assertInterface => unit) => unit = "only";

[@bs.module "tape"] [@bs.scope "test"]
external _testSkip : (string, assertInterface => unit) => unit = "skip";

let rec _assertFactory = t => {
  plan: n => _plan(t, n),
  endTest: () => _end(t, false),
  endTestIfNoErr: b => _end(t, b),
  fail: s => _fail(t, s),
  pass: s => _pass(t, s),
  timeoutAfter: n => _timeoutAfter(t, n),
  skip: s => _skip(t, s),
  ok: (~message=?, b) => _ok(t, b, Js.Nullable.fromOption(message)),
  notOk: (~message=?, b) => _notOk(t, b, Js.Nullable.fromOption(message)),
  error: (~message=?, o) => _error(t, o, Js.Nullable.fromOption(message)),
  equalStr: (~message=?, actual, expected) =>
    _equalStr(t, actual, expected, Js.Nullable.fromOption(message)),
  equalInt: (~message=?, actual, expected) =>
    _equalInt(t, actual, expected, Js.Nullable.fromOption(message)),
  equalFloat: (~message=?, actual, expected) =>
    _equalFloat(t, actual, expected, Js.Nullable.fromOption(message)),
  comment: s => _comment(t, s),
  test: (name, f) => _subtest(t, name, t => f(_assertFactory(t))),
};

let test = (name, f) => _test(name, t => f(_assertFactory(t)));

let testOnly = (name, f) => _testOnly(name, t => f(_assertFactory(t)));

let testSkip = (name, f) => _testSkip(name, t => f(_assertFactory(t)));
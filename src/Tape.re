type error = Js.Nullable.t({. "message": string});

type testFuncs = {
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
  test: (string, testFuncs => unit) => unit,
};

[@bs.module "tape"]
external _test : (string, testFuncs => unit) => unit = "test";

[@bs.send] external _plan : (testFuncs, int) => unit = "plan";

[@bs.send] external _end : (testFuncs, bool) => unit = "end";

[@bs.send] external _fail : (testFuncs, string) => unit = "fail";

[@bs.send] external _pass : (testFuncs, string) => unit = "pass";

[@bs.send] external _timeoutAfter : (testFuncs, int) => unit = "timeoutAfter";

[@bs.send] external _skip : (testFuncs, string) => unit = "skip";

[@bs.send]
external _ok : (testFuncs, bool, Js.Nullable.t(string)) => unit = "ok";

[@bs.send]
external _notOk : (testFuncs, bool, Js.Nullable.t(string)) => unit = "notOk";

[@bs.send]
external _error : (testFuncs, error, Js.Nullable.t(string)) => unit = "error";

[@bs.send]
external _equalStr :
  (testFuncs, string, string, Js.Nullable.t(string)) => unit =
  "equal";

[@bs.send]
external _equalInt : (testFuncs, int, int, Js.Nullable.t(string)) => unit =
  "equal";

[@bs.send]
external _equalFloat :
  (testFuncs, float, float, Js.Nullable.t(string)) => unit =
  "equal";

[@bs.send] external _comment : (testFuncs, string) => unit = "comment";

[@bs.send]
external _subtest : (testFuncs, string, testFuncs => unit) => unit = "test";

[@bs.module "tape"] [@bs.scope "test"]
external _testOnly : (string, testFuncs => unit) => unit = "only";

[@bs.module "tape"] [@bs.scope "test"]
external _testSkip : (string, testFuncs => unit) => unit = "skip";

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
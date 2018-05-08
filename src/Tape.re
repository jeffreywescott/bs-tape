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
external _ok : (assertInterface, bool, ~message: option(string)=?) => unit =
  "ok";

[@bs.send]
external _notOk : (assertInterface, bool, ~message: option(string)=?) => unit =
  "notOk";

[@bs.send]
external _error : (assertInterface, error, ~message: option(string)=?) => unit =
  "error";

[@bs.send]
external _equalStr :
  (assertInterface, string, string, ~message: option(string)=?) => unit =
  "equal";

[@bs.send]
external _equalInt :
  (assertInterface, int, int, ~message: option(string)=?) => unit =
  "equal";

[@bs.send]
external _equalFloat :
  (assertInterface, float, float, ~message: option(string)=?) => unit =
  "equal";

let test = (name, f) =>
  _test(
    name,
    t => {
      let assertImpl = {
        plan: n => _plan(t, n),
        endTest: () => _end(t, false),
        endTestIfNoErr: b => _end(t, b),
        fail: s => _fail(t, s),
        pass: s => _pass(t, s),
        timeoutAfter: n => _timeoutAfter(t, n),
        skip: s => _skip(t, s),
        ok: (~message=?, b) => _ok(t, b, ~message),
        notOk: (~message=?, b) => _notOk(t, b, ~message),
        error: (~message=?, o) => _error(t, o, ~message),
        equalStr: (~message=?, actual, expected) =>
          _equalStr(t, actual, expected, ~message),
        equalInt: (~message=?, actual, expected) =>
          _equalInt(t, actual, expected, ~message),
        equalFloat: (~message=?, actual, expected) =>
          _equalFloat(t, actual, expected, ~message),
      };
      f(assertImpl);
    },
  );
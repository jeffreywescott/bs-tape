open Tape;

test("THIS SHOULD PASS: ok and notOk", t => {
  t.plan(2);
  t.ok(true, ~message="true is, well, true");
  t.notOk(false, ~message="false is, well, false");
});

test("THIS SHOULD PASS: equalStr, equalInt, and equalFloat", t => {
  t.plan(3);
  t.equalStr("foo", "foo");
  t.equalInt(12, 12, ~message="numbers are identical");
  t.equalFloat(3.14, 3.14, ~message="pi is pi");
});

test("THIS SHOULD PASS: skip and endTest", t => {
  t.skip("skipping");
  t.endTest();
});

test("THIS SHOULD PASS: timeoutAfter and endTestIfNoErr", t => {
  t.timeoutAfter(123);
  t.endTestIfNoErr(false);
});

test("THIS SHOULD PASS: pass and error", t => {
  t.plan(2);
  t.pass("workie");
  t.error(Js.Nullable.null, ~message="no error");
});

test("THIS SHOULD FAIL: fail", t => {
  t.plan(1);
  t.fail("no workie");
});
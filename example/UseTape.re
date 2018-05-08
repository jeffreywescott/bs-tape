open Tape;

test("ok and notOk", t => {
  t.plan(2);
  t.ok(true, ~message="true is, well, true");
  t.notOk(false, ~message="false is, well, false");
});

test("equalStr, equalInt, and equalFloat", t => {
  t.plan(3);
  t.equalStr("foo", "foo");
  t.equalInt(12, 12, ~message="numbers are identical");
  t.equalFloat(3.14, 3.14, ~message="pi is pi");
});

testSkip("testSkip", t => {
  t.plan(1);
  t.skip("you won't see this");
});

test("comment, skip and endTest", t => {
  t.comment("----- this is a comment -----");
  t.skip("skipping");
  t.endTest();
});

test("timeoutAfter and endTestIfNoErr", t => {
  t.timeoutAfter(123);
  t.endTestIfNoErr(false);
});

test("pass and error", t => {
  t.plan(2);
  t.pass("workie");
  t.error(Js.Nullable.null, ~message="no error");
});

test("test with a subtest", t => {
  t.plan(1);
  t.test("here is the subtest", st => {
    st.plan(1);
    st.skip("subtest worked");
  });
});
/* comment this back in to see .fail() work */
/*
 test("THIS SHOULD FAIL: fail", t => {
   t.plan(1);
   t.fail("no workie");
 });
 */
/* comment this back in to see testOnly() work */
/*
 testOnly("ONLY RUN THIS", t => {
   t.plan(1);
   t.skip("only");
 });
 */
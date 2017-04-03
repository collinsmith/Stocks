#include <amxmodx>
#include <logger>

#include "../testing_stocks.inc"
#include "../flag_stocks.inc"

static const TEST[][] = {
    "FAILED",
    "PASSED"
};

static val, i, bool: b;
static tests, passed;
static bool: isEqual;
static Logger: logger;

native UnitTest(const function[] = "test", plugin = -1);

public plugin_init() {
  register_plugin("flag_stocks tests", "0.0.1", "Tirant");

  log_amx("Testing flag_stocks");

  tests = passed = 0;
  logger = LoggerCreate();

  UnitTest();

/*
  test_getFlag();
  test_isFlagSet();
  test_setFlag();
  test_unsetFlag();
  test_toggleFlag();
  test_setFlagWithPlayerIndexes();
*/

  log_amx("Finished Stocks tests: %s (%d/%d)", TEST[tests == passed], passed, tests);
}

test(bool: b) {
  isEqual = b;
  tests++;
  if (isEqual) passed++;
}

public test_getFlag() {
  new val = 0b0101;
  i = getFlag(val, 1, logger);
  test(assertEqual(0b0001, i, logger));
  i = getFlag(val, 2, logger);
  test(assertEqual(0b0000, i, logger));
  i = getFlag(val, 3, logger);
  test(assertEqual(0b0100, i, logger));
  i = getFlag(val, 4, logger);
  test(assertEqual(0b0000, i, logger));
}

public test_isFlagSet() {  
  val = 0b0101;
  b = isFlagSet(val, 1, logger);
  test(assertTrue(b, logger));
  b = isFlagSet(val, 2, logger);
  test(assertFalse(b, logger));
  b = isFlagSet(val, 3, logger);
  test(assertTrue(b, logger));
  b = isFlagSet(val, 4, logger);
  test(assertFalse(b, logger));
}

public test_setFlag() {
  val = 0b0101;
  setFlag(val, 1, logger);
  test(assertEqual(0b0101, val, logger));
  setFlag(val, 2, logger);
  test(assertEqual(0b0111, val, logger));
  setFlag(val, 3, logger);
  test(assertEqual(0b0111, val, logger));
  setFlag(val, 4, logger);
  test(assertEqual(0b1111, val, logger));
}

public test_unsetFlag() {
  val = 0b0101;
  unsetFlag(val, 1, logger);
  test(assertEqual(0b0100, val, logger));
  unsetFlag(val, 2, logger);
  test(assertEqual(0b0100, val, logger));
  unsetFlag(val, 3, logger);
  test(assertEqual(0b0000, val, logger));
  unsetFlag(val, 4, logger);
  test(assertEqual(0b0000, val, logger));
}

public test_toggleFlag() {
  val = 0b0101;
  toggleFlag(val, 1, logger);
  test(assertEqual(0b0100, val, logger));
  toggleFlag(val, 2, logger);
  test(assertEqual(0b0110, val, logger));
  toggleFlag(val, 3, logger);
  test(assertEqual(0b0010, val, logger));
  toggleFlag(val, 4, logger);
  test(assertEqual(0b1010, val, logger));
}

public test_setFlagWithPlayerIndexes() {
  val = 0;
  new id = 31;
  b = isFlagSet(val, id, logger);
  test(assertFalse(b, logger));
  setFlag(val, id, logger);
  test(assertEqual(1<<30, val, logger));
  id = 32;
  setFlag(val, id, logger);
  test(assertEqual(1<<30|1<<31, val, logger));
}

/*test_XorFlag() {
  val = 0b0000;
  setFlags(logger, val, 1, 3);
  test(val == 0b0101);
  log_amx("\t%s - setFlags(%X, %d, %d) == 5; actual => %d == 5", TEST[isEqual], val, 1, 3, val);
  test(getXorFlag(logger, val, 1, 2, 4) == 1);
  log_amx("\t%s - getXorFlag(%X, %d, %d, %d) == 1; actual => %d == 1", TEST[isEqual], val, 1, 2, 4, getXorFlag(logger, val, 1, 2, 4));
  test(isXorFlag(logger, val, 1, 2, 4));
  log_amx("\t%s - isXorFlag(%X, %d, %d, %d);", TEST[isEqual], val, 1, 2, 4);
  test(getXorFlag(logger, val, 2, 3, 4) == 3);
  log_amx("\t%s - getXorFlag(%X, %d, %d, %d) == 1; actual => %d == 1", TEST[isEqual], val, 2, 3, 4, getXorFlag(logger, val, 2, 3, 4));
  test(isXorFlag(logger, val, 2, 3, 4));
  log_amx("\t%s - isXorFlag(%X, %d, %d, %d);", TEST[isEqual], val, 2, 3, 4);
  test(getXorFlag(logger, val, 1, 3, 4) == 0);
  log_amx("\t%s - getXorFlag(%X, %d, %d, %d) == 0; actual => %d == 0", TEST[isEqual], val, 1, 3, 4, getXorFlag(logger, val, 1, 3, 4));
  test(!isXorFlag(logger, val, 1, 3, 4));
  log_amx("\t%s - !isXorFlag(%X, %d, %d, %d);", TEST[isEqual], val, 1, 3, 4);
  test(getXorFlag(logger, val, 2, 4) == 0);
  log_amx("\t%s - getXorFlag(%X, %d, %d) == 0; actual => %d == 0", TEST[isEqual], val, 2, 4, getXorFlag(logger, val, 2, 4));
  test(!isXorFlag(logger, val, 2, 4));
  log_amx("\t%s - !isXorFlag(%X, %d, %d);", TEST[isEqual], val, 2, 4);
  test(areFlagsSet(logger, val, 1, 3));
  log_amx("\t%s - areFlagsSet(%X, %d, %d); actual => %d == 0x?1?1", TEST[isEqual], val, 1, 3, val);
  unsetFlags(logger, val, 1, 4);
  log_amx("\t%s - unsetFlags(%X, %d, %d) == 4; actual => %d == 4", TEST[isEqual], val, 1, 4, val);
  test(!areFlagsSet(logger, val, 1, 3));
  log_amx("\t%s - !areFlagsSet(%X, %d, %d); actual => %d == 0x?1?1", TEST[isEqual], val, 1, 3, val);
}*/
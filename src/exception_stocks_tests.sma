#include <amxmodx>
#include <logger>

#include "../testing_stocks.inc"
#include "../exception_stocks.inc"

static const TEST[][] = {
    "FAILED",
    "PASSED"
};

static val, i, bool: b;
static tests, passed;
static bool: isEqual;
static Logger: logger;

native UnitTest(const function[] = "test", plugin = INVALID_PLUGIN_ID);

public plugin_init() {
  register_plugin("exception_stocks tests", "0.0.1", "Tirant");

  log_amx("Testing exception_stocks");

  tests = passed = 0;
  logger = LoggerCreate();

  UnitTest();

  log_amx("Finished Stocks tests: %s (%d/%d)", TEST[tests == passed], passed, tests);
}

test(bool: b) {
  isEqual = b;
  tests++;
  if (isEqual) passed++;
}

public test_ThrowIllegalArgumentException_Logger() {
  ThrowIllegalArgumentException(logger, "Exception with 0 args");
  ThrowIllegalArgumentException(logger, "Exception with 1 arg: %s", "foo");
  ThrowIllegalArgumentException(logger, "Exception with 2 args: %s, %s", "foo", "bar");
}

public test_ThrowIllegalArgumentException_Amxx() {
  ThrowIllegalArgumentException(_, "Exception with 0 args");
  ThrowIllegalArgumentException(_, "Exception with 1 arg: %s", "foo");
  ThrowIllegalArgumentException(_, "Exception with 2 args: %s, %s", "foo", "bar");
}

public test_Throw_Logger() {
  Throw(logger, AMX_ERR_PARAMS, "IllegalArgumentException", "Exception with 0 args");
  Throw(logger, AMX_ERR_PARAMS, "IllegalArgumentException", "Exception with 1 arg: %s", "foo");
  Throw(logger, AMX_ERR_PARAMS, "IllegalArgumentException", "Exception with 2 args: %s, %s", "foo", "bar");
}

public test_Throw_Amxx() {
  Throw(_, AMX_ERR_PARAMS, "IllegalArgumentException", "Exception with 0 args");
  Throw(_, AMX_ERR_PARAMS, "IllegalArgumentException", "Exception with 1 arg: %s", "foo");
  Throw(_, AMX_ERR_PARAMS, "IllegalArgumentException", "Exception with 2 args: %s, %s", "foo", "bar");
}
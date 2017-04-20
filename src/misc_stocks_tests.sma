#include <amxmodx>
#include <logger>

#include "../testing_stocks.inc"
#include "../string_stocks.inc"
#include "../misc_stocks.inc"

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
  register_plugin("misc_stocks tests", "0.0.1", "Tirant");

  log_amx("Testing misc_stocks");

  tests = passed = 0;
  logger = LoggerCreate();

  UnitTest();
  
  log_amx("Finished misc_stocks tests: %s (%d/%d)", TEST[tests == passed], passed, tests);
}

test(bool: b) {
  isEqual = b;
  tests++;
  if (isEqual) passed++;
}

public testCompareVersions() {
  i = compareVersions("1", "2");
  test(assertEqual(1, i, logger));
  i = compareVersions("2", "1");
  test(assertEqual(-1, i, logger));
  i = compareVersions("1", "1");
  test(assertEqual(0, i, logger));
  i = compareVersions("1.0", "1.0");
  test(assertEqual(0, i, logger));
  i = compareVersions("1.1", "1.1");
  test(assertEqual(0, i, logger));
  i = compareVersions("1.1", "1.0");
  test(assertEqual(-1, i, logger));
  i = compareVersions("1.0", "1.1");
  test(assertEqual(1, i, logger));
  i = compareVersions("1", "1.1");
  test(assertEqual(1, i, logger));
  i = compareVersions("1.1", "1");
  test(assertEqual(-1, i, logger));
  i = compareVersions("1", "1.0");
  test(assertEqual(1, i, logger));
  i = compareVersions("1.0.0", "1.0.1");
  test(assertEqual(1, i, logger));
  i = compareVersions("1.2.3.3", "1.2.3.4");
  test(assertEqual(1, i, logger));
  i = compareVersions("1.2.3.4", "1.2.3.3");
  test(assertEqual(-1, i, logger));
}

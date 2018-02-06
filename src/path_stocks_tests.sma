#include <amxmodx>
#include <logger>

#include "../simple_logger_stocks.inc"
#include "../exception_stocks.inc"
#include "../testing_stocks.inc"
#include "../string_stocks.inc"
#include "../path_stocks.inc"

static const TEST[][] = {
    "FAILED",
    "PASSED"
};

static val, i, bool: b;
static tests, passed;
static bool: isEqual;

native UnitTest(const function[] = "test", plugin = INVALID_PLUGIN_ID);

public plugin_init() {
  register_plugin("path_stocks tests", "0.0.1", "Tirant");

  new path[PLATFORM_MAX_PATH], pathLen;
  getPath(path, charsmax(path), "this");
  server_print(path);
  getPath(path, charsmax(path), "this", "is");
  server_print(path);
  getPath(path, charsmax(path), "this", "is", "a");
  server_print(path);
  getPath(path, charsmax(path), "this", "is", "a", "test");
  server_print(path);
  getPath(path, charsmax(path), "this");
  server_print(path);

  pathLen = copy(path, charsmax(path), "this\\is\\a\\test");
  pathLen = fixPath(path);
  server_print(path);

  pathLen = resolvePath(path, charsmax(path), 0, "again");
  server_print(path);

  pathLen = copy(path, charsmax(path), "this\\is\\a\\test\\");
  pathLen = fixPath(path);

  pathLen = resolvePath(path, charsmax(path), pathLen, "again");
  server_print(path);

  pathLen = copy(path, charsmax(path), "this/is/a/test/file.txt");
  getFileName(path, charsmax(path), path, pathLen);
  server_print(path);

  pathLen = copy(path, charsmax(path), "this/is/a/test/file");
  getFileName(path, charsmax(path), path, pathLen);
  server_print(path);

  pathLen = copy(path, charsmax(path), "this/is/a/test/file.txt");
  getFileExtension(path, charsmax(path), path, pathLen);
  server_print(path);

  pathLen = copy(path, charsmax(path), "this/is/a/test/file");
  getFileExtension(path, charsmax(path), path, pathLen);
  server_print(path);

  pathLen = copy(path, charsmax(path), "this/is/a/test/");
  getFileExtension(path, charsmax(path), path, pathLen);
  server_print(path);

  pathLen = copy(path, charsmax(path), "this/is/a/test/file.txt");
  getFileNameWithoutExtension(path, charsmax(path), path, pathLen);
  server_print(path);

  pathLen = copy(path, charsmax(path), "this/is/a/test/file.txt");
  getFileParentPath(path, charsmax(path), path);
  server_print(path);

  createPath(path, charsmax(path), "this/is", "a/test", "file.txt");

  //log_amx("Testing path_stocks");

  //tests = passed = 0;

  //UnitTest();

  //log_amx("Finished Stocks tests: %s (%d/%d)", TEST[tests == passed], passed, tests);
}

test(bool: b) {
  isEqual = b;
  tests++;
  if (isEqual) passed++;
}

countPATH_SEPARATOR(str[]) {
  new count = 0;
  for (new i = 0; str[i] != EOS; i++) {
    if (str[i] == PATH_SEPARATOR) {
      count++;
    }
  }

  return count;
}

countPATH_SEPARATOR_ALT(str[]) {
  new count = 0;
  for (new i = 0; str[i] != EOS; i++) {
    if (str[i] == PATH_SEPARATOR_ALT) {
      count++;
    }
  }

  return count;
}

public test_getPath() {
  new len, testlen, count;
  new temp[32];
  new str[64];

  formatex(str, 63, "%s/%s/%s/%s", "this", "is", "a", "test");
  len = getPath(temp, 31, "this", "is", "a", "test");
  test(assertStringEqual(str, temp));
  count = countPATH_SEPARATOR(temp);
  test(assertEqual(3, count));
  test(assertEqual(strlen(temp), len));
  test(assertTrue(bool:(equal(str, temp))));
}
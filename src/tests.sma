#include <amxmodx>
#include <logger>
#include <exception_handler>
#include "..\\dynamic_param_stocks.inc"
#include "..\\path_stocks.inc"
#include "..\\string_stocks.inc"
#include "..\\flag_stocks.inc"
#include "..\\precache_stocks.inc"

static const TEST[][] = {
    "FAILED",
    "PASSED"
};

static tests, passed;
static bool: isEqual;
static Logger: logger;

public plugin_init() {
    register_plugin("stock tests", "0.0.1", "Tirant");

    log_amx("Testing Stocks");

    tests = passed = 0;
    logger = LoggerCreate();

    test_stringGetOrDefault();
    test_stringJoin();
    test_stringStartsWith();
    test_getPath();
    test_fixPath();
    test_dynamicParamsStocks();
    test_flagStocks();
    test_exceptions();
    test_precacheStocks();

    log_amx("Finished Stocks tests: %s (%d/%d)", TEST[tests == passed], passed, tests);
}

test(bool: b) {
    isEqual = b;
    tests++;
    if (isEqual) passed++;
}

test_stringGetOrDefault() {
    new temp[32];
    new string1[32];
    new string2[32];

    log_amx("Testing stringGetOrDefault");

    string1 = "string";
    string2 = "";
    stringGetOrDefault(temp, _, string1, string2);
    log_amx("\tstringGetOrDefault(temp, _, \"%s\", \"%s\"); temp = \"%s\"", string1, string2, temp);
    test(equal(temp, string1) > 0);
    log_amx("\t\t%s - equal(\"%s\", \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], temp, string1, temp, string1);

    string1 = "";
    string2 = "string";
    stringGetOrDefault(temp, _, string1, string2);
    log_amx("\tstringGetOrDefault(temp, _, \"%s\", \"%s\"); temp = \"%s\"", string1, string2, temp);
    test(equal(temp, string2) > 0);
    log_amx("\t\t%s - equal(\"%s\", \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], temp, string2, temp, string2);

    string1 = "string";
    string2 = "string";
    stringGetOrDefault(temp, _, string1, string2);
    log_amx("\tstringGetOrDefault(temp, _, \"%s\", \"%s\"); temp = \"%s\"", string1, string2, temp);
    test(equal(temp, string1) > 0);
    log_amx("\t\t%s - equal(\"%s\", \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], temp, string1, temp, string1);

    string1 = "string1";
    string2 = "string2";
    stringGetOrDefault(temp, _, string1, string2);
    log_amx("\tstringGetOrDefault(temp, _, \"%s\", \"%s\"); temp = \"%s\"", string1, string2, temp);
    test(equal(temp, string1) > 0);
    log_amx("\t\t%s - equal(\"%s\", \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], temp, string1, temp, string1);

    string1 = "string2";
    string2 = "string1";
    stringGetOrDefault(temp, _, string1, string2);
    log_amx("\tstringGetOrDefault(temp, _, \"%s\", \"%s\"); temp = \"%s\"", string1, string2, temp);
    test(equal(temp, string1) > 0);
    log_amx("\t\t%s - equal(\"%s\", \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], temp, string1, temp, string1);
}

test_stringJoin() {
    new temp[32];
    new pre[32];
    new l1, l2;
    
    log_amx("Testing stringJoin");

    pre = "[]";
    stringJoin(temp, _, "[", ",", "]");
    log_amx("\tstringJoin(temp, _, \"[\", \",\", \"]\"); temp = \"%s\"", temp);
    test(equal(temp, pre) > 0);
    log_amx("\t\t%s - equal(temp, \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], pre, temp, pre);
    l1 = strlen(pre);
    l2 = strlen(temp);
    test(l1 == l2);
    log_amx("\t\t%s - strlen(\"%s\") == strlen(\"%s\"); actual => %d == %d", TEST[isEqual], pre, temp, l1, l2);

    pre = "[]";
    stringJoin(temp, _, "[", ",", "]", "");
    log_amx("\tstringJoin(temp, _, \"[\", \",\", \"]\", \"\"); temp = \"%s\"", temp);
    test(equal(temp, pre) > 0);
    log_amx("\t\t%s - equal(temp, \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], pre, temp, pre);
    l1 = strlen(pre);
    l2 = strlen(temp);
    test(l1 == l2);
    log_amx("\t\t%s - strlen(\"%s\") == strlen(\"%s\"); actual => %d == %d", TEST[isEqual], pre, temp, l1, l2);

    pre = "[1]";
    stringJoin(temp, _, "[", ",", "]", "1");
    log_amx("\tstringJoin(temp, _, \"[\", \",\", \"]\", \"1\"); temp = \"%s\"", temp);
    test(equal(temp, pre) > 0);
    log_amx("\t\t%s - equal(temp, \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], pre, temp, pre);
    l1 = strlen(pre);
    l2 = strlen(temp);
    test(l1 == l2);
    log_amx("\t\t%s - strlen(\"%s\") == strlen(\"%s\"); actual => %d == %d", TEST[isEqual], pre, temp, l1, l2);

    pre = "[1,2]";
    stringJoin(temp, _, "[", ",", "]", "1", "2");
    log_amx("\tstringJoin(temp, _, \"[\", \",\", \"]\", \"1\", \"2\"); temp = \"%s\"", temp);
    test(equal(temp, pre) > 0);
    log_amx("\t\t%s - equal(temp, \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], pre, temp, pre);
    l1 = strlen(pre);
    l2 = strlen(temp);
    test(l1 == l2);
    log_amx("\t\t%s - strlen(\"%s\") == strlen(\"%s\"); actual => %d == %d", TEST[isEqual], pre, temp, l1, l2);

    pre = "[1,2,3]";
    stringJoin(temp, _, "[", ",", "]", "1", "2", "3");
    log_amx("\tstringJoin(temp, _, \"[\", \",\", \"]\", \"1\", \"2\", \"3\"); temp = \"%s\"", temp);
    test(equal(temp, pre) > 0);
    log_amx("\t\t%s - equal(temp, \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], pre, temp, pre);
    l1 = strlen(pre);
    l2 = strlen(temp);
    test(l1 == l2);
    log_amx("\t\t%s - strlen(\"%s\") == strlen(\"%s\"); actual => %d == %d", TEST[isEqual], pre, temp, l1, l2);

    pre = "models/player/gign/gign.mdl";
    stringJoin(temp, _, "", "/", "", "models", "player", "gign", "gign.mdl");
    log_amx("\tstringJoin(temp, _, \"\", \"/\", \"\", \"models\", \"player\", \"gign\", \"gign.mdl\"); temp = \"%s\"", temp);
    test(equal(temp, pre) > 0);
    log_amx("\t\t%s - equal(temp, \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], pre, temp, pre);
    l1 = strlen(pre);
    l2 = strlen(temp);
    test(l1 == l2);
    log_amx("\t\t%s - strlen(\"%s\") == strlen(\"%s\"); actual => %d == %d", TEST[isEqual], pre, temp, l1, l2);

    pre = "123models/player/gign/gign.mdl";
    stringJoin(temp, _, "123", "/", "", "models", "player", "gign", "gign.mdl");
    log_amx("\tstringJoin(temp, _, \"\", \"/\", \"\", \"models\", \"player\", \"gign\", \"gign.mdl\"); temp = \"%s\"", temp);
    test(equal(temp, pre) > 0);
    log_amx("\t\t%s - equal(temp, \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], pre, temp, pre);
    l1 = strlen(pre);
    l2 = strlen(temp);
    test(l1 == l2);
    log_amx("\t\t%s - strlen(\"%s\") == strlen(\"%s\"); actual => %d == %d", TEST[isEqual], pre, temp, l1, l2);

    pre = "models/player/gign/gign.mdl123";
    stringJoin(temp, _, "", "/", "123", "models", "player", "gign", "gign.mdl");
    log_amx("\tstringJoin(temp, _, \"\", \"/\", \"\", \"models\", \"player\", \"gign\", \"gign.mdl\"); temp = \"%s\"", temp);
    test(equal(temp, pre) > 0);
    log_amx("\t\t%s - equal(temp, \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], pre, temp, pre);
    l1 = strlen(pre);
    l2 = strlen(temp);
    test(l1 == l2);
    log_amx("\t\t%s - strlen(\"%s\") == strlen(\"%s\"); actual => %d == %d", TEST[isEqual], pre, temp, l1, l2);

    new temp2[8];
    new pre2[8];

    pre2 = "[12,45]";
    stringJoin(temp2, _, "[", ",", "]", "12", "45");
    log_amx("\tstringJoin(temp2, _, \"[\", \",\", \"]\", ); temp2 = \"%s\"", temp2);
    test(equal(temp2, pre2) > 0);
    log_amx("\t\t%s - equal(temp2, \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], pre2, temp2, pre2);
    l1 = strlen(pre2);
    l2 = strlen(temp2);
    test(l1 == l2);
    log_amx("\t\t%s - strlen(\"%s\") == strlen(\"%s\"); actual => %d == %d", TEST[isEqual], pre2, temp2, l1, l2);

    pre2 = "[12,345";
    stringJoin(temp2, _, "[", ",", "]", "12", "34567");
    log_amx("\tstringJoin(temp2, _, \"[\", \",\", \"]\", ); temp2 = \"%s\"", temp2);
    test(equal(temp2, pre2) > 0);
    log_amx("\t\t%s - equal(temp2, \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], pre2, temp2, pre2);
    l1 = strlen(pre2);
    l2 = strlen(temp2);
    test(l1 == l2);
    log_amx("\t\t%s - strlen(\"%s\") == strlen(\"%s\"); actual => %d == %d", TEST[isEqual], pre2, temp2, l1, l2);

    pre2 = "[1,2]34";
    stringJoin(temp2, _, "[", ",", "]34", "1", "2");
    log_amx("\tstringJoin(temp2, _, \"[\", \",\", \"]\", ); temp2 = \"%s\"", temp2);
    test(equal(temp2, pre2) > 0);
    log_amx("\t\t%s - equal(temp2, \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], pre2, temp2, pre2);
    l1 = strlen(pre2);
    l2 = strlen(temp2);
    test(l1 == l2);
    log_amx("\t\t%s - strlen(\"%s\") == strlen(\"%s\"); actual => %d == %d", TEST[isEqual], pre2, temp2, l1, l2);

    pre2 = "[1,2,3]";
    stringJoin(temp2, _, "[", ",", "]456", "1", "2", "3");
    log_amx("\tstringJoin(temp2, _, \"[\", \",\", \"]\"); temp2 = \"%s\"", temp2);
    test(equal(temp2, pre2) > 0);
    log_amx("\t\t%s - equal(temp2, \"%s\"); actual => \"%s\" == \"%s\"", TEST[isEqual], pre2, temp2, pre2);
    l1 = strlen(pre2);
    l2 = strlen(temp2);
    test(l1 == l2);
    log_amx("\t\t%s - strlen(\"%s\") == strlen(\"%s\"); actual => %d == %d", TEST[isEqual], pre2, temp2, l1, l2);
}

test_stringStartsWith() {
    new string1[32];
    new string2[32];

    log_amx("Testing stringStartsWith");

    string1 = "string";
    string2 = "string";
    test(stringStartsWith(string1, string2));
    log_amx("\t%s - stringStartsWith(\"%s\", \"%s\");", TEST[isEqual], string1, string2);

    string1 = "string";
    string2 = "strin";
    test(stringStartsWith(string1, string2));
    log_amx("\t%s - stringStartsWith(\"%s\", \"%s\");", TEST[isEqual], string1, string2);

    string1 = "strin";
    string2 = "string";
    test(!stringStartsWith(string1, string2));
    log_amx("\t%s - !stringStartsWith(\"%s\", \"%s\");", TEST[isEqual], string1, string2);
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

test_getPath() {
    new len, testlen, count;
    new temp[32];
    new str[64];

    log_amx("Testing getPath");

    formatex(str, 63, "%s/%s/%s/%s", "this", "is", "a", "test");
    len = getPath(temp, sizeof temp, "this", "is", "a", "test");
    log_amx("\tgetPath(temp, sizeof temp, \"this\", \"is\", \"a\", \"test\"); temp = \"%s\"", temp);
    count = countPATH_SEPARATOR(temp);
    test(count == 3);
    log_amx("\t\t%s - count('/') in getPath(...) == 3; actual => %d == %d", TEST[isEqual], count, 3);
    testlen = strlen(temp);
    test(len == testlen);
    log_amx("\t\t%s - strlen(temp) == getPath(...); actual => %d == %d", TEST[isEqual], testlen, len);
    test(equal(str, temp, 31) > 0);
    log_amx("\t\t%s - equal(str, temp, 31); actual => \"%s\" == \"%s\"", TEST[isEqual], str, temp);

    formatex(str, 63, "%s/%s/%s/%s", "models", "player", "gign", "gign.mdl");
    len = getPath(temp, sizeof temp, "models", "player", "gign", "gign.mdl");
    log_amx("\tgetPath(temp, sizeof temp, \"models\", \"player\", \"gign\", \"gign.mdl\"); temp = \"%s\"", temp);
    count = countPATH_SEPARATOR(temp);
    test(count == 3);
    log_amx("\t\t%s - count('/') in getPath(...) == 4; actual => %d == %d", TEST[isEqual], count, 3);
    testlen = strlen(temp);
    test(len == testlen);
    log_amx("\t\t%s - strlen(temp) == getPath(...); actual => %d == %d", TEST[isEqual], testlen, len);
    test(equal(str, temp, 31) > 0);
    log_amx("\t\t%s - equal(str, temp, 31); actual => \"%s\" == \"%s\"", TEST[isEqual], str, temp);

    formatex(str, 63, "%s/%s", "sound", "test.wav");
    len = getPath(temp, sizeof temp, "sound", "test.wav");
    log_amx("\tgetPath(temp, sizeof temp, \"sound\", \"test.wav\"); temp = \"%s\"", temp);
    count = countPATH_SEPARATOR(temp);
    test(count == 1);
    log_amx("\t\t%s - count('/') in getPath(...) == 4; actual => %d == %d", TEST[isEqual], count, 1);
    testlen = strlen(temp);
    test(len == testlen);
    log_amx("\t\t%s - strlen(temp) == getPath(...); actual => %d == %d", TEST[isEqual], testlen, len);
    test(equal(str, temp, 31) > 0);
    log_amx("\t\t%s - equal(str, temp, 31); actual => \"%s\" == \"%s\"", TEST[isEqual], str, temp);

    formatex(str, 63, "%s", "server.cfg");
    len = getPath(temp, sizeof temp, "server.cfg");
    log_amx("\tgetPath(temp, sizeof temp, \"server.cfg\"); temp = \"%s\"", temp);
    count = countPATH_SEPARATOR(temp);
    test(count == 0);
    log_amx("\t\t%s - count('/') in getPath(...) == 4; actual => %d == %d", TEST[isEqual], count, 0);
    testlen = strlen(temp);
    test(len == testlen);
    log_amx("\t\t%s - strlen(temp) == getPath(...); actual => %d == %d", TEST[isEqual], testlen, len);
    test(equal(str, temp, 31) > 0);
    log_amx("\t\t%s - equal(str, temp, 31); actual => \"%s\" == \"%s\"", TEST[isEqual], str, temp);

    formatex(str, 63, "%s", "12345678123456781234567812345678");
    len = getPath(temp, sizeof temp, "12345678123456781234567812345678");
    log_amx("\tgetPath(temp, sizeof temp, \"12345678123456781234567812345678\"); temp = \"%s\"", temp);
    testlen = strlen(temp);
    test(len == testlen);
    log_amx("\t\t%s - strlen(temp) == getPath(...); actual => %d == %d", TEST[isEqual], testlen, len);
    test(equal(str, temp, 31) > 0);
    log_amx("\t\t%s - equal(str, temp, 31); actual => \"%s\" == \"%s\"", TEST[isEqual], str, temp);

    formatex(str, 63, "%s/%s/%s/%s", "12345678", "12345678", "12345678", "12345678");
    len = getPath(temp, sizeof temp, "12345678", "12345678", "12345678", "12345678");
    log_amx("\tgetPath(temp, sizeof temp, \"12345678\", \"12345678\", \"12345678\", \"12345678\"); temp = \"%s\"", temp);
    testlen = strlen(temp);
    test(len == testlen);
    log_amx("\t\t%s - strlen(temp) == getPath(...); actual => %d == %d", TEST[isEqual], testlen, len);
    test(equal(str, temp, 31) > 0);
    log_amx("\t\t%s - equal(str, temp, 31); actual => \"%s\" == \"%s\"", TEST[isEqual], str, temp);
}

test_fixPath_path(temp[], maxlen = sizeof temp) {
    new len, testlen;
    new sep1, sep2;
    new altsep1, altsep2;
 
    sep1 = countPATH_SEPARATOR(temp);
    altsep1 = countPATH_SEPARATOR_ALT(temp);
    len = fixPath(temp, maxlen);
    log_amx("\tfixPath(temp, sizeof temp, \"%s\"); temp = \"%s\"", temp, temp);
    sep2 = countPATH_SEPARATOR(temp);
    altsep2 = countPATH_SEPARATOR_ALT(temp);
    test(altsep2 == 0);
    log_amx("\t\t%s - count('\\') in fixPath(...) == 0; actual => %d == %d", TEST[isEqual], altsep2, 0);
    test(sep2 == (sep1 + altsep1));
    log_amx("\t\t%s - count('\\') in fixPath(...) == (sep1 + altsep1); actual => %d == %d", TEST[isEqual], sep2, (sep1 + altsep1));
    testlen = strlen(temp);
    test(len == testlen);
    log_amx("\t\t%s - strlen(temp) == fixPath(...); actual => %d == %d", TEST[isEqual], testlen, len);
}

test_fixPath() {
    log_amx("Testing fixPath");
    test_fixPath_path("this/is/a/test");
    test_fixPath_path("this\\is/a/test");
    test_fixPath_path("this/is/a\\test");
    test_fixPath_path("this\\is/a\\test");
    test_fixPath_path("this\\is\\a\\test");
}

test_dynamicParamsStocks() {
    log_amx("Testing dynamicParamsStocks");

    test(numParamsEqual(logger, 0, 0));
    log_amx("\t%s - numParamsEqual(0, 0);", TEST[isEqual]);
    test(!numParamsEqual(logger, 0, 1));
    log_amx("\t%s - !numParamsEqual(0, 1);", TEST[isEqual]);
    test(!numParamsEqual(logger, 1, 0));
    log_amx("\t%s - !numParamsEqual(1, 0);", TEST[isEqual]);
    test(numParamsEqual(logger, 1, 1));
    log_amx("\t%s - numParamsEqual(1, 1);", TEST[isEqual]);

    test(!numParamsFewer(logger, 0, 0));
    log_amx("\t%s - !numParamsFewer(0, 0);", TEST[isEqual]);
    test(!numParamsFewer(logger, 0, 1));
    log_amx("\t%s - !numParamsFewer(0, 1);", TEST[isEqual]);
    test(numParamsFewer(logger, 1, 0));
    log_amx("\t%s - numParamsFewer(1, 0);", TEST[isEqual]);
    test(!numParamsFewer(logger, 1, 1));
    log_amx("\t%s - !numParamsFewer(1, 1);", TEST[isEqual]);

    test(numParamsFewerEqual(logger, 0, 0));
    log_amx("\t%s - numParamsFewerEqual(0, 0);", TEST[isEqual]);
    test(!numParamsFewerEqual(logger, 0, 1));
    log_amx("\t%s - !numParamsFewerEqual(0, 1);", TEST[isEqual]);
    test(numParamsFewerEqual(logger, 1, 0));
    log_amx("\t%s - numParamsFewerEqual(1, 0);", TEST[isEqual]);
    test(numParamsFewerEqual(logger, 1, 1));
    log_amx("\t%s - numParamsFewerEqual(1, 1);", TEST[isEqual]);

    test(!numParamsGreater(logger, 0, 0));
    log_amx("\t%s - !numParamsGreater(0, 0);", TEST[isEqual]);
    test(numParamsGreater(logger, 0, 1));
    log_amx("\t%s - numParamsGreater(0, 1);", TEST[isEqual]);
    test(!numParamsGreater(logger, 1, 0));
    log_amx("\t%s - !numParamsGreater(1, 0);", TEST[isEqual]);
    test(!numParamsGreater(logger, 1, 1));
    log_amx("\t%s - !numParamsGreater(1, 1);", TEST[isEqual]);

    test(numParamsGreaterEqual(logger, 0, 0));
    log_amx("\t%s - numParamsGreaterEqual(0, 0);", TEST[isEqual]);
    test(numParamsGreaterEqual(logger, 0, 1));
    log_amx("\t%s - numParamsGreaterEqual(0, 1);", TEST[isEqual]);
    test(!numParamsGreaterEqual(logger, 1, 0));
    log_amx("\t%s - !numParamsGreaterEqual(1, 0);", TEST[isEqual]);
    test(numParamsGreaterEqual(logger, 1, 1));
    log_amx("\t%s - numParamsGreaterEqual(1, 1);", TEST[isEqual]);

    test(numParamsInRange(logger, 0, 0, 0));
    log_amx("\t%s - numParamsInRange(0, 0, 0);", TEST[isEqual]);
    test(!numParamsInRange(logger, 0, 0, 1));
    log_amx("\t%s - !numParamsInRange(0, 0, 1);", TEST[isEqual]);
    test(numParamsInRange(logger, 0, 1, 0));
    log_amx("\t%s - numParamsInRange(0, 1, 0);", TEST[isEqual]);
    test(numParamsInRange(logger, 0, 1, 1));
    log_amx("\t%s - numParamsInRange(0, 1, 1);", TEST[isEqual]);
    test(!numParamsInRange(logger, 1, 2, 0));
    log_amx("\t%s - !numParamsInRange(1, 2, 0);", TEST[isEqual]);
    test(numParamsInRange(logger, 6, 10, 8));
    log_amx("\t%s - numParamsInRange(6, 10, 8);", TEST[isEqual]);
    test(!numParamsInRange(logger, 1, 0, 0));
    log_amx("\t%s - !numParamsInRange(1, 0, 0); (illegal arguments)", TEST[isEqual]);
}

test_flagStocks() {
    new i;
    new bool: b;

    log_amx("Testing flag stocks");

    new val = 0b0101;
    i = getFlag(val, 1);
    test(i == 0b0001);
    log_amx("\t%s - getFlag(%X,%d) == 1; actual => %d == 1", TEST[isEqual], val, 1, i);
    i = getFlag(val, 2);
    test(i == 0b0000);
    log_amx("\t%s - getFlag(%X,%d) == 0; actual => %d == 0", TEST[isEqual], val, 2, i);
    i = getFlag(val, 3);
    test(i == 0b0100);
    log_amx("\t%s - getFlag(%X,%d) == 4; actual => %d == 4", TEST[isEqual], val, 3, i);
    i = getFlag(val, 4);
    test(i == 0b0000);
    log_amx("\t%s - getFlag(%X,%d) == 0; actual => %d == 0", TEST[isEqual], val, 4, i);

    val = 0b0101;
    b = isFlagSet(val, 1);
    test(b);
    log_amx("\t%s - isFlagSet(%X,%d); actual => %d", TEST[isEqual], val, 1, b);
    b = isFlagSet(val, 2);
    test(!b);
    log_amx("\t%s - !isFlagSet(%X,%d); actual => %d", TEST[isEqual], val, 2, b);
    b = isFlagSet(val, 3);
    test(b);
    log_amx("\t%s - isFlagSet(%X,%d); actual => %d", TEST[isEqual], val, 3, b);
    b = isFlagSet(val, 4);
    test(!b);
    log_amx("\t%s - !isFlagSet(%X,%d); actual => %d", TEST[isEqual], val, 4, b);

    val = 0b0101;
    setFlag(val, 1);
    test(val == 0b0101);
    log_amx("\t%s - setFlag(%X,%d) == 5; actual => %d == 5", TEST[isEqual], val, 1, val);
    setFlag(val, 2);
    test(val == 0b0111);
    log_amx("\t%s - setFlag(%X,%d) == 7; actual => %d == 7", TEST[isEqual], val, 2, val);
    setFlag(val, 3);
    test(val == 0b0111);
    log_amx("\t%s - setFlag(%X,%d) == 7; actual => %d == 7", TEST[isEqual], val, 3, val);
    setFlag(val, 4);
    test(val == 0b1111);
    log_amx("\t%s - setFlag(%X,%d) == 15; actual => %d == 15", TEST[isEqual], val, 4, val);

    val = 0b0101;
    unsetFlag(val, 1);
    test(val == 0b0100);
    log_amx("\t%s - unsetFlag(%X,%d) == 4; actual => %d == 4", TEST[isEqual], val, 1, val);
    unsetFlag(val, 2);
    test(val == 0b0100);
    log_amx("\t%s - unsetFlag(%X,%d) == 4; actual => %d == 4", TEST[isEqual], val, 2, val);
    unsetFlag(val, 3);
    test(val == 0b0000);
    log_amx("\t%s - unsetFlag(%X,%d) == 0; actual => %d == 0", TEST[isEqual], val, 3, val);
    unsetFlag(val, 4);
    test(val == 0b0000);
    log_amx("\t%s - unsetFlag(%X,%d) == 0; actual => %d == 0", TEST[isEqual], val, 4, val);

    val = 0b0101;
    toggleFlag(val, 1);
    test(val == 0b0100);
    log_amx("\t%s - toggleFlag(%X,%d) == 4; actual => %d == 4", TEST[isEqual], val, 1, val);
    toggleFlag(val, 2);
    test(val == 0b0110);
    log_amx("\t%s - toggleFlag(%X,%d) == 6; actual => %d == 6", TEST[isEqual], val, 2, val);
    toggleFlag(val, 3);
    test(val == 0b0010);
    log_amx("\t%s - toggleFlag(%X,%d) == 2; actual => %d == 2", TEST[isEqual], val, 3, val);
    toggleFlag(val, 4);
    test(val == 0b1010);
    log_amx("\t%s - toggleFlag(%X,%d) == 10; actual => %d == 10", TEST[isEqual], val, 4, val);

    val = 0;
    new id = 31;
    b = isFlagSet(val, id);
    test(!b);
    log_amx("\t%s - !isFlagSet(%X,%d); actual => %d", TEST[isEqual], val, id, b);
    setFlag(val, id);
    test(val == 1<<30);
    log_amx("\t%s - setFlag(%X,%d) == 1<<30; actual => %d == %d", TEST[isEqual], val, id, 1<<30, val);
    id = 32;
    setFlag(val, id);
    test(val == 1<<31|1<<30);
    log_amx("\t%s - setFlag(%X,%d) == 1<<31|1<<30; actual => %d == %d", TEST[isEqual], val, id, 1<<31|1<<30, val);
}

test_exceptions() {
    new val = 0b0101;

    log_amx("Testing exceptions");

    TryBegin(logger); {
        isFlagSet(val, 1);
        test(!TryCatch("IllegalArgumentException"));
        log_amx("\t%s - isFlagSet(%X,%d) does not throw IllegalArgumentException", TEST[isEqual], val, 1);
        TryHandle();
    } TryEnd();

    TryBegin(logger); {
        isFlagSet(val, 2);
        test(!TryCatch(""));
        log_amx("\t%s - isFlagSet(%X,%d) does not throw IllegalArgumentException", TEST[isEqual], val, 2);
        TryHandle();
    } TryEnd();

    TryBegin(logger); {
        isFlagSet(val, 0);
        test(TryCatch("IllegalArgumentException"));
        log_amx("\t%s - isFlagSet(%X,%d) throws IllegalArgumentException", TEST[isEqual], val, 0);
        TryHandle();
    } TryEnd();

    TryBegin(logger); {
        isFlagSet(val, cellbits+1);
        test(TryCatch(""));
        log_amx("\t%s - isFlagSet(%X,%d) throws IllegalArgumentException", TEST[isEqual], val, cellbits+1);
        TryHandle();
    } TryEnd();
}

test_precacheStocks() {
    new temp[32];
    new model[32];
    new sound[32];
    new str[64];

    log_amx("Testing getPlayerModelPath");

    model = "gign";
    formatex(str, charsmax(str), "%s/%s/%s/%s.mdl", MODELS, PLAYER, model, model);
    getPlayerModelPath(temp, _, model);
    log_amx("\tgetPlayerModelPath(temp, _, \"%s\"); temp = \"%s\"", model, temp);
    test(equal(temp, str) > 0);
    log_amx("\t\t%s - equal(\"%s\", \"%s\"); actual => \"%s\"", TEST[isEqual], str, temp, temp);

    model = "gign12345678";
    formatex(str, charsmax(str), "%s/%s/%s/%s.mdl", MODELS, PLAYER, model, model);
    getPlayerModelPath(temp, _, model);
    log_amx("\tgetPlayerModelPath(temp, _, \"%s\"); temp = \"%s\"", model, temp);
    test(equal(temp, str, 31) > 0);
    log_amx("\t\t%s - equal(\"%s\", \"%s\", 31); actual => \"%s\"", TEST[isEqual], str, temp, temp);

    model = "v_bowie";
    formatex(str, charsmax(str), "%s/%s.mdl", MODELS, model);
    getModelPath(temp, _, model);
    log_amx("\tgetModelPath(temp, _, \"%s\"); temp = \"%s\"", model, temp);
    test(equal(temp, str) > 0);
    log_amx("\t\t%s - equal(\"%s\", \"%s\"); actual => \"%s\"", TEST[isEqual], str, temp, temp);

    model = "v_bowie123456781234567812345678";
    formatex(str, charsmax(str), "%s/%s.mdl", MODELS, model);
    getModelPath(temp, _, model);
    log_amx("\tgetModelPath(temp, _, \"%s\"); temp = \"%s\"", model, temp);
    test(equal(temp, str, 31) > 0);
    log_amx("\t\t%s - equal(\"%s\", \"%s\", 31); actual => \"%s\"", TEST[isEqual], str, temp, temp);
}
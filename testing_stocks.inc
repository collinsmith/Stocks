#if defined _testing_stocks_included
  #endinput
#endif
#define _testing_stocks_included

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

stock bool: assertEqual(any: expected, any: actual, Logger: logger) {
  if (expected != actual) {
    LoggerLogError(logger, "AssertionError: Expected: %d, was: %d", expected, actual);
    return false;
  }

  return true;
}

stock bool: assertTrue(bool: bool, Logger: logger) {
  if (!bool) {
    LoggerLogError(logger, "AssertionError: Expected: true, was: false");
    return false;
  }

  return true;
}

stock bool: assertFalse(bool: bool, Logger: logger) {
  if (bool) {
    LoggerLogError(logger, "AssertionError: Expected: false, was: true");
    return false;
  }

  return true;
}
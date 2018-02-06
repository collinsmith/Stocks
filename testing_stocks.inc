/**
 * This file contains utility functions that can be used when testing scripts.
 */

#if defined _testing_stocks_included
  #endinput
#endif
#define _testing_stocks_included

#tryinclude "include/stocks/exception_stocks.inc"
#if !defined _exception_stocks_included
  #include <exception_stocks>
#endif

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

/**
 * Checks that {@code expected} equals {@code actual} and logs an error message
 * if they are not.
 * 
 * @param expected The expected value to assert
 * @param actual   The actual value
 * 
 * @return {@code true} if {@code actual} equals {@code expected}, {@code false}
 *         otherwise
 * 
 * @throws AssertionError if {@code actual} is not equal to the {@code expected}
 *         value.
 */
stock bool: assertEqual(any: expected, any: actual) {
  if (expected != actual) {
    ThrowAssertionException("Expected: %d, was: %d", expected, actual);
    return false;
  }

  return true;
}

/**
 * Checks that the specified {@code condition} evaluates as {@code true} and
 * logs an error message if it is not.
 * 
 * @param condition The condition to evaluate and assert as {@code true}
 * 
 * @return {@code true} if {@code condition} is {@code true}, {@code false}
 *         otherwise
 * 
 * @throws AssertionError if {@code condition} is {@code false}.
 */
stock bool: assertTrue(bool: condition) {
  if (!condition) {
    ThrowAssertionException("Expected: true, was: false");
    return false;
  }

  return true;
}

/**
 * Checks that the specified {@code condition} evaluates as {@code false} and
 * logs an error message if it is not.
 * 
 * @param condition The condition to evaluate and assert as {@code false}
 * 
 * @return {@code true} if {@code condition} is {@code false}, {@code false}
 *         otherwise
 * 
 * @throws AssertionError if {@code condition} is {@code true}.
 */
stock bool: assertFalse(bool: condition) {
  if (condition) {
    ThrowAssertionException("Expected: false, was: true");
    return false;
  }

  return true;
}

/**
 * Checks that the {@code actual} string equals the {@code expected} string and
 * logs an error message if they are not.
 * 
 * @param expected The expected string
 * @param actual   The actual string to check
 * 
 * @return {@code true} if {@code actual} equals {@code expected}, {@code false}
 *         otherwise
 * 
 * @throws AssertionError if {@code actual} is not equal to the {@code expected}
 *         value.
 */
stock bool: assertStringEqual(const expected[], const actual[]) {
  if (!equal(expected, actual)) {
    ThrowAssertionException("Expected: %s, was: %s", expected, actual);
    return false;
  }

  return true;
}

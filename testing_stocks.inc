#if defined _testing_stocks_included
  #endinput
#endif
#define _testing_stocks_included

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

/**
 * Checks that {@code expected} equals {@code actual} and logs an error message
 * if they are not.
 * 
 * @param expected The expected value to assert
 * @param actaul   The actual value
 * @param 
 * 
 * @return {@code true} if {@code actual} equals {@code expected}, {@code false}
 *          otherwise
 * 
 * @throws AssertionError if {@code actual} is not equal to the {@code expected}
 *         value.
 */
stock bool: assertEqual(any: expected, any: actual, Logger: logger) {
  if (expected != actual) {
    new fmt[] = "AssertionError: Expected: %d, was: %d";
    if (logger > Invalid_Logger) {
      LoggerLogError(logger, fmt, expected, actual);
    } else {
      log_error(AMX_ERR_PARAMS, fmt, expected, actual);
    }

    return false;
  }

  return true;
}

/**
 * Checks that the specified {@code condition} evaluates as {@code true} and
 * logs an error message if it is not.
 * 
 * @param condition The condition to evaluate and assert as {@code true}
 * @param logger    The logger to log the error message (if any) to, otherwise
 *                    {@code Invalid_Logger} to log the error message to the
 *                    AMXX error log 
 * 
 * @return {@code true} if {@code condition} is {@code true}, {@code false}
 *          otherwise
 * 
 * @throws AssertionError if {@code condition} is {@code false}.
 */
stock bool: assertTrue(bool: condition, Logger: logger) {
  if (!condition) {
    new fmt[] = "AssertionError: Expected: true, was: false";
    if (logger > Invalid_Logger) {
      LoggerLogError(logger, fmt);
    } else {
      log_error(AMX_ERR_PARAMS, fmt);
    }

    return false;
  }

  return true;
}

/**
 * Checks that the specified {@code condition} evaluates as {@code false} and
 * logs an error message if it is not.
 * 
 * @param condition The condition to evaluate and assert as {@code false}
 * @param logger    The logger to log the error message (if any) to, otherwise
 *                    {@code Invalid_Logger} to log the error message to the
 *                    AMXX error log 
 * 
 * @return {@code true} if {@code condition} is {@code false}, {@code false}
 *          otherwise
 * 
 * @throws AssertionError if {@code condition} is {@code true}.
 */
stock bool: assertFalse(bool: condition, Logger: logger) {
  if (condition) {
    new fmt[] = "AssertionError: Expected: false, was: true";
    if (logger > Invalid_Logger) {
      LoggerLogError(logger, fmt);
    } else {
      log_error(AMX_ERR_PARAMS, fmt);
    }
    
    return false;
  }

  return true;
}
/**
 * This file contains utility functions to test parameters.
 */

#if defined _param_stocks_included
  #endinput
#endif
#define _param_stocks_included

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

/**
 * Checks whether or not the {@code actual} number of parameters in a native
 * equals the {@code expected} number of parameters, and logs an error message
 * if they are not.
 *
 * @param expected The number of parameters expected
 * @param actual   The actual number of parameters
 * @param logger   The logger to log the error message (if any) to, otherwise
 *                   {@code Invalid_Logger} to log the error message to the AMXX
 *                   error log
 * 
 * @return {@code true} if the {@code actual} number of parameters equals the
 *         {@code expected} number of parameters, {@code false} otherwise.
 * 
 * @throws AssertionException if the {@code actual} number of parameters does
 *         not equal the {@code expected} number of parameters.
 */
stock bool: numParamsEqual(expected, actual, Logger: logger = Invalid_Logger) {
  if (actual == expected) {
    return true;
  }

  new fmt[] = "AssertionError: Expected %d params, was %d";
  if (logger > Invalid_Logger) {
    LoggerLogError(logger, fmt, expected, actual);
  } else {
    log_error(AMX_ERR_PARAMS, fmt, expected, actual);
  }

  return false;
}

/**
 * Checks whether or not the {@code actual} number of parameters in a native
 * equals {@code 0} parameters, and logs an error message if they are not.
 *
 * @param actual   The actual number of parameters
 * @param logger   The logger to log the error message (if any) to, otherwise
 *                   {@code Invalid_Logger} to log the error message to the AMXX
 *                   error log
 * 
 * @return {@code true} if the {@code actual} number of parameters equals
 *         {@code 0}, {@code false} otherwise.
 * 
 * @throws AssertionException if the {@code actual} number of parameters does
 *         not equal {@code 0}.
 */
stock bool: hasNoParams(actual, Logger: logger = Invalid_Logger) {
  return numParamsEqual(0, actual);
}

/**
 * Checks whether or not the {@code actual} number of parameters in a native
 * is less than the {@code maximum} number of parameters, and logs an error
 * message if they are not.
 *
 * @param maximum  The maximum of parameters expected, plus one
 * @param actual   The actual number of parameters
 * @param logger   The logger to log the error message (if any) to, otherwise
 *                   {@code Invalid_Logger} to log the error message to the AMXX
 *                   error log
 * 
 * @return {@code true} if the {@code actual} number of parameters is less than
 *         the {@code maximum} number of parameters, {@code false} otherwise.
 * 
 * @throws AssertionException if the {@code actual} number of parameters is
 *         greater than or equal to the {@code maximum} number of parameters.
 */
stock bool: numParamsFewer(maximum, actual, Logger: logger = Invalid_Logger) {
  if (actual < maximum) {
    return true;
  }

  new fmt[] = "AssertionError: Expected fewer than %d params, was %d";
  if (logger > Invalid_Logger) {
    LoggerLogError(logger, fmt, maximum, actual);
  } else {
    log_error(AMX_ERR_PARAMS, fmt, maximum, actual);
  }

  return false;
}

/**
 * Checks whether or not the {@code actual} number of parameters in a native
 * is less than or equal to the {@code maximum} number of parameters, and logs
 * an error message if they are not.
 *
 * @param maximum  The maximum of parameters expected
 * @param actual   The actual number of parameters
 * @param logger   The logger to log the error message (if any) to, otherwise
 *                   {@code Invalid_Logger} to log the error message to the AMXX
 *                   error log
 * 
 * @return {@code true} if the {@code actual} number of parameters is less than
 *         or equal to the {@code maximum} number of parameters, {@code false}
 *         otherwise.
 * 
 * @throws AssertionException if the {@code actual} number of parameters is
 *         greater than the {@code maximum} number of parameters.
 */
stock bool: numParamsFewerEqual(maximum, actual, Logger: logger = Invalid_Logger) {
  return numParamsFewer(logger, maximum + 1, test);
}

/**
 * Checks whether or not the {@code actual} number of parameters in a native
 * is greater than the {@code minimum} number of parameters, and logs an error
 * message if they are not.
 *
 * @param minimum  The minimum of parameters expected, minus one
 * @param actual   The actual number of parameters
 * @param logger   The logger to log the error message (if any) to, otherwise
 *                   {@code Invalid_Logger} to log the error message to the AMXX
 *                   error log
 * 
 * @return {@code true} if the {@code actual} number of parameters is greater
 *         than the {@code minimum} number of parameters, {@code false}
 *         otherwise.
 * 
 * @throws AssertionException if the {@code actual} number of parameters is
 *         less than the {@code minimum} number of parameters.
 */
stock bool: numParamsGreater(minimum, actual, Logger: logger = Invalid_Logger) {
  if (actual > minimum) {
    return true;
  }

  new fmt[] = "AssertionError: Expected more than %d params, was %d";
  if (logger > Invalid_Logger) {
    LoggerLogError(logger, fmt, minimum, actual);
  } else {
    log_error(AMX_ERR_PARAMS, fmt, minimum, actual);
  }

  return false;
}

/**
 * Checks whether or not the {@code actual} number of parameters in a native
 * is greater than or equal to the {@code minimum} number of parameters, and
 * logs an error message if they are not.
 *
 * @param minimum  The minimum of parameters expected
 * @param actual   The actual number of parameters
 * @param logger   The logger to log the error message (if any) to, otherwise
 *                   {@code Invalid_Logger} to log the error message to the AMXX
 *                   error log
 * 
 * @return {@code true} if the {@code actual} number of parameters is greater
 *         than or equal to the {@code minimum} number of parameters,
 *         {@code false} otherwise.
 * 
 * @throws AssertionException if the {@code actual} number of parameters is
 *         less than the {@code minimum} number of parameters.
 */
stock bool: numParamsGreaterEqual(minimum, actual, Logger: logger = Invalid_Logger) {
    return numParamsGreater(logger, minimum - 1, test);
}

/**
 * Checks whether or not the {@code actual} number of parameters in a native is
 * between the given range (specified by {@code [minimum..maximum]}), and logs
 * an error message if they are not.
 * 
 * @param minimum  The minimum of parameters expected (inclusive)
 * @param maximum  The maximum of parameters expected (inclusive)
 * @param actual   The actual number of parameters
 * @param logger   The logger to log the error message (if any) to, otherwise
 *                   {@code Invalid_Logger} to log the error message to the AMXX
 *                   error log
 * 
 * @return {@code true} if the {@code actual} number of parameters is in the
 *         specified range, {@code false} otherwise.
 * 
 * @throws AssertionException if the {@code actual} number of parameters is
 *         not in the specified range.
 */
stock bool: numParamsInRange(minimum, maximum, actual, Logger: logger = Invalid_Logger) {
  if (minimum > maximum) {
    new fmt[] = "IllegalArgumentException: minimum (%d) must be less than maximum (%d)";
    if (logger > Invalid_Logger) {
      LoggerLogError(logger, fmt, minimum, maximum);
    } else {
      log_error(AMX_ERR_PARAMS, fmt, minimum, maximum);
    }

    return false;
  }

  if (minimum <= actual && actual <= maximum) {
    return true;
  }

  new fmt[] = "AssertionError: Expected %d to %d params, was %d";
  if (logger > Invalid_Logger) {
    LoggerLogError(logger, fmt, minimum, maximum, actual);
  } else {
    log_error(AMX_ERR_PARAMS, fmt, minimum, maximum, actual);
  }

  return false;
}

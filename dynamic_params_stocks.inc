/**
 * This file contains utility functions to test parameters.
 */

#if defined _dynamic_params_stocks_included
  #endinput
#endif
#define _dynamic_params_stocks_included

stock IllegalArgumentException(const fmt[], any:...) {
  new message[192] = "IllegalArgumentException: ";
  format_args(message[26], 191 - 26, 1);
  return message;
}

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

stock bool: numParamsEqual(expected, actual, const Logger: logger = Invalid_Logger) {
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

stock bool: hasNoParams(actual, const Logger: logger = Invalid_Logger) {
  return numParamsEqual(0, actual);
}

stock bool: numParamsFewer(minimum, actual, const Logger: logger = Invalid_Logger) {
  if (actual < minimum) {
    return true;
  }

  new fmt[] = "AssertionError: Expected fewer than %d params, was %d";
  if (logger > Invalid_Logger) {
    LoggerLogError(logger, fmt, minimum, actual);
  } else {
    log_error(AMX_ERR_PARAMS, fmt, minimum, actual);
  }

  return false;
}

stock bool: numParamsFewerEqual(minimum, actual, const Logger: logger = Invalid_Logger) {
  return numParamsFewer(logger, min + 1, test);
}

stock bool: numParamsGreater(maximum, actual, const Logger: logger = Invalid_Logger) {
  if (actual > maximum) {
    return true;
  }

  new fmt[] = "AssertionError: Expected more than %d params, was %d";
  if (logger > Invalid_Logger) {
    LoggerLogError(logger, fmt, maximum, actual);
  } else {
    log_error(AMX_ERR_PARAMS, fmt, maximum, actual);
  }

  return false;
}

stock bool: numParamsGreaterEqual(maximum, actual, const Logger: logger = Invalid_Logger) {
    return numParamsGreater(logger, max - 1, test);
}

stock bool: numParamsInRange(minimum, maximum, actual, const Logger: logger = Invalid_Logger) {
  if (minimum > maximum) {
    new fmt[] = "IllegalArgumentException: max(%d) < min(%d)";
    if (logger > Invalid_Logger) {
      LoggerLogError(logger, fmt, maximum, minimum);
    } else {
      LoggerLogError(logger, fmt, maximum, minimum);
    }

    return false;
  }

  if (actual >= minimum && actual <= maximum) {
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

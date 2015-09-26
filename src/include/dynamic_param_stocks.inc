#if defined _dynamic_param_stocks_included
    #endinput
#endif
#define _dynamic_param_stocks_included

#include <logger>

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

stock bool: numParamsEqual(Logger: logger, expectation, test) {
    if (test == expectation) {
        return true;
    }

    LoggerLogError(logger, "Expected %d params, found %d.", expectation, test);
    return false;
}

stock bool: numParamsFewer(Logger: logger, min, test) {
    if (test < min) {
        return true;
    }

    LoggerLogError(logger, "Expected fewer than %d params, found %d.", min, test);
    return false;
}

stock bool: numParamsFewerEqual(Logger: logger, min, test) {
    return numParamsFewer(logger, min+1, test);
}

stock bool: numParamsGreater(Logger: logger, max, test) {
    if (test > max) {
        return true;
    }

    LoggerLogError(logger, "Expected greater than %d params, found %d.", max, test);
    return false;
}

stock bool: numParamsGreaterEqual(Logger: logger, max, test) {
    return numParamsGreater(logger, max-1, test);
}

stock bool: numParamsInRange(Logger: logger, min, max, test) {
    if (min > max) {
        LoggerLogError(logger, "Illegal argument exception! max(%d) < min(%d)", max, min);
        return false;
    }

    if (test >= min && test <= max) {
        return true;
    }

    LoggerLogError(logger, "Expected %d to %d params, found %d.", min, max, test);
    return false;
}
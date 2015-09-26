#if defined _flag_stocks_included
    #endinput
#endif
#define _flag_stocks_included

#include <logger>
#include "include/exceptions.inc"

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

stock Exception: checkArguments(Logger: logger, flag) {
    if (flag <= 0) {
        return throw(logger, IllegalArgumentException, "flag must be > 0; flag=%d", flag);
    } else if (flag > cellbits) {
        return throw(logger, IllegalArgumentException, "flag must be <= %d; flag=%d", cellbits, flag);
    }

    return Success;
}

/**
 * 
 */
stock Exception: getFlag(Logger: logger, val, flag, &i) {
    new Exception: exceptiion = checkArguments(logger, flag);
    if (exceptiion) {
        return exceptiion;
    }

    i = val & (1<<(flag-1));
    return Success;
}

/**
 * 
 */
stock Exception: isFlagSet(Logger: logger, val, flag, &bool: b) {
    new i;
    new Exception: exception = getFlag(logger, val, flag, i);
    if (exception) {
        return exception;
    }
    
    b = (i != 0);
    return Success;
}

/**
 * 
 */
stock Exception: setFlag(Logger: logger, &val, flag) {
    new Exception: exception = checkArguments(logger, flag);
    if (exception) {
        return exception;
    }

    val |= (1<<(flag-1));
    return Success;
}

/**
 * 
 */
stock Exception: unsetFlag(Logger: logger, &val, flag) {
    new Exception: exception = checkArguments(logger, flag);
    if (exception) {
        return exception;
    }

    val &= ~(1<<(flag-1));
    return Success;
}

/**
 * 
 */
stock Exception: toggleFlag(Logger: logger, &val, flag) {
    new Exception: exception = checkArguments(logger, flag);
    if (exception) {
        return exception;
    }

    val ^= (1<<(flag-1));
    return Success;
}
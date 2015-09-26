#if defined _exceptions_included
    #endinput
#endif
#define _exceptions_included

#include <logger>

static stock buffer[256];

enum Exception {
    Success = 0,
    IllegalArgumentException
};

stock const EXCEPTION[Exception][] = {
    "",
    "IllegalArgumentException"
};

stock Exception: throw(const Logger: logger, const Exception: exception, const format[] = "", any: ...) {
    if (isStringEmpty(format)) {
        LoggerLogError(logger, EXCEPTION[exception]);
    } else {
        vformat(buffer, charsmax(buffer), format, 4);
        LoggerLogError(logger, "%s: %s", EXCEPTION[exception], buffer);
    }

    return exception;
}
#if defined _flag_stocks_included
    #endinput
#endif
#define _flag_stocks_included

#include <logger>

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

/**
 * Checks if the passed flag is valid for a bit field and throws {@link
 * exception_handler#IllegalArgumentException} if it is not.
 * 
 * @param flag Bit to check, value between {@literal 1} and {@link #cellbits}
 *                 (inclusive)
 * 
 * @return {@literal true} if the passed bit is valid, otherwise {@literal
 *         false}
 * 
 * @throws IllegalArgumentException when the bit is not valid.
 */
static stock bool: checkFlag(const Logger: logger = Invalid_Logger, flag) {
    if (flag <= 0) {
        if (logger != Invalid_Logger) {
            LoggerLogError(logger,
                    "IllegalArgumentException: flag must be > 0; flag=%d",
                    flag);
        } else {
            log_error(AMX_ERR_PARAMS,
                    "IllegalArgumentException: flag must be > 0; flag=%d",
                    flag);
        }

        return false;
    } else if (flag > cellbits) {
        if (logger != Invalid_Logger) {
            LoggerLogError(logger,
                    "IllegalArgumentException: flag must be <= %d; flag=%d",
                    cellbits,
                    flag);
        } else {
            log_error(AMX_ERR_PARAMS,
                    "IllegalArgumentException: flag must be <= %d; flag=%d",
                    cellbits,
                    flag);
        }

        return false;
    }

    return true;
}

/**
 * Returns the bitwise-and for the given bit in the passed field.
 * 
 * @param field Bitwise field to use
 * @param flag  Bit from the field to perform a bitwise-and with
 * 
 * @return bitwise-and of the bit in the given field
 * 
 * @throws IllegalArgumentException when the bit is not valid.
 * 
 * @see #isFlagSet(cell,cell);
 */
stock getFlag(const Logger: logger = Invalid_Logger, field, flag) {
    checkFlag(logger, flag);
    return field & (1<<(flag-1));
}

/**
 * Returns whether or not the given bit is set (i.e., {@literal 1}) in the
 * passed field.
 * 
 * @param field Bitwise field to use
 * @param flag  Bit from the field to perform a bitwise-and with and check to
 *                  see if nonzero
 * 
 * @return whether or not the given bit is set
 * 
 * @throws IllegalArgumentException when the bit is not valid.
 * 
 * @see #getFlag(cell,cell);
 */
stock bool: isFlagSet(const Logger: logger = Invalid_Logger, field, flag) {
    return getFlag(logger, field, flag) != 0;
}

/**
 * Sets the given bit in the passed field.
 * 
 * @param field Bitwise field to use
 * @param flag  Bit in the field to set to {@literal 1}
 * 
 * @return the new value of the field
 * 
 * @throws IllegalArgumentException when the bit is not valid.
 */
stock setFlag(const Logger: logger = Invalid_Logger, &field, flag) {
    checkFlag(logger, flag);
    return field |= (1<<(flag-1));
}

/**
 * Resets the given bit in the passed field.
 * 
 * @param field Bitwise field to use
 * @param flag  Bit in the field to set to {@literal 0}
 * 
 * @return the new value of the field
 * 
 * @throws IllegalArgumentException when the bit is not valid.
 */
stock unsetFlag(const Logger: logger = Invalid_Logger, &field, flag) {
    checkFlag(logger, flag);
    return field &= ~(1<<(flag-1));
}

/**
 * Toggles the given bit in the passed field.
 * 
 * @param field Bitwise field to use
 * @param flag  Bit in the field to toggle (i.e., change from {@literal 0} to
 *                  {@literal 1} or from {@literal 1} to {@literal 0}).
 * 
 * @return the new value of the field
 * 
 * @throws IllegalArgumentException when the bit is not valid.
 */
stock toggleFlag(const Logger: logger = Invalid_Logger, &field, flag) {
    checkFlag(logger, flag);
    return field ^= (1<<(flag-1));
}

/**
 * Macro definition of {@link #isFlagSet}
 */
stock bool: areFlagsSet(const Logger: logger = Invalid_Logger, field, any: ...) {
    new const numArgs = numargs();
    for (new i = 1; i < numArgs; i++) {
        if (!isFlagSet(logger, field, getarg(i))) {
            return false;
        }
    }

    return true;
}

/**
 * Macro definition of {@code !{@link #isFlagSet}} (i.e., check that none of the
 * specified flags are set.
 */
stock bool: areFlagsNotSet(const Logger: logger = Invalid_Logger, field, any: ...) {
    new const numArgs = numargs();
    for (new i = 1; i < numArgs; i++) {
        if (isFlagSet(logger, field, getarg(i))) {
            return false;
        }
    }

    return true;
}

/**
 * Macro definition of {@link #setFlag}
 */
stock setFlags(const Logger: logger = Invalid_Logger, &field, any: ...) {
    new const numArgs = numargs();
    for (new i = 1; i < numArgs; i++) {
        setFlag(logger, field, getarg(i));
    }

    return field;
}

/**
 * Macro definition of {@link #unsetFlag}
 */
stock unsetFlags(const Logger: logger = Invalid_Logger, &field, any: ...) {
    new const numArgs = numargs();
    for (new i = 1; i < numArgs; i++) {
        unsetFlag(logger, field, getarg(i));
    }

    return field;
}

/**
 * Macro definition of {@link #toggleFlag}
 */
stock toggleFlags(const Logger: logger = Invalid_Logger, &field, any: ...) {
    new const numArgs = numargs();
    for (new i = 1; i < numArgs; i++) {
        toggleFlag(logger, field, getarg(i));
    }

    return field;
}

/**
 * Check if one and only one of the passed flags is set in the given field and
 * returns the bit which is set.
 *
 * @param field Bitwise field to use
 *
 * @return bit number which is set, or {@literal 0} if none or more than one is
 *         set
 *
 * @see #isXorFlag
 */
stock getXorFlag(const Logger: logger = Invalid_Logger, field, any: ...) {
    new flag = 0;
    new const numArgs = numargs();
    for (new i = 1, arg = getarg(i); i < numArgs; arg = getarg(++i)) {
        if (isFlagSet(logger, field, arg)) {
            switch (flag) {
                case 0: flag = arg;
                default: return 0;
            }
        }
    }

    return flag;
}

/**
 * Check if one and only one of the passed flags is set in the given field.
 *
 * @param field Bitwise field to use
 *
 * @return {@literal true} if one and only one flag is set, otherwise {@literal
 *         false}
 *
 * @see #getXorFlag
 */
stock bool: isXorFlag(const Logger: logger = Invalid_Logger, field, any: ...) {
    new flag = 0;
    new const numArgs = numargs();
    for (new i = 1, arg = getarg(i); i < numArgs; arg = getarg(++i)) {
        if (isFlagSet(logger, field, arg)) {
            switch (flag) {
                case 0: flag = arg;
                default: return false;
            }
        }
    }

    return flag > 0;
}
#if defined _flag_stocks_included
    #endinput
#endif
#define _flag_stocks_included

#include <logger>
#include <exception_handler>

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
static stock bool: checkFlag(flag) {
    if (flag <= 0) {
        Throw(IllegalArgumentException,
                "flag must be > 0; flag=%d",
                flag);
        return false;
    } else if (flag > cellbits) {
        Throw(IllegalArgumentException,
                "flag must be <= %d; flag=%d",
                cellbits,
                flag);
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
stock getFlag(field, flag) {
    checkFlag(flag);
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
stock bool: isFlagSet(field, flag) {
    return getFlag(field, flag) != 0;
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
stock setFlag(&field, flag) {
    checkFlag(flag);
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
stock unsetFlag(&field, flag) {
    checkFlag(flag);
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
stock toggleFlag(&field, flag) {
    checkFlag(flag);
    return field ^= (1<<(flag-1));
}

stock bool: areFlagsSet(field, any: ...) {
    new const numArgs = numargs();
    for (new i = 1; i < numArgs; i++) {
        if (!isFlagSet(field, getarg(i))) {
            return false;
        }
    }

    return true;
}

stock setFlags(&field, any: ...) {
    new const numArgs = numargs();
    for (new i = 1; i < numArgs; i++) {
        setFlag(field, getarg(i));
    }

    return field;
}

stock unsetFlags(&field, any: ...) {
    new const numArgs = numargs();
    for (new i = 1; i < numArgs; i++) {
        unsetFlags(field, getarg(i));
    }

    return field;
}

stock toggleFlags(&field, any: ...) {
    new const numArgs = numargs();
    for (new i = 1; i < numArgs; i++) {
        toggleFlag(field, getarg(i));
    }

    return field;
}

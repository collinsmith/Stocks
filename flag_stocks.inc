/**
 * This file contains utility functions to manipulate and check flags within a
 * bit field (a cell where each bit represents a boolean value which is
 * interpreted as {@code true} if set and {@code false} if unset).
 * 
 * Flags are one-based, meaning they are in the range {@code [1..cellbits]}
 * (inclusive).
 */

#if defined _flag_stocks_included
  #endinput
#endif
#define _flag_stocks_included

#tryinclude "include/stocks/exception_stocks.inc"
#if !defined _exception_stocks_included
  #include <exception_stocks>
#endif

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

/**
 * Indicates whether or not the passed flag is valid for a bit field.
 * 
 * @param flag   The bit to check, should be in the range {@code [1..cellbits]}
 *                 (inclusive)
 * 
 * @throws IllegalArgumentException if {@code flag} is invalid.
 */
stock bool: checkFlag(flag) {
  if (flag <= 0) {
    ThrowIllegalArgumentException("flag must be > 0; flag=%d", flag);
    return false;
  } else if (flag > cellbits) {
    ThrowIllegalArgumentException("flag must be <= %d; flag=%d", cellbits, flag);
    return false;
  }

  return true;
}

/**
 * Returns the bitwise-and for the given flag in the passed field.
 * 
 * @param field  The bitwise field to check
 * @param flag   The bit to check, should be in the range {@code [1..cellbits]}
 *                 (inclusive)
 * 
 * @return The bitwise-and of the flag and the given field
 * 
 * @throws IllegalArgumentException if {@code flag} is invalid.
 * 
 * @see #isFlagSet
 */
stock getFlag(field, flag) {
  checkFlag(flag);
  return field & (1 << (flag - 1));
}

/**
 * Indicates whether or not the given {@code flag} is set in the passed bit
 * {@code field}.
 * 
 * @param field  The bitwise field to check
 * @param flag   The bit to check, should be in the range {@code [1..cellbits]}
 *                 (inclusive)
 * 
 * @return {@code true} if the flag is set, {@code false} otherwise
 * 
 * @throws IllegalArgumentException if {@code flag} is invalid.
 * 
 * @see #getFlag
 */
stock bool: isFlagSet(field, flag) {
  return getFlag(field, flag) != 0;
}

/**
 * Sets the given {@code flag} in the passed {@code field}.
 * 
 * @param field  The bitwise field to set {@code flag}.
 * @param flag   The bit to set
 * 
 * @return The new value of {@code field}. Note that {@code field} is also
 *         changed as a result of this call.
 * 
 * @throws IllegalArgumentException if {@code flag} is invalid.
 */
stock setFlag(&field, flag) {
  checkFlag(flag);
  return field |= (1 << (flag - 1));
}

/**
 * Unsets the given {@code flag} in the passed {@code field}.
 * 
 * @param field  The bitwise field to unset {@code flag}.
 * @param flag   The bit to unset
 * 
 * @return The new value of {@code field}. Note that {@code field} is also
 *         changed as a result of this call
 * 
 * @throws IllegalArgumentException if {@code flag} is invalid.
 */
stock unsetFlag(&field, flag) {
  checkFlag(flag);
  return field &= ~(1 << (flag - 1));
}

/**
 * Toggles the given {@code flag} in the passed {@code field}.
 * 
 * @param field  The bitwise field to toggle {@code flag}.
 * @param flag   The bit to toggle
 * 
 * @return The new value of {@code field}. Note that {@code field} is also
 *         changed as a result of this call
 * 
 * @throws IllegalArgumentException if {@code flag} is invalid.
 */
stock toggleFlag(&field, flag) {
  checkFlag(flag);
  return field ^= (1 << (flag - 1));
}

stock bool: areFlagsSet(field, any: ...) {
  new const numArgs = numargs();
  for (new i = 2; i < numArgs; i++) {
    if (!isFlagSet(field, getarg(i))) {
      return false;
    }
  }

  return true;
}

stock bool: areFlagsNotSet(field, any: ...) {
  new const numArgs = numargs();
  for (new i = 2; i < numArgs; i++) {
    if (isFlagSet(field, getarg(i))) {
      return false;
    }
  }

  return true;
}

stock setFlags(&field, any: ...) {
  new const numArgs = numargs();
  for (new i = 2; i < numArgs; i++) {
    setFlag(field, getarg(i));
  }

  return field;
}

stock unsetFlags(&field, any: ...) {
  new const numArgs = numargs();
  for (new i = 2; i < numArgs; i++) {
    unsetFlag(field, getarg(i));
  }

  return field;
}

stock toggleFlags(&field, any: ...) {
  new const numArgs = numargs();
  for (new i = 2; i < numArgs; i++) {
    toggleFlag(field, getarg(i));
  }

  return field;
}

/**
 * Indicates if one and only one of the passed flags is set in the given field
 * and returns the bit which is set.
 *
 * @param field The bitwise field to check
 *
 * @return The bit number which is set, or {@code 0} if none or more than one is
 *         set
 *
 * @see #isXorFlag
 */
stock getXorFlag(field, any: ...) {
  new flag = 0;
  new const numArgs = numargs();
  for (new i = 2, arg = getarg(i); i < numArgs; arg = getarg(++i)) {
    if (isFlagSet(field, arg)) {
      switch (flag) {
        case 0: flag = arg;
        default: return 0;
      }
    }
  }

  return flag;
}

/**
 * Indicates if one and only one of the passed flags is set in the given field.
 *
 * @param field The bitwise field to check
 *
 * @return {@code true} if one and only one flag is set, {@code false} otherwise
 *
 * @see #getXorFlag
 */
stock bool: isXorFlag(field, any: ...) {
  new flag = 0;
  new const numArgs = numargs();
  for (new i = 2, arg = getarg(i); i < numArgs; arg = getarg(++i)) {
    if (isFlagSet(field, arg)) {
      switch (flag) {
        case 0: flag = arg;
        default: return false;
      }
    }
  }

  return flag > 0;
}

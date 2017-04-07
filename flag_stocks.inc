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

#tryinclude "../exception_stocks.inc"
#tryinclude "stocks/exception_stocks.inc"
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
 * @param logger The logger to output any error messages to,
 *                 or {@code Invalid_Logger} to output error messages directly
 *                 into the AMXX log file
 * 
 * @throws IllegalArgumentException if {@code flag} is invalid.
 */
stock bool: checkFlag(flag, Logger: logger = Invalid_Logger) {
  if (flag <= 0) {
    ThrowIllegalArgumentException(logger, "flag must be > 0; flag=%d", flag);
    return false;
  } else if (flag > cellbits) {
    ThrowIllegalArgumentException(logger, "flag must be <= %d; flag=%d", cellbits, flag);
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
 * @param logger The logger to output any error messages to,
 *                 or {@code Invalid_Logger} to output error messages directly
 *                 into the AMXX log file
 * 
 * @return The bitwise-and of the flag and the given field
 * 
 * @throws IllegalArgumentException if {@code flag} is invalid.
 * 
 * @see #isFlagSet
 */
stock getFlag(field, flag, Logger: logger = Invalid_Logger) {
  checkFlag(flag, logger);
  return field & (1 << (flag - 1));
}

/**
 * Indicates whether or not the given {@code flag} is set in the passed bit
 * {@code field}.
 * 
 * @param field  The bitwise field to check
 * @param flag   The bit to check, should be in the range {@code [1..cellbits]}
 *                 (inclusive)
 * @param logger The logger to output any error messages to,
 *                 or {@code Invalid_Logger} to output error messages directly
 *                 into the AMXX log file
 * 
 * @return {@code true} if the flag is set, {@code false} otherwise
 * 
 * @throws IllegalArgumentException if {@code flag} is invalid.
 * 
 * @see #getFlag
 */
stock bool: isFlagSet(field, flag, Logger: logger = Invalid_Logger) {
  return getFlag(field, flag, logger) != 0;
}

/**
 * Sets the given {@code flag} in the passed {@code field}.
 * 
 * @param field  The bitwise field to set {@code flag}.
 * @param flag   The bit to set
 * @param logger The logger to output any error messages to,
 *                 or {@code Invalid_Logger} to output error messages directly
 *                 into the AMXX log file
 * 
 * @return The new value of {@code field}. Note that {@code field} is also
 *         changed as a result of this call.
 * 
 * @throws IllegalArgumentException if {@code flag} is invalid.
 */
stock setFlag(&field, flag, Logger: logger = Invalid_Logger) {
  checkFlag(flag, logger);
  return field |= (1 << (flag - 1));
}

/**
 * Unsets the given {@code flag} in the passed {@code field}.
 * 
 * @param field  The bitwise field to unset {@code flag}.
 * @param flag   The bit to unset
 * @param logger The logger to output any error messages to,
 *                 or {@code Invalid_Logger} to output error messages directly
 *                 into the AMXX log file
 * 
 * @return The new value of {@code field}. Note that {@code field} is also
 *         changed as a result of this call
 * 
 * @throws IllegalArgumentException if {@code flag} is invalid.
 */
stock unsetFlag(&field, flag, Logger: logger = Invalid_Logger) {
  checkFlag(flag, logger);
  return field &= ~(1 << (flag - 1));
}

/**
 * Toggles the given {@code flag} in the passed {@code field}.
 * 
 * @param field  The bitwise field to toggle {@code flag}.
 * @param flag   The bit to toggle
 * @param logger The logger to output any error messages to,
 *                 or {@code Invalid_Logger} to output error messages directly
 *                 into the AMXX log file
 * 
 * @return The new value of {@code field}. Note that {@code field} is also
 *         changed as a result of this call
 * 
 * @throws IllegalArgumentException if {@code flag} is invalid.
 */
stock toggleFlag(&field, flag, Logger: logger = Invalid_Logger) {
  checkFlag(flag, logger);
  return field ^= (1 << (flag - 1));
}
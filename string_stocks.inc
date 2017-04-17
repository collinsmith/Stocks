/**
 * This file contains utility functions that can be used when dealing with
 * strings.
 */

#if defined _string_stocks_included
  #endinput
#endif
#define _string_stocks_included

/*******************************************************************************
 * MACROS
 ******************************************************************************/

/**
 * Indicates whether or not the passed string is empty using the logical macro
 * {@code str[0] == EOS}.
 * 
 * @param %1 The string to test
 * 
 * @return {@code true} if the string is empty, {@code false} otherwise
 */
#define isStringEmpty(%1)\
  (%1[0] == EOS)

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

/**
 * Joins a series of strings together.
 * 
 * @example stringJoin(dst, _, "[", ",", "]", "1", "2", "3");
 *          dst = "[1,2,3]"
 *
 * @example stringJoin(dst, _, "[", ",", "]");
 *          dst = "[]"
 * 
 * @example stringJoin(dst, _, "", "/", "", "models", "player", "gign", "gign.mdl");
 *          dst = "models/player/gign/gign.mdl"
 * 
 * @param dst     Destination buffer to copy into
 * @param len     Maximum number of bytes to copy
 * @param prefix  String to preceed result with
 * @param infix   String to place in-between two joined strings
 * @param postfix String to follow result with
 * @param ...     Strings to join together
 * 
 * @return Number of bytes copied.
 */
stock stringJoin(dst[], len, const prefix[] = "[", const infix[] = ",", const postfix[] = "]", ...) {
  new const maxLen = len;
  len = copy(dst, maxLen, prefix);
  
  new const numArgs = numargs();
  for (new i = 5; i < numArgs && len <= maxLen; i++) {
    if (i > 5) {
      len += copy(dst[len], maxLen - len, infix);
    }

    for (new j = 0, ch = getarg(i, j); ch != EOS && len <= maxLen; ch = getarg(i, ++j)) {
      dst[len++] = ch;
    }
  }

  len += copy(dst[len], maxLen - len, postfix);
  dst[len] = EOS;
  return len;
}

/**
 * Copies a given string into a buffer if it is non-empty, or copies the default
 * parameter instead in the case where it is empty.
 * 
 * @param dst Destination buffer to copy into
 * @param len Maximum number of bytes to copy
 * @param str String to test
 * @param def Default value to copy if {@param str} is empty
 * 
 * @return Number of bytes copied.
 */
stock stringGetOrDefault(dst[], len, const str[], const def[]) {
  if (isStringEmpty(str)) {
    return copy(dst, len, def);
  }

  return copy(dst, len, str);
}

/**
 * Tests whether or not a given string starts with a specified string.
 * 
 * @param str        The string to check
 * @param startsWith The test string to check if {@param str} starts with
 * 
 * @return {@literal true} if it does, otherwise {@code false}
 */
stock bool: stringStartsWith(const str[], const startsWith[]) {
  return equal(str, startsWith) == 1;
}
/**
 * 
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
  new tempLen = copy(dst, len, prefix);
  new numArgs = numargs();
  for (new i = 5; i < numArgs && tempLen <= len; i++) {
    if (i > 5) {
      tempLen += copy(dst[tempLen], len - tempLen, infix);
    }

    for (new j = 0, ch = getarg(i, j); ch != EOS && tempLen <= len; ch = getarg(i, ++j)) {
      dst[tempLen++] = ch;
    }
  }

  tempLen += copy(dst[tempLen], len - tempLen, postfix);
  dst[tempLen] = EOS;
  return tempLen;
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
stock stringGetOrDefault(dst[], len = sizeof dst, const str[], const def[]) {
  if (isStringEmpty(str)) {
    return copy(dst, len, def);
  }

  return copy(dst, len, str);
}

/**
 * Tests whether or not a given string starts with a specified string.
 * 
 * @param str  String to check
 * @param test Test string to check if {@param str} starts with
 * 
 * @return {@literal true} if it does, otherwise {@code false}
 */
stock bool: stringStartsWith(const str[], const test[]) {
  new i, c1, c2;
  for (i = 0, c1 = str[i], c2 = test[i];
      c1 == c2 && c1 != EOS && c2 != EOS;
      i++, c1 = str[i], c2 = test[i]) {
  }

  return c2 == EOS;
}
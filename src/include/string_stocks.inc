#if defined _string_stocks_included
    #endinput
#endif
#define _string_stocks_included

#include <string>

/*******************************************************************************
 * MACROS
 ******************************************************************************/

/**
 * Tests whether or not the passed zero terminated array is zero using the logic
 * that {@code str[0] == EOS}.
 * 
 * @param %1 string to test
 * 
 * @return {@literal true} if it is, otherwise {@literal false}
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
 * @param len     Maximum number of bytes to copy (will zero terminate at len-1)
 * @param prefix  String to preceed result with
 * @param infix   String to place in-between two joined strings
 * @param postfix String to follow result with
 * @param ...     Strings to join together
 * 
 * @return Number of bytes copied.
 */
stock stringJoin(dst[], len = sizeof dst, const prefix[] = "[", const infix[] = ",", const postfix[] = "]", ...) {
    new tempLen = copy(dst, len, prefix);
    new numArgs = numargs();
    for (new i = 5; i < numArgs && tempLen < len; i++) {
        if (i > 5) {
            tempLen += copy(dst[tempLen], len-tempLen, infix);
        }

        for (new j = 0, ch = getarg(i, j); ch != EOS && tempLen < len; ch = getarg(i, ++j)) {
            dst[tempLen++] = ch;
        }
    }

    tempLen += copy(dst[tempLen], len-tempLen, postfix);
    dst[len-1] = EOS;
    return tempLen-1;
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
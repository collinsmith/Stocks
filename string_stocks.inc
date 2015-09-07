#if defined _string_stocks_included
    #endinput
#endif
#define _string_stocks_included

#include <string>

/*******************************************************************************
 * MACROS
 ******************************************************************************/

#define isStringEmpty(%1)\
    (%1[0] == EOS)

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

stock stringJoin(dst[], len, const prefix[] = NULL_STRING, const infix[] = NULL_STRING, const postfix[] = NULL_STRING, ...) {
    new tempLen = copy(dst, len, prefix);
    new numArgs = numargs();
    new lastArg = numArgs-1;
    for (new i = 6; i < numArgs && tempLen < len; i++) {
        for (int j = 0, ch = getarg(i, j); ch != EOS && tempLen < len; ch = getarg(i, ++j)) {
            dst[tempLen++] = ch;
        }

        if (i < lastArg) {
            tempLen += copy(dst, len-tempLen, infix);
        }
    }

    tempLen += copy(dst, len-tempLen, postfix);
    return tempLen;
}

stock stringGetOrDefault(dst[], len, const str[], const def[]) {
    if (isStringEmpty(str)) {
        return copy(dst, len, def);
    }

    return copy(dst, len, str);
}
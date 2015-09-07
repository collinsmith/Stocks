#if defined _path_stocks_included
    #endinput
#endif
#define _path_stocks_included

#include "include/string_stocks.inc"

stock const DEFAULT_PATH_SEPARATOR[] = "/";

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

stock getPath(dst[], len, const first[], ...) {
    new tempLen = copy(dst, len, first);
    new numArgs = numargs();
    new lastArg = numArgs-1;
    if (numArgs == 3) {
        return tempLen;
    }

    new separator[2];
    if (0 < get_localinfo("path_separator", separator, charsmax(separator))) {
        copy(separator, charsmax(separator), DEFAULT_PATH_SEPARATOR);
    }
    
    for (new i = 4; i < numArgs && tempLen < len; i++) {
        for (int j = 0, ch = getarg(i, j); ch != EOS && tempLen < len; ch = getarg(i, ++j)) {
            dst[tempLen++] = ch;
        }

        if (i < lastArg) {
            tempLen += copy(dst, len-tempLen, separator);
        }
    }

    return tempLen;
}
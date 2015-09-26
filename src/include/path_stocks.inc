#if defined _path_stocks_included
    #endinput
#endif
#define _path_stocks_included

#include <file>

#define PATH_SEPARATOR      '/'
#define PATH_SEPARATOR_ALT  '\\'

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

/**
 * Concatenates strings as a formatted path using {@literal PATH_SEPARATOR} as
 * the path separator.
 *
 * @example getPath(temp, sizeof temp, "models", "player", "gign", "gign.mdl");
 *          temp = "models/player/gign/gign.mdl"
 * 
 * @param dst      Destination buffer to copy path into
 * @param len      Size of the buffer (will zero terminate at len-1)
 * @param first... Paths to concatenate
 * 
 * @return Number of bytes copied.
 */
stock getPath(dst[], len = sizeof dst, const first[], ...) {
    new tempLen = copy(dst, len, first);
    new numArgs = numargs();
    if (numArgs == 3) {
        dst[tempLen-1] = EOS;
        return tempLen-1;
    }

    for (new i = 3; i < numArgs && tempLen < len; i++) {
        dst[tempLen++] = PATH_SEPARATOR;
        for (new j = 0, ch = getarg(i, j); ch != EOS && tempLen <= len; ch = getarg(i, ++j)) {
            dst[tempLen++] = ch;
        }
    }

    dst[tempLen-2] = EOS;
    return tempLen-2;
}

/**
 * Checks if the index within a passed string is equal to {@literal
 * PATH_SEPARATOR_ALT} and sets it to {@literal PATH_SEPARATOR}.
 *
 * @example fixPathSeparator("models\player/gign/gign.mdl", 6);
 *          temp = "models/player/gign/gign.mdl"
 *          returns true;
 * 
 * @example fixPathSeparator("models\player/gign/gign.mdl", 13);
 *          temp = "models\player/gign/gign.mdl"
 *          returns true;
 * 
 * @example fixPathSeparator("models\player/gign/gign.mdl", 0);
 *          temp = "models\player/gign/gign.mdl"
 *          returns false;
 * 
 * @param path  String to test a character for
 * @param index Byte within the path to check and fix
 * 
 * @return {@literal true} if the character is a path separator (either 
 *         {@literal PATH_SEPARATOR} or {@literal PATH_SEPARATOR_ALT}),
 *         otherwise {@literal false}
 */
stock bool: fixPathSeparator(path[], index) {
    switch (path[index]) {
        case PATH_SEPARATOR_ALT: {
            path[index] = PATH_SEPARATOR;
            return true;
        }
        case PATH_SEPARATOR: {
            return true;
        }
        default:
            return false;
    }

    return false;
}

/**
 * Fixes a path by replacing all {@literal PATH_SEPARATOR_ALT} characters with
 * {@literal PATH_SEPARATOR}.
 *
 * @example fixPath("models/player/gign/gign.mdl");
 *          "models/player/gign/gign.mdl" -> "models/player/gign/gign.mdl"
 * 
 * @example fixPath("models\player/gign\gign.mdl");
 *          "models\player/gign\gign.mdl" -> "models/player/gign/gign.mdl"
 * 
 * @param path String represented path to fix
 * @param len  Maximum number of bytes to check and fix (skips len-1)
 * 
 * @return Number of bytes checked.
 * 
 * @see #fixPathAndMkdir(cell[],cell)
 */
stock fixPath(path[], len = sizeof path) {
    for (new i = 0; i < len; i++) {
        fixPathSeparator(path, i);
    }

    return len-1;
}

/**
 * Fixes a path by replacing all {@literal PATH_SEPARATOR_ALT} characters with
 * {@literal PATH_SEPARATOR} and created directories for each one as it goes.
 *
 * @example fixPath("models/player/gign/gign.mdl");
 *          "models/player/gign/gign.mdl" -> "models/player/gign/gign.mdl"
 * 
 * @example fixPath("models\player/gign\gign.mdl");
 *          "models\player/gign\gign.mdl" -> "models/player/gign/gign.mdl"
 * 
 * @param path String represented path to fix
 * @param len  Maximum number of bytes to check and fix (skips len-1)
 * 
 * @return Number of bytes checked.
 * 
 * @see #fixPath(cell[],cell)
 */
stock fixPathAndMkdir(path[], len = sizeof path) {
    for (new i = 0; i < len; i++) {
        if (fixPathSeparator(path, i)) {
            path[i] = EOS;
            mkdir(path);
            path[i] = PATH_SEPARATOR;
        }
    }

    return len-1;
}
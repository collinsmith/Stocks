/**
 * This file contains utility functions to build and manipulate file paths.
 */

#if defined _path_stocks_included
  #endinput
#endif
#define _path_stocks_included

#include <file>

#define PATH_SEPARATOR     47 // '/'
#define PATH_SEPARATOR_ALT 92 // '\'

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

/**
 * Concatenates the specified strings formatted as a path using
 * {@value #PATH_SEPARATOR} as the path separator.
 * 
 * For example:
 * {@code getPath(temp, charsmax(temp), "models", "player", "gign", "gign.mdl")}
 * would result in {@code temp} set to {@code "models/player/gign/gign.mdl"}
 * 
 * @param dst   The destination output buffer for the path
 * @param len   The maximum number of character to output
 * @param first The first path to concatenate
 * @param ...   The remaining paths to concatenate
 * 
 * @return The total number of bytes copied
 */
stock getPath(dst[], len, const first[], /*const remaining[][]*/ ...) {
  new tempLen = copy(dst, len, first);
  new numArgs = numargs();
  for (new i = 3; i < numArgs && tempLen <= len; i++) {
    dst[tempLen++] = PATH_SEPARATOR;
    for (new j = 0, ch = getarg(i, j); ch != EOS && tempLen <= len; ch = getarg(i, ++j)) {
      dst[tempLen++] = ch;
    }
  }
  
  dst[tempLen] = EOS;
  return tempLen;
}

/**
 * Checks if the character at the specified {@code index} in {@code path} is
 * equal to {@value #PATH_SEPARATOR_ALT} and sets it to {@value #PATH_SEPARATOR}.
 * 
 * For example:
 * {@code
 *   new temp[] = "models\player/gign/gign.mdl";
 *   fixPathSeparator(temp, 6);
 * }
 * would result in {@code temp} set to {@code "models/player/gign/gign.mdl"}
 * 
 * @param path  The path to test and fix
 * @param index The index within {@code path} to check
 * 
 * @return {@code true} if the character is a path separator (either
 *         {@value #PATH_SEPARATOR} or {@value #PATH_SEPARATOR_ALT}),
 *         {@code false} otherwise
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
 * Fixes the path by replacing all {@value #PATH_SEPARATOR_ALT} characters with
 * {@value #PATH_SEPARATOR}.
 * 
 * For example:
 * {@code
 *   new temp[] = "models\player\gign\gign.mdl";
 *   fixPath(temp);
 * }
 * would result in {@code temp} set to {@code "models/player/gign/gign.mdl"}
 * 
 * @param path The path to test and fix
 * @param len  The maximum number of character to check
 * 
 * @return The total number of bytes checked
 */
stock fixPath(path[], len) {
  for (new i = 0; i <= len; i++) {
    fixPathSeparator(path, i);
  }

  return len;
}

/**
 * Fixes the path by replacing all {@value #PATH_SEPARATOR_ALT} characters with
 * {@value #PATH_SEPARATOR} and creates directories for each directory as it
 * goes.
 * 
 * @param path The path to fix and make directories for
 * @param len  The maximum number of character to check
 * 
 * @return The total number of bytes checked
 * 
 * @see #fixPath
 */
stock fixPathAndMkdir(path[], len) {
  for (new i = 0; i <= len; i++) {
    if (fixPathSeparator(path, i)) {
      path[i] = EOS;
      mkdir(path);
      path[i] = PATH_SEPARATOR;
    }
  }

  return len;
}

stock BuildPath(dst[], len, const first[], ...) {
  new const maxLen = len;
  new const numArgs = numargs();
  len = FixAndCopyPath(dst, len, first);
  for (new i = 3; i < numArgs && len <= maxLen; i++) {
    dst[len++] = PATH_SEPARATOR;
    for (new j = 0, ch = getarg(i, j); ch != EOS && len <= maxLen; ch = getarg(i, ++j)) {
      dst[len++] = (ch == PATH_SEPARATOR_ALT) ? PATH_SEPARATOR : ch;
    }
  }

  dst[len] = EOS;
  return len;
}

static stock FixAndCopyPath(dst[], len, const path[]) {
  new i = 0;
  for (new ch = path[i]; ch != EOS && i <= len; i++, ch = path[i]) {
    dst[i] = (ch == PATH_SEPARATOR_ALT) ? PATH_SEPARATOR : ch;
  }

  return i;
}


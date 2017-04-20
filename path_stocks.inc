#if defined _path_stocks_included
  #endinput
#endif
#define _path_stocks_included

#tryinclude "include/stocks/string_stocks.inc"
#tryinclude "include/string_stocks.inc"
#if !defined _string_stocks_included
  #include <string_stocks>
#endif

#define PATH_EXTENSION     46 // '.'
#define PATH_SEPARATOR     47 // '/'
#define PATH_SEPARATOR_ALT 92 // '\'

#define FixPathSeparator(%1) ((%1 == PATH_SEPARATOR_ALT) ? PATH_SEPARATOR : %1)

stock get_pluginsdir(name[], len) {
  return get_localinfo("amxx_pluginsdir", name, len);
}

/** Builds a path, fixing separators on the fly */
stock getPath(dst[], len, const first[], ...) {
  new const maxLen = len; len = copyPath(dst, len, first);
  new const numArgs = numargs();
  for (new i = 3; i < numArgs && len <= maxLen; i++) {
    dst[len++] = PATH_SEPARATOR;
    for (new j = 0, ch; len <= maxLen && (ch = getarg(i, j)); j++, len++) {
      dst[len] = FixPathSeparator(ch);
    }
  }

  dst[len] = EOS;
  return len;
}

/** Copies the path into dst and fixes path separators on the fly */
static stock copyPath(dst[], len, const path[]) {
  new const maxLen = len; len = 0;
  for (new ch; len <= maxLen && (ch = path[len]); len++) {
    dst[len] = FixPathSeparator(ch);
  }

  dst[len] = EOS;
  return len;
}

/** Fixes path separators for the path and return the length of the path */
stock fixPath(path[]) {
  new len = 0;
  for (new ch; (ch = path[len]); len++) {
    if (ch == PATH_SEPARATOR_ALT) {
      path[len] = PATH_SEPARATOR;
    }
  }

  return len;
}

/** Same as getPath, except dst is already assumed to contain a valid path which child is appended to */
stock resolvePath(dst[], len, dstLen = 0, const child[]) {
  new const maxLen = len; len = 0;
  if (dstLen <= 0) {
    dstLen = strlen(dst);
  }

  if (dst[dstLen - 1] != PATH_SEPARATOR) {
    dst[dstLen++] = PATH_SEPARATOR;
  }

  return dstLen + copyPath(dst[dstLen], maxLen - dstLen, child);
}

stock getFileName(dst[], len, const path[], pathLen = 0) {
  if (pathLen <= 0) {
    pathLen = strlen(path);
  }

  new const maxLen = len; len = pathLen;
  new ch;
  while (--len >= 0
      && (ch = path[len]) != PATH_SEPARATOR
      && ch != PATH_SEPARATOR_ALT) {}
  return copy(dst, maxLen, path[len + 1]);
}

stock getFileExtension(dst[], len, const path[], pathLen = 0) {
  if (pathLen <= 0) {
    pathLen = strlen(path);
  }

  new const maxLen = len; len = pathLen;
  new ch;
  while (--len >= 0
      && (ch = path[len]) != PATH_EXTENSION
      && ch != PATH_SEPARATOR
      && ch != PATH_SEPARATOR_ALT) {}

  switch (path[len]) {
    case PATH_SEPARATOR:     len = maxLen;
    case PATH_SEPARATOR_ALT: len = maxLen;
  }
  return copy(dst, maxLen, path[len + 1]);
}

stock getFileNameWithoutExtension(dst[], len, const path[], pathLen = 0) {
  if (pathLen <= 0) {
    pathLen = strlen(path);
  }

  new const maxLen = len; len = pathLen;
  new ch, extensionStart = pathLen;
  while (--len >= 0
      && (ch = path[len]) != PATH_SEPARATOR
      && ch != PATH_SEPARATOR_ALT) {
    if (ch == PATH_EXTENSION) {
      extensionStart = len;
    }
  }
  
  return copy(dst, min(maxLen, extensionStart - len - 1), path[len + 1]);
}

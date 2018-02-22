/**
 * This file contains utility functions that can be used to translate resources.
 */

#if defined _resource_stocks_included
  #endinput
#endif
#define _resource_stocks_included

#include <amxconst>
#include <lang>
#include <string>
#include <celltrie>

#tryinclude "include/stocks/exception_stocks.inc"
#if !defined _exception_stocks_included
  #include <exception_stocks>
#endif

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

stock isResourceString(const res[]) {
  if (res[0] != '@') {
    return false;
  }
  
  if (equal(res[1], "string/", 7)) {
    return true;
  }

  return false;
}

stock bool: getResourceType(const res[], type[], len) {
  if (res[0] != '@') {
    type[0] = EOS;
    return false;
  }

  if (equal(res[1], "string/", 7)) {
    copyc(type, len, res[1], '/');
    return true;
  }
  
  copyc(type, len, res[1], '/');
  ThrowUnsupportedOperationException("Resource type not supported: %s", type);
  return false;
}

stock parseResource(const res[], dst[], len, id = LANG_SERVER) {
  if (res[0] != '@') {
    return;
  }

  if (equal(res[1], "string/", 7)) {
    if (!LookupLangKey(dst, len, res[8], id)) {
      formatex(dst, len, "ML_NOTFOUND: %s", res[8]);
    }
  } else {
    new type[32];
    copyc(type, charsmax(type), res[1], '/');
    ThrowUnsupportedOperationException("Resource type not supported: %s", type);
  }
}

stock parseResourceFast(res[], len, id = LANG_SERVER) {
  parseResource(res, res, len, id);
}

stock stripResource(const res[], dst[], len) {
  if (res[0] != '@') {
    return;
  }

  if (equal(res[1], "string/", 7)) {
    copy(dst, len, res[8]);
  } else {
    new type[8];
    copyc(type, charsmax(type), res[1], '/');
    ThrowUnsupportedOperationException("Resource type not supported: %s", type);
  }
}

stock stripResourceFast(res[], len) {
  stripResource(res, res, len);
}

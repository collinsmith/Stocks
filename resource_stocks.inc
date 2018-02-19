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

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

/**
 * Parses the given string and outputs the resolved value.
 * 
 * @param res The resource string to parse
 * @param dst The resolved value
 * @param len The maximum length of the resolved value
 * @param id  A player index or {@code LANG_SERVER} used to determine the
 *              language that the resource should be translated to
 */
stock parseResource(const res[], dst[], len, id = LANG_SERVER) {
  if (res[0] == '@') {
    new type[32];
    new const offset = copyc(type, charsmax(type), res[1], '/') + 2;
    if (equal(type, "string")) {
      // TODO: Not found should display something else than ML trans key
      LookupLangKey(dst, len, res[offset], id);
    } else {
      copy(dst, len, res);
    }
  }
}

// TODO: Documentation
stock parseResourceFast(res[], len, id = LANG_SERVER) {
  parseResource(res, res, len, id);
}

// TODO: Documentation
stock parseClassResource(const Trie: class, const property[], res[], len, id = LANG_SERVER) {
  TrieGetString(class, property, res, len);
  parseResourceFast(res, len, id);
}

// TODO: Documentation
stock getClassPropertyName(const Trie: class, const property[], res[], len) {
  TrieGetString(class, property, res, len);
}

// TODO: Documentation
stock bool: zm_getClassProperty(const Trie: class, const property[], res[], len, id = LANG_SERVER) {
  new const bool: keyExists = TrieGetString(class, property, res, len);
  parseResourceFast(res, len, id);
  return keyExists;
}

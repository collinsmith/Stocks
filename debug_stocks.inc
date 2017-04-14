/**
 * This file contains utility functions that can be used when debugging scripts.
 */

#if defined _debug_stocks_included
  #endinput
#endif
#define _debug_stocks_included

#include <amxmodx>

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

stock TrieToString(const Trie: trie, dst[], len) {
  if (trie == Invalid_Trie) {
    return copy(dst, len, "Invalid_Trie");
  }

  new const maxLen = len;
  len = copy(dst, maxLen, "{ ");

  new Snapshot: keySet = TrieSnapshotCreate(trie);
  new const count = TrieSnapshotLength(keySet);
  for (new i = 0; i < count; i++) {
    new keyStart = len;
    len += TrieSnapshotGetKey(keySet, i, dst[len], maxLen - len);
    dst[len] = EOS;
    new keyEnd = len;

    len += copy(dst[len], maxLen - len, ": ");
    dst[keyEnd] = EOS;
    len += TrieCoerceToString(trie, dst[keyStart], dst[len], maxLen - len);
    dst[keyEnd] = ':';
    len += copy(dst[len], maxLen - len, ", ");
  }

  TrieSnapshotDestroy(trie);
  if (count > 0) {
    len -= 2;
  }

  len += copy(dst[len], maxLen - len, " }");
  return len;
}

static stock TrieCoerceToString(const Trie: trie, const key[], dst[], len) {
  assert TrieKeyExists(trie, key);
  new cell;
  new bool: success = TrieGetCell(trie, key, cell);
  if (success) {
    return num_to_str(cell, dst, len);
  }

  new const maxLen = len;
  len = copy(dst, maxLen, "\"");
  success = TrieGetString(trie, key, dst[len], maxLen - len, cell);
  len += cell;
  len += copy(dst[len], maxLen - len, "\"");
  if (success) {
    return len;
  }

  /*new cells[256];
  success = TrieGetArray(trie, key, cells, sizeof cells, cell);
  if (success) {
    new const maxLen = len;
    len = copy(dst, maxLen, "[ ");
    for (new i = 0; i < cell; i++) {
      len += num_to_str(cells[i], dst[len], maxLen - len);
      len += copy(dst[len], maxLen - len, ", ");
    }

    if (cell > 0) {
      len -= 2;
    }

    len += copy(dst[len], maxLen - len, " ]");
    return len;
  }*/

  log_error(AMX_ERR_GENERAL, "Unsupported value type found.");
  return 0;
}

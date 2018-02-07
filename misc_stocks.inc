/**
 * This file contains utility functions which do not warrant their own files.
 */

#if defined _misc_stocks_included
  #endinput
#endif
#define _misc_stocks_included

#include <logger>

#tryinclude "include/stocks/string_stocks.inc"
#if !defined _string_stocks_included
  #include <string_stocks>
#endif

#tryinclude "include/stocks/exception_stocks.inc"
#if !defined _exception_stocks_included
  #include <exception_stocks>
#endif

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

/**
 * Defines the character to use as a separator for register console commands and
 * their prefix.
 */
#define CON_CMD_SEPARATOR '.'

/**
 * Registers a console command and logs that the command has been registered.
 * This function behaves the same as {@link #register_concmd} with the exception
 * that if {@code prefix} is non-empty, {@code command} will have it prepended
 * to the created command. By default, this will create commands in the form
 * {@code "${prefix}.${command}"}.
 * 
 * @param prefix   The sequence of characters that should preceed the command.
 *                   This will not include {@value #CON_CMD_SEPARATOR}, which
 *                   will automatically be appended. Additionally, multiple
 *                   aliases can be entered, separated by a comma, e.g.,
 *                   {@code "cmd,command"}.
 * @param command  The alias of the command
 * @param callback The function to execute when the command is entered
 * @param desc     A brief description of the command
 * @param access   The privleges required to execute the command
 * @param logCmd   {@code true} to log the command registration
 * 
 * @return The idenfitifier assigned to the command by {@link #register_concmd},
 *         or {@code 0} on failure. If multiple aliases are registered at once,
 *         then the identifier for the first successfully registered one is
 *         returned.
 * 
 * @throws IllegalArgumentException if {@code command} or {@code callback} is
 *         empty.
 */
stock registerConCmd(const prefix[], const command[], const callback[],
                     const desc[] = "", access = ADMIN_CFG,
                     const bool: logCmd = false) {
  if (isStringEmpty(command)) {
    ThrowIllegalArgumentException("command cannot be empty!");
    return 0;
  } else if (isStringEmpty(callback)) {
    ThrowIllegalArgumentException("callback cannot be empty!");
    return 0;
  }

  new arg[32], len = 0;
  if (!isStringEmpty(prefix)) {
    len += copy(arg[len], charsmax(arg) - len, prefix);
    if (len < charsmax(arg)) {
      arg[len++] = CON_CMD_SEPARATOR;
    }
  }

  new const prefixLen = len;

  new cmd = 0, offset = 0;
  while ((len = split_string(command[offset], ",", arg[prefixLen], charsmax(arg) - prefixLen)) != -1) {
    arg[prefixLen + len] = EOS;
    offset += len;

    new tmpCmd = register_concmd(arg, callback, access, desc);
    if (!cmd) cmd = tmpCmd;
    if (logCmd) logd("register_concmd \"%s\"", arg);
  }

  len = copy(arg[prefixLen], charsmax(arg) - prefixLen, command[offset]);
  arg[prefixLen + len] = EOS;

  new tmpCmd = register_concmd(arg, callback, access, desc);
  if (!cmd) cmd = tmpCmd;

  if (logCmd) logd("register_concmd \"%s\"", arg);
  return cmd;
}

stock compareVersions(const current[], const other[]) {
  new trash1[32], trash2[32];
  new p1, v1[8], p2, v2[8];
  
  new a, b;
  new i;
  for (;;) {
    p1 = strtok2(current[a], v1, charsmax(v1), trash1, charsmax(trash1), '.', TRIM_FULL);
    p2 = strtok2(other[b], v2, charsmax(v2), trash2, charsmax(trash2), '.', TRIM_FULL);
    if (p1 != -1 && p2 != -1) {
      i = str_to_num(v2) - str_to_num(v1);
      if (i != 0) {
        return i;
      }

      a += p1 + 1;
      b += p2 + 1;
    } else if (p1 != -1) {
      return -1;
    } else if (p2 != -1) {
      return 1;
    } else {
      i = str_to_num(v2) - str_to_num(v1);
      return i;
    }
  }

  return 0;
}

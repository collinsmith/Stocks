/**
 * This file contains utility functions which do not warrant their own files.
 */

#if defined _misc_stocks_included
  #endinput
#endif
#define _misc_stocks_included

#tryinclude <logger>
#if !defined Invalid_Logger
  #define Invalid_Logger Logger:(0)
#endif

#tryinclude "../string_stocks.inc"
#tryinclude "include/stocks/string_stocks.inc"
#if !defined _string_stocks_included
  #include <string_stocks>
#endif

#tryinclude "../exception_stocks.inc"
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
 * @param logger   The logger to log the event to, or {@code Invalid_Logger} to
 *                   not log the event
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
                     Logger: logger = Invalid_Logger) {
  if (isStringEmpty(command)) {
    ThrowIllegalArgumentException(logger, "command cannot be empty!");
    return 0;
  } else if (isStringEmpty(callback)) {
    ThrowIllegalArgumentException(logger, "callback cannot be empty!");
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

#if defined _logger_included
    if (logger > Invalid_Logger) {
      LoggerLogDebug2(logger, false, "register_concmd \"%s\"", arg);
    }
#else
    log_amx("register_concmd \"%s\"", arg);
#endif
  }

  len = copy(arg[prefixLen], charsmax(arg) - prefixLen, command[offset]);
  arg[prefixLen + len] = EOS;

  new tmpCmd = register_concmd(arg, callback, access, desc);
  if (!cmd) cmd = tmpCmd;

#if defined _logger_included
  if (logger > Invalid_Logger) {
    LoggerLogDebug2(logger, false, "register_concmd \"%s\"", arg);
  }
#else
  log_amx("register_concmd \"%s\"", arg);
#endif

  return cmd;
}
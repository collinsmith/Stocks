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

#tryinclude "../exception_stocks.inc"
#tryinclude "stocks/exception_stocks.inc"
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
 * @param prefix   The sequence of character that should preceed the command.
 *                   This will not include {@value #CON_CMD_SEPARATOR}, which
 *                   will automatically be appended
 * @param command  The alias of the command
 * @param callback The function to execute when the command is entered
 * @param desc     A brief description of the command
 * @param access   The privleges required to execute the command
 * @param logger   The logger to log the event to, or {@code Invalid_Logger} to
 *                   not log the event
 * 
 * @return The idenfitifier assigned to the command by {@link #register_concmd},
 *         or {@code 0} on failure.
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

  if (!isStringEmpty(prefix)) {
    new temp[32];
    new len = copy(temp, 31, prefix);
    temp[len++] = CON_CMD_SEPARATOR;
    copy(temp[len], 31 - len, command);
    new cmd = register_concmd(temp, callback, access, desc);
#if defined _logger_included
    if (logger > Invalid_Logger) {
      LoggerLogDebug2(logger, true, "register_concmd \"%s\"", temp);
    }
#endif

    return cmd;
  }

  new cmd = register_concmd(command, callback, access, desc);
#if defined _logger_included
  if (logger > Invalid_Logger) {
    LoggerLogDebug2(logger, true, "register_concmd \"%s\"", command);
  }
#endif
  
  return cmd;
}
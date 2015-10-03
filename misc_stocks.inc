#if defined _misc_stocks_included
    #endinput
#endif
#define _misc_stocks_included

#include <amxconst>

#tryinclude <string_stocks>
#tryinclude "include\\stocks\\string_stocks.inc"

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

/**
 * Defines the character to use as a separator for registered console commands.
 */
#define CON_CMD_SEPARATOR '.'

/**
 * Registers a console command and logs that the command has been registered.
 * The primary purpose of this stock is to create a macro for creating commands
 * used by admins/developers to debug their plugins. The command will
 * automatically be created as {@code {@param prefix}.{@param command}}, e.g.,
 * if prefix="cmd", and command="list", then the created command will be: 
 * "cmd.list". If prefix is equal to empty string {@code ""}, then the dot can
 * be optionally ommitted (i.e., two commands will be created in this case, one
 * with, and one without the dot).
 * 
 * @param prefix      Sequence of characters preceeding the command
 * @param command     Command which when typed in console, executes a function
 * @param function    Name of the function to execute
 * @param description Brief description of the purpose for the command
 * @param logger      Logger to log when the command has been registered
 */
stock registerConCmd(
        const prefix[],
        const command[],
        const function[],
        const description[] = NULL_STRING,
        const access = ADMIN_CFG,
        const Logger: logger = Logger:(0)) {
    assert !isStringEmpty(command);
    assert !isStringEmpty(function);
    if (!isStringEmpty(prefix)) {
        new temp[64];
        new len = copy(temp, 31, prefix);
        temp[len++] = CON_CMD_SEPARATOR;
        copy(temp[len], 31, prefix);
        register_concmd(
                temp,
                function,
                access,
                description);

        if (logger != Logger:(0)) {
            LoggerLogDebug2(logger, true, "register_concmd \"%s\"", temp);
        }
        
        return;
    }

    register_concmd(
            command,
            function,
            access,
            description);

    new temp[33];
    temp[0] = CON_CMD_SEPARATOR;
    copy(temp[1], 31, command);
    register_concmd(
            temp,
            function,
            access,
            description);

    if (logger != Logger:(0)) {
        LoggerLogDebug2(logger, true, "register_concmd \"%s\"", command);
        LoggerLogDebug2(logger, true, "register_concmd \"%s\"", temp);
    }
}
#if defined _param_test_stocks_included
    #endinput
#endif
#define _param_test_stocks_included

#include <amxconst>

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

/**
 * Returns whether or not the specified index is a valid player index, i.e.,
 * between 1 and {@link amxconst.inc::#MaxClients}.
 * 
 * @param id Index to check
 * 
 * @return {@literal true} if it is, otherwise {@literal false}
 */
stock bool: isValidId(const id) {
    return 1 <= id && id <= MaxClients;
}
#if defined _dynamic_param_stocks_included
    #endinput
#endif
#define _dynamic_param_stocks_included

#define AMX_ERR_CODE AMX_ERR_NATIVE

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

stock bool:numParamsEqual(expectation, test) {
    if (test == expectation) {
        return true;
    }

    

    return false;
}
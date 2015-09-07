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

    new trace = dbg_trace_begin();
    new line, function[64], file[64];
    dbg_trace_info(
            trace,
            line,
            function,
            charsmax(function),
            name,
            charsmax(name));

    log_error(
            AMX_ERR_CODE,
            "[%s] Expected %d parameters, found %d",
            function,
            expectation,
            test);

    return false;
}
/**
 * 
 */

#if defined _exception_stocks_included
  #endinput
#endif
#define _exception_stocks_included

#tryinclude <logger>
#if !defined Invalid_Logger
  #define Invalid_Logger Logger:(0)
#endif

#if !defined AMX_ERR_ASSERT
  #define AMX_ERR_ASSERT 2
#endif

enum Exception {
  AssertionException,
  IllegalArgumentException,
};

stock const Exceptions[Exception][] = {
  "AssertionException",
  "IllegalArgumentException",
};

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

#define message_length 1023
static stock temp[message_length + 1];

stock ThrowAssertionException(Logger: logger = Invalid_Logger,
                              const msg[] = "", any: ...) {
  #pragma unused msg
  new len = format_args(temp, message_length, 1);
  temp[len] = EOS;
  Throw(logger, AMX_ERR_ASSERT, Exceptions[AssertionException], temp);
}

stock ThrowIllegalArgumentException(Logger: logger = Invalid_Logger,
                                    const msg[] = "", any: ...) {
  #pragma unused msg
  new len = format_args(temp, message_length, 1);
  temp[len] = EOS;
  Throw(logger, AMX_ERR_PARAMS, Exceptions[IllegalArgumentException], temp);
}

stock Throw(Logger: logger = Invalid_Logger,
            error = AMX_ERR_GENERAL, const exception[],
            const msg[] = "", any: ...) {
  #pragma unused msg
  static message[message_length + 1];
  new len = copy(message, message_length, exception);
  len += copy(message[len], message_length - len, ": ");
  len += format_args(message[len], message_length - len, 2);
  message[len] = EOS;
#if defined _logger_included
  if (logger > Invalid_Logger) {
    LoggerLogError(logger, message);
  }
#endif
  
  log_error(error, message);
}
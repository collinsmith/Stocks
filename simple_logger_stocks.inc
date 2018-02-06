/**
 * This file contains macros to ease implementation of the logger API.
 */

#if defined _simple_logger_stocks_included
  #endinput
#endif
#define _simple_logger_stocks_included

#include <logger>

#define logd LoggerLogDebug
#define logi LoggerLogInfo
#define logw LoggerLogWarn
#define loge LoggerLogError

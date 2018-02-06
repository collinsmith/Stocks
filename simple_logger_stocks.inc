/**
 * This file contains macros to ease implementation of the logger API.
 */

#if defined _simple_logger_stocks_included
  #endinput
#endif
#define _simple_logger_stocks_included

#include <logger>

#define LOG_METHOD Logger

#define message_length 1023
static stock temp[message_length + 1];

stock logd(const msg[], any: ...) {
  #pragma unused msg
  format_args(temp, message_length, 1);
  LOG_METHOD(DebugLevel, temp);
}

stock logi(const msg[], any: ...) {
  #pragma unused msg
  format_args(temp, message_length, 1);
  LOG_METHOD(InfoLevel, temp);
}

stock logw(const msg[], any: ...) {
  #pragma unused msg
  format_args(temp, message_length, 1);
  LOG_METHOD(WarnLevel, temp);
}

stock loge(const msg[], any: ...) {
  #pragma unused msg
  format_args(temp, message_length, 1);
  LOG_METHOD(ErrorLevel, temp);
}

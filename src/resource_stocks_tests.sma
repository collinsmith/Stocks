#include <amxmodx>
#include <logger>

#include "../simple_logger_stocks.inc"
#include "../exception_stocks.inc"
#include "../resource_stocks.inc"

public plugin_init() {
  register_plugin("misc_stocks tests", "0.0.1", "Tirant");

  SetGlobalLoggerVerbosity(DebugLevel);
  SetLoggerVerbosity(DebugLevel);
  
  new res[32] = "@string/TEMP";
  new temp[32];
  getResourceType(res, temp, charsmax(temp));
  logd("|||||||||||||||||||||||||||||| resource=%s; temp=%s", res, temp);
}

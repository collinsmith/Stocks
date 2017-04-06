/**
 * 
 */

#if defined _precache_stocks_included
  #endinput
#endif
#define _precache_stocks_included

#tryinclude "../exception_stocks.inc"
#if !defined _exception_stocks_included
  #include <exception_stocks>
#endif

#tryinclude "../path_stocks.inc"
#if !defined _path_stocks_included
  #include <path_stocks>
#endif

#tryinclude "../string_stocks.inc"
#if !defined _string_stocks_included
  #include <string_stocks>
#endif

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

/**
 * Formats the path for a player model.
 * 
 * @param dst   The output buffer for the formatted path to {@code model}
 * @param len   The maximum number of bytes that the path can fill
 * @param model Name of the player model file without the extension. This file
 *                is assumed to be located at:
 *                {@code "models/player/${model}/${model}.mdl"}
 * 
 * @return The number of bytes copied.
 * 
 * @throws IllegalArgumentException if {@code model} is empty.
 */
stock getPlayerModelPath(dst[], len, const model[], Logger: logger = Invalid_Logger) {
  if (isStringEmpty(model)) {
    ThrowIllegalArgumentException(logger, "model should not be empty!");
  }

  new tempLen = getPath(dst, len, MODELS, PLAYER, model, model);
  return tempLen + copy(dst[tempLen], len - tempLen, MDL);
}

/**
 * Formats the path for a model.
 * 
 * @param dst   The output buffer for the formatted path to {@code model}
 * @param len   The maximum number of bytes that the path can fill
 * @param model Name of the model file without the extension. This file is
 *                assumed to be located at {@code "models/${model}.mdl"}.
 *                Model can be specified as a subpath, e.g.,
 *                {@code "knives/v_bowie"} {@literal ->} {@code "models/knives/v_bowie.mdl"}
 * 
 * @return The number of bytes copied.
 * 
 * @throws IllegalArgumentException if {@code model} is empty.
 */
stock getModelPath(dst[], len, const model[], Logger: logger = Invalid_Logger) {
  if (isStringEmpty(model)) {
    ThrowIllegalArgumentException(logger, "model should not be empty!");
  }

  new tempLen = getPath(dst, len, MODELS, model);
  return tempLen + copy(dst[tempLen], len - tempLen, MDL);
}

/**
 * Precaches a given model. Models should begin with {@code "models"}, and
 * typical names can be formatted using {@link #getPlayerModelPath} and
 * {@link #getModelPath} for player and other models respectively.
 * 
 * @param model The path to the model
 * 
 * @return {@code true} if the model was precached, {@code false} otherwise
 * 
 * @throws IllegalArgumentException if {@code model} is empty or does not begin
 *         with "models", or if the model specified by the path does not exist.
 */
stock bool: precacheModel(const model[], Logger: logger = Invalid_Logger) {
  if (logger != Invalid_Logger) {
    LoggerLogDebug(logger, "Precaching \"%s\"", model);
  }

  if (isStringEmpty(model)) {
    ThrowIllegalArgumentException(logger, "model should not be empty!");
    return false;
} else if (stringStartsWith(model, MODELS)) {
    ThrowIllegalArgumentException(logger,
        "model path should start with \"%s\"! (\"%s\")", MODELS, model);
    return false;
} else if (!file_exists(model)) {
    ThrowIllegalArgumentException(logger,
        "model specified by path \"%s\" does not exist!", model);
    return false;
  }

  engfunc(EngFunc_PrecacheModel, model);
  return true;
}

/**
 * Precaches a given file.
 * 
 * @param file The path to the file
 * 
 * @return {@code true} if the file was precached, {@code false} otherwise
 */
stock bool:precache(const file[], Logger: logger = Invalid_Logger) {
  if (logger != Invalid_Logger) {
    LoggerLogDebug(logger, "Precaching \"%s\"", file);
  }

  if (isStringEmpty(file)) {
    ThrowIllegalArgumentException(logger, "file should not be empty!");
    return false;
  } else if (!file_exists(file)) {
    ThrowIllegalArgumentException(logger,
        "file specified by path \"%s\" does not exist!", file);
    return false;
  }

  engfunc(EngFunc_PrecacheGeneric, file);
  return true;
}

/**
 * Precaches a given sound file. Sounds are assumed to be located within the
 * sound directory (i.e., "sound/${sound}").
 * 
 * @param sound Path of the sound
 * 
 * @return      {@literal true} if the sound was precached, otherwise {@literal
 *                  false}
 */
stock bool: precacheSound(const sound[], Logger: logger = Invalid_Logger) {
  new path[256];
  getPath(path, _, SOUND, sound);
  return precache(path, logger);
}
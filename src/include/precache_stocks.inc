#if defined _precache_stocks_included
    #endinput
#endif
#define _precache_stocks_included

#include <amxmodx>
#include <amxmisc>
#include <exception_handler>
#include <fakemeta>

#include "include/path_stocks.inc"
#include "include/string_stocks.inc"

stock const MODELS[] = "models";
stock const PLAYER[] = "player";
stock const MDL[] = ".mdl";
stock const SOUND[] = "sound";

/*******************************************************************************
 * Stocks
 ******************************************************************************/

/**
 * Formats the path for a player model.
 * 
 * @param dst   Array to populate with the path of the model (see below example)
 * @param len   Number of cells in the copy array that the path can fill
 * @param model Name of the player model file without the extension. This file
 *                  is assumed to be located at:
 *                  "models/player/${model}/${model}.mdl"
 * 
 * @return number of cells copied.
 * 
 * @throws IllegalArgumentException if the model specified is empty
 */
stock getPlayerModelPath(dst[], len = sizeof dst, const model[]) {
    if (isStringEmpty(model)) {
        Throw(IllegalArgumentException, "model should not be empty!");
    }

    new tempLen = getPath(dst, len, MODELS, PLAYER, model, model);
    return tempLen + copy(dst[tempLen], len-tempLen-1, MDL);
}

/**
 * Formats the path for a model.
 * 
 * @param dst   Array to populate with the path of the model (see below example)
 * @param len   Number of cells in the copy array that the path can fill
 * @param model Name of the model file without the extension. This file is
 *                  assumed to be located at "models/${model}.mdl". Model can be
 *                  specified as a subpath, e.g.,
 *                  "knives/v_bowie" would equate to the file named
 *                  "models/knives/v_bowie.mdl"
 * 
 * @return number of cells copied.
 * 
 * @throws IllegalArgumentException if the model specified is empty
 */
stock getModelPath(dst[], len = sizeof dst, const model[]) {
    if (isStringEmpty(model)) {
        Throw(IllegalArgumentException, "model should not be empty!");
    }

    new tempLen = getPath(dst, len, MODELS, model);
    return tempLen + copy(dst[tempLen], len-tempLen-1, MDL);
}

/**
 * Precaches a given model. Models should begin with "models", and typical
 * names can be formatted using getPlayerModelPath and getModelPath
 * for player and other models respectively.
 * 
 * @param model Path of the model
 * 
 * @return      {@literal true} if the model was precached, otherwise {@literal
 *                  false}
 * 
 * @throws IllegalArgumentException if the model specified is empty, or it does
 *             not begin with "models", or if the model specified by the path
 *             does not exist
 */
stock bool: precacheModel(const model[]) {
    if (isStringEmpty(model)) {
        Throw(IllegalArgumentException,
                "model should not be empty!");
        return false;
    } else if (stringStartsWith(model, MODELS)) {
        Throw(IllegalArgumentException,
                "model path should start with \"%s\"! (\"%s\")",
                MODELS,
                model);
        return false;
    } else if (!file_exists(model)) {
        Throw(FileNotFoundException,
                "model specified by path \"%s\" does not exist!",
                model);
        return false;
    }

    engfunc(EngFunc_PrecacheModel, model);
    return true;
}

/**
 * Precaches a given file.
 * 
 * @param file Path of the file
 * 
 * @return     {@literal true} if the file was precached, otherwise {@literal
 *                  false}
 */
stock bool:precache(const file[]) {
    if (isStringEmpty(file)) {
        Throw(IllegalArgumentException,
                "file should not be empty!");
        return false;
    } else if (!file_exists(file)) {
        Throw(FileNotFoundException,
                "file specified by path \"%s\" does not exist!",
                file);
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
stock bool: precacheSound(const sound[]) {
    new path[256];
    getPath(path, _, SOUND, sound);
    return precache(path);
}
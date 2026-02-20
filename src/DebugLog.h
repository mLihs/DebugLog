#pragma once

#include <Arduino.h>
#include <stdio.h>  // For snprintf in printf-style macros

// -----------------------------------------------------------------------------
//  CONFIG
// -----------------------------------------------------------------------------

// Globale Debug-Enable/Disable
#ifndef DEBUG_LOG_ENABLED
  #define DEBUG_LOG_ENABLED 1   // auf 0 setzen für Release
#endif

// Log-Level
#define LOG_LEVEL_NONE    0
#define LOG_LEVEL_ERROR   1
#define LOG_LEVEL_WARN    2
#define LOG_LEVEL_INFO    3
#define LOG_LEVEL_DEBUG   4
#define LOG_LEVEL_VERBOSE 5

#ifndef DEBUG_LOG_LEVEL
  #define DEBUG_LOG_LEVEL LOG_LEVEL_DEBUG   // Standard-Level
#endif

// ANSI-Farben (nur, wenn Terminal das kann)
#ifndef DEBUG_LOG_COLORS
  #define DEBUG_LOG_COLORS 1   // auf 0 setzen, wenn Farben nerven
#endif

// -----------------------------------------------------------------------------
//  INTERNER HELFER
// -----------------------------------------------------------------------------

#if DEBUG_LOG_ENABLED
  inline void debugLogPrintHeader(const __FlashStringHelper* levelTag) {
    // Level
    Serial.print(levelTag);
    Serial.print(F(" "));
  }

  inline void debugLogColorStart(const __FlashStringHelper* colorCode) {
  #if DEBUG_LOG_COLORS
    Serial.print(colorCode);
  #endif
  }

  inline void debugLogColorEnd() {
  #if DEBUG_LOG_COLORS
    Serial.print(F("\033[0m"));
  #endif
  }

  // Farbcodes
  #define DBG_COLOR_RED     F("\033[31m")
  #define DBG_COLOR_YELLOW  F("\033[33m")
  #define DBG_COLOR_GREEN   F("\033[32m")
  #define DBG_COLOR_CYAN    F("\033[36m")
  #define DBG_COLOR_GRAY    F("\033[90m")

  // Basis-Makro: eine Zeile loggen (Template für alle Level)
  #define DEBUG_LOG_LINE(levelTag, colorCode, msg)      \
    do {                                                \
      debugLogColorStart(colorCode);                    \
      debugLogPrintHeader(levelTag);                    \
      Serial.println(msg);                              \
      debugLogColorEnd();                               \
    } while (0)

#else // DEBUG_LOG_ENABLED == 0
  // Alles komplett wegoptimieren
  #define DEBUG_LOG_LINE(levelTag, colorCode, msg) do {} while (0)
#endif // DEBUG_LOG_ENABLED

// -----------------------------------------------------------------------------
//  LEVEL-SPEZIFISCHE MAKROS
// -----------------------------------------------------------------------------

#if DEBUG_LOG_ENABLED && (DEBUG_LOG_LEVEL >= LOG_LEVEL_ERROR)
  #define LOGE(msg) DEBUG_LOG_LINE(F("[E]"), DBG_COLOR_RED, msg)
#else
  #define LOGE(msg) do {} while (0)
#endif

#if DEBUG_LOG_ENABLED && (DEBUG_LOG_LEVEL >= LOG_LEVEL_WARN)
  #define LOGW(msg) DEBUG_LOG_LINE(F("[W]"), DBG_COLOR_YELLOW, msg)
#else
  #define LOGW(msg) do {} while (0)
#endif

#if DEBUG_LOG_ENABLED && (DEBUG_LOG_LEVEL >= LOG_LEVEL_INFO)
  #define LOGI(msg) DEBUG_LOG_LINE(F("[I]"), DBG_COLOR_GREEN, msg)
#else
  #define LOGI(msg) do {} while (0)
#endif

#if DEBUG_LOG_ENABLED && (DEBUG_LOG_LEVEL >= LOG_LEVEL_DEBUG)
  #define LOGD(msg) DEBUG_LOG_LINE(F("[D]"), DBG_COLOR_CYAN, msg)
#else
  #define LOGD(msg) do {} while (0)
#endif

#if DEBUG_LOG_ENABLED && (DEBUG_LOG_LEVEL >= LOG_LEVEL_VERBOSE)
  #define LOGV(msg) DEBUG_LOG_LINE(F("[V]"), DBG_COLOR_GRAY, msg)
#else
  #define LOGV(msg) do {} while (0)
#endif

// -----------------------------------------------------------------------------
//  PRINTF-STYLE FORMATTING MACROS (Stack-safe)
// -----------------------------------------------------------------------------
// These macros use snprintf with a fixed-size buffer to prevent stack overflow
// from String concatenation. Use these for logging with variables.
//
// Example:
//   LOGI_F("Sensor %s connected (ID: %d)", name.c_str(), id);
//   LOGD_F("Temperature: %.1f°C, Humidity: %d%%", temp, humidity);
//

#if DEBUG_LOG_ENABLED && (DEBUG_LOG_LEVEL >= LOG_LEVEL_ERROR)
  #define LOGE_F(format, ...) \
    do { \
      char _log_buffer[256]; \
      snprintf(_log_buffer, sizeof(_log_buffer), format, ##__VA_ARGS__); \
      DEBUG_LOG_LINE(F("[E]"), DBG_COLOR_RED, _log_buffer); \
    } while (0)
#else
  #define LOGE_F(format, ...) do {} while (0)
#endif

#if DEBUG_LOG_ENABLED && (DEBUG_LOG_LEVEL >= LOG_LEVEL_WARN)
  #define LOGW_F(format, ...) \
    do { \
      char _log_buffer[256]; \
      snprintf(_log_buffer, sizeof(_log_buffer), format, ##__VA_ARGS__); \
      DEBUG_LOG_LINE(F("[W]"), DBG_COLOR_YELLOW, _log_buffer); \
    } while (0)
#else
  #define LOGW_F(format, ...) do {} while (0)
#endif

#if DEBUG_LOG_ENABLED && (DEBUG_LOG_LEVEL >= LOG_LEVEL_INFO)
  #define LOGI_F(format, ...) \
    do { \
      char _log_buffer[256]; \
      snprintf(_log_buffer, sizeof(_log_buffer), format, ##__VA_ARGS__); \
      DEBUG_LOG_LINE(F("[I]"), DBG_COLOR_GREEN, _log_buffer); \
    } while (0)
#else
  #define LOGI_F(format, ...) do {} while (0)
#endif

#if DEBUG_LOG_ENABLED && (DEBUG_LOG_LEVEL >= LOG_LEVEL_DEBUG)
  #define LOGD_F(format, ...) \
    do { \
      char _log_buffer[256]; \
      snprintf(_log_buffer, sizeof(_log_buffer), format, ##__VA_ARGS__); \
      DEBUG_LOG_LINE(F("[D]"), DBG_COLOR_CYAN, _log_buffer); \
    } while (0)
#else
  #define LOGD_F(format, ...) do {} while (0)
#endif

#if DEBUG_LOG_ENABLED && (DEBUG_LOG_LEVEL >= LOG_LEVEL_VERBOSE)
  #define LOGV_F(format, ...) \
    do { \
      char _log_buffer[256]; \
      snprintf(_log_buffer, sizeof(_log_buffer), format, ##__VA_ARGS__); \
      DEBUG_LOG_LINE(F("[V]"), DBG_COLOR_GRAY, _log_buffer); \
    } while (0)
#else
  #define LOGV_F(format, ...) do {} while (0)
#endif


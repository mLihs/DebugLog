/**
 * DebugLog Library - Basic Example
 * 
 * Demonstrates the usage of all log levels:
 * - LOGE / LOGE_F: Error messages (red)
 * - LOGW / LOGW_F: Warning messages (yellow)
 * - LOGI / LOGI_F: Info messages (green)
 * - LOGD / LOGD_F: Debug messages (cyan)
 * - LOGV / LOGV_F: Verbose messages (gray)
 * 
 * Note: The _F variants (printf-style) are recommended for logging with
 * variables to prevent stack overflow in embedded systems.
 */

#include <DebugLog.h>

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n=== DebugLog Library Example ===\n");
  
  // Example log messages at different levels (simple static strings)
  LOGE("This is an ERROR message");
  LOGW("This is a WARNING message");
  LOGI("This is an INFO message");
  LOGD("This is a DEBUG message");
  LOGV("This is a VERBOSE message");
  
  Serial.println("\n--- Example with variables (OLD way - can cause stack overflow) ---\n");
  
  // ⚠️ WARNING: String concatenation can cause stack overflow in tight loops
  // This is shown for demonstration but NOT recommended for production code
  int sensorValue = 42;
  float temperature = 23.5;
  String deviceName = "ESP32";
  
  LOGI("Sensor reading: " + String(sensorValue));  // ❌ Not recommended
  LOGD("Temperature: " + String(temperature) + "°C");  // ❌ Not recommended
  LOGV("Device: " + deviceName);  // ❌ Not recommended
  
  Serial.println("\n--- Example with variables (NEW way - stack-safe) ---\n");
  
  // ✅ RECOMMENDED: Printf-style formatting (stack-safe, fixed buffer)
  LOGI_F("Sensor reading: %d", sensorValue);
  LOGD_F("Temperature: %.1f°C", temperature);
  LOGV_F("Device: %s", deviceName.c_str());  // Use .c_str() for String objects
  
  // More examples with printf-style formatting
  uint32_t timestamp = millis();
  int errorCode = 404;
  float voltage = 3.3f;
  
  LOGI_F("Timestamp: %lu ms", timestamp);
  LOGE_F("Error code: %d", errorCode);
  LOGD_F("Voltage: %.2f V", voltage);
  LOGD_F("Multiple values: ID=%d, Temp=%.1f, Status=%s", sensorValue, temperature, "OK");
  
  Serial.println("\n=== Example Complete ===\n");
}

void loop() {
  // Example in loop (use printf-style for frequently called code)
  static unsigned long lastLog = 0;
  if (millis() - lastLog > 2000) {
    // ✅ Recommended: Printf-style for loop code
    LOGD_F("Loop running... millis() = %lu", millis());
    lastLog = millis();
  }
  delay(100);
}


#include <WiFi.h>
#include <Arduino_MQTT_Client.h>
#include <ThingsBoard.h>
// #include <ArduinoOTA.h> (Uncomment if you are using PlatformIO)

// Wi-Fi and ThingsBoard configuration
constexpr char WIFI_SSID[] = "Wokwi-GUEST";
constexpr char WIFI_PASSWORD[] = "";
constexpr char TOKEN[] = "zlfeW9lsoRJBb1jTQki3";
constexpr char THINGSBOARD_SERVER[] = "thingsboard.cloud";
constexpr uint16_t THINGSBOARD_PORT = 1883U;
constexpr uint32_t MAX_MESSAGE_SIZE = 1024U;
constexpr uint32_t SERIAL_DEBUG_BAUD = 115200U;

// Pin definition for the LED
constexpr uint8_t LED_PIN = 13;

// Global variables
bool ledState = false;  // LED state
bool subscribed = false; // Indicates if RPC subscription is done

// Initialize WiFi and MQTT clients
WiFiClient wifiClient;
Arduino_MQTT_Client mqttClient(wifiClient);
ThingsBoard tb(mqttClient, MAX_MESSAGE_SIZE);

// Function declarations
void initWiFi();
bool reconnect();
RPC_Response processSetLedStatus(const RPC_Data &data);
void processTime(const JsonVariantConst& data);

// Define the array of RPC callbacks
const std::array<RPC_Callback, 1U> callbacks = {
  RPC_Callback{ "setLedStatus", processSetLedStatus }
};

void setup() {
  // Initialize serial communication
  Serial.begin(SERIAL_DEBUG_BAUD);
  
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);
  
  // Small delay to ensure the serial monitor is ready
  delay(1000);
  
  // Initialize Wi-Fi connection
  initWiFi();
}

void loop() {
  // Small delay to avoid overwhelming the loop
  delay(10);

  // Attempt to reconnect if the Wi-Fi connection is lost
  if (!reconnect()) {
    return;
  }

  // Check if we are connected to ThingsBoard
  if (!tb.connected()) {
    // Attempt to connect to ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT)) {
      Serial.println("Failed to connect");
      return;
    }

    // Subscribe to RPC callbacks
    Serial.println("Subscribing for RPC...");
    if (!tb.RPC_Subscribe(callbacks.cbegin(), callbacks.cend())) {
      Serial.println("Failed to subscribe for RPC");
      return;
    }
  }

  // Control the LED state
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);

  // Request the current time if not already subscribed
  if (!subscribed) {
    Serial.println("Requesting RPC...");
    if (!tb.RPC_Request("getCurrentTime", processTime)) {
      Serial.println("Failed to request for RPC");
      return;
    }
    Serial.println("Request done");
    subscribed = true;
  }

  // Maintain the connection and process incoming messages
  tb.loop();
}

void initWiFi() {
  // Start the connection to the Wi-Fi network
  Serial.println("Connecting to AP ...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}

bool reconnect() {
  // Check the Wi-Fi connection status and reconnect if necessary
  if (WiFi.status() != WL_CONNECTED) {
    initWiFi();
  }
  return WiFi.status() == WL_CONNECTED;
}

RPC_Response processSetLedStatus(const RPC_Data &data) {
  // Process the RPC request to change the LED state
  int dataInt = data;
  ledState = dataInt == 1;  // Update the LED state based on the received data
  Serial.println(ledState ? "LED ON" : "LED OFF");
  return RPC_Response("newStatus", dataInt);  // Respond with the new status
}

void processTime(const JsonVariantConst& data) {
  // Process the RPC response containing the current time
  Serial.print("Received time from ThingsBoard: ");
  Serial.println(data["time"].as<String>());
}

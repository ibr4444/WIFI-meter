#include <WiFi.h>
#include <TFT_eSPI.h>

// Wi-Fi credentials
const char* ssid = "Ibra";         // Replace with your Wi-Fi SSID
const char* password = "87654321"; // Replace with your Wi-Fi password

// Create TFT display object
TFT_eSPI tft = TFT_eSPI(); // Create TFT object, defined in the TFT_eSPI library

// Define bar positions and sizes
int barY = 150;  // Y position of the bars (moved slightly further down)
int barWidth = 20;  // Slightly wider bars
int barSpacing = 8; // Spacing between bars

void setup() {
  Serial.begin(115200);

  // Initialize the TFT display
  tft.init();
  tft.setRotation(1);  // Set rotation of the screen
  tft.fillScreen(TFT_BLACK); // Fill the screen with black

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Clear the display for initial setup
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  // Get the Wi-Fi signal strength (RSSI)
  long rssi = WiFi.RSSI();
  
  // Clear the display for new values
  tft.fillScreen(TFT_BLACK);

  // Display the "Wi-Fi Signal Strength" label centered at the top
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(1);  // Smaller text size to fit on the screen

  // Calculate position to center the "Wi-Fi Signal Strength" label
  int textWidth = tft.textWidth("Wi-Fi Signal Strength:");
  int textX = (tft.width() - textWidth) / 2;  // Center the text horizontally
  tft.setCursor(textX, 25);  // Position the text slightly lower
  tft.print("Wi-Fi Signal Strength:");

  // Display RSSI value as text centered below the label
  String rssiText = String(rssi) + " dBm";
  int rssiTextWidth = tft.textWidth(rssiText);
  int rssiTextX = (tft.width() - rssiTextWidth) / 2;  // Center the RSSI value horizontally
  tft.setCursor(rssiTextX, 45); // Position the RSSI value below the label
  tft.setTextSize(2);  // Slightly bigger text for better visibility
  tft.print(rssiText);

  // Map RSSI value to the number of bars to highlight and their height
  int barsToHighlight = map(rssi, -100, -30, 0, 4); // Map RSSI to 0 to 4 bars

  // Calculate starting X position for bars (center the bars horizontally)
  int totalBarWidth = (barWidth * 4) + (barSpacing * 3); // Total width of all bars with spacing
  int barX = (tft.width() - totalBarWidth) / 2; // Center the bars horizontally

  // Draw 4 bars to represent signal strength (tallest bar on the left)
  for (int i = 0; i < 4; i++) {
    // Calculate the x position for each bar
    int barXPos = barX + i * (barWidth + barSpacing);
    
    // Set the bar height based on the signal strength
    int barHeight = map(i, 0, 3, 50, 15); // Taller bars on the left, smaller on the right
    
    // If this bar should be filled, make it green (strong signal), else grey (weak signal)
    if (i < barsToHighlight) {
      tft.fillRect(barXPos, barY - barHeight, barWidth, barHeight, TFT_GREEN); // Filled bars
    } else {
      tft.fillRect(barXPos, barY - barHeight, barWidth, barHeight, TFT_RED); // Empty bars
    }
  }

  // Delay before updating the display again
  delay(1000);
}

// Wifi
#include <WiFi.h>

// Network name
const char* ssid = "My ESP32";
// Password
const char* password = "12345678";

// Creates the server object on port 80
WiFiServer server(80);

void setup() {
  modeAccessPoint();
}

void loop() {
  waitIncomingConnection();
}

void modeAccessPoint() {
  // Wifi ------------------------------------------------------------------------------
  // Sets WiFi as Access_Point
  WiFi.mode(WIFI_AP);
  // Creates the Acess_Point network
  WiFi.softAP(ssid, password);
  // Starts the TCP server on the port declared at the beginning
  server.begin();
  // ----------------------------------------------------------------------------------
}

// Waiting for someone to connect, when it connects it starts to do something
void waitIncomingConnection()
{
  // Imput data
  String inData = "";
  // Create a client object
  WiFiClient client = server.available();
  // If you created the client object successfully
  if (client) {
    // If there is a client connected
    while (client.connected()) {
      if (client.available()) {
        char recieved = client.read();
        inData += recieved;
        if (recieved == '\n')
        {
  
          // Resets the indata variable to pick up the next command
          inData = "";
        }
      }
    }
    // Close the connection
    client.stop();
  }
}

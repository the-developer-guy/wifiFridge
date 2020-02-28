#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "server.h"
#include "adc.h"
#include "digitalIo.h"
#include "htmlText.h"

WiFiServer server(80);
WiFiClient client;

String header;
String compressorState = "off";

unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;


void startServer(void)
{
  server.begin();
}

void checkClient(void)
{
 
  client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println(htmlResponseOk());
            
            // Display the HTML web page
            client.println(htmlHeading());
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println(htmlTextCss());
            
            // Web Page Heading
            client.println(htmlTitle());
            
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>Vault 1337 Fridge</p>");
            if(ioDoorOpen())
            {
              client.println("<p>Door open!</p>");
            }
            else
            {
              client.println("<p>Door closed.</p>");
            }
            client.print("<p>Fridge temperature: ");
            client.print(getAdcText());
            client.println("&deg;C</p>");
            

            if (ioCoolingOn()) {
              client.println("<p>Cooling...</p>");
            }
            client.println("</body></html>\n");
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

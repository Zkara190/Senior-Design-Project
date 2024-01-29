#include "WiFiS3.h"
#define SECRET_SSID "Charles Laptop"
#define SECRET_PASS "51+9tQ66"
#define relay 2
#define relaytwo 3
#define relaythree 4
String header;
String output = "off";

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)

int led =  LED_BUILTIN;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Access Point Web Server");

  pinMode(relay, OUTPUT); // set the Relay pin mode
  pinMode(relaytwo, OUTPUT);
  pinMode(relaythree, OUTPUT);

  digitalWrite(relay, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // by default the local IP address will be 192.168.4.1
  // you can override it with the following:
  WiFi.config(IPAddress(192,48,56,2));

  // print the network name (SSID);
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  }

  // wait 10 seconds for connection:
  delay(10000);

  // start the web server on port 80
  server.begin();

  // you're connected now, so print out the status
  printWiFiStatus();
}


void loop() {
  
  // compare the previous status to the current status
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }
  }
  
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      delayMicroseconds(10);                // This is required for the Arduino Nano RP2040 Connect - otherwise it will loop so fast that SPI will never be served.
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out to the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            // turns the relay on and off
            if (header.indexOf("GET /on") >= 0) {
              output = "on";
              digitalWrite(relay, LOW);
            } else if (header.indexOf("GET /off") >= 0) {
              output = "off";
              digitalWrite(relay, HIGH);
            }
           // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".on { background-color: #FF0000; border: 5px; color: white; padding: 16px 40px; border-radius: 20px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".off {background-color: #000000;border: 5px; color: white; padding: 16px 40px; border-radius: 20px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>");
            //text box
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head><title>Arduino Text Box</title></head>");
            client.println("<body>");
            client.println("<h1>Enter text:</h1>");
            client.println("<form action='/save' method='GET'>");
            client.println("<input type='text' name='textbox' id='textbox'>");
            client.println("<input type ='submit' value='Save'>");
            client.println("</form>");
            client.println("</body>");
            client.println("</html>");
            Serial.println("Get /save");
            //Webpage heading
            client.println("<body><h1>VATR Control Panel</h1>");  //creates labels for the webpage
            client.println("<p>Relay " + output + "</p>");
            if (output == "off") {
              client.println("<p><a href=\"/on\"><button class=\"off\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/off\"><button class=\"on\">ON</button></a></p>");
            }
             

            client.println("</body></html>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        
        // Check to see if the client request was "GET /H" or "GET /L":
        if (header.indexOf("GET /on") >= 0) {
              output = "on";
              digitalWrite(relay, LOW);
            } else if (header.indexOf("GET /off") >= 0) {
              output = "off";
              digitalWrite(relay, HIGH);
            }
      }
    }
    //clear header varible
   if(client.find("GET /save"))   // get value entered into the text box
   { String textboxValue = client.readStringUntil('\r');
   textboxValue.trim();   //trim any leading or trailing spaces
   delay(1000);
   }
    // close the connection:
    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Now open this URL on your browser --> http://");
  Serial.println(ip);
}

 

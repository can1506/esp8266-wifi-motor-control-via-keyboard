#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi credentials
const char* ssid = "wifi_name";
const char* password = "wifi_password";

// Motor control pins
const int IN3 = D1; 
const int IN4 = D2; 
const int ENB = D3;

// Create an instance of the ESP8266WebServer class on port 80
ESP8266WebServer server(80);

// Handle the root URL ("/") to display a simple web page with JavaScript for control
void handleRoot() {
  //  HTML page with JavaScript for controlling the ESP8266
  String html = "<html><body>";
  html += "<h1>ESP8266 Hiz Kontrol</h1>";
  html += "<p>ileri = 'w'</p>";
  html += "<script>"
          "var keyDown = false;"
          "document.addEventListener('keydown', function(event) {"
          "  if (event.key === 'w' && !keyDown) {"
          "    fetch('/receive?state=move');"
          "    keyDown = true;"
          "  } else if (event.key === 's' && !keyDown) {"
          "    fetch('/receive?state=reset');"
          "    keyDown = false;"
          "  }"  
          "});"
          "document.addEventListener('keyup', function(event) {"
          "  if (event.key === 'w') {"
          "    fetch('/receive?state=stop');"
          "    keyDown = false;"
          "  }"  
          "});"
          "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// Handle the "/receive" URL with the state parameter to control the motor
void handleReceive() {
  // Get the value of the "state" parameter from the URL 
  String state = server.arg("state");

  // Check the value of the "state" parameter and control the motor accordingly
  if (state == "move") {
    Serial.println("Forward");
    analogWrite(ENB, 150);
  } else if (state == "stop" || state == "reset") {
    Serial.println("Stop");
    analogWrite(ENB, 0);
  }

  // Redirect back to the root URL ("/")
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  // Set motor control pins as outputs
  Serial.begin(9600);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Set initial motor direction and speed
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println(WiFi.localIP());
  Serial.println("Connected to WiFi");

  // Set up HTTP handlers for the server and start the server
  server.on("/", HTTP_GET, handleRoot);
  server.on("/receive", HTTP_GET, handleReceive);
  server.begin();
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}
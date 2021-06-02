#include <ESP8266WiFi.h>

/**************************************************************
 *
 * In this IoT project, you control any electrical appliances 
 * with the help of Google assistant & Amazon's Alexa.
 *
 *   Project:                    https://github.com/KamranBabar16/KB-Smart-Home-Automation-Using-NodeMCU/
 *   My Website:                 https://bit.ly/3nNIqyj
 *   Social networks:            https://twitter.com/KamranBabar16
 *                               https://www.facebook.com/KamranBabarOfficial
 *                               https://www.linkedin.com/in/kamranbabar16/
 *
 **************************************************************
 *
 * NOTE: Use this only for non-commercial projects!!!
 *
 **************************************************************/

#include <IRrecv.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <BlynkSimpleEsp8266.h>
#include <EEPROM.h>
#include <StreamString.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;

int LDR = A0;

uint16_t RECV_PIN = D10;
IRrecv irrecv(RECV_PIN);
decode_results results;

const char *ssid = "WiFi_SSID";              //Your WiFi SSID
const char *password = "WiFi_PASS";                //Your WiFi Password
char auth[] = "BLYNK_AUTH"; //your blink auth token

int RELAY1 = D0;
int RELAY2 = D1;
int RELAY3 = D2;
int RELAY4 = D3;
int RELAY5 = D4;
int RELAY6 = D5;
int RELAY7 = D6;
int RELAY8 = D7;
int swval[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int errpin = D9;

WiFiServer server(80);

BLYNK_WRITE(V1)
{
  int pd1 = param.asInt();
  appchng(RELAY1, pd1, 1);
}
BLYNK_WRITE(V2)
{
  int pd2 = param.asInt();
  appchng(RELAY2, pd2, 2);
}
BLYNK_WRITE(V3)
{
  int pd3 = param.asInt();
  appchng(RELAY3, pd3, 3);
}
BLYNK_WRITE(V4)
{
  int pd4 = param.asInt();
  appchng(RELAY4, pd4, 4);
}
BLYNK_WRITE(V5)
{
  int pd5 = param.asInt();
  appchng(RELAY5, pd5, 5);
}
BLYNK_WRITE(V6)
{
  int pd6 = param.asInt();
  appchng(RELAY6, pd6, 6);
}
BLYNK_WRITE(V7)
{
  int pd7 = param.asInt();
  appchng(RELAY7, pd7, 7);
}
BLYNK_WRITE(V8)
{
  int pd8 = param.asInt();
  appchng(RELAY8, pd8, 8);
}

void appchng(int k, int q, int m)
{
  digitalWrite(k, q);
  swval[m] = q;
  EEPROM.write(m, q);
  EEPROM.commit();
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  //The ESP8266 tries to reconnect automatically when the connection is lost
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  delay(10);

  //eeprom
  EEPROM.begin(512);

  pinMode(LDR, INPUT);

  swval[1] = EEPROM.read(1);
  swval[2] = EEPROM.read(2);
  swval[3] = EEPROM.read(3);
  swval[4] = EEPROM.read(4);
  swval[5] = EEPROM.read(5);
  swval[6] = EEPROM.read(6);
  swval[7] = EEPROM.read(7);
  swval[8] = EEPROM.read(8);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(RELAY5, OUTPUT);
  pinMode(RELAY6, OUTPUT);
  pinMode(RELAY7, OUTPUT);
  pinMode(RELAY8, OUTPUT);
  pinMode(errpin, OUTPUT);
  digitalWrite(RELAY1, swval[1]);
  digitalWrite(RELAY2, swval[2]);
  digitalWrite(RELAY3, swval[3]);
  digitalWrite(RELAY4, swval[4]);
  digitalWrite(RELAY5, swval[5]);
  digitalWrite(RELAY6, swval[6]);
  digitalWrite(RELAY7, swval[7]);
  digitalWrite(RELAY8, swval[8]);
  digitalWrite(errpin, HIGH);

  // Connect to WiFi network
  initWiFi();
  //delay(5000);
  server.begin();

  Blynk.config(auth);
  Blynk.connect();
}

BLYNK_CONNECTED()
{
  Blynk.virtualWrite(V1, swval[1]);
  delay(100);
  Blynk.virtualWrite(V2, swval[2]);
  delay(100);
  Blynk.virtualWrite(V3, swval[3]);
  delay(100);
  Blynk.virtualWrite(V4, swval[4]);
  delay(100);
  Blynk.virtualWrite(V5, swval[5]);
  delay(100);
  Blynk.virtualWrite(V6, swval[6]);
  delay(100);
  Blynk.virtualWrite(V7, swval[7]);
  delay(100);
  Blynk.virtualWrite(V8, swval[8]);
  delay(100);
}
void relayswitch(int i, int j, int v)
{
  if (swval[j] == 1)
  {
    digitalWrite(i, LOW);
    swval[j] = 0;
    EEPROM.write(j, 0);
  }
  else
  {
    digitalWrite(i, HIGH);
    swval[j] = 1;
    EEPROM.write(j, 1);
  }
  EEPROM.commit();
  Blynk.virtualWrite(v, swval[j]);
}

void readLDR()
{
  LDR = analogRead(LDR);
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(0, LDR);
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(errpin, HIGH);
  }
  else
  {
    digitalWrite(errpin, LOW);
    Blynk.run();
  }

  //ir receiveing code

  //CHANGE VALUE ACCORDINGLY

  if (irrecv.decode(&results))
  {
    unsigned int ircode = results.value;
    //Serial.println(ircode);
    if (ircode == 1086290565)
    {
      relayswitch(RELAY1, 1, V1);
    }
    else if (ircode == 1086306885)
    {
      relayswitch(RELAY2, 2, V2);
    }
    else if (ircode == 1086290055)
    {
      relayswitch(RELAY3, 3, V3);
    }
    else if (ircode == 1086280365)
    {
      relayswitch(RELAY4, 4, V4);
    }
    else if (ircode == 1086296685)
    {
      relayswitch(RELAY5, 5, V5);
    }
    else if (ircode == 1086279855)
    {
      relayswitch(RELAY6, 6, V6);
    }
    else if (ircode == 1086282405)
    {
      relayswitch(RELAY7, 7, V7);
    }
    else if (ircode == 1086298725)
    {
      relayswitch(RELAY8, 8, V8);
    }
    irrecv.resume(); // Receive the next value
  }
  delay(100);

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  // Wait until the client sends some data
  while (!client.available())
  {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  client.flush();

  // Set RELAY according to the request
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
  client.println("<title>Amits Room</title>");
  client.println("<br><br>");

  // Return the response RELAY1
  client.print("Relay 1 is now: ");
  // Control RELAY 1
  if (request.indexOf("/RELAY1=ON") != -1)
  {
    digitalWrite(RELAY1, LOW);
    swval[1] = 0;
    EEPROM.write(1, 0);
    EEPROM.commit();
  }
  if (request.indexOf("/RELAY1=OFF") != -1)
  {
    digitalWrite(RELAY1, HIGH);
    swval[1] = 1;
    EEPROM.write(1, 1);
    EEPROM.commit();
  }
  if (swval[1] == 0)
  {
    client.print("ON");
  }
  if (swval[1] == 1)
  {
    client.print("OFF");
  }

  client.println("<br><br>");
  client.println("<a href=\"/RELAY1=ON\"\"><button>TURN ON </button></a>");
  client.println("<a href=\"/RELAY1=OFF\"\"><button>TURN OFF </button></a><br />");

  // Return the response RELAY2
  client.println("<br><br>");
  client.print("Relay 2 is now: ");
  // Control RELAY 2
  if (request.indexOf("/RELAY2=ON") != -1)
  {
    digitalWrite(RELAY2, LOW);
    swval[2] = 0;
    EEPROM.write(2, 0);
    EEPROM.commit();
  }
  if (request.indexOf("/RELAY2=OFF") != -1)
  {
    digitalWrite(RELAY2, HIGH);
    swval[2] = 1;
    EEPROM.write(2, 1);
    EEPROM.commit();
  }
  if (swval[2] == 0)
  {
    client.print("ON");
  }
  if (swval[2] == 1)
  {
    client.print("OFF");
  }

  client.println("<br><br>");
  client.println("<a href=\"/RELAY2=ON\"\"><button>TURN ON </button></a>");
  client.println("<a href=\"/RELAY2=OFF\"\"><button>TURN OFF </button></a><br />");

  // Return the response RELAY3
  client.println("<br><br>");
  client.print("Relay 3 is now: ");
  // Control RELAY 3
  if (request.indexOf("/RELAY3=ON") != -1)
  {
    digitalWrite(RELAY3, LOW);
    swval[3] = 0;
    EEPROM.write(3, 0);
    EEPROM.commit();
  }
  if (request.indexOf("/RELAY3=OFF") != -1)
  {
    digitalWrite(RELAY3, HIGH);
    swval[3] = 1;
    EEPROM.write(3, 1);
    EEPROM.commit();
  }
  if (swval[3] == 0)
  {
    client.print("ON");
  }
  if (swval[3] == 1)
  {
    client.print("OFF");
  }

  client.println("<br><br>");
  client.println("<a href=\"/RELAY3=ON\"\"><button>TURN ON </button></a>");
  client.println("<a href=\"/RELAY3=OFF\"\"><button>TURN OFF </button></a><br />");

  // Return the response RELAY4
  client.println("<br><br>");
  client.print("Relay 4 is now: ");
  // Control RELAY 4
  if (request.indexOf("/RELAY4=ON") != -1)
  {
    digitalWrite(RELAY4, LOW);
    swval[4] = 0;
    EEPROM.write(4, 0);
    EEPROM.commit();
  }
  if (request.indexOf("/RELAY4=OFF") != -1)
  {
    digitalWrite(RELAY4, HIGH);
    swval[4] = 1;
    EEPROM.write(4, 1);
    EEPROM.commit();
  }
  if (swval[4] == 0)
  {
    client.print("ON");
  }
  if (swval[4] == 1)
  {
    client.print("OFF");
  }

  client.println("<br><br>");
  client.println("<a href=\"/RELAY4=ON\"\"><button>TURN ON </button></a>");
  client.println("<a href=\"/RELAY4=OFF\"\"><button>TURN OFF </button></a><br />");

  // Return the response RELAY5
  client.println("<br><br>");
  client.print("Relay 5 is now: ");
  // Control RELAY 5
  if (request.indexOf("/RELAY5=ON") != -1)
  {
    digitalWrite(RELAY5, LOW);
    swval[5] = 0;
    EEPROM.write(5, 0);
    EEPROM.commit();
  }
  if (request.indexOf("/RELAY5=OFF") != -1)
  {
    digitalWrite(RELAY5, HIGH);
    swval[5] = 1;
    EEPROM.write(5, 1);
    EEPROM.commit();
  }
  if (swval[5] == 0)
  {
    client.print("ON");
  }
  if (swval[5] == 1)
  {
    client.print("OFF");
  }

  client.println("<br><br>");
  client.println("<a href=\"/RELAY5=ON\"\"><button>TURN ON </button></a>");
  client.println("<a href=\"/RELAY5=OFF\"\"><button>TURN OFF </button></a><br />");

  // Return the response RELAY6
  client.println("<br><br>");
  client.print("Relay 6 is now: ");
  // Control RELAY 6
  if (request.indexOf("/RELAY6=ON") != -1)
  {
    digitalWrite(RELAY6, LOW);
    swval[6] = 0;
    EEPROM.write(6, 0);
    EEPROM.commit();
  }
  if (request.indexOf("/RELAY6=OFF") != -1)
  {
    digitalWrite(RELAY6, HIGH);
    swval[6] = 1;
    EEPROM.write(6, 1);
    EEPROM.commit();
  }
  if (swval[6] == 0)
  {
    client.print("ON");
  }
  if (swval[6] == 1)
  {
    client.print("OFF");
  }

  client.println("<br><br>");
  client.println("<a href=\"/RELAY6=ON\"\"><button>TURN ON </button></a>");
  client.println("<a href=\"/RELAY6=OFF\"\"><button>TURN OFF </button></a><br />");

  // Return the response RELAY7
  client.println("<br><br>");
  client.print("Relay 7 is now: ");
  // Control RELAY 7
  if (request.indexOf("/RELAY7=ON") != -1)
  {
    digitalWrite(RELAY7, LOW);
    swval[7] = 0;
    EEPROM.write(7, 0);
    EEPROM.commit();
  }
  if (request.indexOf("/RELAY7=OFF") != -1)
  {
    digitalWrite(RELAY7, HIGH);
    swval[7] = 1;
    EEPROM.write(7, 1);
    EEPROM.commit();
  }
  if (swval[7] == 0)
  {
    client.print("ON");
  }
  if (swval[7] == 1)
  {
    client.print("OFF");
  }

  client.println("<br><br>");
  client.println("<a href=\"/RELAY7=ON\"\"><button>TURN ON </button></a>");
  client.println("<a href=\"/RELAY7=OFF\"\"><button>TURN OFF </button></a><br />");

  // Return the response RELAY8
  client.println("<br><br>");
  client.print("Relay 8 is now: ");
  // Control RELAY 8
  if (request.indexOf("/RELAY8=ON") != -1)
  {
    digitalWrite(RELAY8, LOW);
    swval[8] = 0;
    EEPROM.write(8, 0);
    EEPROM.commit();
  }
  if (request.indexOf("/RELAY8=OFF") != -1)
  {
    digitalWrite(RELAY8, HIGH);
    swval[8] = 1;
    EEPROM.write(8, 1);
    EEPROM.commit();
  }
  if (swval[8] == 0)
  {
    client.print("ON");
  }
  if (swval[8] == 1)
  {
    client.print("OFF");
  }

  client.println("<br><br>");
  client.println("<a href=\"/RELAY8=ON\"\"><button>TURN ON </button></a>");
  client.println("<a href=\"/RELAY8=OFF\"\"><button>TURN OFF </button></a><br />");
  client.println("</html>");

  delay(1);
}

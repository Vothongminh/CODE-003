//#VTM https://www.youtube.com/c/VTMVlogVoThongMinh
#include <DHT.h>                          //Add DHT.h library
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>            //Add LiquidCrystal_I2C.h library
#include <Wire.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
String apiKey = "*********";              // Enter your Write API key from ThingSpeak
const char* ssid = "*********";           // Give your wifi network name
const char* password = "**********";      // Give your wifi network password
const char* server = "api.thingspeak.com";
//#define led 20
#define DHTPIN 14 // what digital pin we're connected to
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;
//...........................................................................................
void setup()
{
  Serial.begin(9600);
  //pinMode(led, OUTPUT);
  dht.begin();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Wire.begin(2, 0);
  lcd.clear();
  lcd.begin();
  lcd.backlight();
  lcd.home();
  lcd.print("   Connected");
  delay(1000);
  cuonchu();
}
//...........................................................................................
void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
  lcd.setCursor(12, 0);
  lcd.print(t);
  lcd.setCursor(12, 1);
  lcd.print(h);
  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" degrees Celcius, Humidity: ");
    Serial.print(h);
    Serial.println("%. Send to Thingspeak.");
  }
  client.stop();

  Serial.println("Waiting...");

  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);
}
//...........................................................................................
void cuonchu() {
  // Cuộn 13 vị trí sang trái
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // Cuộn 1 vị trí sang trái:
    lcd.scrollDisplayLeft();
    // delay:
    delay(150);
  }

  // Cuộn 29 vị trí sang phải:
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    // Cuộn 1 vị trí sang phải:
    lcd.scrollDisplayRight();
    // wdelay:
    delay(150);
  }

  // Cuộn 16 vị trí sang trái
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // Cuộn 1 vị trí sang trái:
    lcd.scrollDisplayLeft();
    // delay:
    delay(150);
  }

  // delay:
  delay(1000);

}

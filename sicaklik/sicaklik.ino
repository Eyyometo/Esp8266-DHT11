#define BLYNK_TEMPLATE_ID "TMPL6V5ooMIwy"
#define BLYNK_TEMPLATE_NAME "Sicaklik Alarm"
#define BLYNK_AUTH_TOKEN "G877O3lrgDcYTFihbd62mbkWFEU0uFld"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> 

#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Biyikoglu";  //  wifi ismi
char pass[] = "metin1546542";  // wifi şifre

#define DHTPIN 2          // Dht 11 bağlantı pini D4 pini
#define DHTTYPE DHT11     // DHT 11  
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.println(t);
  Blynk.virtualWrite(V6, h);
  Blynk.virtualWrite(V5, t);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);


  if(t > 30){      //alarm vereceği değer ve üstü 
 
    Blynk.logEvent("sicaklik","Sıcaklık degeri yuksek");  //blynk sunucusu üzerinden mobil uygulamaya atar mesaj
  }
}

void setup(){
   Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(2500L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}
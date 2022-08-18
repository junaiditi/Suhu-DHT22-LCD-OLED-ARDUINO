#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSerif9pt7b.h>

#define dht_pin 2
#define led_merah 11
#define led_kuning 12
#define led_biru 13
#define buzzer 7
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DHTTYPE DHT22
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(dht_pin, DHTTYPE);

void setup(){
Serial.begin(115200);
dht.begin();
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
pinMode(buzzer, OUTPUT);
pinMode(led_merah, OUTPUT);
pinMode(led_kuning, OUTPUT);
pinMode(led_biru, OUTPUT);

}

void loop(){
delay(2000);
display.setFont(&FreeSerif9pt7b);
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0, 40);

float h = dht.readHumidity();
float suhu = dht.readTemperature();
float f = dht.readTemperature(true);

if (isnan (h) || isnan (suhu) || isnan (f)) {
  return;

}

float hif = dht.computeHeatIndex(f,h);
float hic = dht.computeHeatIndex(suhu,h, false);

if (suhu <29) {
  digitalWrite(led_merah, LOW);
  digitalWrite(led_kuning, LOW);
  digitalWrite(led_biru, HIGH);
  display.println("SUHU RENDAH");
  display.display();
  //tone(buzzer, LOW);

}

else if (suhu <=35 and suhu >=29){
  digitalWrite(led_merah, LOW);
  digitalWrite(led_kuning, HIGH);
  digitalWrite(led_biru, LOW);
  display.println("SUHU CUKUP");
  display.display();
  //tone(buzzer, 0);

}
else if (suhu >35){
  digitalWrite(led_merah, HIGH);
  digitalWrite(led_kuning, LOW);
  digitalWrite(led_biru, LOW);
  display.println("SUHU PANAS");
  display.display();
  tone(buzzer, 1000);
  delay(100);
  tone(buzzer, 500);
  delay(100);
}

else {
  digitalWrite(led_merah, LOW);
  digitalWrite(led_kuning, LOW);
  digitalWrite(led_biru, LOW);
  display.println("    ");
  display.display();
  //tone(buzzer, 0);
}
}

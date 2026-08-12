#include <Wire.h>
#include <Adafruit_BMP085.h>

#define seaLevelPressure_hPa 1013.25

Adafruit_BMP085 bmp;

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN A0       // Define the digital pin connected to DHT11
#define DHTTYPE DHT11   // Define sensor type

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

int rain_sensor = 10;
int switch1 = 11;

SoftwareSerial LIFISerial(2, 3);

void setup()
{
    Serial.begin(9600);
    LIFISerial.begin(9600);
    dht.begin();

    lcd.begin(16, 2);

    pinMode(rain_sensor, INPUT);
    pinMode(switch1, INPUT_PULLUP);

    lcd.setCursor(0, 0);
    lcd.print("Hilly ");
    lcd.setCursor(0, 1);
    lcd.print("Topographies");

    delay(1000);

    if (!bmp.begin()) {
        Serial.println("Could not find a valid BMP085 sensor, check wiring!");
        while (1) {}
    }
}

void loop()
{
    int rain_value = digitalRead(rain_sensor);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("rain_value: ");
    lcd.setCursor(0, 1);
    lcd.print(rain_value);

    delay(1000);

    int humidity = dht.readHumidity();
    int temperature = dht.readTemperature();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T: ");
    lcd.print(temperature);

    lcd.print(" H: ");
    lcd.print(humidity);

    delay(1000);

    int switch_value = digitalRead(switch1);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("switch_value: ");
    lcd.print(switch_value);

    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pressure = ");
    lcd.print(bmp.readPressure());
    lcd.print(" Pa");

    delay(1000);

    if (humidity >= 65)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("high humidity");

        delay(1000);

        String dataToSend = "high humidity";
        LIFISerial.println(dataToSend);

        delay(1000); // Delay
    }
    else if (rain_value == 0)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("RAIN ALERT!");

        delay(1000);

        String dataToSend = "RAIN ALERT!";
        LIFISerial.println(dataToSend);

        delay(1000); // Delay
    }

    // Check if vehicle is near
    else if (switch_value == 0)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("EMERGENCY ALERT");

        String dataToSend = "EMERGENCY ALERT!";
        LIFISerial.println(dataToSend);

        delay(1000); // Delay
    }
    else if (bmp.readPressure() >= 100000)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("abnormal pressure");

        String dataToSend = "abnormal pressure!";
        LIFISerial.println(dataToSend);

        delay(1000); // Delay
    }
    else
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("normal!");

        lcd.setCursor(0, 1);
        lcd.print("stay safe:)");

        String dataToSend = "normal!";
        LIFISerial.println(dataToSend);

        delay(1000);
    }

    delay(1000); // Adjust the delay as needed for performance
}

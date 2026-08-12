#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

int buzzer = 4;
int green_led = 6;

SoftwareSerial LIFISerial(2, 3);

String msg;

void setup()
{
    Serial.begin(9600);

    LIFISerial.begin(2400);

    lcd.begin(16, 2);

    lcd.setCursor(0, 0);
    lcd.print("Hilly ");
    lcd.setCursor(0, 1);
    lcd.print("Topographies");

    delay(3000);

    pinMode(buzzer, OUTPUT);
    pinMode(green_led, OUTPUT);

    digitalWrite(buzzer, LOW);
    digitalWrite(green_led, HIGH);

    // Initialize the software serial for Zigbee communication
}

void loop()
{
    if (LIFISerial.available())
    {
        String receivedData = LIFISerial.readStringUntil('\n'); // Read data until newline character

        if (receivedData.indexOf("high humidity") != -1)
        {
            digitalWrite(green_led, LOW);
            digitalWrite(buzzer, HIGH);

            delay(2000);

            digitalWrite(buzzer, LOW);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("high humidity");

            msg = "high humidity";
            SendMessage();

            delay(2000);
        }
        else if (receivedData.indexOf("RAIN ALERT!") != -1)
        {
            digitalWrite(green_led, LOW);
            digitalWrite(buzzer, HIGH);

            delay(2000);

            digitalWrite(buzzer, LOW);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("RAIN ALERT!");

            msg = "RAIN ALERT!";
            SendMessage();

            delay(2000);
        }
        else if (receivedData.indexOf("abnormal pressure!") != -1)
        {
            digitalWrite(green_led, LOW);
            digitalWrite(buzzer, HIGH);

            delay(2000);

            digitalWrite(buzzer, LOW);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("abnormal pressure!");

            msg = "abnormal pressure!";
            SendMessage();

            delay(2000);
        }
        else if (receivedData.indexOf("EMERGENCY ALERT!") != -1)
        {
            digitalWrite(green_led, LOW);
            digitalWrite(buzzer, HIGH);

            delay(2000);

            digitalWrite(buzzer, LOW);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("EMERGENCY ALERT!");

            msg = "EMERGENCY ALERT!";
            SendMessage();

            delay(2000);
        }
        else if (receivedData.indexOf("normal!") != -1)
        {
            digitalWrite(buzzer, LOW);
            digitalWrite(green_led, HIGH);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("stay safe!");
        }
        else
        {
            digitalWrite(green_led, HIGH);
            digitalWrite(buzzer, LOW);
        }
    }
}

void SendMessage()
{
    Serial.println("AT"); // test check communication with gsm module
    delay(500);

    Serial.println("ATE0"); // ATE0: Switch echo off. ATE1: Switch echo on.
    delay(500);

    Serial.println("AT+CMGF=1"); // set sms text mode
    delay(500);

    Serial.println("AT+CMGS=\"+916302588517\"\r"); // send specific number
    delay(500);

    Serial.println(msg);
    delay(500);

    Serial.write(26);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Message sent..");

    Serial.println("Message sent..");
    delay(1000);
}

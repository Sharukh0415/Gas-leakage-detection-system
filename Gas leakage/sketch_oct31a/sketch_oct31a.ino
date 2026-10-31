
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD address and dimensions
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin configuration
#define GAS_SENSOR A0
#define BUZZER 8
#define LED 7

// Gas detection threshold
int gasThreshold = 400;

int gasValue = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(GAS_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(BUZZER, LOW);
  digitalWrite(LED, LOW);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print(" GAS DETECTOR ");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  delay(2000);
  lcd.clear();
}

void loop()
{
  // Read gas sensor value
  gasValue = analogRead(GAS_SENSOR);

  // Display sensor value
  Serial.print("Gas Level: ");
  Serial.println(gasValue);

  lcd.setCursor(0, 0);
  lcd.print("Gas Level: ");
  lcd.print(gasValue);
  lcd.print("   ");

  // Check gas leakage
  if (gasValue > gasThreshold)
  {
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("GAS LEAKAGE!   ");
  }
  else
  {
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED, LOW);

    lcd.setCursor(0, 1);
    lcd.print("AIR IS SAFE    ");
  }

  delay(500);
}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int BUTTON_PIN = 2;
const int BUZZER_PIN = 8;

// Reminder interval for testing.
// Change this to a longer interval for normal use.
const unsigned long REMINDER_INTERVAL = 60UL * 60UL * 1000UL; // 60 minutes

unsigned long lastDrinkTime = 0;
unsigned long drinkCount = 0;
bool reminderActive = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();

  lastDrinkTime = millis();

  lcd.setCursor(0, 0);
  lcd.print("Water Reminder");
  lcd.setCursor(0, 1);
  lcd.print("Ready!");
  delay(1500);

  updateDisplay();
}

void loop() {
  unsigned long now = millis();

  // Button pressed: record a drink and reset the timer.
  if (digitalRead(BUTTON_PIN) == LOW) {
    lastDrinkTime = now;
    drinkCount++;
    reminderActive = false;
    noTone(BUZZER_PIN);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Drink recorded!");
    lcd.setCursor(0, 1);
    lcd.print("Today: ");
    lcd.print(drinkCount);

    delay(1000);

    // Wait for the button to be released.
    while (digitalRead(BUTTON_PIN) == LOW) {
      delay(10);
    }

    updateDisplay();
  }

  // Reminder is due.
  if (!reminderActive && now - lastDrinkTime >= REMINDER_INTERVAL) {
    reminderActive = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Drink water!");
    lcd.setCursor(0, 1);
    lcd.print("Press button");

    tone(BUZZER_PIN, 2000);
  }

  // Show elapsed time while no reminder is active.
  static unsigned long lastDisplayUpdate = 0;
  if (!reminderActive && now - lastDisplayUpdate >= 1000) {
    lastDisplayUpdate = now;
    updateDisplay();
  }
}

void updateDisplay() {
  unsigned long elapsedMinutes = (millis() - lastDrinkTime) / 60000UL;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Since drink:");
  lcd.setCursor(0, 1);
  lcd.print(elapsedMinutes);
  lcd.print(" min  Today:");
  lcd.print(drinkCount);
}

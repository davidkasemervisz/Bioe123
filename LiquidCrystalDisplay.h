
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// address 0x27, 20x4 display
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

int current_rpm = -1;
int current_time;

void initDisplay() {
  lcd.init();
  lcd.backlight();
}

void updateDisplay(int rpm, int time) {
  if(current_rpm != rpm || current_time != time) {
    current_rpm = rpm;
    current_time = time;

    int minutes = time / 60;
    int seconds = time - minutes * 60;

    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.print("RPM: ");
    lcd.print(current_rpm);
    lcd.setCursor(1, 3);
    lcd.print("Time: ");
    lcd.print(minutes);
    lcd.print(":");
    if(seconds < 10) {
      lcd.print("0");
    }
    lcd.print(seconds);
  }
}

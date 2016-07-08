#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

struct LoginPassword {
  String _name;
  String login;
  String password;
};

struct ProgrammState {
  byte selectedLp;
  boolean lcdPrinted;
  byte lcdPrintPosition;
};

LoginPassword list[2] = {
  { "1 example", "e-mail@example.ru", "PaSsWWOrD"},
  { "2 example", "e-mail@example.ru", "$%$^NDG++_:>"}
};

ProgrammState state = {0, 0, 0};

void setup () {
  pinMode(A0, INPUT);
  digitalWrite(A0, HIGH);

  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop () {
  checkButtons();
  lcdPrint();
}

void lcdPrint () {
  if ( !state.lcdPrinted ) {
    state.lcdPrinted = true;
    lcd.clear();
    if ( state.lcdPrintPosition == 0 ) {
      lcd.print(list[state.selectedLp]._name);
    }
    if ( state.lcdPrintPosition == 1 ) {
      lcd.print(list[state.selectedLp]._name);
      lcd.setCursor(0, 1);
      lcd.print("Print Login");
    }
    if ( state.lcdPrintPosition == 2 ) {
      lcd.print(list[state.selectedLp]._name);
      lcd.setCursor(0, 1);
      lcd.print("Print Password");
    }
  }
}

void checkButtons () {
  int buttonPressed = analogRead(A0);
  if ( buttonPressed < 310 && state.lcdPrintPosition == 0 ) {
    state.selectedLp = max(state.selectedLp++, 1);
    delay(200);
    state.lcdPrinted = false;
  }
  else if ( buttonPressed < 450 && state.lcdPrintPosition == 0 ) {
    state.selectedLp = min(state.selectedLp--, 0);
    delay(200);
    state.lcdPrinted = false;
  }
  else if ( buttonPressed < 800 ) {
    if ( state.lcdPrintPosition == 0 ) {
      state.lcdPrintPosition = 1;
      state.lcdPrinted = false;
    } else if ( state.lcdPrintPosition == 1 ) {
      Serial.println(list[state.selectedLp].login);
      state.lcdPrintPosition = 2;
      state.lcdPrinted = false;
    } else if ( state.lcdPrintPosition == 2 ) {
      Serial.println(list[state.selectedLp].password);
      state.lcdPrintPosition = 0;
      state.lcdPrinted = false;
    }
    delay(200);
  }
}

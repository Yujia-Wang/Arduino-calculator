#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

const int rs = 12;
const int en = 10;
const int d4 = A4;
const int d5 = A5;
const int d6 = A6;
const int d7 = A7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', '='}
};
byte rowPins[rows] = {5, 4, 3, 2};
byte colPins[cols] = {9, 8, 7, 6};
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

boolean valOnePresent = false;
boolean next = false;
boolean final = false;
String num1;
String num2;
int ans;
char operation;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  char key = kpd.getKey();

  if (key != NO_KEY && (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9')) {
    if (valOnePresent == false) {
      num1 = num1 + key;
      lcd.clear();
      lcd.setCursor(16, 0);
      lcd.autoscroll();
      lcd.print(num1);
      lcd.noAutoscroll();
    } else {
      num2 = num2 + key;
      lcd.clear();
      lcd.setCursor(16, 0);
      lcd.autoscroll();
      lcd.print(num1);
      lcd.print(operation);
      lcd.print(num2);
      lcd.noAutoscroll();
      final = true;
    }
  } 
  else if (valOnePresent == false && key != NO_KEY && (key == '+' || key == '=')) {
    if (valOnePresent == false) {
      valOnePresent = true;
      operation = key;
      lcd.clear();
      lcd.setCursor(16, 0);
      lcd.autoscroll();
      lcd.print(num1);
      lcd.print(operation);
      lcd.noAutoscroll();
    }
  }
  else if (final == true && key != NO_KEY && key == '=') {
    ans = num1.toInt() + num2.toInt();
    lcd.clear();
    lcd.setCursor(16, 1);
    lcd.autoscroll();
    lcd.print('=');
    lcd.print(ans);
    lcd.noAutoscroll(); 
  }
  else if (key != NO_KEY && key == 'C') {
    lcd.clear();
    valOnePresent = false;
    final = false;
    num1 = "";
    num2 = "";
    ans = 0;
    operation = ' ';
  }
  

}

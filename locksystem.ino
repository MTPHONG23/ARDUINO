#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Khai báo các biến và định nghĩa các chân kết nối

const byte ROWS = 4; //Số hàng của keypad
const byte COLS = 4; //Số cột của keypad
char keys[ROWS][COLS] ={
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
}; //Khai báo các phím trên keypad

byte pin_rows[ROWS] = {9, 8, 7, 6}; //Chân kết nối hàng của keypad
byte pin_column[COLS] = {5, 4, 3, 2}; //Chân kết nối cột của keypad
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROWS, COLS);
//Khởi tạo keypad

LiquidCrystal_I2C lcd(0x27,16,2); //LCD 16x2  

const int buzzerPin = 10; // Chân kết nối còi báo
const int lockPin = 11; // Chân kết nối khóa điện từ

int password[3] = {7, 3, 8}; //Password cần nhập
int enterPassword[3]; //Mảng lưu password người dùng nhập vào
int index = 0; // Vị trí hiện tại của phím được nhấn
int maxcount = 3; //Số lần nhập password sai tối đa
int count = 0; //Biến đếm số lần nhập password sai

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(11,HIGH);
  // Khởi tạo chân kết nối
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("ENTER PASSWORD");
  delay(1000);
  lcd.clear();
  Serial.begin(9600);
  // Khởi tạo màn hình LCD
}

bool checkPassword() {
  // Hàm kiểm tra password nhập vào có đúng không
  for (int i = 0; i < 3; i++) {
    if (enterPassword[i] != password[i]) {
      return false;
    }
  }
  return true;
  
}
void loop() {
  // Đọc phím từ module bàn phím
  char key = keypad.getKey();
  if (key){
    Serial.println(key);
  }

  if (key != NO_KEY) {
    // Hiển thị số được nhập lên LCD
    lcd.setCursor(index+7, 0);
    lcd.print(key);
    enterPassword[index] = key - '0'; // Lưu giá trị phím vào mảng
    index++;// tăng index để nhập phần tử tiếp theo
    if (index == 3) {
      // Nếu đã nhập đủ 3 phím, kiểm tra password
      if (checkPassword()) {
        lcd.setCursor(4, 0);
        lcd.print(" CORRECT! "); // hiện dòng chữ Access granted! lên LCD
        delay(1000);
        lcd.clear(); // Xóa màn hình
        digitalWrite(lockPin, LOW); // Mở khóa nếu password đúng
        delay(5000);
        digitalWrite(lockPin, HIGH);
        delay(2000);
        lcd.clear();
        lcd.setCursor(2, 0);        
        lcd.print(" ENTER PASSWORD ");
        delay(1000);
        lcd.clear();
        index = 0;
        count=0;
      } else {
        count++;
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print(" INCORRECT! "); // Nếu password sai, kêu còi báo và yêu cầu nhập lại
        delay(500);
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print(" ENTER PASSWORD ");
        delay(1000);
        lcd.clear();
        index = 0;
        if (count ) 
        digitalWrite(lockPin, HIGH);
        if (count >= maxcount) {
          // Nếu nhập sai từ 3 lần trở lên, kêu còi báo và khóa lại
          lcd.setCursor(4,0);
          lcd.print("MAXIMUM");
          delay(1000);
          digitalWrite(buzzerPin, HIGH);
          delay(5000);
          digitalWrite(buzzerPin, LOW);
          lcd.clear();
          digitalWrite(lockPin, HIGH);
          delay(2000); } } } } }

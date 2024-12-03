#include <Arduino.h>

#define MQ2_PIN 12      // Chân GPIO kết nối với DO của MQ-2
#define BUZZER_PIN 16    // Chân GPIO kết nối với loa
#define nut 17   // Chân GPIO kết nối với nút bấm

bool isBuzzerOn = false;  // Trạng thái của loa (bật/tắt)
bool lastButtonState = false  ;  // Lưu trạng thái nút trước đó
bool buttonState = false;
bool bamnut = false;

void setup() {
  pinMode(MQ2_PIN, INPUT_PULLUP);   // Thiết lập chân MQ-2 là input
  pinMode(BUZZER_PIN, OUTPUT);      // Thiết lập chân loa là output
  pinMode(nut, INPUT_PULLUP); // Thiết lập chân nút bấm là input với PULLUP
  Serial.begin(115200);
}

void loop() {
  int sensorState = touchRead(MQ2_PIN);   // Đọc trạng thái MQ-2
  buttonState = digitalRead(nut);

  if (sensorState > 60){
    bamnut = 0;
    noTone(BUZZER_PIN);  // Tắt loa
    isBuzzerOn = false;  // Đánh dấu loa đã tắt
    Serial.println("Tay khong cham");
  }
  // Xử lý khi khí gas được phát hiện
  if (sensorState < 60 ) {
    Serial.println("Tay cham, nut chua duoc bam");
    tone(BUZZER_PIN, 1000);
    buttonState = digitalRead(nut);
    if (buttonState == 0) {bamnut = 1;} 
    if (bamnut == 1) {noTone(BUZZER_PIN); Serial.println("Tay cham, nut da duoc bam"); }
  }

  delay(500);
}

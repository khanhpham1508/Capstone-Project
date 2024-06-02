#define IN1 A1
#define IN2 A2
#define IN3 A3
#define IN4 A4
#define MAX_SPEED 225 
#define MIN_SPEED 0
const int sensor1 = 7;
const int potPin = A0;

// Biến để lưu giá trị đọc từ biến trở
int potValue = 0;  
// Thời gian chạy của motor
int motorRunTime = 0;
bool previousSensorState = HIGH;
void setup() {
  Serial.begin(9600);
  pinMode(sensor1, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
void motor_1_Dung() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
void motor_2_Dung() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void motor_1_Tien(int speed) { //speed: từ 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN1, HIGH);// chân này không có PWM
  analogWrite(IN2, 255 - speed);
}
void motor_1_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN1, LOW);// chân này không có PWM
  analogWrite(IN2, speed);
}
void motor_2_Tien(int speed) { //speed: từ 0 - MAX_SPEED
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  analogWrite(IN3, speed);
  digitalWrite(IN4, LOW);// chân này không có PWM
}
void motor_2_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);//đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED - http://arduino.vn/reference/constrain
  digitalWrite(IN3, LOW);// chân này không có PWM
  analogWrite(IN4, speed);
}
void Tien() {
  motor_1_Tien(MAX_SPEED); 
}
void Dung() {
  motor_1_Lui(MIN_SPEED);
}
void loop() {
  potValue = analogRead(potPin);
  int sensorValue = digitalRead(sensor1);
  motorRunTime = map(potValue, 0, 1023, 0, 5000);
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print("  Motor Run Time (ms): ");
  Serial.println(motorRunTime);
  // Hiển thị giá trị đọc được trên Serial Monitor
  Serial.print("Giá trị cảm biến: ");
  Serial.println(sensorValue);
if(sensorValue==LOW && previousSensorState == HIGH){
  Tien();
  delay(motorRunTime);
  Dung();
  }
  previousSensorState = sensorValue;
}

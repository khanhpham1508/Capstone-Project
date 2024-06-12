#define IN1 A1
#define IN2 A2
#define IN3 A3
#define IN4 A4
#define MAX_SPEED 100
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

// Hàm dừng motor 1
void motor_1_Dung() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

// Hàm dừng motor 2
void motor_2_Dung() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Hàm điều khiển motor 1 tiến tới với tốc độ 'speed'
void motor_1_Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED); // Đảm bảo giá trị nằm trong khoảng MIN_SPEED đến MAX_SPEED
  digitalWrite(IN1, HIGH); // Chân này không có PWM
  analogWrite(IN2, 255 - speed);
}

// Hàm điều khiển motor 1 lùi lại với tốc độ 'speed'
void motor_1_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED); // Đảm bảo giá trị nằm trong khoảng MIN_SPEED đến MAX_SPEED
  digitalWrite(IN1, LOW); // Chân này không có PWM
  analogWrite(IN2, speed);
}

// Hàm điều khiển motor 2 tiến tới với tốc độ 'speed'
void motor_2_Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED); // Đảm bảo giá trị nằm trong khoảng MIN_SPEED đến MAX_SPEED
  analogWrite(IN3, speed);
  digitalWrite(IN4, LOW); // Chân này không có PWM
}

// Hàm điều khiển motor 2 lùi lại với tốc độ 'speed'
void motor_2_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED); // Đảm bảo giá trị nằm trong khoảng MIN_SPEED đến MAX_SPEED
  digitalWrite(IN3, LOW); // Chân này không có PWM
  analogWrite(IN4, speed);
}

// Hàm điều khiển motor 1 tiến tới với tốc độ tối đa
void Tien() {
  motor_1_Tien(MAX_SPEED); 
}

// Hàm dừng motor 1
void Dung() {
  motor_1_Lui(MIN_SPEED);
}

void loop() {
  // Đọc giá trị từ biến trở
  potValue = analogRead(potPin);
  // Đọc giá trị từ cảm biến
  int sensorValue = digitalRead(sensor1);
  // Chuyển đổi giá trị biến trở sang thời gian chạy của motor
  motorRunTime = map(potValue, 0, 1023, 0, 5000);
  int DelayTime = motorRunTime *2;

  // Hiển thị giá trị biến trở và thời gian chạy của motor trên Serial Monitor
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print("  Motor Run Time (ms): ");
  Serial.println(motorRunTime);

  // Hiển thị giá trị cảm biến trên Serial Monitor
  Serial.print("Giá trị cảm biến: ");
  Serial.println(sensorValue);

  // Nếu giá trị cảm biến chuyển từ HIGH sang LOW
  if (sensorValue == LOW && previousSensorState == HIGH) {
    // Motor tiến tới
    Tien();
    // Dừng motor sau một khoảng thời gian
    delay(DelayTime);
    Dung();
  }

  // Cập nhật trạng thái cảm biến trước đó
  previousSensorState = sensorValue;
}

#include <Servo.h>
#include <NewPing.h>

/* ----------- PINS ----------- */
#define SERVO_PIN 7
#define TRIG_PIN 4
#define ECHO_PIN 3
#define BUTTON_PIN 2
#define PIR_PIN 12
#define LED_PIN 13

#define IR_SENSOR_RIGHT 5
#define IR_SENSOR_LEFT  6

/* ----------- CONSTANTS ----------- */
#define OBSTACLE_DISTANCE 50
#define STEP_FORWARD_TIME 200
#define STEP_STOP_TIME 300
#define TURN_TIME 900
#define HAND_DISTANCE 15

/* ----------- OBJECTS ----------- */
Servo scanServo;
NewPing sonar(TRIG_PIN, ECHO_PIN, 200);

/* ----------- STATES ----------- */
bool robotEnabled = false;
bool buttonLatched = false;

enum RobotMode
{
  OBSTACLE_MODE,
  HUMAN_FOLLOW_MODE
};

RobotMode currentMode = OBSTACLE_MODE;

/* ----------- MOTOR PINS ----------- */
int rightMotorPin1 = 11;
int rightMotorPin2 = 10;
int leftMotorPin1  = 9;
int leftMotorPin2  = 8;

/* ----------- SERVO TIMER (HUMAN FOLLOW) ----------- */
unsigned long lastServoUpdate = 0;

void setup()
{
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);

  scanServo.attach(SERVO_PIN);
  scanServo.write(90);

  digitalWrite(LED_PIN, LOW);
  stopMotors();
}

void loop()
{
  handleButton();

  if (!robotEnabled)
  {
    stopMotors();
    scanServo.write(90);
    digitalWrite(LED_PIN, LOW);
    return;
  }

  if (currentMode == OBSTACLE_MODE)
  {
    obstacleAvoidanceLogic();
  }
  else
  {
    humanFollowLogic();
  }
}

/* ================= BUTTON ================= */
void handleButton()
{
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && !buttonLatched)
  {
    robotEnabled = !robotEnabled;
    buttonLatched = true;
    delay(50);
  }

  if (buttonState == HIGH)
  {
    buttonLatched = false;
  }
}

/* ================= OBSTACLE MODE ================= */
void obstacleAvoidanceLogic()
{
  scanServo.write(90);
  delay(120);

  int distance = sonar.ping_cm();

  if (distance == 0 || distance > OBSTACLE_DISTANCE)
  {
    moveForward();
    delay(STEP_FORWARD_TIME);
    stopMotors();
    delay(STEP_STOP_TIME);
  }
  else
  {
    stopMotors();
    delay(300);

    moveBackward();
    delay(200);
    stopMotors();
    delay(300);

    scanServo.write(180);
    delay(400);
    int distanceLeft = sonar.ping_cm();

    scanServo.write(0);
    delay(400);
    int distanceRight = sonar.ping_cm();

    scanServo.write(90);
    delay(300);

    if (distanceLeft == 0 || distanceLeft > distanceRight)
    {
      turnLeft();
      delay(TURN_TIME);
    }
    else
    {
      turnRight();
      delay(TURN_TIME);
    }

    stopMotors();
    delay(200);

    /* ----- PIR CHECK AFTER TURN ----- */
    digitalWrite(LED_PIN, LOW);
    unsigned long startTime = millis();

    while (millis() - startTime < 2000)
    {
      if (digitalRead(PIR_PIN) == HIGH)
      {
        digitalWrite(LED_PIN, HIGH);
        currentMode = HUMAN_FOLLOW_MODE;
        return;
      }
    }
  }
}

/* ================= HUMAN FOLLOW MODE ================= */
void humanFollowLogic()
{
  if (millis() - lastServoUpdate >= 1)
  {
    scanServo.write(90);
    lastServoUpdate = millis();
  }

  int irRight = digitalRead(IR_SENSOR_RIGHT);
  int irLeft  = digitalRead(IR_SENSOR_LEFT);
  int distance = sonar.ping_cm();

  if (irLeft == LOW && irRight == HIGH)
  {
    turnLeft();
  }
  else if (irRight == LOW && irLeft == HIGH)
  {
    turnRight();
  }
  else if (distance > 0 && distance <= HAND_DISTANCE)
  {
    moveForward();
  }
  else
  {
    stopMotors();
  }
}

/* ================= MOTORS ================= */
void moveForward()
{
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
}

void moveBackward()
{
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
}

void turnLeft()
{
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
}

void turnRight()
{
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
}

void stopMotors()
{
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
}

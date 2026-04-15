#include <Servo.h>
#include <NewPing.h>

/* ----------- PINS ----------- */
#define SERVO_PIN 7
#define TRIG_PIN 4
#define ECHO_PIN 3
#define BUTTON_PIN 2

// Motor driver pins
int rightMotorPin1 = 11; // IN1
int rightMotorPin2 = 10; // IN2
int leftMotorPin1  = 9;  // IN3
int leftMotorPin2  = 8;  // IN4

/* ----------- CONSTANTS ----------- */
#define OBSTACLE_DISTANCE 50
#define STEP_FORWARD_TIME 200
#define STEP_STOP_TIME 300
#define TURN_TIME 1200   // <<< increased for ~80–90° turn

Servo scanServo;
NewPing sonar(TRIG_PIN, ECHO_PIN, 200);

/* ----------- ON / OFF STATE ----------- */
bool robotEnabled = false;
bool buttonLatched = false;

void setup()
{
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  scanServo.attach(SERVO_PIN);
  scanServo.write(90);

  stopMotors();
}

void loop()
{
  handleButton();

  if (!robotEnabled)
  {
    stopMotors();
    scanServo.write(90);
    return;
  }

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
      delay(TURN_TIME);   // <<< stronger left turn
    }
    else
    {
      turnRight();
      delay(TURN_TIME);   // <<< stronger right turn
    }

    stopMotors();
    delay(200);
  }
}

/* ----------- BUTTON HANDLER ----------- */
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

/* ----------- MOTOR CONTROL ----------- */

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

// Turn LEFT → Right forward, Left backward
void turnLeft()
{
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
}

// Turn RIGHT → Left forward, Right backward
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

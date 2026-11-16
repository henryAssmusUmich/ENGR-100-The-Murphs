//STEPPER STUFF
#include <AccelStepper.h>
#define N1 2  // 1N1
#define N2 3  // 1N2
#define N3 4  // 1N3
#define N4 12 // 1N4
#define stepsPerRev 4096
#define stepsPerIndex 512
double targetIndex = 0;
AccelStepper theStepper(AccelStepper::HALF4WIRE, N1,N2,N3,N4);
bool ALIGNED = false;

int indexToSteps(float index){
  return floor(index*stepsPerIndex);
}

float stepsToIndex(int steps){
  float indexPerStep = float(steps)/stepsPerIndex;
  return indexPerStep;
}

void runToIndex(int index){
  int steps = indexToSteps(index);
  theStepper.moveTo(steps);
}

void setup() {
  //STEPPER SETUP
  delay(2000);
  Serial.begin(115200);
  theStepper.setMaxSpeed(1000); // Arbitrary 
  theStepper.setAcceleration(1000); // Arbitrary
  theStepper.moveTo(0); // moves to zero off start
}

void loop() {
  //STEPPER LOOP
  runToIndex(targetIndex); 
  Serial.println("\n");
  int position = theStepper.currentPosition();
  float pos = stepsToIndex(position);
  Serial.print("The Position is: ");
  Serial.println(pos);
  double distToGo = theStepper.distanceToGo();
  if(distToGo == 0){
    ALIGNED = true;
  } else {
    ALIGNED = false;
  }
  theStepper.run();
  Serial.println(ALIGNED);
  Serial.println(distToGo);
  if(ALIGNED){
    delay(1000);
    targetIndex += 1;
    ALIGNED = false;
  }
  delay(100);
}



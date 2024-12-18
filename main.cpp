#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.



// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Daniel Acosta & Tanisha Hossain                           */
/*    Created:      May 22, 2024                                              */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"

// Allows for easier use of the VEX Library
using namespace vex;

// competition
competition Comp;
brain br;

// controller
controller cr;

//correction variables
//TEST THESE BEFORE COMP
//TEST THESE BEFORE COMP
//TEST THESE BEFORE COMP
double radToRPM = 1;
int turnb = 100;

//vector
double posX = 0;
double posY = 0;

motor mFL(PORT1);
motor mFR(PORT10);
motor mBL(PORT11);
motor mBR(PORT20);

// motor for latch and forklift
motor mForkLift(PORT12);
motor mLatch(PORT3);
//motor mXeilin(PORT16);

//sensors
bumper bumpf(Brain.ThreeWirePort.G);
bumper bumpb(Brain.ThreeWirePort.B);
bumper bumpclaw(Brain.ThreeWirePort.A); //CHOOSE PORT (IDK)
vision visf(PORT6);

void a(){mForkLift.spin(forward,10,rpm);}
void fu(){mForkLift.spin(reverse,10,rpm);}
//void b(){mLatch.spin(forward,10,rpm);}
//void c(){mLatch.spin(reverse,10,rpm);}


//turns x degreees
void turnX(int x){
  mFR.spinToPosition(x + mFR.position(degrees),degrees);
  mBR.spinToPosition(-x + mBR.position(degrees),degrees);
}

void moveForward(){
  mFR.spin(forward,50,rpm);
  mBR.spin(forward,50,rpm);
  //mFL.spin(forward,50,rpm);
  //mBL.spin(forward,50,rpm);
}
//code to run during drive control period
void drv(){
  //drives the robot
  mFR.spin(forward,(cr.Axis3.position() - cr.Axis4.position()), rpm);
  mBR.spin(forward,(cr.Axis3.position() - cr.Axis4.position()), rpm);


  //latch
  cr.ButtonR1.pressed(b);
  cr.ButtonR2.pressed(c);
}


//uses vision sensor to find nearest object and goes to it
void sense(){
  visf.takeSnapshot(blue);

  if (!visf.objects[0].exists) {
    turnX(45);
    visf.takeSnapshot(blue);
  }else{

    //rotates it until it's in the correct direction
    while(!(185> visf.largestObject.centerX >125)){
      visf.takeSnapshot(blue);
      if(185< visf.largestObject.centerX){
        turnX(-5);
      } else if (visf.largestObject.centerX < 125){
        turnX(5);
      }else{
        break;
      }
    }
    moveForward();

    //chinchilla
  }

  wait(0.5, seconds);
}

//code for self driving
void automous(){
  bumpf.pressed(turn180);
  mLatch.spin(forward);//CHECK THIS LATER
  sense();
}

//for testing
void motorTest(){
  mFR.spin(forward,(cr.Axis3.position() - cr.Axis4.position()), rpm);
  mBR.spin(forward,(cr.Axis3.position() - cr.Axis4.position()), rpm);
  mFL.spin(forward,(cr.Axis3.position() + cr.Axis4.position()), rpm);
  mBL.spin(forward,(cr.Axis3.position() + cr.Axis4.position()), rpm);
}

int main() {
  //Comp.autonomous(automous);
  //Comp.drivercontrol(drv);
  

  while (true) {
    motorTest();
  }

  return 0;
}

// File:          flippy_controller.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/TouchSensor.hpp>
#include <webots/Motor.hpp>
#include <iostream>

// All the webots classes are defined in the "webots" namespace
using namespace webots;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();

  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();
  
  Motor *m1 = robot->getMotor("M1");
  Motor *m2 = robot->getMotor("M2");
  m1->setPosition(INFINITY);
  // m2->setPosition(INFINITY);
  m1->setVelocity(-1.0);
  // m2->set_Velocity(1.0);
  TouchSensor *t1 = robot->getTouchSensor("T1");
  TouchSensor *t2 = robot->getTouchSensor("T2");
  
  t1->enable(timeStep);
  t2->enable(timeStep);

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(timeStep) != -1) {
    // Read the sensors:
    // Enter here functions to read sensor data, like:
    double val = t2->getValue();
    std::cout << val << std::endl;  
    // Process sensor data here.

    // Enter here functions to send actuator commands, like:
    //  motor->setPosition(10.0);
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}

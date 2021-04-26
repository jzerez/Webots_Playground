// File:          flippy_controller.cpp
// Date:          Spring, 2021
// Description:   Basic controller for 3D flippy robot
// Author:        Jonathan Zerez
// Modifications:

// Include Standar WeBots libraries
#include <webots/Robot.hpp>
#include <webots/TouchSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Device.hpp>
#include <webots/Receiver.hpp>
#include <webots/Emitter.hpp>
#include <webots/Connector.hpp>


// Include standard C++ libraries
#include <string>
#include <iostream>
#include <cstring>

// All the webots classes are defined in the "webots" namespace
using namespace webots;

const float VELOCITY = 1.0;

// This is the main program of your controller.
// It creates an instance of the Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.

// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, const char *argv[]) {

  std::cout << "INITIALIZING CONTROLLER" << std::endl;
  // create the Robot instance.
  Robot* robot = new Robot();

  std::string s1_name = robot->getName().append("_S1");
  std::string s2_name = robot->getName().append("_S2");
  

  // get the time step of the current world (in milliseconds)
  int timeStep = (int)robot->getBasicTimeStep();

  // Initialize motors (pointers)
  Motor* m1 = robot->getMotor("M1");
  Motor* m2 = robot->getMotor("M2");

  // Initialize motor operating modes (INFINITY means velocity driven)
  m1->setPosition(INFINITY);
  m1->setVelocity(0.0);
  m2->setPosition(INFINITY);
  m2->setVelocity(VELOCITY);

  // Initialize touchsensors (pointers)
  TouchSensor* t1 = robot->getTouchSensor("T1");
  TouchSensor* t2 = robot->getTouchSensor("T2");

  // Enable touch sensors. Sets refresh frequency to timeStep
  t1->enable(timeStep);
  t2->enable(timeStep);

  Receiver* r1 = robot->getReceiver("R1");
  r1->enable(timeStep);
  
  Emitter* e1 = robot->getEmitter("E1");
  
  // Which sphere is moving. 0 for none, 1 for sphere1, 2 for sphere2
  int moving_sphere;

  // The first argument in controllerArgs specifies which sphere is moving
  if (strcmp(argv[1], "0") == 0) {
    moving_sphere = 0;
    m1->setPosition(INFINITY);
    m1->setVelocity(1.0);
    m2->setPosition(INFINITY);
    m2->setVelocity(1.0);

    std::cout << "STATE IS: 0. NO MOVEMENT" << std::endl;
  } else if (strcmp(argv[1], "1") == 0) {
    moving_sphere = 1;
    std::cout << "STATE IS: 1. SPHERE 1 WILL MOVE FIRST" << std::endl;
  } else if (strcmp(argv[1], "2") == 0) {
    moving_sphere = 2;
    std::cout << "STATE IS: 2. SPHERE 2 WILL MOVE FIRST" << std::endl;
  } else {
    moving_sphere = 1;
    std::cout << "STATE IS: DEFAULT. SPHERE 1 WILL MOVE FIRST" << std::endl;
  }
  moving_sphere = 1;

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(timeStep) != -1) {
    switch(moving_sphere) {
      case 0:
        // robot is not moving
        std::cout << moving_sphere << t1->getValue() << t2->getValue() << std::endl;
        
        break;
      case 1:
        // Sphere1 is moving about sphere2

        // IF the robot registers a touch through the touch sensor, pivot
        if (t1->getValue() == 1) {
          m2->setVelocity(0.0);
          e1->send(s2_name.c_str(), sizeof(s2_name.c_str()));
          e1->send(s1_name.c_str(), sizeof(s1_name.c_str()));
          m1->setVelocity(VELOCITY);
          moving_sphere = 2;
        }
        break;
      case 2:
        // sphere2 is moving about sphere1
        // If the robot registers a touch through the touch sensor, pivot
        if (t2->getValue() == 1) {
          m1->setVelocity(0.0);
          e1->send(s1_name.c_str(), sizeof(s1_name.c_str()));
          e1->send(s2_name.c_str(), sizeof(s2_name.c_str()));
          m2->setVelocity(VELOCITY);
          moving_sphere = 1;
        }
        break;
    }
    // read the value of the touch sensor at the second sphere
    // double val = t2->getValue();
    // std::cout << val << std::endl;

    // sample code for recieving messages from the physics plug-in (not working)
    // std::cout<< "new message recieved" << std::endl;
    if (r1->getQueueLength() > 0) {
      std::cout<<r1->getData()<<std::endl;
      r1->nextPacket();
    }
    

  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}

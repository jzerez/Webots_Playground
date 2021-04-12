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
#include <webots/Connector.hpp>

// Include standard C++ libraries
#include <string>
#include <iostream>
#include <cstring>

// All the webots classes are defined in the "webots" namespace
using namespace webots;

const float VELOCITY = 1.0;
bool pivot(
  TouchSensor* curr_moving_sensor,
  Motor* curr_moving_motor,
  Motor* curr_stationary_motor,
  Connector* curr_moving_connector,
  Connector* curr_stationary_connector,
  Connector* curr_moving_sym_connector,
  Connector* curr_stationary_sym_connector,
  std::string debug = "None"
){
  // checks to see if the moving node has made contact, and then switches the moving node
  // NOTE: curr_moving_motor is the one that is spinning. It is NOT translating in space.
  if (curr_moving_sensor->getValue() == 1) {
    std::cout << debug << std::endl;
    curr_moving_motor->setVelocity(0.0);
    if (curr_moving_sym_connector->getPresence() == 1){
      curr_stationary_connector->unlock();
      curr_stationary_sym_connector->unlock();
      curr_moving_sym_connector->lock();
      curr_stationary_motor->setVelocity(VELOCITY);
      std::cout << "HIT OTHER FLIPPY" << std::endl;
      return true;
    } else if (curr_moving_connector->getPresence() == 1) {
      curr_stationary_connector->unlock();
      curr_stationary_sym_connector->unlock();
      curr_moving_connector->lock();
      curr_stationary_motor->setVelocity(VELOCITY);
      std::cout << "HIT FLOOR" << std::endl;
      return true;
    } else {
      std::cout << "NO JOINT FOUND" << std::endl;
    }
  }
  return false;

}

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

  // Initialize connectors (pointers)
  // NOTE: we don't need to Initialize the floor joint because it is passive
  // TODO: see if a symetric connector will work without being defined in cpp
  Connector* s1_joint = robot->getConnector("s1_connector");
  Connector* s2_joint = robot->getConnector("s2_connector");
  Connector* s1_sym_joint = robot->getConnector("s1_sym_connector");
  Connector* s2_sym_joint = robot->getConnector("s2_sym_connector");

  // Set the query frequency in ms
  s1_joint->enablePresence(timeStep);
  s2_joint->enablePresence(timeStep);
  s1_sym_joint->enablePresence(timeStep);
  s2_sym_joint->enablePresence(timeStep);

  // Lock the connections in place (no relative movement)
  // s1_joint->lock();
  s2_joint->lock();

  // Which sphere is moving. 0 for none, 1 for sphere1, 2 for sphere2
  int moving_sphere;
=
  // The first argument in controllerArgs specifies which sphere is moving
  if (strcmp(argv[1], "0") == 0) {
    moving_sphere = 0;
    m1->setPosition(INFINITY);
    m1->setVelocity(0.0);
    m2->setPosition(INFINITY);
    m2->setVelocity(0.0);
    s1_joint->lock();
    s2_joint->lock();
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


  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(timeStep) != -1) {
    switch(moving_sphere) {
      case 0:
        // robot is not moving
        // std::cout << "stationary" << std::endl;
        break;
      case 1:
        // Sphere1 is moving about sphere2

        // IF the robot registers a touch through the touch sensor, pivot
        if (pivot(t1, m2, m1, s1_joint, s2_joint, s1_sym_joint, s2_sym_joint, "SPHERE1 MOVING")) {
          moving_sphere = 2;
        }
        break;
      case 2:
        // sphere2 is moving about sphere1
        // If the robot registers a touch through the touch sensor, pivot
        if (pivot(t2, m1, m2, s2_joint, s1_joint,  s2_sym_joint, s1_sym_joint, "SPHERE2 MOVING")) {
          moving_sphere = 1;
        }
        break;
    }
    // read the value of the touch sensor at the second sphere
    // double val = t2->getValue();
    // std::cout << val << std::endl;

    // sample code for recieving messages from the physics plug-in (not working)
    // std::cout<< "new message recieved" << std::endl;
    // std::cout<<wb_receiver_get_data(r1)<<std::endl;

  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}

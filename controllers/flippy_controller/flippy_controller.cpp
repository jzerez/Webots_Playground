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
#include <webots/Device.hpp>
#include <webots/Receiver.hpp>
#include <webots/Connector.hpp>
#include <string>
#include <iostream>

// All the webots classes are defined in the "webots" namespace
using namespace webots;

void pivot(
  TouchSensor* curr_moving_sensor,
  Motor* curr_moving_motor,
  Motor* curr_stationary_motor,
  Connector* curr_moving_connector,
  Connector* curr_stationary_connector
){
  // checks to see if the moving node has made contact, and then switches the moving node
  // NOTE: curr_moving_motor is the one that is spinning. It is NOT translating in space.
  if (curr_moving_sensor->getValue() == 1) {
    curr_moving_motor->setVelocity(0.0);
    if (curr_moving_connector->getPresence() == 1) {
      curr_moving_connector->lock();
      curr_stationary_connector->unlock();
      curr_stationary_motor->setVelocity(1.0);
    }
  }
  
}


// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {

  std::cout << "INITIALIZING CONTROLLER" << std::endl;
  // create the Robot instance.
  Robot* robot = new Robot();

  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();

  // Initialize motors (pointers)
  Motor* m1 = robot->getMotor("M1");
  Motor* m2 = robot->getMotor("M2");

  m1->setPosition(INFINITY);
  m1->setVelocity(0.0);
  m2->setPosition(INFINITY);
  m2->setVelocity(1.0);

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

  // Set the query frequency in ms
  s1_joint->enablePresence(10);
  s2_joint->enablePresence(10);

  // Lock the connections in place
  // s1_joint->lock();
  s2_joint->lock();

  // which sphere is moving. 0 for none, 1 for sphere1, 2 for sphere2
  int moving_sphere = 1;


  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(timeStep) != -1) {
      switch(moving_sphere) {
        case 0:
          // robot is not moving
          std::cout << "stationary" << std::endl;
          break;
        case 1:
          // Sphere1 is moving about sphere2
          pivot(t1, m2, m1, s1_joint, s2_joint);
          moving_sphere = 2;
          break;
        case 2:
          // sphere2 is moving about sphere1
          pivot(t2, m1, m2, s2_joint, s1_joint);
          moving_sphere = 1;
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

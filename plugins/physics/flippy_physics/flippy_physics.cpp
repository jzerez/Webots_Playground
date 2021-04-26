/*
 * File: flippy_physics.cpp
 * Date: Spring, 2021
 * Description: Custom Physics plugin for flippy. Handles crawling over terrain
 * Author: Jonathan Zerez
 * Modifications:
 */

#include <ode/ode.h>
#include <plugins/physics.h>
#include <iostream>
#include <unordered_set>

static pthread_mutex_t mutex; // needed to run with multi-threaded version of ODE

typedef enum {STATIONARY_1, STATIONARY_2} states;

static dBodyID robot_body {};
static dBodyID floor_body {};
static dBodyID sphere1_body {};
static dBodyID sphere2_body {};
std::unordered_set<dJointID> joints {};



/*
 * Note: This plugin will become operational only after it was compiled and associated with the current world (.wbt).
 * To associate this plugin with the world follow these steps:
 *  1. In the Scene Tree, expand the "WorldInfo" node and select its "physics" field
 *  2. Then hit the [Select] button at the bottom of the Scene Tree
 *  3. In the list choose the name of this plugin (same as this file without the extention)
 *  4. Then save the .wbt by hitting the "Save" button in the toolbar of the 3D view
 *  5. Then reload the world: the plugin should now load and execute with the current simulation
 */


// Removes all user-created joints from a specified body DEF
void remove_joints(const char* body_def) {
  dBodyID body = dWebotsGetBodyFromDEF(body_def);
  int num_joints = dBodyGetNumJoints(body);
  for (int i = 0; i < num_joints; i++) {
    dJointID joint = dBodyGetJoint(body, i);
    // Only user-created joints will be in the joints set
    if (joints.find(joint) != joints.end()) {
      joints.erase(joint);
      dJointDisable(joint);
    }

  }
}

// Creates a fixed joints between two specified bodies
void add_fixed_joint(dBodyID b1, dBodyID b2) {
  dWorldID joint_world = dBodyGetWorld(b1);
  pthread_mutex_lock(&mutex);
  dJointID joint = dJointCreateFixed(joint_world, 0);
  dJointAttach(joint, b1, b2);
  dJointSetFixed(joint);
  joints.insert(joint);
  pthread_mutex_unlock(&mutex);
}

void webots_physics_init() {
  pthread_mutex_init(&mutex, NULL);

  dWebotsConsolePrintf("INITIALIZING PHYSICS...");

  // Initialize Simulation Bodies
  // TODO: Need to initialize bodies in a for loop when it comes to multi-agents
  robot_body = dWebotsGetBodyFromDEF("FLIPPY");
  floor_body = dWebotsGetBodyFromDEF("FLOOR");
  sphere1_body = dWebotsGetBodyFromDEF("F000_S1");
  sphere2_body = dWebotsGetBodyFromDEF("F000_S2");


  dWorldID world = dBodyGetWorld(robot_body);

  // Create initial joint
  // TODO: create joint according to robot state only.
  dWebotsConsolePrintf("creating joint....");


  pthread_mutex_lock(&mutex);
  // Creates a fixed joint belonging to the world ID, with the default joint group ID (0)
  dJointID joint = dJointCreateFixed(world, 0);
  dJointAttach(joint, sphere2_body, floor_body);
  // Fixes the bodies while maintaining their current relative orientations and displacements
  dJointSetFixed(joint);
  // Add the user-created joint to the set of joints
  // Required because otherwise we'd delete joints between the solid bodies of a single flippy
  joints.insert(joint);
  pthread_mutex_unlock(&mutex);

}

void webots_physics_step() {
  /*
   * Do here what needs to be done at every time step, e.g. add forces to bodies
   *   dBodyAddForce(body1, f[0], f[1], f[2]);
   *   ...
   */

  // Read data incomming from the controller
  int dataSize;
  const char* data = (const char*)dWebotsReceive(&dataSize);
  if (dataSize > 0) {
    // This code parses the messages in the packet
    char *msg = new char[dataSize];
    int count = 1, i = 0, j = 0;
    for ( ; i < dataSize; ++i) {
      char c = data[i];
      if (c == '\0') {
        msg[j] = c;
        if (count == 1) {
          // This is the first message in the package.
          // Specifies the body (by DEF) to unfix
          dWebotsConsolePrintf("REMOVING JOINTS FROM: ");
          dWebotsConsolePrintf(msg);
          remove_joints(msg);
        } else {
          // This is the second message in the package.
          // Specifies the body (by DEF) to fix
          dWebotsConsolePrintf("ADDING JOINT TO: ");
          dWebotsConsolePrintf(msg);
          dBodyID body1 = dWebotsGetBodyFromDEF(msg);
          dBodyID body2 = dWebotsGetBodyFromDEF("FLOOR");
          add_fixed_joint(body1, body2);
        }
        ++count;
        j = 0;
      } else {
        msg[j] = c;
        ++j;
      }
    }

  }


}

int webots_physics_collide(dGeomID g1, dGeomID g2) {
  /*
   * This function needs to be implemented if you want to overide Webots collision detection.
   * It must return 1 if the collision was handled and 0 otherwise.
   * Note that contact joints should be added to the contact_joint_group which can change over the time, e.g.
   *   n = dCollide(g1, g2, MAX_CONTACTS, &contact[0].geom, sizeof(dContact));
   *   dJointGroupID contact_joint_group = dWebotsGetContactJointGroup();
   *   dWorldID world = dBodyGetWorld(body1);
   *   ...
   *   pthread_mutex_lock(&mutex);
   *   dJointCreateContact(world, contact_joint_group, &contact[i])
   *   dJointAttach(contact_joint, body1, body2);
   *   pthread_mutex_unlock(&mutex);
   *   ...
   */
   // dBodyID b1 = dGeomGetBody(g1);
   // dBodyID b2 = dGeomGetBody(g2);

  // if ((!dAreGeomsSame(g1, floor_geom) && dBodyGetNumJoints(b1) == 0) ||
       // (!dAreGeomsSame(g2, floor_geom) && dBodyGetNumJoints(b2) == 0)) {
    // add_fixed_joint(g1, g2);
    // return 1;
  // }
  return 0;
}

void webots_physics_cleanup() {
  /*
   * Here you need to free any memory you allocated in above, close files, etc.
   * You do not need to free any ODE object, they will be freed by Webots.
   */
  pthread_mutex_destroy(&mutex);
}

/*
 * File:
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

#include <ode/ode.h>
#include <plugins/physics.h>
#include <iostream>

static pthread_mutex_t mutex; // needed to run with multi-threaded version of ODE

typedef enum {STATIONARY_1, STATIONARY_2} states;

static dGeomID robot_geom {};
static dGeomID floor_geom {};
static dGeomID sphere1_geom {};
static dGeomID sphere2_geom {};

static dBodyID robot_body {};
static dBodyID floor_body {};
static dBodyID sphere1_body {};
static dBodyID sphere2_body {};

static dWorldID world {};

static states state;


/*
 * Note: This plugin will become operational only after it was compiled and associated with the current world (.wbt).
 * To associate this plugin with the world follow these steps:
 *  1. In the Scene Tree, expand the "WorldInfo" node and select its "physics" field
 *  2. Then hit the [Select] button at the bottom of the Scene Tree
 *  3. In the list choose the name of this plugin (same as this file without the extention)
 *  4. Then save the .wbt by hitting the "Save" button in the toolbar of the 3D view
 *  5. Then reload the world: the plugin should now load and execute with the current simulation
 */

void webots_physics_init() {
  pthread_mutex_init(&mutex, NULL);
  /*
   * Get ODE object from the .wbt model, e.g.
   *   dBodyID body1 = dWebotsGetBodyFromDEF("MY_ROBOT");
   *   dBodyID body2 = dWebotsGetBodyFromDEF("MY_SOLID");
   *   dGeomID geom2 = dWebotsGetGeomFromDEF("MY_SOLID");
   * If an object is not found in the .wbt world, the function returns NULL.
   * Your code should correcly handle the NULL cases because otherwise a segmentation fault will crash Webots.
   *
   * This function is also often used to add joints to the simulation, e.g.
   *   dWorldID world = dBodyGetWorld(body1);
   *   pthread_mutex_lock(&mutex);
   *   dJointID joint = dJointCreateBall(world, 0);
   *   dJointAttach(joint, body1, body2);
   *   pthread_mutex_unlock(&mutex);
   *   ...
   */
   dWebotsConsolePrintf("INITIALIZING PHYSICS...");
   robot_geom = dWebotsGetGeomFromDEF("FLIPPY");
   floor_geom = dWebotsGetGeomFromDEF("FLOOR");
   sphere1_geom = dWebotsGetGeomFromDEF("SPHERE1");
   sphere2_geom = dWebotsGetGeomFromDEF("SPHERE2");
   
   robot_body = dWebotsGetBodyFromDEF("FLIPPY");
   floor_body = dWebotsGetBodyFromDEF("FLOOR");
   sphere1_body = dWebotsGetBodyFromDEF("SPHERE1");
   sphere2_body = dWebotsGetBodyFromDEF("SPHERE2");
   
   
   
   world = dBodyGetWorld(robot_body);
   
   dWebotsConsolePrintf("creating joint....");
   pthread_mutex_lock(&mutex);
   // Creates a fixed joint belonging to the world ID, with the default joint group ID (0)
   dJointID joint = dJointCreateFixed(world, 0);
   dJointAttach(joint, robot_body, floor_body);
   dJointSetFixed(joint);
   pthread_mutex_unlock(&mutex);


}

void webots_physics_step() {
  /*
   * Do here what needs to be done at every time step, e.g. add forces to bodies
   *   dBodyAddForce(body1, f[0], f[1], f[2]);
   *   ...
   */
   // dWebotsConsolePrintf("PLEASE");
   // pthread_mutex_lock(&mutex);
   // Creates a fixed joint belonging to the world ID, with the default joint group ID (0)
   // dJointID joint = dJointCreateFixed(world, 0);
   // dJointAttach(joint, sphere2_body, floor_body);
   // dWebotsConsolePrintf("please");
   // pthread_mutex_unlock(&mutex);
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
   // dWebotsConsolePrintf("COLLIDE");
   // dBodyID body1 = dGeomGetBody(g1);
   // dBodyID body2 = dGeomGetBody(g2);
   
   // dJointGroupID contact_joint_group = dWebotsGetContactJointGroup();
   // dWorldID = dBodyGetWorld(body1);
   
   // pthread_mutex_lock(&mutex);
   // dJointCreateContact(world, contact_joint_group, &contact[0])
   // dJointAttach(contact_joint, body1, body2);
   // pthread_mutex_unlock(&mutex);
   
   
   // dWebotsSend(1, true, sizeof(true));
   // pthread_mutex_lock(&mutex);
   // Creates a fixed joint belonging to the world ID, with the default joint group ID (0)
   // dJointID joint = dJointCreateFixed(world, 0);
   // dJointAttach(joint, g1, g2);
   // pthread_mutex_unlock(&mutex);
   
   // dJointGroupID contact_joint_group = dWebotsGetContactJointGroup();
   // pthread_mutex_lock(&mutex);
   // dJointCreateContact(world, contact_joint_group, &contact[i])
   // dJointAttach(contact_joint, body1, body2);
   // pthread_mutex_unlock(&mutex);
   
  return 0;
}

void webots_physics_cleanup() {
  /*
   * Here you need to free any memory you allocated in above, close files, etc.
   * You do not need to free any ODE object, they will be freed by Webots.
   */
  pthread_mutex_destroy(&mutex);
}

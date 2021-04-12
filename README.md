# Webots_Playground
An introductory WeBots Project with the end goal of creating a 3D simulation of swarm robots. Controller code for this project was written in C++.

## Environment Setup
**TL;DR: Download [Webots](https://cyberbotics.com/) and make sure you have Python v3+**

The simulation is built off of [Webots](https://cyberbotics.com/), which is an open source robot simulator similar to gazebo. It support various different programming languages such as C, C++, Python, Java, and Matlab, as well as frameworks like ROS.

Additional python scripts have also been created in order to make the process of creating WeBots simulations and worlds a bit more streamlined. Make sure you have some kind of Python version 3.

## File Structure

#### `./controllers` Directory
The `./controllers` directory contains folders for each of the controller files. **The main controller for this project can be found in [flippy_controller.cpp](./controllers/flippy_controller/flippy_controller.cpp)**

#### `./plugins` Directory
This contains folders for various custom physics plugin files. **This project does not rely on any custom physics plugins**. If one wanted to create customized physics behaviors, the plugins would live in this directory. For more information about this, checkout [Webot's Documentation on physics plugins.](https://cyberbotics.com/doc/reference/physics-plugin)

#### `./protos` Directory
This contains `.proto` files. These files are essentially wrappers for complex Webots objects. **This project uses [flippy.proto](./protos/flippy.proto) as a wrapper for the flippy robot object**. These files are used for specifying object parameters and architectures, giving the user a simplified set of parameters to interact with in the Webots UI. It substantially simplifies the feature tree of the project. [More information about protos can be found here](https://cyberbotics.com/doc/guide/tutorial-7-your-first-proto).

## Supplementary Scripts
None as of 04/12/2021

## More information and documentation
TODO

## References
* [Flippy](https://ssr.seas.harvard.edu/files/ssr/files/phdthesis2020malley.pdf)
*

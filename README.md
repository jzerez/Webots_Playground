# Webots_Playground
An introductory WeBots Project with the end goal of creating a 3D simulation of swarm robots called flippys. Controller code for this project was written in C++. As of 05/03/2021, flippys are only capable of walking forward over any surfaces and are not implemented with rulesets. As such, there are no emergent behaviors.

#### Table of Contents
1. [Environment Setup](#environment-setup)
2. [How/What to Run](#howwhat-to-run)
3. [File Structure](#file-structure)
    1. [`./controllers` Directory](#controllers-directory)
    2. [`./plugins` Directory](#plugins-directory)
    3. [`./script_inputs` Directory](#script_inputs-directory)
    4. [`./script_outputs` Directory](#script_outputs-directory)
4. [Useful Resources](#useful-resources)
    1. [Creating a Physics Plug-in with ODE](#creating-a-physics-plug-in-with-ode)
    2. [Webots General Documentation](#webots-general-documentation)
5. [Recommendations and Next Steps](#recommendations-and-next-steps)
6. [References](#references)

## Environment Setup
**TL;DR: Download [Webots](https://cyberbotics.com/), Install a [C/C++ Compiler for Webots](https://cyberbotics.com/doc/guide/using-cpp) and make sure you have Python v3+**

The simulation is built off of [Webots](https://cyberbotics.com/), which is an open source robot simulator similar to gazebo. It support various different programming languages such as C, C++, Python, Java, and Matlab, as well as frameworks like ROS. The code for this project that interfaces directly with Webots is written in C++. As such, you'll need to make sure you have a C/C++ compiler. Instructions can be found [here](https://cyberbotics.com/doc/guide/using-cpp).

Additional python scripts have also been created in order to make the process of creating WeBots simulations and worlds a bit more streamlined. Make sure you have some kind of Python version 3.
___
## How/What to Run:
In Webots, one can choose to open and run [flippy_sim.wbt](./worlds/flippy_sim.wbt). It contains a singular flippy in a rectangular pen. It is useful for testing individual flippy behavior. As of 05/03/2021, the flippy should simply just walk forward via alternatingly pivoting around its two main spheres.

If one wishes to run a simulation with multiple flippys one must first initialize a world with the desired number of flippys. To do this quickly, use the [make_flippys.py](./make_flippys.py) to automate the process. PROTOs cannot be used in this project because each flippy needs to have a unique ID and unique DEF to interface with the physics engine. As such, each flippy needs to be individually created. The script can be run directly from the command line with `python make_flippys.py`. To change the output of the script, one must change the code in the `if __name__ == "__main__":` statement in the script. Below is an example of how to configure the script.

```python
if __name__ == "__main__":
  # Create a swarm of flippys that is 4 wide, 1 tall, and 2 long
  dims = np.array([4, 1, 2])
  # The average spacing between the flippys will be 0.15m, 0.03m and 0.2m
  spacing = np.array((0.15, 0.03, 0.2))
  # The first flippy will be located at:
  offset = np.array([-0.15, 0.03, 0])

  # Create the location and rotation of each flippy in the swarm, including noise
  locs, rots = create_layout(dims, spacing, offset=offset)

  # Writes the flippys to the output .wbt file
  #(./worlds/flippy_sim_autogenerated.wbt)
  make_flippys(locs, rots, write_to_wbt=True, start_index=0)
```

If the argument `write_to_wbt` is set to `True` in the call to `make_flippys()`, a file called `flippy_sim_autogenerated.wbt` will be created in the `./worlds` directory of the project. Simply open up that file in Webots to visualize the swarm.

If `write_to_wbt` is set to `False`, a file called `flippys.txt` will be created in the `./script_outputs` directory of the project. The text in the file must be copied into the desired world file.

More information about using this script and creating a world can be found [here](./creating_a_world.md).

___
## File Structure

#### `./controllers` Directory
The `./controllers` directory contains folders for each of the controller files. **The main controller for this project can be found in [flippy_controller.cpp](./controllers/flippy_controller/flippy_controller.cpp)**. Changing this file is the key to modifying flippy behavior.

#### `./plugins` Directory
This contains folders for various custom physics plugin files. **This project relies on a custom physics plugins which can be found in [flippy_physics.cpp](./plugins/physics/flippy_physics/flippy_physics.cpp)**. For more information about custom physics plugins, checkout [Webot's Documentation on physics plugins.](https://cyberbotics.com/doc/reference/physics-plugin)

#### `./protos` Directory
This contains `.proto` files. These files are essentially wrappers for complex Webots objects. These files are used for specifying object parameters and architectures, giving the user a simplified set of parameters to interact with in the Webots UI. It substantially simplifies the feature tree of the project. [More information about protos can be found here](https://cyberbotics.com/doc/guide/tutorial-7-your-first-proto). **This project does not use any `.proto` files**. This is because of the way that Webot's physics plugins are implemented. Each flippy in a swarm must be its own unique robot with a unique ID and DEF. As such, `.proto` files will not work.

#### `./script_inputs` Directory
This contains template files for the `make_flippys.py` script. There are two required files:
* `flippy_sim_template.wbt`: This file is the base world file. It is required to create an autogenerated world.
* `flippy_template.proto`: This file is the base flippy file. IT is required to create each flippy in the swarm.

#### `./script_outputs` Directory
This contains outputs from the `make_flippys.py` script (if `write_to_wbt=False`). These files will be `.txt`'s and will be properly formatted to be pasted directly into any `.wbt` file.

___

## Useful Resources

### Creating a Physics Plug-in with ODE
* [ODE's wiki style documentation](http://ode.org/wiki/index.php?title=Manual)
* [ODE's joint object documention (function list)](http://opende.sourceforge.net/docs/group__joints.html)
* [WeBots Physics Plugin example code (plugin)](https://github.com/cyberbotics/webots/blob/released/projects/samples/howto/plugins/physics/flying_mybot/flying_mybot.c)
* [Webots Physics Plugin example code (controller)](https://github.com/cyberbotics/webots/blob/released/projects/samples/howto/controllers/physics/physics.c)
* [Webots utility functions for interacting with ODE](https://www.cyberbotics.com/doc/reference/utility-functions)

### Webots General documentation
* [Webots Nodes and API Documentation](https://cyberbotics.com/doc/reference/nodes-and-api-functions?tab-language=c++). This resource contains links to documentation for the various Webots objects. This is useful to understand how they work and how to integrate them into your controller.
* [Webots Robot reference page](https://cyberbotics.com/doc/reference/robot?tab-language=c++)
* [Webots User Guide Tutorials](https://cyberbotics.com/doc/guide/tutorials)
* [Webots General FAQ](https://cyberbotics.com/doc/guide/general-faq)
* [Webots Safe-mode Guide (Useful for when Webots crashes on start-up)](https://cyberbotics.com/doc/guide/starting-webots#safe-mode)
### Other
* [How to make joints](./making_joints.md) 
___
## Recommendations and Next Steps
* **Implement flippy-to-flippy interactions**: In order to do anything interesting, flippys need to be able to interact with each other. This means that they must be able to communicate with their nearest neighbors in some way. This can be accomplished by adding additional `Reciever` and `Emitter` objects to each flippy for the purposes of flippy-to-flippy communication.
* **Implement obstacle identification**: The flippys need to know if an obstacle they hit is another flippy or just a static part of the environment. 
* **Develop rules for right-of-way**: In the case that two flippys are moving simultaneously and run into each other, one needs to become stationary until the other passes by. There must be a handshake of some kind between the flippys that determines which one of the two will have the right-of-way.
* **Improve flippy behavior when starting from a dead stop**: As of 05/03/2021, if the flippy starts moving in a state where both of its spheres are touching the ground, the robot enters a state of rapid pivoting between nodes. This causes the simulation to slow to less than 1% of real time. There needs to be a system implemented that ignores successive touch-sensor inputs if they've occurred too recently to the last recorded input.
* **Add 2nd Degree of Freedom for the flippys**: Currently the flippys can only actuate in one direction. In other words, they can only move in straight lines. For interesting behavior, and extra degree of freedom should be added so that flippys are able to steer themselves.

___
## References
* [2D Flippy Paper](https://ssr.seas.harvard.edu/files/ssr/files/phdthesis2020malley.pdf)

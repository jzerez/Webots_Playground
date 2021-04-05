"""epuck_go_forward controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
from controller import Robot

# create the Robot instance.
robot = Robot()
motors = robot.getDevice('m1')

# motor_names = ['s1', 's2']
# for name in motor_names:
    # wheels.append(robot.getDevice(name))

s = -1

motors[0].setPosition(float('inf'))
motors[0].setVelocity(-1)
# l_motor = robot.getDevice('left wheel motor')
# r_motor = robot.getDevice('right wheel motor')


# l_motor.setPosition(10.0)
# r_motor.setPosition(10.0)

# get the time step of the current world.
timestep = int(robot.getBasicTimeStep())

# You should insert a getDevice-like function in order to get the
# instance of a device of the robot. Something like:
#  motor = robot.getMotor('motorname')
#  ds = robot.getDistanceSensor('dsname')
#  ds.enable(timestep)

# Main loop:
# - perform simulation steps until Webots is stopping the controller
while robot.step(timestep) != -1:
    # Read the sensors:
    # Enter here functions to read sensor data, like:
    #  val = ds.getValue()

    # Process sensor data here.

    # Enter here functions to send actuator commands, like:
    #  motor.setPosition(10.0)
    pass

# Enter here exit cleanup code.

# from controller import Robot
import controller as c
print(c.__file__)
# create the Robot instance.
robot = c.Robot()
motors = robot.getDevice('M1')

motors.setPosition(float('inf'))
motors.setVelocity(-1)

ts = int(robot.getBasicTimeStep())

while robot.step(ts) != -1:
    # Read the sensors:
    # Enter here functions to read sensor data, like:
    #  val = ds.getValue()

    # Process sensor data here.

    # Enter here functions to send actuator commands, like:
    #  motor.setPosition(10.0)
    pass

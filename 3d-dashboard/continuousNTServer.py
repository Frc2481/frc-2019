from networktables import NetworkTables
import time
import math

NetworkTables.initialize()
sd = NetworkTables.getTable("SmartDashboard")

i = 0
while True:
    sd.putNumber("ElevatorPosition", 3*(math.sin(i*0.25)+1))
    sd.putNumber("HatchSlidePosition", 10*(math.sin(i*0.25)+1))
    i = i + 1
    print i
    time.sleep(0.1)
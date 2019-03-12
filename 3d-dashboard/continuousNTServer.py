from networktables import NetworkTables
import time
import math

NetworkTables.initialize()
sd = NetworkTables.getTable("SmartDashboard")

i = 0
while True:
    sd.putNumber("ElevatorPos", 20*(math.sin(i*0.125)+1))
    sd.putNumber("HatchSlidePos", 8.5*(math.sin(i*0.125)))
    sd.putNumber("IntakePosition", 8.5*(math.sin(i*0.125)+1))
    sd.putNumber("LineStrip1Position", 10*math.sin(i*0.125))
    sd.putNumber("LineStrip2Position", 10*math.sin(i*0.125+math.pi))

    cargoOrHatch = (i%300)/100 #Use integer division to our advantage.  0 - nothing, 1 - cargo, 2 - hatch
    sd.putBoolean("HasCargo", cargoOrHatch == 1)
    sd.putBoolean("HasHatch", cargoOrHatch == 2)

    sd.putNumber("FL steer encoder pos", (i%360)-180)
    sd.putNumber("FR steer encoder pos", (i%360)-180)
    sd.putNumber("BL steer encoder pos", (i%360)-180)
    sd.putNumber("BR steer encoder pos", (i%360)-180)
    
    i = i + 1
    print i
    time.sleep(0.05)
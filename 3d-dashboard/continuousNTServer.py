from networktables import NetworkTables
import time
import math

NetworkTables.initialize()
sd = NetworkTables.getTable("SmartDashboard")

sd.putBoolean("FL steer encoder connected", True)
sd.putBoolean("FLSteerEncCalibrated", True)
sd.putBoolean("FR steer encoder connected", True)
sd.putBoolean("FRSteerEncCalibrated", False)
sd.putBoolean("BL steer encoder connected", False)
sd.putBoolean("BLSteerEncCalibrated", True)
sd.putBoolean("BR steer encoder connected", False)
sd.putBoolean("BRSteerEncCalibrated", False)

i = 0
while True:
    sd.putNumber("ElevatorPos", 30*(math.sin(i*0.125)+1))
    sd.putNumber("HatchSlidePos", 8.5*(math.sin(i*0.125)))
    sd.putNumber("CargoPos", 7500*(math.sin(i*0.125)+1))
    sd.putNumber("LineStrip1Position", 10*math.sin(i*0.125))
    sd.putNumber("LineStrip2Position", 10*math.sin(i*0.125+math.pi))

    cargoOrHatch = (i%300)/100 #Use integer division to our advantage.  0 - nothing, 1 - cargo, 2 - hatch
    sd.putBoolean("HasCargo", cargoOrHatch == 1)
    sd.putBoolean("HasHatch", cargoOrHatch == 2)

    sd.putNumber("FL Steer encoder pos", (i%360)-180)
    sd.putNumber("FR Steer encoder pos", (i%360)-180)
    sd.putNumber("BL Steer encoder pos", (i%360)-180)
    sd.putNumber("BR Steer encoder pos", (i%360)-180)

    sd.putBoolean("IsElevatorEncoderConnected", True)
    sd.putBoolean("IsElevatorZeroed", True)
    sd.putBoolean("intakeEncConnnected", True)
    sd.putBoolean("IsCargoIntakeZeroed", False)
    sd.putBoolean("slideEncConnnected", False)
    sd.putBoolean("IsHatchZeroed", False)
    
    i = i + 1
    print i
    time.sleep(0.05)
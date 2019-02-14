from networktables import NetworkTables
import time
import math

NetworkTables.initialize()
sd = NetworkTables.getTable("SmartDashboard")

i = 0
while True:
    sd.putNumber("ElevatorSlidePosition", 3*(math.sin(i*0.125)+1))
    sd.putNumber("ElevatorPosition", 20*(math.sin(i*0.125)+1))
    sd.putNumber("HatchSlidePosition", 10*(math.sin(i*0.125)+1))

    cargoOrHatch = (i%300)/100 #Use integer division to our advantage.  0 - nothing, 1 - cargo, 2 - hatch
    sd.putBoolean("HasCargo", cargoOrHatch == 1)
    sd.putBoolean("HasHatch", cargoOrHatch == 2)
    
    i = i + 1
    print i
    time.sleep(0.05)
# MakeblockPlotter
Spring 2016 EE400D

This is the software file for EE400D 3D SMD Project. Codes were based provided code by open-source company Makeblock.
You can find their original code on Makeblock's GitHub -- https://github.com/Makeblock-official/

Required Arduino Code Modifications for 3D SMD:
1. Pinout Reassignment
      Because the pinouts for the Me UNO Shield is different from Me Orion, the code had to be modified to match those pins. The blog post can be found here: http://www.arxterra.com/spring-2016-3d-smd-me-uno-shield-and-software/
2. Z-Axis Arduino Code Modification
    The original Makeblock X-Y Plotter Robot Kit controls the Z-axis using a microservo and pen to control. However, we decided to use a stepper motor to control the Z-axis so it can be suspended on a threaded drive.
3. Addition of A-Axis (rotation of IC Chips)
    This concept requires an addition of another stepper motor to be able to self-automate and correct the orientation of the IC Chip.
4. Limiting Switch Feedback (notifies that we’ve gone too far)
    The addition of the limiting switch needed to be added to the Z-control here.
5. Microservo control (reel feeders)
    The microservos will control the reel feeders’ cut-tape, which could help keep the cut-tape away from the vacuum nozzle.
6. Solenoid Valve Control (vacuum suction)
    Solenoid valve will be able to close off the vacuum suction since the vacuum pump does not have its own controllable switch.
7. Adjust GUI (Reassigning pinouts on Java)    
    
    More information can be found on Arxterra Website: 
    Arduino Modifications: http://www.arxterra.com/spring-2016-3d-smd-software/
    Java Modifications: http://www.arxterra.com/spring-2016-3d-smd-me-uno-shield-and-software/
    


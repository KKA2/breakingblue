# Breaking Blue
*Authors: Kate Barlock, Kat Herring, Ann Keenan*

A 2-D multi-stage action adventure game in which you play as a Blue involved in the struggle to overcome the Reds.


## Known Issues
- Load text from file causes segfault (commented out usage in Level1 to prevent currently)
- Figure teleports to end of tunnel if attempting to stand up during it. (Possible fix to modify so teleports back to start?) 
  - Note: I (Kate) will modify this next so that the player crouches when they hit the top of something and they are standing on the ground (i.e. they're in the tunnel)

## Resolved Issues
- Jumping while running at wall allows teleport through wall (Result of temp fix in checkGround until checkCollision finished)
- Pressing the down button will allow figure to phase through a wall
- Figure floats upwards when encountering a border

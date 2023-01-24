v2.2.0 (1/24/22)
- Created flywheel.cpp & flywheel.hpp, and moved relevant functions into these files
- Renamed high goal constants and flywheel constants for better readability
- Created PIDTurnTo function for turning towards specific objects
- autonSelect variable is now declared in initialize() and the starting odometry positions adjust accordingly
- Odometry and PID terminal print functions now use printf instead of cout
- Started working on auto aim function
----------------------------------------------------------------------------------------------------------------------------------
v2.1.0 (1/21/23) - Southern Maryland Showdown
- Included fstream
- Reformatted flywheel adjustment algorithm
- Major fixes to odometry tracking system
- Created waitUntilMoveAbsolute function for use with the indexer
- Created misc.cpp & misc.hpp to organize miscellaneous functions
- Adjusted odometry algorithm to use an inertial sensor instead of a right tracking wheel
- Created functionality for odometry & values PID values to print to the terminal
- Updated left autons
- Finished base PID functions without tuned constants
- Added ability for the intake to move backwards
- Driver can now toggle between two flywheel motor velocities: 363 RPM (Enough to shoot a disc from the low goal barrier) and 600 RPM (max speed)
----------------------------------------------------------------------------------------------------------------------------------
v2.0.0 (1/15/23) - "I Have A Dream" Challenge
- Description for version numbering system added to README.md
- Functions for indexer and flywheel created
- Function for expansion adjusted for the new expansion module
- Started creating odometry & PID functions
- Created competition_intialize.hpp and competition_intialize.cpp, and moved all pre-auton exclusive functions into those files
- Removed all button boolean variables
- Added Full AWP to auton select options
- Installed sylib
- Removed flywheel.cpp, intake.cpp, and their respective header files
- Added delays after indexer movements
- Untracked cache files
----------------------------------------------------------------------------------------------------------------------------------
v1.0.1 (12/20/22)
- Switched program icon to an Alien
- Moved global.hpp out of subsystemHeaders
- Slight change to input curving for increased precision
- Fixed motor temperature check
- Expansion can now only activate when 15 seconds are left in the Driver Control Period
- Controller rumbles when activating expansion
----------------------------------------------------------------------------------------------------------------------------------
v1.0.0 (12/17/22) - Capital Beltway Challenge
- Added input curving to the motor
- Merged competition_initialize.cpp back into main.cpp
- Added delays between controller printing to make controller display functions work
- Fixed bug with AutonSelect display occuring when checking motor temperatures
- Update to PROS CLI 3.4.1
- Added keybind checking and notes to the pre-auton menu
- Created auton drive & turn functions
- Driver can now switch which side is the "head" of the bot
- Created Driver Controller Display: displays the current drive direction and flywheel spin status
- Added intake, indexer, and flywheel motors to the motor check page
----------------------------------------------------------------------------------------------------------------------------------
v0.1.1 (10/21/22)
- Created CHANGELOG.md
- Created drive.hpp, drive.cpp, competition_initialize.cpp, autonomous.cpp, & opcontrol.cpp
- Deleted globals.hpp & globals.cpp (temporary global files)
- drive.cpp - Tank Drive function made
----------------------------------------------------------------------------------------------------------------------------------
v0.1.0 (10/8/22)
- Added new subsystem headers
- Added new subsystem files
- Changed origin of the repository to the new 53 GitHub organization
- Edited README.md
----------------------------------------------------------------------------------------------------------------------------------
v0.0.3 (Summer Update (global.h & main.cpp changes))
----------------------------------------------------------------------------------------------------------------------------------
v0.0.2 (Added Pre-Auton Controller & Main Button Functions)
----------------------------------------------------------------------------------------------------------------------------------
v0.0.1 (Create README.md)
----------------------------------------------------------------------------------------------------------------------------------
v0.0.0 (Repository Creation)
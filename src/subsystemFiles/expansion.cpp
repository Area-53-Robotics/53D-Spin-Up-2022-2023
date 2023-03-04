#include "main.h"
#include "subsystemHeaders/expansion.hpp"

/*
    * Fires the pneumatic pistons on our
    * expansion system and alerts the
    * driver that the function was
    * successful
*/
void Expansion() {
    ExpansionPistons.set_value(true);
    Controller.rumble(".");
    sylib::delay(50);
    Controller.clear();
    sylib::delay(50);
    Controller.print(0, 0, "Expanded");
}
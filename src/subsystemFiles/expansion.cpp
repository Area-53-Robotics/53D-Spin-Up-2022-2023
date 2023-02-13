#include "main.h"
#include "subsystemHeaders/expansion.hpp"

void Expansion() {
    ExpansionPiston.set_value(true);
    Controller.rumble(".");
    sylib::delay(50);
    Controller.clear();
    sylib::delay(50);
    Controller.print(0, 0, "Expanded");
}
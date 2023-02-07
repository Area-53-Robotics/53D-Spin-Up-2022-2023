#include "main.h"
#include "subsystemHeaders/indexer.hpp"

void Indexer() {
    waitUntilMoveAbsolute(IndexerMotor, 35, 200);
    waitUntilMoveAbsolute(IndexerMotor, 0, 200);
}

void Expansion() {
    waitUntilMoveAbsolute(IndexerMotor, 150, 200);
    // IndexerMotor.move_absolute(130.0, 200);
    Controller.rumble(".");
    sylib::delay(50);
    Controller.clear();
    sylib::delay(50);
    Controller.print(0, 0, "Expanded");
}
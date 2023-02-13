#include "main.h"
#include "subsystemHeaders/indexer.hpp"

void Indexer() {
    waitUntilMoveAbsolute(IndexerMotor, 50, 200);
    waitUntilMoveAbsolute(IndexerMotor, 5, 200);
}
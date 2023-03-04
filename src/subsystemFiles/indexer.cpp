#include "main.h"
#include "subsystemHeaders/indexer.hpp"

//* Boolean variable to store whether the indexer is on or not.
bool indexerOn = false;

/*
    * When triggered by the driver, the indexer wheel is rotated 360
    * degrees
*/
void Indexer() {
    indexerOn = true;
    IndexerMotor.move_relative(360, 200);
    indexerOn = false;
}
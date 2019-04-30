/**
 * @file Door.cpp
 * @brief Implementation of the Door-Class
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @date 2019-04-30
 * @copyright Copyright (c) 2019
 * 
 */
#include "Door.h"

//=====PUBLIC====================================================================================
Door::Door(int positionClosed, int positionOpen) : pPosClosed(positionClosed), pPosOpen(positionOpen) {
    DBFUNCCALLln("Door::Door(int positionOpen, int positionClosed)");
    init();
}

/**
 * @bug Example for an bug
 */
bool Door::open() {
    DBFUNCCALLln("Door::open()");
    if (pActualPos < pPosOpen) {
        pActualPos += 1;
    }
    DBINFO3ln(String("DoorPosition: ") + String(pActualPos));
    if (pActualPos == pPosOpen) {
        return true;
    }
    return false;
}

bool Door::close() {
    DBFUNCCALLln("Door::close()");
    if (pActualPos > pPosClosed) {
        pActualPos -= 1;
    }
    DBINFO3ln(String("DoorPosition: ") + String(pActualPos));
    if (pActualPos == pPosClosed) {
        return true;
    }
    return false;
}

//=====PRIVATE====================================================================================
void Door::init() {
    while (!open()) {
    };
}
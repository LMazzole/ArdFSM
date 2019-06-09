/**
 * @file Door.h
 * @brief Implementation of the Door-Class
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @date 2019-04-30
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef DOOR_H
#define DOOR_H

#include "Arduino.h"

#include "LogConfiguration.h"

/**
 * @brief Provides the basic Functions to Controll the Door
 * 
 */
class Door {
    //=====PUBLIC====================================================================================
   public:
    /**
    * @brief Construct a new Door object
    * 
    * positionOpen > positionClosed
    * 
    * @param positionOpen - Position in which the Door is Open
    * @param positionClosed - Position in which the Door is Closed
    */
    Door(int positionClosed, int positionOpen);

    /**
     * @brief Opens the Door one Step per Function-Call
     * 
     * @return true - The Door is open
     * @return false - The Door is closed
     */
    bool open();

    /**
     * @brief Closes the Door one Step per Function-Call
     * 
     * @return true - The Door is closed
     * @return false - The Door is open
     */
    bool close();

    //=====PRIVATE====================================================================================
   private:
    const int pPosClosed;  ///< Position of the closed door
    const int pPosOpen;    ///< Position of the open door
    int pActualPos = 3;    ///< Initial door position somwhere between

    /**
     * @brief Initialisen the Door in closed Position
     * 
     */
    void init();
};

#endif
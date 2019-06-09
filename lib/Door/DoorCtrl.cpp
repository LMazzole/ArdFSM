/**
 * @file DoorCtrl.cpp
 * @brief Implementation of the Door Control-Class
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @version 1.0 -Implementation Door Controll FSM - Luca Mazzoleni (luca.mazzoleni@hsr.ch) - 2019-04-23
 * 
 * @date 2019-04-23
 * @copyright Copyright (c) 2019
 * 
 */

#include "DoorCtrl.h"

//=====PUBLIC====================================================================================
DoorCtrl::DoorCtrl() : currentState(State::opened) {
    doActionFPtr = &DoorCtrl::doAction_opened;
}

void DoorCtrl::loop() {
    DBFUNCCALLln("DoorCtrl::loop()");
    process((this->*doActionFPtr)());  //do actions
}

void DoorCtrl::loop(Event currentEvent) {
    DBFUNCCALLln("DoorCtrl::loop(Event)");
    process(currentEvent);
    process((this->*doActionFPtr)());  //do actions
}

const DoorCtrl::State DoorCtrl::getcurrentState() {
    return currentState;
}
//=====PRIVATE====================================================================================
void DoorCtrl::process(Event e) {
    DBFUNCCALL("DoorCtrl::process ")
    DBEVENTln(decodeEvent(e));
    switch (currentState) {
        case State::opened:
            if (Event::Close == e) {
                exitAction_opened();    // Exit-action current state
                entryAction_closing();  // Entry-actions next state
            } else if (Event::Error == e) {
                exitAction_opened();       // Exit-action current state
                entryAction_errorState();  // Entry-actions next state
            }
            break;

        case State::closing:
            if (Event::Open == e) {
                exitAction_closing();   // Exit-action current state
                entryAction_opening();  // Entry-actions next state
            } else if (Event::Closed == e) {
                exitAction_closing();  // Exit-action current state
                entryAction_closed();  // Entry-actions next state
            } else if (Event::Error == e) {
                exitAction_closing();      // Exit-action current state
                entryAction_errorState();  // Entry-actions next state
            }
            break;

        case State::closed:
            if (Event::Open == e) {
                exitAction_closed();    // Exit-action current state
                entryAction_opening();  // Entry-actions next state
            } else if (Event::Error == e) {
                exitAction_closed();       // Exit-action current state
                entryAction_errorState();  // Entry-actions next state
            }
            break;

        case State::opening:
            if (Event::Close == e) {
                exitAction_opening();   // Exit-action current state
                entryAction_closing();  // Entry-actions next state
            } else if (Event::Opened == e) {
                exitAction_opening();  // Exit-action current state
                entryAction_opened();  // Entry-actions next state
            } else if (Event::Error == e) {
                exitAction_opening();      // Exit-action current state
                entryAction_errorState();  // Entry-actions next state
            }
            break;

        case State::errorState:
            if (Event::Resume == e) {
                exitAction_errorState();  // Exit-action current state
                switch (lastStateBevorError) {
                    case State::opened:
                        entryAction_opened();  // Entry-actions next state
                        break;
                    case State::closing:
                        entryAction_closing();  // Entry-actions next state
                        break;
                    case State::closed:
                        entryAction_closed();  // Entry-actions next state
                        break;
                    case State::opening:
                        entryAction_opening();  // Entry-actions next state
                        break;
                    default:
                        break;
                }
            }
        default:
            break;
    }
}

//==1 opened==========================================================
void DoorCtrl::entryAction_opened() {
    DBSTATUSln("Door Entering State: opened");
    currentState = State::opened;  // state transition
    doActionFPtr = &DoorCtrl::doAction_opened;
    //Entry-Action
}

DoorCtrl::Event DoorCtrl::doAction_opened() {
    DBINFO1ln("Door State: opened");
    //Generate the Event
    return Event::NoEvent;
}

void DoorCtrl::exitAction_opened() {
    DBSTATUSln("Door Leaving State: opened");
}

//==2 closing==========================================================
void DoorCtrl::entryAction_closing() {
    DBSTATUSln("Door Entering State: closing");
    currentState = State::closing;  // state transition
    doActionFPtr = &DoorCtrl::doAction_closing;
    //Entry-Action
}

DoorCtrl::Event DoorCtrl::doAction_closing() {
    DBINFO1ln("Door State: closing");
    //Generate Event
    if (pDoor.close()) {
        return Event::Closed;
    }
    return Event::NoEvent;
}

void DoorCtrl::exitAction_closing() {
    DBSTATUSln("Door Leaving State: closing");
}

//==3 closed==========================================================
void DoorCtrl::entryAction_closed() {
    DBSTATUSln("Door Entering State: closed");
    currentState = State::closed;  // state transition
    doActionFPtr = &DoorCtrl::doAction_closed;
    //Entry-Action
}

DoorCtrl::Event DoorCtrl::doAction_closed() {
    DBINFO1ln("Door State: closed");
    //Generate the Event
    return Event::NoEvent;
}

void DoorCtrl::exitAction_closed() {
    DBSTATUSln("Door Leaving State: closed");
}

//==4 opening==========================================================
void DoorCtrl::entryAction_opening() {
    DBSTATUSln("Door Entering State: opening");
    currentState = State::opening;  // state transition
    doActionFPtr = &DoorCtrl::doAction_opening;
    //Entry-Action
}

DoorCtrl::Event DoorCtrl::doAction_opening() {
    DBINFO1ln("Door State: opening");
    //Generate the Event
    if (pDoor.open()) {
        return Event::Opened;
    }
    return Event::NoEvent;
}

void DoorCtrl::exitAction_opening() {
    DBSTATUSln("Door Leaving State: opening");
}

//==errorState========================================================
void DoorCtrl::entryAction_errorState() {
    DBSTATUSln("Door Entering State: errorState");
    lastStateBevorError = currentState;
    currentState = State::errorState;  // state transition
    doActionFPtr = &DoorCtrl::doAction_errorState;
    //Entry-Action
}

DoorCtrl::Event DoorCtrl::doAction_errorState() {
    DBINFO1ln("Door State: errorState");
    //Generate the Event

    return Event::NoEvent;
}

void DoorCtrl::exitAction_errorState() {
    DBSTATUSln("Door Leaving State: errorState");
}

//============================================================================
//==Aux-Function==============================================================
String DoorCtrl::decodeState(State state) {
    switch (state) {
        case State::opened:
            return "State::opened";
        case State::closing:
            return "State::closing";
            break;
        case State::closed:
            return "State::closed";
            break;
        case State::opening:
            return "State::opening";
            break;
        case State::errorState:
            return "State::errorState";
            break;
        default:
            return "ERROR: No matching state";
            break;
    }
}

String DoorCtrl::decodeEvent(Event event) {
    switch (event) {
        case Event::Open:
            return "Event::Open";
            break;
        case Event::Close:
            return "Event::Close";
            break;
        case Event::Opened:
            return "Event::Opened";
            break;
        case Event::Closed:
            return "Event::Closed";
            break;
        case Event::Error:
            return "Event::Error";
            break;
        case Event::Resume:
            return "Event::Resume";
            break;
        case Event::NoEvent:
            return "Event::NoEvent";
            break;
        default:
            return "ERROR: No matching event";
            break;
    }
}
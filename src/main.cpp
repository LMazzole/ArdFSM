/**
 * @file main.cpp
 * @brief Example for a simple non blocking FSM in CPP and how to use Doxygen
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @date 2019-04-30
 * @copyright Copyright (c) 2019
 * 
 */

/*
https://en.wikipedia.org/wiki/Finite-state_machine 
Moore machine
  The FSM uses only entry actions, i.e., output depends only on the state.
  The advantage of the Moore model is a simplification of the behaviour.

  Consider an elevator door:
  The state machine recognizes two commands: "command_open" and "command_close",
  which trigger state changes.
  The entry action (E:) in state "Opening" starts a motor opening the door,
  the entry action in state "Closing" starts a motor in the other direction closing the door.
  States "Opened" and "Closed" stop the motor when fully opened or closed.
  They signal to the outside world (e.g., to other state machines)
  the situation: "door is open" or "door is closed".
*/

#include <Arduino.h>

#include "LogConfiguration.h"  //You can change the DebugLevel in LogConfiguration

#include "DoorCtrl.h"

DoorCtrl *doorctrl;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    while (!Serial) {
        ;  // wait for serial port to connect. Needed for native USB port only
    }

    doorctrl = new DoorCtrl();
}

void loop() {
    // put your main code here, to run repeatedly:

    //https://www.arduino.cc/en/Tutorial/SwitchCase2
    int inByte;
    DBSTATUSln("==Test Door CTRL==");
    //read Serial in and generate events
    Serial.print("Current State: ");
    Serial.println(doorctrl->decodeState(doorctrl->getcurrentState()));
    Serial.println("Possible Events are:");
    Serial.println("O - Open");
    Serial.println("A - Automatic Open");
    Serial.println("C - Close");
    Serial.println("a - Automatic Close");
    Serial.println("E - Error");
    Serial.println("R - Resume");
    Serial.println("N - No Event");
    Serial.println("o - Signal: Opened");
    Serial.println("c - Signal:  Closed");
    Serial.print("Choose Event: ");
    while (Serial.available() <= 0) {
    }
    inByte = Serial.read();
    Serial.print((char)inByte);
    Serial.println();
    switch (inByte) {
        case 'O':
            doorctrl->loop(DoorCtrl::Event::Open);
            break;
        case 'A':
            while ((doorctrl->getcurrentState() != DoorCtrl::State::opened) && (Serial.read() != 'E')) {
                doorctrl->loop(DoorCtrl::Event::Open);
            }
            break;
        case 'C':
            doorctrl->loop(DoorCtrl::Event::Close);
            break;
        case 'a':
            while ((doorctrl->getcurrentState() != DoorCtrl::State::closed) && (Serial.read() != 'E')) {
                doorctrl->loop(DoorCtrl::Event::Close);
            }
            break;
        case 'E':
            doorctrl->loop(DoorCtrl::Event::Error);
            break;
        case 'R':
            doorctrl->loop(DoorCtrl::Event::Resume);
            break;
        case 'N':
            doorctrl->loop(DoorCtrl::Event::NoEvent);
            break;
        case 'o':
            doorctrl->loop(DoorCtrl::Event::Opened);
            break;
        case 'c':
            doorctrl->loop(DoorCtrl::Event::Closed);
            break;
        default:
            DBINFO1ln("Error: Unknown value entered");
            break;
    }
}
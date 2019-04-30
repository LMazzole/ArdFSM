/**
 * @file DoorCtrl.h
 * @brief The Door Controll class contains the FSM for the Door
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @version 1.0 -Implementation Door Controll FSM - Luca Mazzoleni (luca.mazzoleni@hsr.ch) - 2019-04-23
 * 
 * @date 2019-04-23
 * @copyright Copyright (c) 2019
 * 
 * 
 */

#ifndef DoorCTRL_H__
#define DoorCTRL_H__

#include "LogConfiguration.h"

#include "Door.h"

/**
 * @brief Contains the FSM for the Door
 * 
 */
class DoorCtrl {
    //=====PUBLIC====================================================================================
   public:
    /**
    * @brief Enum holds all possible events
    * 
    */
    enum class Event { Open,    ///< Ext: Start Opening
                       Close,   ///< Ext: Start Closeing
                       Opened,  ///< Signal: Open position reached
                       Closed,  ///< Signal: Close position reached
                       Error,   ///< Error occured
                       Resume,  ///< Ext: Resume after Error occured
                       NoEvent  ///< No event generated
    };

    /**
    * @brief Enum holds all possible states for the Door
    * 
    */
    enum class State { opened,     ///< 1 opended State
                       closing,    ///< 2 closing State
                       closed,     ///< 3 closed State
                       opening,    ///< 4 opening State
                       errorState  ///< error State
    };

    /**
     * @brief Construct a new Door Ctrl object
     * and initailize the currentState with low state
     * 
     * @todo pass the initial state to the CTor
     */
    DoorCtrl();

    /**
     * @brief Calls the do-function of the active state and hence generates Events
     * 
     */
    void loop();

    /**
     * @brief Procceses the current Event and calls the do-function of the active state
     * 
     * @param currentEvent - Event
     */
    void loop(Event currentEvent);

    /**
     * @brief Get the current State
     * 
     * @return State - current State
     */
    const State getcurrentState();

    /**
     * @brief Decodes the State-Enum and returns a description
     * 
     * Move this Func to private if you don't need it in main
     * 
     * @param state - enum State
     * @return String - State as String
     */
    String decodeState(State state);

    //=====PRIVATE====================================================================================
   private:
    State lastStateBevorError;  ///< holds the last state of the FSM so it's possible to resume after error
    State currentState;         ///< holds the current state of the FSM
    Event currentEvent;         ///< holds the current event of the FSM

    /**
     * @brief Functionpointer to call the current states do-function
     * 
     * https://stackoverflow.com/questions/1485983/calling-c-class-methods-via-a-function-pointer
     */
    Event (DoorCtrl::*doActionFPtr)(void) = nullptr;  //initialize in CTor!!

    Door pDoor = Door(0, 10);  ///< Door Object with ClosedPostion 0 and OpenPosition 10

    //=====PrivateFunctions=========================================================================
    /**
     * @brief Changes the state of the FSM based on the event
     * Here is where the magic happens :)
     * 
     * @param e - Event
     */
    void process(Event e);
    //=====StateFunctions=====
    //=====opened==========================================================
    /**
     * @brief executes the entry action of the opened state.
     * 
     */
    void entryAction_opened();

    /**
     * @brief executes the main action of the opened state.
     * 
     * This is an idle-State so it returns always NoEvent when called
     * 
     * @return DoorCtrl::Event - generated Event
     */
    DoorCtrl::Event doAction_opened();

    /**
     * @brief executes the exit action of the opened state.
     * 
     */
    void exitAction_opened();

    //=====closing==========================================================
    /**
     * @brief executes the entry action of the closing state.
     * 
     */
    void entryAction_closing();

    /**
     * @brief executes the main action of the closing state.
     * 
     * Calls close() and returns Event::Closed when the Door is closed.
     * else returns NoEvent
     * 
     * @return DoorCtrl::Event - generated Event
     */
    DoorCtrl::Event doAction_closing();

    /**
     * @brief executes the exit action of the closing state.
     * 
     */
    void exitAction_closing();

    //=====closed==========================================================
    /**
     * @brief executes the entry action of the closed  state.
     * 
     */
    void entryAction_closed();

    /**
     * @brief executes the main action of the closed state.
     *
     * This is an idle-State so it returns always NoEvent when called
     * 
     * @return DoorCtrl::Event - generated Event
     */
    DoorCtrl::Event doAction_closed();

    /**
     * @brief executes the exit action of the closed state.
     * 
     */
    void exitAction_closed();

    //=====opening==========================================================
    /**
     * @brief executes the entry action of the opening state.
     * 
     */
    void entryAction_opening();

    /**
     * @brief executes the main action of the opening state.
     * 
     * Calls open() and returns Event::Closed when the Door is opend.
     * else returns NoEvent.
     * 
     * @return DoorCtrl::Event - generated Event
     */
    DoorCtrl::Event doAction_opening();

    /**
     * @brief executes the exit action of the opening state.
     * 
     */
    void exitAction_opening();

    //==errorState==========================================================
    /**
     * @brief entry action of the errorState state.
     * 
     */
    void entryAction_errorState();

    /**
     * @brief main action of the errorState state.
     * 
     *  @return DoorCtrl::Event - generated Event
     */
    DoorCtrl::Event doAction_errorState();

    /**
     * @brief exit action of the errorState state.
     * 
     */
    void exitAction_errorState();

    //============================================================================
    //==Aux-Function==============================================================

    /**
     * @brief Decodes the Event-Enum and returns a description
     * 
     * @param event - enum Event
     * @return String - Event as String
     */
    String decodeEvent(Event event);
};
#endif

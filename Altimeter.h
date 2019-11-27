

    /**********************************************************************\
   /          hRocket: An Arduino powered altimeter                         \
  /            Federal University of Technology - Parana - Brazil            \
  \              by Guilherme Bertoldo and Jonas Joacir Radtke               /
   \                       updated November 27, 2019                        /
    \**********************************************************************/


#ifndef ALTIMETER_H
#define ALTIMETER_H

#include "Arduino.h"
#include "Barometer.h"
#include "Memory.h"
#include "Button.h"
#include "HumanInterface.h"

/*

  Altimeter controller

*/

/*

                                      Altimeter states

*/

enum class AltimeterState {readyToLaunch, flying, falling, recovered};

/*

                                             apogee
        --------------------------------------____----------------------------------------
         |                                 ***    ****                                  |
         |                             ****            ****                             | flying
         |                          ***                    ***                          |
         |                       ***                          *** ------------------------
         |                      **                              **                      |
         |                    **                                  **                    |
         |                  **                                      **                  | 
         |                 *                                          *                 |
  flying |               **                                            **               |
         |              **                                              **              |
         |            **                                                  **            | 
         |           **                                                    **           | falling
         |          *                                                        *          |
         |         *                                                          *         |
         |        *                                                            *        | 
         |      **                                                              **      |
         |      *                                                                *      |
         |     *                                                                  *     |
        ---- **                                                                    ** ----
                  --->   readyToLaunch                         recovered   <---
      ------------------------------------------------------------------------------------

*/


class Altimeter
{
  public:

    //  Altimeter initializer
    bool begin();

    // Runs altimeter controller
    void run();

  private:

    // The following functions define the behavior of the altimeter,
    // that change dynamically in accordance to the altimeter's state
    void     readyToLaunchRun();
    void            flyingRun();
    void           fallingRun();
    void         recoveredRun();

    // Updates altitude vector
    void registerAltitude(bool writeToMemory);

  private:

    AltimeterState                    state; // Current state of altimeter
    Barometer                     barometer; // Barometer manager
    Memory                           memory; // EEPROM Memory manager
    Button                           button; // Button for interaction with user
    HumanInterface           humanInterface; // Interface for communication with humans

    static constexpr unsigned long int timeStep  {250}; // Time step for registering altitude (ms)
    int                                       n   {8};  // Size of 'altitude' vector
    float                           altitude[8];        // Initial altitudes

};

#endif // ALTIMETER_H

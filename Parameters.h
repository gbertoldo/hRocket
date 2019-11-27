

    /**********************************************************************\
   /          hRocket: An Arduino powered altimeter                         \
  /            Federal University of Technology - Parana - Brazil            \
  \              by Guilherme Bertoldo and Jonas Joacir Radtke               /
   \                       updated November 27, 2019                        /
    \**********************************************************************/


#ifndef PARAMETERS_H
#define PARAMETERS_H

namespace Parameters
{

  extern const char*                      softwareVersion; // Version of this software
  extern const int                                 pinLed; // Screen uses pin 13 to blink Arduino internal led
  extern const int                              pinButton; // Pin of button
  extern const int                     pinButtonVCCSource; // Pin used in the button as 5V
  extern const float      displacementForLiftoffDetection; // Displacement from the ground for liftoff detection (meter)
  extern const float      displacementForFallingDetection; // Displacement from apogee to recognize that the rocket is falling (meter)
  extern const float     displacementForRecoveryDetection; // Displacement for recovery detection (meter)

}

#endif // PARAMETERS_H

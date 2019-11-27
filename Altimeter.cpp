

    /**********************************************************************\
   /          hRocket: An Arduino powered altimeter                         \
  /            Federal University of Technology - Parana - Brazil            \
  \              by Guilherme Bertoldo and Jonas Joacir Radtke               /
   \                       updated November 27, 2019                        /
    \**********************************************************************/


#include "Altimeter.h"
#include "Parameters.h"


bool Altimeter::begin()
{

  // Initializing human interface
  humanInterface.begin();

  // Show initialization message
  humanInterface.showInitMessage();

  // Initializing button
  button.begin(Parameters::pinButton);

  // Pin used in the button as 5V
  pinMode(Parameters::pinButtonVCCSource, OUTPUT);
  digitalWrite(Parameters::pinButtonVCCSource, HIGH);

  // Initializing EEPROM memory and barometer (these modules are critical, so their initialization must be checked)
  if ( memory.begin() && barometer.begin() )
  {

    // Initializing altitude vector
    for (int i = 0; i < n; i++)
    {
      altitude[i] = 0;
    }

    switch (memory.getState())
    {

      case MemoryState::full:
        state = AltimeterState::recovered;
        break;

      case MemoryState::empty:
        state = AltimeterState::readyToLaunch;
        break;

      default:
        humanInterface.println(" Altimeter fatal error: unknown memory state. Stopping...\n");
        while (true);

    }

  }
  else
  {

    humanInterface.println(" Altimeter fatal error: unable to initialize altimeter...\n");

    while (true) {};

  }

};


void Altimeter::run()
{

  // Altimeter's actions depend on altimeter's state.
  switch (state)
  {

    case AltimeterState::readyToLaunch:
      readyToLaunchRun();
      break;

    case AltimeterState::flying:
      flyingRun();
      break;

    case AltimeterState::falling:
      fallingRun();
      break;

    case AltimeterState::recovered:
      recoveredRun();
      break;

    default:;

  }

}


void Altimeter::readyToLaunchRun()
{

  // Registering altitude without writing to memory
  // Writing to memory is performed only after liftoff
  registerAltitude(false);

  /*

           Scanning for liftoff

  */

  bool isFlying = false;

  if ( abs(altitude[n - 1] - altitude[0]) > Parameters::displacementForLiftoffDetection) isFlying = true;
  /*
      Why using absolute value for altitude variation? Suppose the recovery system suffers a failure during flight,
      turn off and turn on again. If it is falling, altitude variation will be negative and the above conditional
      will be fulfilled. Altimeter will change state to 'flying' and soon to 'falling'.
  */

  // If flying, stores data to memory and changes altimeter's state
  if ( isFlying ) {

    // Setting barometer new baseline
    barometer.setBaseline(altitude[0]);
    /* 
      Why resetting the barometer height baseline? If altimeter stays switched on for a long time, environment pressure
      and temperature may change and, hence, change local baseline height. To avoid this problem, it is necessary to 
      reset the barometer height baseline when liftoff is detected.
    */

    // Storing data to memory using the corrected altitude
    for (int i = 0; i < n; i++) 
    {
      altitude[i] = altitude[i]-altitude[0];
      
      memory.writeAltitude(altitude[i]);
    }
    
    // Changing recovery system's state
    state = AltimeterState::flying;

  }
  else
  {

    // Showing recovery system is ready to launch
    humanInterface.showReadyToLaunchStatus();

  }

}


void Altimeter::flyingRun()
{

  // Registering altitude and writing to memory
  registerAltitude(true);

  // Shows to user the flying status
  humanInterface.showFlyingStatus();

  // Checks for falling state
  bool isFalling = false;

  if ( abs( altitude[n - 1] - barometer.getApogee() ) > Parameters::displacementForFallingDetection ) isFalling = true;

  // If rocket is falling changes altimeter's state
  if ( isFalling )
  {
    
    // Saving apogee
    memory.writeApogee();

    // Changing recovery system's state
    state = AltimeterState::falling;

  }

}


void Altimeter::fallingRun()
{

  // Registers altitude and writes to memory
  registerAltitude(true);

  // Checks for recovery
  bool isRecovered = false;

  if ( abs( altitude[n - 1] - altitude[0] ) < Parameters::displacementForRecoveryDetection ) isRecovered = true;

  // If rocket is recovered, changes recovery system's state
  if ( isRecovered )
  {

    // Changing recovery system's state
    state = AltimeterState::recovered;

  }

}


void Altimeter::recoveredRun()
{

  // Shows to user the recovered status
  humanInterface.showRecoveredStatus();

  // Reading button
  switch (button.getState())
  {

    case ButtonState::pressedAndReleased:
      humanInterface.blinkApogee(memory);
      humanInterface.showApogee(memory);
      humanInterface.showTrajectory(timeStep, memory);
      break;

    case ButtonState::longPressed:
      // Erasing memory
      memory.erase();
      
      // Restarting the altimeter
      begin();

      break;

    default:;

  };

}


void Altimeter::registerAltitude(bool writeToMemory)
{

  static unsigned long int currentStep = 0;

  if (millis() / timeStep > currentStep)
  {
    currentStep = currentStep + 1;

    for (int i = 0; i < n - 1; i++)
    {
      altitude[i] = altitude[i + 1];
    }

    altitude[n - 1] = barometer.getAltitude();

    if (writeToMemory) memory.writeAltitude(altitude[n - 1]);
  }

};

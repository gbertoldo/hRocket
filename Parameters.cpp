

    /**********************************************************************\
   /          hRocket: An Arduino powered altimeter                         \
  /            Federal University of Technology - Parana - Brazil            \
  \              by Guilherme Bertoldo and Jonas Joacir Radtke               /
   \                       updated November 27, 2019                        /
    \**********************************************************************/

#include "Parameters.h"

namespace Parameters
{

  const char*                      softwareVersion {"hRocket v.1.0"};
  const int                                 pinLed {13};
  const int                              pinButton {10};
  const int                     pinButtonVCCSource {12};
  const float      displacementForLiftoffDetection {10};
  const float      displacementForFallingDetection {5};
  const float     displacementForRecoveryDetection {2.0};

}

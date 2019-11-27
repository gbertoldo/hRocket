/*

       ^
       |
       |                                        ****
       |                                  ******    *****
       |                              *****             ******
       |                           ***                        ****
       |                        ***                              ***
       |                      **                                   ****
       |                    **                                        ***
       |                 ***                  hRocket                    *
       |                **                                                ***
       |              **             An Arduino powered altimeter           **
       |            ***                                                       **
       |           **                                                          *
       |         **
       |         *                             UTFPR
       |       **
       |      *               Federal University of Technology - Parana
       |    **
       |   *                   FRANCISCO BELTRAO  -  PARANA  -  BRAZIL
       |  **
       | *                  by Jonas Joacir Radtke and Guilherme Bertoldo
       |*
       +-------------------------------------------------------------------------------->

*/

#include "Altimeter.h"


// Creates an instance of the Altimeter class
Altimeter altimeter;


void setup()
{

  // Initializing the altimeter
  altimeter.begin();

}


void loop() {

  // Running the altimeter
  altimeter.run();

}

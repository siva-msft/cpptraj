#ifndef INC_CONSTANTS_H
#define INC_CONSTANTS_H
/*! \file Constants.h
    \brief Useful Physical constants

    The constants here are stored in as high precision as possible for
    double. Certain constants may have larger than 52 bit fraction,
    which may result in some small precision loss. The number of digits
    chosen in those cases (all PI-related) was done so using the criterion
    that the conversion back to PI matches within roundoff (e.g.
    TWOPI / 2 = 3.141592653589793).
 */
namespace Constants {
  // Various incarnations of PI
  const double PI           = 3.141592653589793; 
  const double TWOPI        = 6.283185307179586;  // may have precision loss
  const double FOURPI       = 12.566370614359172; // may have precision loss
  const double FOURTHIRDSPI = 4.1887902047863909; // may have precision loss 
  const double FOURFIFTHSPI = 2.5132741228718345; // may have precision loss
  const double PIOVER2      = 1.5707963267948966; // may have precision loss 
  // Convert degrees <-> radians
  const double DEGRAD       = 0.017453292519943295; // may have precision loss 
  const double RADDEG       =   57.29577951308232;  // may have precision loss
  // For checking floating point zero
  const double SMALL        = 0.00000000000001;
  /// Gas constant in J/mol*K
  const double GASK_J       = 8.3144621;
  /// Gas constant in kcal/mol*K
  const double GASK_KCAL    = 0.0019872041;
  // Convert electron charge <-> Amber units (w/ prefactor)
  const double ELECTOAMBER  = 18.2223;
  const double AMBERTOELEC  = 1.0 / ELECTOAMBER;
  /// Amber internal units of time are 1/20.455 ps
  const double AMBERTIME_TO_PS = 20.455;
}
#endif

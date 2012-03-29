#ifndef INC_PTRAJ_CONVERT_H
#define INC_PTRAJ_CONVERT_H
/*! \file ptraj_convert.h
    \brief Used to convert cpptraj state info to format recognized
           by ptraj actions/analysis.
 */
#include "ArgList.h"
#include "ptraj_arg.h"
#include "ptraj_state.h"
#include "Topology.h"

/// Convert ArgList information to argStackType
argStackType *CreateArgumentStack(ArgList &, int);
/// Free argStackType
void FreeArgumentStack(argStackType *);

/// Convert Topology information to ptrajState
ptrajState *CreateState(Topology *currentParm, int maxFrames);
/// Free ptrajState
void FreeState(ptrajState*);
#endif

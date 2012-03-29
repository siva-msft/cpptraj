// Conflib
#include "Traj_Conflib.h"
#include "CpptrajStdio.h"

// CONSTRUCTOR
Conflib::Conflib() { 
  energy_=0.0;
  radGyr_=0.0;
  timesFound_=0;
  conflibAtom_=0;
}

//------------------------------------------------------------------------
// Conflib::closeTraj()
void Conflib::closeTraj() {
  CloseFile();
}

// Conflib::openTraj()
int Conflib::openTraj() {
  if (OpenFile()) return 1;
  return 0;
}

// Conflib::setupTrajin()
int Conflib::setupTrajin(Topology *trajParm) {
  long unsigned int confFrame;
  int Frames = 0;

  // Conflib is double,double,int,natom*3*double
  confFrame = (((trajParm->natom * 3) + 2) * sizeof(double)) + sizeof(int);
  Frames = (int) (file_size_ / confFrame);

  if ( (file_size_ % confFrame) != 0 ) {
    mprintf("Warning: %s: Could not accurately predict # frames. This usually \n",
            BaseName());
    mprintf("         indicates a corrupted trajectory. Will attempt to read %i frames.\n",
            Frames);
  }
  conflibAtom_ = trajParm->natom;
  return Frames;
}

// Conflib::readFrame()
int Conflib::readFrame(int set, double *X, double *V,double *box, double *T) {

  if (IO->Read(&energy_,sizeof(double)) < 0) return 1;
  IO->Read(&radGyr_,sizeof(double));
  IO->Read(&timesFound_,sizeof(int));
  IO->Read(X,sizeof(double)*conflibAtom_*3); 

  if (debug_>0) mprinterr("CONFLIB %10i: %10.4lf %10.4lf %6i %10.4lf %10.4lf %10.4lf\n",
                         set, energy_, radGyr_, timesFound_, X[0], X[1], X[2]);
  return 0;
}

// Conflib::setupTrajout()
int Conflib::setupTrajout(Topology *trajParm) {
  mprintf("Error: conflib writes not yet implemented.\n");
  return 1;
}

// Conflib::writeFrame()
int Conflib::writeFrame(int set, double *X, double *V,double *box, double T) {
  mprintf("Error: conflib writes not yet implemented.\n");
  return 1;
}

// Conflib::info()
void Conflib::info() {
  mprintf("is an LMOD conflib file");
}


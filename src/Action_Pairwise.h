#ifndef INC_ACTIONS_PAIRWISE_H
#define INC_ACTIONS_PAIRWISE_H
/// Class: Pairwise 
/// Action to compare pairs of atoms. 
#include "Action.h"
class Pairwise: public Action {
    AtomMask Mask0;
    AtomMask RefMask;
    AmberParm *RefParm;
    Frame *RefFrame;
    bool *skipv;
    int *natexidx;
    bool hasExclusion;
    double kes;
    DataSet *ds_vdw;
    DataSet *ds_elec;
    double ELJ, Eelec;
    int Ncomparison;
    std::vector<double> ref_eelec;
    double cut_eelec;
    double cut_eelec1;
    bool isReference;
    std::vector<double> atom_eelec;

    int AllocateExclusion(AmberParm *);
    int NumInteractions(AtomMask *, AmberParm *);
    int SetupExclusion(AmberParm *, int);
    double Energy_LJ(AmberParm *, int, int, double, double *);
    double Energy_Coulomb(AmberParm *, int, int, double, double *);
    void Energy(AtomMask*,Frame*,AmberParm*);
  public:
    Pairwise();
    ~Pairwise();

    int init();
    int setup();
    int action();
    void print();
};
#endif  

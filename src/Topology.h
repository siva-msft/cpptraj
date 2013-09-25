#ifndef INC_TOPOLOGY_H
#define INC_TOPOLOGY_H
#include <string>
#include "Atom.h"
#include "Residue.h"
#include "Molecule.h"
#include "AtomMask.h"
#include "Frame.h"
#include "FileName.h"
// Class: Topology
/// Hold information for all atoms
class Topology {
  public:
    Topology();
    // ----- Set internal variables -----
    void SetOffset(double oIn);
    void SetDebug(int);
    void SetParmName(std::string const&, FileName const&);
    void SetGBradiiSet(std::string const&);
    void SetPindex(int);
    void SetReferenceCoords( Frame* ); // TODO: Pass in frame reference
    void IncreaseFrames(int);
    void SetTag(std::string const& t)    { parmTag_ = t;                  }
    void SetVelInfo(bool v)              { hasVelInfo_ = v;               }
    void SetNrepDim(int n)               { nRepDim_ = n;                  }
    // ----- Return internal variables -----
    std::string const& Tag()       const { return parmTag_;               }
    int Pindex()                   const { return pindex_;                }
    int Natom()                    const { return (int)atoms_.size();     }
    int Nres()                     const { return (int)residues_.size();  }
    int Nmol()                     const { return (int)molecules_.size(); }
    int Nsolvent()                 const { return NsolventMolecules_;     }
    int Nframes()                  const { return nframes_;               }
    int Ntypes()                   const { return ntypes_;                }
    int NextraPts()                const { return n_extra_pts_;           }
    bool HasVelInfo()              const { return hasVelInfo_;            }
    int NrepDim()                  const { return nRepDim_;               }
    std::string const& ParmName()         const { return parmName_;       }
    FileName const& OriginalFilename()    const { return fileName_;       }
    std::string const& GBradiiSet()       const { return radius_set_;     }
    bool NoRefCoords()                    const { return (refCoords_.empty()); }
    int FinalSoluteRes() const;
    const char *c_str() const;
    // ---- Atom-specific routines -----
    typedef std::vector<Atom>::const_iterator atom_iterator;
    atom_iterator begin()            const { return atoms_.begin(); }
    atom_iterator end()              const { return atoms_.end();   }
    const Atom &operator[](int idx)  const { return atoms_[idx];    }
    std::vector<Atom> const& Atoms() const { return atoms_;         }
    // ----- Residue-specific routines -----
    typedef std::vector<Residue>::const_iterator res_iterator;
    inline res_iterator ResStart() const { return residues_.begin(); }
    inline res_iterator ResEnd()   const { return residues_.end();   }
    const Residue& Res(int idx)    const { return residues_[idx];    }
    // ----- Molecule-specific routines -----
    typedef std::vector<Molecule>::const_iterator mol_iterator;
    inline mol_iterator MolStart() const { return molecules_.begin(); }
    inline mol_iterator MolEnd()   const { return molecules_.end();   }
    const Molecule& Mol(int idx)   const { return molecules_[idx];    }
    // ----- Bond-specific routines -----
    inline const std::vector<int>& Bonds() const { return bonds_; }
    inline const std::vector<int>& BondsH() const { return bondsh_; }
    inline const std::vector<double>& BondRk() const { return bondrk_; }
    inline const std::vector<double>& BondReq() const { return bondreq_; }
    int GetBondParamIdx( int, double &, double &) const;
    double GetBondedCutoff(int, int) const;
    // ----- Angle-specific routines -----
    inline const std::vector<int>& Angles() const { return angles_; }
    inline const std::vector<int>& AnglesH() const { return anglesh_; }
    inline const std::vector<double>& AngleTk() const { return angletk_; }
    inline const std::vector<double>& AngleTeq() const { return angleteq_; }
    // ----- Dihedral-specific routines -----
    inline const std::vector<int>& Dihedrals() const { return dihedrals_; }
    inline const std::vector<int>& DihedralsH() const { return dihedralsh_; }
    inline const std::vector<double>& DihedralPk() const { return dihedralpk_; }
    inline const std::vector<double>& DihedralPn() const { return dihedralpn_; }
    inline const std::vector<double>& DihedralPhase() const { return dihedralphase_; }
    inline const std::vector<double>& SCEE() const { return scee_; }
    inline const std::vector<double>& SCNB() const { return scnb_; }
    // ----- Amber Hbond info -----
    inline const std::vector<double>& Asol() const { return asol_; }
    inline const std::vector<double>& Bsol() const { return bsol_; }
    inline const std::vector<double>& HBcut() const { return hbcut_; }
    // ----- Amber extra info ----- TODO: Generate automatically
    inline const std::vector<double>& Solty() const { return solty_; }
    inline const std::vector<NameType>& Itree() const { return itree_; }
    inline const std::vector<int>& Join() const { return join_; }
    inline const std::vector<int>& Irotat() const { return irotat_; }
    // ----- Non-bond routines -----
    inline void GetLJ_A_B(int,int,double&,double&) const; 
    inline const std::vector<int>& NB_index() const { return nbindex_; }
    inline const std::vector<double>& LJA() const { return lja_; }
    inline const std::vector<double>& LJB() const { return ljb_; }
    // ----- Misc routines -----
    std::string TruncResAtomName(int) const;
    std::string TruncResNameNum(int) const;
    int FindAtomInResidue(int, NameType const&) const;
    int FindResidueMaxNatom() const;
    int SoluteAtoms() const;
    int SetSolvent(std::string const&);
    // ----- Print topology info -----
    void Summary() const;
    void Brief() const;
    void PrintAtomInfo(std::string const&) const;
    void PrintBondInfo(std::string const&) const;
    void PrintMoleculeInfo(std::string const&) const;
    void PrintResidueInfo(std::string const&) const;
    void PrintChargeMassInfo(std::string const&, int) const;
    // ----- Routines to Access/Modify Box info -----
    inline Box const& ParmBox()   const { return box_;        }
    inline Box::BoxType BoxType() const { return box_.Type(); }
    void SetBox( Box const& bIn )       { box_ = bIn;         }
    // ----- PDB/Mol2 etc setup routines -----
    void AddTopAtom(Atom const&, NameType const&, int, int&, const double*);
    void StartNewMol();
    // ----- Amber setup routines -----
    int CreateAtomArray(std::vector<NameType>&, std::vector<double>&,
                        std::vector<int>&, std::vector<double>&,
                        std::vector<int>&, std::vector<NameType>&,
                        std::vector<double>&,std::vector<double>&, 
                        std::vector<NameType>&, std::vector<int>&);
    int SetBondInfo(std::vector<int> &, std::vector<int> &,
                    std::vector<double>&,std::vector<double>&);
    int SetAngleInfo(std::vector<int> &, std::vector<int> &,
                    std::vector<double>&,std::vector<double>&);
    int SetDihedralInfo(std::vector<int> &, std::vector<int> &,
                    std::vector<double>&,std::vector<double>&,
                    std::vector<double>&,
                    std::vector<double>&,std::vector<double>&);
    int SetAmberHbond(std::vector<double>&,std::vector<double>&,std::vector<double>&);
    int SetAmberExtra(std::vector<double>&,std::vector<NameType> &,
                      std::vector<int> &,std::vector<int> &);
    int SetNonbondInfo(int, std::vector<int>& nbindex, 
                       std::vector<double>&, std::vector<double>&);
    // ----- Common Setup Routines -----
    int CommonSetup(bool);
    void ClearBondInfo();
    void AddBond(int,int);
    // ----- Mask Routines -----
    bool SetupIntegerMask(AtomMask &) const;
    bool SetupCharMask(AtomMask &) const;
    bool SetupIntegerMask(AtomMask &, Frame const&) const;
    bool SetupCharMask(AtomMask &, Frame const&) const;
    // ----- Topology modification routines -----
    void ScaleDihedralK(double);
    Topology* partialModifyStateByMask(AtomMask const& m) const {
      return modifyStateByMask(m, false);
    }
    Topology* modifyStateByMask(AtomMask const& m) const {
      return modifyStateByMask(m, true);
    }
    Topology* ModifyByMap(std::vector<int> const& m) const {
      return ModifyByMap(m, true);
    }
  private:
    std::vector<Atom> atoms_;
    std::vector<Residue> residues_;
    std::vector<Molecule> molecules_;
    FileName fileName_;
    std::string parmTag_;
    std::string parmName_;
    std::string radius_set_;

    std::vector<int> bonds_;
    std::vector<int> bondsh_;
    std::vector<double> bondrk_;
    std::vector<double> bondreq_;

    std::vector<int> angles_;
    std::vector<int> anglesh_;
    std::vector<double> angletk_;
    std::vector<double> angleteq_;

    std::vector<int> dihedrals_;
    std::vector<int> dihedralsh_;
    std::vector<double> dihedralpk_;
    std::vector<double> dihedralpn_;
    std::vector<double> dihedralphase_;
    std::vector<double> scee_;
    std::vector<double> scnb_;

    std::vector<double> asol_;
    std::vector<double> bsol_;
    std::vector<double> hbcut_;

    std::vector<double> solty_;
    std::vector<NameType> itree_;
    std::vector<int> join_;
    std::vector<int> irotat_;

    std::vector<int> nbindex_;
    std::vector<double> lja_;
    std::vector<double> ljb_;

    Box box_;
    Frame refCoords_;

    double offset_;         ///< Offset used when searching for bonds
    int debug_;
    int NsolventMolecules_;
    int finalSoluteRes_;
    int pindex_;
    int nframes_;
    int ntypes_; // This is stored for the purpose of checking array sizes
    int n_extra_pts_;
    bool hasVelInfo_; // TODO: This information should be passed separate from Topology
    int nRepDim_;     // TODO: This information should be passed separate from Topology

    void PrintBonds(std::vector<int> const&, AtomMask const&) const;
    void SetAtomBondInfo();
    static void WarnBondLengthDefault(Atom::AtomicElementType,
                                      Atom::AtomicElementType,double);
    static double GetBondLength(Atom::AtomicElementType, Atom::AtomicElementType);
    static bool NameIsSolvent(NameType const&);
    void GetBondsFromAtomCoords();
    void VisitAtom(int, int);
    int DetermineMolecules();
    void AtomDistance(int, int, int, std::set<int>&) const;
    void DetermineExcludedAtoms();
    void DetermineNumExtraPoints();
    int SetSolventInfo();

    void Mask_SelectDistance( Frame const&, char*, bool, bool, double ) const;
    void Mask_AND(char*,char*) const;
    void Mask_OR(char*,char*) const;
    void Mask_NEG(char*) const;
    void MaskSelectResidues(NameType const&, char *) const;
    void MaskSelectResidues(int, int, char *) const;
    void MaskSelectElements( NameType const&, char* ) const;
    void MaskSelectTypes( NameType const& , char* ) const;
    void MaskSelectAtoms(NameType const&, char*) const;
    void MaskSelectAtoms(int, int, char*) const;
    bool ParseMask(Frame const&, AtomMask &,bool) const;

    Topology* modifyStateByMask(AtomMask const&, bool) const;
    Topology* ModifyByMap(std::vector<int> const&, bool) const;
    std::vector<int> SetupSequentialArray(std::vector<int> const&, int, std::vector<int> const&) const;
};
// ----- INLINE FUNCTIONS ------------------------------------------------------
void Topology::GetLJ_A_B(int a1, int a2, double& A, double& B) const {
  // Currently atom #s start from 1 in TypeIndex
  int param = (ntypes_ * (atoms_[a1].TypeIndex()-1)) + atoms_[a2].TypeIndex()-1;
  int index = nbindex_[param] - 1;
  A = lja_[index];
  B = ljb_[index];
}
#endif

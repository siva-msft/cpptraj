#ifndef INC_MATRIX_3X3_H
#define INC_MATRIX_3X3_H
#include "Vec3.h"
class Matrix_3x3 {
  public:
    Matrix_3x3();
    Matrix_3x3(const Matrix_3x3&);
    Matrix_3x3(const double*);
    Matrix_3x3(double,double,double);
    Matrix_3x3& operator=(const Matrix_3x3&);
 
    // NOTE: No bounds check!
    double operator[](int idx) const { return M_[idx]; }

    int Diagonalize( double*, double* );
    int Diagonalize_Sort(double *, double *);
    int Diagonalize_Sort_Chirality(double*, double*,int);
    void Print(const char*);

    Matrix_3x3& operator*=(const Matrix_3x3&);
    void RotationAroundZ(double, double);
    void RotationAroundY(double, double);
    /// Multiply 3x3 matrix times 1x3 vector
    Vec3 operator*(Vec3 const& rhs) const {
      double x = rhs[0]; 
      double y = rhs[1]; 
      double z = rhs[2];
      return Vec3( ((M_[0]*x) + (M_[1]*y) + (M_[2]*z)),
                   ((M_[3]*x) + (M_[4]*y) + (M_[5]*z)),
                   ((M_[6]*x) + (M_[7]*y) + (M_[8]*z))  );
    }
    /// Multiply transpose of 3x3 matrix times 1x3 vector
    Vec3 TransposeMult(Vec3 const& rhs) const {
      double x = rhs[0];
      double y = rhs[1];
      double z = rhs[2];
      return Vec3( ((M_[0]*x) + (M_[3]*y) + (M_[6]*z)),
                   ((M_[1]*x) + (M_[4]*y) + (M_[7]*z)),
                   ((M_[2]*x) + (M_[5]*y) + (M_[8]*z))  );
    }
    // TODO: Get rid of this
    const double* Dptr() const { return M_; }
  private:
    double M_[9];
    // The following three variables are set during Diagonalize_Sort. They
    // indicate the original ordering of the eigenvalues/eigenvectors. This
    // information can be used to prevent reflections when e.g. aligning
    // coordinates along principal axes (see e.g. Action_Principal).
    int i1_;
    int i2_;
    int i3_;
    static const int MAX_ITERATIONS;
};
#endif

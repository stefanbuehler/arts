#pragma once

#include <matpack.h>

#include "configtypes.h"
#include "grids.h"

namespace Legendre {

//! Stores the up (U), south (S), east (E) values of a field relative to the sphere
struct SphericalField {
  Numeric U{0};
  Numeric S{0};
  Numeric E{0};

  //! Returns the total strength of the field
  [[nodiscard]] Numeric total() const noexcept { return std::hypot(U, S, E); }

  //! Returns the total strength of the field
  [[nodiscard]] Numeric total_horizontal() const noexcept {
    return std::hypot(S, E);
  }

  //! Always construct to zeroes explicitly
  constexpr SphericalField() noexcept = default;
};

//! Holds a SphericalField for multiple dimensions (radius times longitudes)
using MatrixOfSphericalField = Grid<SphericalField, 2>;

/** Returns the Schmidt normalized Lagrange polynominal and its derivative
 *
 * The derivative is undefined if theta is 0 or pi, so the function cannot
 * be called with these values
 *
 * This function is taken from the implementation by at https://github.com/klaundal/ppigrf
 * (2024-06-13).  It implements the calculations step-by-step, updating both main and derivative
 * based on previous values.
 *
 * @param[in] theta Colatitude in radians
 * @param[in] nmax Max number of n
 * @return The pair of (nmax+1) x (nmax+1) matrices, order: main and derivative
 */
std::pair<Matrix, Matrix> schmidt(const Numeric theta, const Index nmax);

/** Computes the spherical field
 * 
 * If latitude is beyond a limit, the longitude is set to zero
 * and the latitude at the limit away from the pole is used. For these
 * position, the absolute of the horizontal component is kept around in
 * the south-facing component and the east-facing component is set to zero
 * 
 * The latitude limit is defined in the ColatitudeConversion struct.
 * 
 * The longitude is constrained to the range [-180, 180) to have consistent
 * behavior at the daytime border.
 * 
 * This function is taken from the implementation by Isabela de Oliveira Martins
 * at https://github.com/de-oliveira/IsabelaFunctions/blob/master/IsabelaFunctions/fieldmodel.py
 * (2021-05-06).
 * 
 * @param[in] g A N x N matrix of g-coefficients
 * @param[in] h A N x N matrix of h-coefficients
 * @param[in] r0 The reference radius (spherical)
 * @param[in] pos The position [r, lat, lon] (spherical)
 * @return A spherical field {Br, Btheta, Bphi}
 */
Vector3 schmidt_fieldcalc(const Matrix& g,
                          const Matrix& h,
                          const Numeric r0,
                          const Vector3 pos);

/** Computes sum (s[i] P_i(x)) for all s [first is for P_0, second is for P_1, ...]
  * 
  * @param[in] s The coefficients
  * @param[in] x The x values
  * @return The sum
  */
Numeric legendre_sum(const ExhaustiveConstVectorView& s, const Numeric& x);

/** Computes P_n(x)
  * 
  * @param[in] n The order
  * @param[in] x The value
  * @return The polynomial
  */
Numeric legendre(Index n, Numeric x);

/** Computes n!
  * 
  * @param[in] n The index
  * @return The factorial value
  */
Numeric factorial(Index n);

/** Computes P^m_l(x)
  * 
  * @param[in] l The degree
  * @param[in] m The order
  * @param[in] x The value
  * @return The associated polynomial
  */
Numeric assoc_legendre(Index l, Index m, Numeric x);

/** Computes the ratio of gamma functions
  * 
  * @param[in] x The first argument
  * @param[in] y The second argument
  * @return The ratio
  */
Numeric tgamma_ratio(Numeric x, Numeric y);

/** Computes the double Gauss Legendre quadrature
 *
 * The degree of the single Gauss Legendre quadrature is the length of x and w,
 * which must be the same.
 * 
 * @param x The coordinates
 * @param w The weights
 */
void PositiveDoubleGaussLegendre(ExhaustiveVectorView x,
                                 ExhaustiveVectorView w);

/** Computes the Gauss Legendre quadrature
  * 
  * @param x The coordinates
  * @param w The weights
  */
void GaussLegendre(ExhaustiveVectorView x, ExhaustiveVectorView w);

/** Computes the positive part of the Gauss Legendre quadrature
  *
  * The degree of the full polynomial is twice the legnth of x and w,
  * which must be the same, but only the positive parts are kept.
  * 
  * @param x The coordinates
  * @param w The weights
  */
void PositiveGaussLegendre(ExhaustiveVectorView x, ExhaustiveVectorView w);
}  // namespace Legendre

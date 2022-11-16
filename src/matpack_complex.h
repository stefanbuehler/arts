/* Copyright (C) 2002-2012 Stefan Buehler <sbuehler@ltu.se>

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA. */

/*!
  \file   complex.h
  \author Oliver Lemke <olemke@core-dump.info>
  \date   2002-12-19
  
  \brief  A class implementing complex numbers for ARTS.
*/

#ifndef matpack_complex_h
#define matpack_complex_h

#include "lapack.h"
#include "matpackI.h"
#include "matpack_concepts.h"
#include "nonstd.h"
#include <complex>
#include <utility>

using Complex = std::complex<Numeric>;
struct ComplexLayout {Numeric real, imag;};

/** Return a reference to the real value of c */
inline Numeric& real_val(Complex& c) noexcept {return reinterpret_cast<ComplexLayout(&)>(c).real;}

/** Return a reference to the imaginary value of c */
inline Numeric& imag_val(Complex& c) noexcept {return reinterpret_cast<ComplexLayout(&)>(c).imag;}

/** Return a const reference to the real value of c */
inline const Numeric& real_val(const Complex& c) noexcept {return reinterpret_cast<const ComplexLayout(&)>(c).real;}

/** Return a const reference to the imaginary value of c */
inline const Numeric& imag_val(const Complex& c) noexcept {return reinterpret_cast<const ComplexLayout(&)>(c).imag;}

inline std::complex<float> operator+(const double& d,
                                     const std::complex<float>& c) {
  return (float(d) + c);
}
inline std::complex<float> operator*(const double& d,
                                     const std::complex<float>& c) {
  return (float(d) * c);
}

inline std::complex<float> operator+(const std::complex<float>& c,
                                     const double& d) {
  return (c + float(d));
}
inline std::complex<float> operator*(const std::complex<float>& c,
                                     const double& d) {
  return (c * float(d));
}

// Constexpr versions of common Complex operations

// Helpers to keep equations readable
#define a1 c.real()
#define b1 c.imag()
#define a2 z.real()
#define b2 z.imag()

/** squared magnitude of c */
constexpr Numeric abs2(Complex c) noexcept { return a1 * a1 + b1 * b1; }

/** the conjugate of c */
constexpr Complex conj(Complex c) noexcept { return {a1, -b1}; }

/** real */
constexpr Numeric real(Complex c) noexcept { return a1; }

/** imag */
constexpr Numeric imag(Complex c) noexcept { return b1; }

// Basic constexpr operations for Complex that don't exist in the standard yet (C++11)
// NOTE: Remove these if there is ever an overload warning updating the C++ compiler version

constexpr Complex operator+(Complex c, Numeric n) noexcept {
  return {a1 + n, b1};
}
constexpr Complex operator-(Complex c, Numeric n) noexcept {
  return {a1 - n, b1};
}
constexpr Complex operator*(Complex c, Numeric n) noexcept {
  return {a1 * n, b1 * n};
}
constexpr Complex operator/(Complex c, Numeric n) noexcept {
  return {a1 / n, b1 / n};
}

constexpr Complex operator+(Numeric n, Complex c) noexcept {
  return {n + a1, b1};
}
constexpr Complex operator-(Numeric n, Complex c) noexcept {
  return {n - a1, -b1};
}
constexpr Complex operator*(Numeric n, Complex c) noexcept {
  return {n * a1, n * b1};
}
constexpr Complex operator/(Numeric n, Complex c) noexcept {
  return Complex(n * a1, -n * b1) / abs2(c);
}

constexpr Complex operator+(Complex c, Complex z) noexcept {
  return {a1 + a2, b1 + b2};
}
constexpr Complex operator-(Complex c, Complex z) noexcept {
  return {a1 - a2, b1 - b2};
}
constexpr Complex operator*(Complex c, Complex z) noexcept {
  return {a1 * a2 - b1 * b2, a1 * b2 + b1 * a2};
}
constexpr Complex operator/(Complex c, Complex z) noexcept {
  return Complex(a1 * a2 + b1 * b2, -a1 * b2 + b1 * a2) / abs2(z);
}
constexpr Complex operator-(Complex c) noexcept { return {-a1, -b1}; }

// Remove helpers to keep global namespace usable
#undef a1
#undef b1
#undef a2
#undef b2

// Basic constexpr operations for different types since C++11 std::complex is lacking conversions
// FIXME: Cannot be template because Eigen interferes, so explicit copies are required for operations
// NOTE: Remove these if there is ever an overload warning updating the C++ compiler version
#define _complex_operations_(T)                   \
  constexpr Complex operator+(Complex c, T x) noexcept {   \
    return operator+(c, static_cast<Numeric>(x)); \
  }                                               \
  constexpr Complex operator-(Complex c, T x) noexcept {   \
    return operator-(c, static_cast<Numeric>(x)); \
  }                                               \
  constexpr Complex operator*(Complex c, T x) noexcept {   \
    return operator*(c, static_cast<Numeric>(x)); \
  }                                               \
  constexpr Complex operator/(Complex c, T x) noexcept {   \
    return operator/(c, static_cast<Numeric>(x)); \
  }                                               \
                                                  \
  constexpr Complex operator+(T x, Complex c) noexcept {   \
    return operator+(static_cast<Numeric>(x), c); \
  }                                               \
  constexpr Complex operator-(T x, Complex c) noexcept {   \
    return operator-(static_cast<Numeric>(x), c); \
  }                                               \
  constexpr Complex operator*(T x, Complex c) noexcept {   \
    return operator*(static_cast<Numeric>(x), c); \
  }                                               \
  constexpr Complex operator/(T x, Complex c) noexcept {   \
    return operator/(static_cast<Numeric>(x), c); \
  }

_complex_operations_(int)
_complex_operations_(float)
_complex_operations_(Index)

#undef _complex_operations_

constexpr bool isnan(Complex c) noexcept {
  return nonstd::isnan(c.real()) or nonstd::isnan(c.imag());
}

    // Declare existence of the global joker object:
    extern const Joker joker;

// Declare the existence of class ConstComplexMatrixView:
class ConstComplexIterator1D;

// Declare the existence of class ComplexVectorView:
class ComplexVectorView;

// Declare the existence of class ConstComplexVectorView:
class ConstComplexVectorView;

// Declare the existence of class ConstMatrixView:
class ConstComplexMatrixView;

/** The iterator class for sub vectors. This takes into account the
 *  defined stride. */
class ComplexIterator1D {
 public:
  /** Default constructor. */
  ComplexIterator1D() = default;

  /** Explicit constructor. */
  ComplexIterator1D(Complex* x, Index stride)
      : mx(x), mstride(stride) { /* Nothing to do here. */
  }

  // Operators:

  /** Prefix increment operator. */
  ComplexIterator1D& operator++() {
    mx += mstride;
    return *this;
  }

  /** Dereferencing. */
  Complex& operator*() const { return *mx; }

  /** Not equal operator, needed for algorithms like copy. */
  bool operator!=(const ComplexIterator1D& other) const {
    if (mx != other.mx)
      return true;
    return false;
  }

  friend void copy(ConstComplexIterator1D origin,
                   const ConstComplexIterator1D& end,
                   ComplexIterator1D target);

 private:
  /** Current position. */
  Complex* mx{nullptr};
  /** Stride. */
  Index mstride{0};
};

/** The constant iterator class for sub vectors. This takes into
 *  account the defined stride. */
class ConstComplexIterator1D {
 public:
  /** Default constructor. */
  ConstComplexIterator1D() = default;

  /** Explicit constructor. */
  ConstComplexIterator1D(Complex* x, Index stride)
      : mx(x), mstride(stride) { /* Nothing to do here. */
  }

  // Operators:
  /** Prefix increment operator. */
  ConstComplexIterator1D& operator++() {
    mx += mstride;
    return *this;
  }

  /** Dereferencing. */
  const Complex& operator*() const { return *mx; }

  /** Not equal operator, needed for algorithms like copy. */
  bool operator!=(const ConstComplexIterator1D& other) const {
    if (mx != other.mx)
      return true;
    return false;
  }

  friend void copy(ConstComplexIterator1D origin,
                   const ConstComplexIterator1D& end,
                   ComplexIterator1D target);

 private:
  /** Current position. */
  const Complex* mx{nullptr};
  /** Stride. */
  Index mstride{0};
};

// Declare the complex vector class:
class ComplexVector;

// Declare the ComplexMatrixView class
class ComplexMatrixView;

/** A constant view of a ComplexVector.
 * 
 Together with the derived class ComplexVectorView this contains the main
 implementation of a ComplexVector. The class ComplexVector is just a special
 case of a ComplexVectorView which also allocates storage. */
class ConstComplexVectorView {
 public:
  static constexpr bool matpack_type{true};
  
  constexpr ConstComplexVectorView(const ConstComplexVectorView&) = default;
  constexpr ConstComplexVectorView(ConstComplexVectorView&&) = default;
  ConstComplexVectorView& operator=(const ConstComplexVectorView&) = default;
  ConstComplexVectorView& operator=(ConstComplexVectorView&&) = default;

  // Typedef for compatibility with STL
  using const_iterator = ConstComplexIterator1D;

  // Member functions:
  [[nodiscard]] bool empty() const noexcept { return (nelem() == 0); }
  [[nodiscard]] Index nelem() const noexcept { return mrange.mextent; }
  [[nodiscard]] Index size() const noexcept { return mrange.mextent; }
  [[nodiscard]] Complex sum() const;

  // Const index operators:
  /** Plain const index operator. */
  const Complex& operator[](Index n) const {  // Check if index is valid:
    ARTS_ASSERT(0 <= n);
    ARTS_ASSERT(n < mrange.mextent);
    return get(n);
  }

  /** Get element implementation without assertions. */
  [[nodiscard]] const Complex& get(Index n) const {
    return *(mdata + mrange.mstart + n * mrange.mstride);
  }

  /** Get element implementation without assertions. */
  [[nodiscard]] const Numeric& get_real(Index n) const {
    return reinterpret_cast<const ComplexLayout(&)>(get(n)).real;
  }

  /** Get element implementation without assertions. */
  [[nodiscard]] const Numeric& get_imag(Index n) const {
    return reinterpret_cast<const ComplexLayout(&)>(get(n)).imag;
  }
  
  /** Get a view of the real part of the vector */
  [[nodiscard]] ConstVectorView real() const;
  
  /** Get a view of the imaginary part of the vector */
  [[nodiscard]] ConstVectorView imag() const;

  ConstComplexVectorView operator[](const Range& r) const;
  friend Complex operator*(const ConstComplexVectorView& a,
                           const ConstComplexVectorView& b);

  // Functions returning iterators:
  [[nodiscard]] ConstComplexIterator1D begin() const;
  [[nodiscard]] ConstComplexIterator1D end() const;

  // Conversion to 1 column matrix:
  operator ConstComplexMatrixView() const;

  //! Destructor
  virtual ~ConstComplexVectorView() = default;

  // Friends:
  friend class ComplexVectorView;
  friend class ConstComplexIterator2D;
  friend class ConstComplexMatrixView;
  friend void mult(ComplexVectorView,
                   const ConstComplexMatrixView&,
                   const ConstComplexVectorView&);

  friend std::ostream& operator<<(std::ostream& os, const ConstComplexVectorView& v);

  // A special constructor, that allows to make a ConstVectorView of a scalar.
  ConstComplexVectorView(const Complex& a);

  //! Start element in memory
  [[nodiscard]] Index selem() const noexcept {return mrange.mstart;}

  //! Steps in memory between elements
  [[nodiscard]] Index delem() const noexcept {return mrange.mstride;}

  [[nodiscard]] Complex* get_c_array() const noexcept {return mdata;}

 protected:
  // Constructors:
  ConstComplexVectorView() = default;
  ConstComplexVectorView(Complex* data, const Range& range);
  ConstComplexVectorView(Complex* data, const Range& p, const Range& n);

  // Data members:
  // -------------
  /** The range of mdata that is actually used. */
  Range mrange{0, 0};
  /** Pointer to the plain C array that holds the data */
  Complex* mdata{nullptr};
};

/** The ComplexVectorView class.
 * 
 This contains the main implementation of a complex vector. The class     
 ComplexVector is just a special case of subvector which also allocates
 storage.
 
 Unfortunately, names of element functions of derived classes hide
 the names of the original class, even if the arguments are
 different. This means that we have to redefine those element
 functions that can have different arguments, for example the
 constant index operators and iterators. */
class ComplexVectorView : public ConstComplexVectorView {
 public:
  // Make const methods visible from base class
  using ConstComplexVectorView::begin;
  using ConstComplexVectorView::end;
  using ConstComplexVectorView::operator[];
  using ConstComplexVectorView::get;
  using ConstComplexVectorView::get_imag;
  using ConstComplexVectorView::get_real;
  using ConstComplexVectorView::imag;
  using ConstComplexVectorView::real;

  constexpr ComplexVectorView(const ComplexVectorView&) = default;
  ComplexVectorView(const ComplexVector&);
  ComplexVectorView(ComplexVector& v);

  // Typedef for compatibility with STL
  using iterator = ComplexIterator1D;

  /** Plain Index operator. */
  Complex& operator[](Index n) {  // Check if index is valid:
    ARTS_ASSERT(0 <= n);
    ARTS_ASSERT(n < mrange.mextent);
    return get(n);
  }

  /** Get element implementation without assertions. */
  Complex& get(Index n) {
    return *(mdata + mrange.mstart + n * mrange.mstride);
  }

  /** Get element implementation without assertions. */
  Numeric& get_real(Index n) {
    return reinterpret_cast<ComplexLayout(&)>(get(n)).real;
  }

  /** Get element implementation without assertions. */
  Numeric& get_imag(Index n) {
    return reinterpret_cast<ComplexLayout(&)>(get(n)).imag;
  }
  
  /** Get a view of the real part of the vector */
  [[nodiscard]] VectorView real();
  
  /** Get a view of the imaginary part of the vector */
  [[nodiscard]] VectorView imag();

  ComplexVectorView operator[](const Range& r);

  // ComplexIterators:
  ComplexIterator1D begin();
  ComplexIterator1D end();

  // Assignment operators:
  ComplexVectorView& operator=(const ConstComplexVectorView& v);
  ComplexVectorView& operator=(const ComplexVectorView& v);
  ComplexVectorView& operator=(const ComplexVector& v);
  ComplexVectorView& operator=(const Array<Complex>& v);
  ComplexVectorView& operator=(Complex x);
  ComplexVectorView& operator=(const ConstVectorView& v);
  ComplexVectorView& operator=(const VectorView& v);
  ComplexVectorView& operator=(const Vector& v);
  ComplexVectorView& operator=(const Array<Numeric>& v);
  ComplexVectorView& operator=(Numeric x);

  // Other operators:
  ComplexVectorView operator*=(Complex x);
  ComplexVectorView operator/=(Complex x);
  ComplexVectorView operator+=(Complex x);
  ComplexVectorView operator-=(Complex x);
  ComplexVectorView operator*=(Numeric x);
  ComplexVectorView operator/=(Numeric x);
  ComplexVectorView operator+=(Numeric x);
  ComplexVectorView operator-=(Numeric x);

  ComplexVectorView operator*=(const ConstComplexVectorView& x);
  ComplexVectorView operator/=(const ConstComplexVectorView& x);
  ComplexVectorView operator+=(const ConstComplexVectorView& x);
  ComplexVectorView operator-=(const ConstComplexVectorView& x);
  ComplexVectorView operator*=(const ConstVectorView& x);
  ComplexVectorView operator/=(const ConstVectorView& x);
  ComplexVectorView operator+=(const ConstVectorView& x);
  ComplexVectorView operator-=(const ConstVectorView& x);

  // Conversion to 1 column matrix:
  operator ComplexMatrixView();

  //! Destructor
   ~ComplexVectorView() override = default;

  // Friends:
  friend class ConstComplexIterator2D;
  friend class ComplexIterator2D;
  friend class ComplexMatrixView;

  // A special constructor, that allows to make a ComplexVectorView of a scalar.
  ComplexVectorView(Complex& a);

 protected:
  // Constructors:
  ComplexVectorView() = default;
  ComplexVectorView(Complex* data, const Range& range);
  ComplexVectorView(Complex* data, const Range& p, const Range& n);
};

/** The row iterator class for sub matrices. This takes into account the
 defined row stride. The iterator points to a row of the matrix,  *
 which acts just like a ComplexVectorView. */
class ComplexIterator2D {
 public:
  // Constructors:
  /** Default constructor. */
  ComplexIterator2D() = default;

  /** Explicit constructor. */
  ComplexIterator2D(const ComplexVectorView& x, Index stride)
      : msv(x), mstride(stride) { /* Nothing to do here. */
  }

  // Operators:
  /** Prefix increment operator. */
  ComplexIterator2D& operator++() {
    msv.mdata += mstride;
    return *this;
  }

  /** Not equal operator, needed for algorithms like copy. */
  bool operator!=(const ComplexIterator2D& other) const {
    if (msv.mdata + msv.mrange.mstart !=
        other.msv.mdata + other.msv.mrange.mstart)
      return true;
    return false;
  }

  /** The -> operator is needed, so that we can write i->begin() to get
     the 1D iterators. */
  ComplexVectorView* operator->() { return &msv; }

  /** Dereferencing. */
  ComplexVectorView& operator*() { return msv; }

 private:
  /** Current position. */
  ComplexVectorView msv;
  /** Row stride. */
  Index mstride{0};
};

/** The const row iterator class for sub matrices. This takes into account the
 defined row stride. The iterator points to a row of the matrix,  *
 which acts just like a ComplexVectorView. */
class ConstComplexIterator2D {
 public:
  // Constructors:
  /** Default constructor. */
  ConstComplexIterator2D() = default;

  /** Explicit constructor. */
  ConstComplexIterator2D(ConstComplexVectorView x, Index stride)
      : msv(std::move(x)), mstride(stride) { /* Nothing to do here. */
  }

  // Operators:
  /** Prefix increment operator. */
  ConstComplexIterator2D& operator++() {
    msv.mdata += mstride;
    return *this;
  }

  /** Not equal operator, needed for algorithms like copy. */
  bool operator!=(const ConstComplexIterator2D& other) const {
    if (msv.mdata + msv.mrange.mstart !=
        other.msv.mdata + other.msv.mrange.mstart)
      return true;
    return false;
  }

  /** The -> operator is needed, so that we can write i->begin() to get
     t he 1D iterators. */
  const ConstComplexVectorView* operator->() const { return &msv; }

  /** Dereferencing. */
  const ConstComplexVectorView& operator*() const { return msv; }

 private:
  /** Current position. */
  ConstComplexVectorView msv;
  /** Row stride. */
  Index mstride{0};
};

/** The ComplexVector class. This is a subvector that also allocates storage
 automatically, and deallocates it when it is destroyed. We take  *
 all the functionality from ComplexVectorView. Additionally defined in
 this class are:
 
 1. Constructors and destructors (allocating memory).
 2. Assignment operator
 3. Assignment operator from scalar.
 4. Resize function.
 */
class ComplexVector : public ComplexVectorView {
 public:
  // Constructors:
  ComplexVector() = default;
  ComplexVector(ComplexVector&& cv) noexcept : ComplexVectorView(std::forward<ComplexVectorView>(cv)) {
    cv.mdata = nullptr;
  }
  explicit ComplexVector(Index n);
  ComplexVector(Index n, Complex fill);
  ComplexVector(Index n, Numeric fill);
  ComplexVector(Complex start, Index extent, Complex stride);
  ComplexVector(Complex start, Index extent, Numeric stride);
  ComplexVector(Numeric start, Index extent, Complex stride);
  ComplexVector(Numeric start, Index extent, Numeric stride);
  explicit ComplexVector(const ConstComplexVectorView& v);
  ComplexVector(const ComplexVector& v);
  explicit ComplexVector(const Vector& v);
  explicit ComplexVector(const std::vector<Complex>&);
  explicit ComplexVector(const std::vector<Numeric>&);
  ComplexVector(Complex* c, const Range& r0) ARTS_NOEXCEPT
  : ComplexVectorView(c, r0) {
    ARTS_ASSERT(r0.get_extent() >= 0, "Must have size. Has: ", r0.get_extent());
  }

  /** Initialization from a vector type. */
  explicit ComplexVector(const matpack::vector_like_not_vector auto& init) : ComplexVector(matpack::column_size(init)) {
    for (Index i=0; i<size(); i++) operator[](i) = init[i];
  }

  // Assignment operators:
  ComplexVector& operator=(const ComplexVector& v);
  ComplexVector& operator=(const Array<Complex>& v);
  ComplexVector& operator=(Complex x);

  /** Set from a vector type. */
   ComplexVector& operator=(const matpack::vector_like_not_vector auto& init) {
    return *this = ComplexVector(init);
  }

  ComplexVector& operator=(ComplexVector&& v) ARTS_NOEXCEPT {
    if (this != &v) {
      delete[] mdata;
      mdata = v.mdata;
      mrange = v.mrange;
      v.mrange = Range(0, 0);
      v.mdata = nullptr;
    }
    return *this;
  }

  // Resize function:
  void resize(Index n);

  // Swap function:
  friend void swap(ComplexVector& v1, ComplexVector& v2) noexcept;

  // Destructor:
   ~ComplexVector() noexcept override;
};

// Declare class ComplexMatrix:
class ComplexMatrix;

/** A constant view of a ComplexMatrix.
 * 
 This, together with the derived class Complex*MatrixView, contains the   *
 main implementation of a ComplexMatrix. It defines the concepts of
 ComplexMatrixView. Plus additionally the recursive subrange operator,
 which makes it possible to create a ComplexMatrixView from a subrange of
 a ComplexMatrixView.
 
 The class ComplexMatrix is just a special case of a ComplexMatrixView
 which also allocates storage. */
class ConstComplexMatrixView {
 public:
  static constexpr bool matpack_type{true};
  
  constexpr ConstComplexMatrixView(const ConstComplexMatrixView&) = default;
  constexpr ConstComplexMatrixView(ConstComplexMatrixView&&) = default;
  ConstComplexMatrixView& operator=(const ConstComplexMatrixView&) = default;
  ConstComplexMatrixView& operator=(ConstComplexMatrixView&&) = default;

  // Typedef for compatibility with STL
  using const_iterator = ConstComplexIterator2D;

  // Member functions:
  [[nodiscard]] Index selem() const noexcept { return mrr.mstart + mcr.mstart; }
  [[nodiscard]] Index nrows() const noexcept { return mrr.mextent; }
  [[nodiscard]] Index ncols() const noexcept { return mcr.mextent; }
  [[nodiscard]] Index drows() const noexcept { return mrr.mstride; }
  [[nodiscard]] Index dcols() const noexcept { return mcr.mstride; }
  
  // Total size
  [[nodiscard]] Index size() const noexcept {return nrows() * ncols();}
  [[nodiscard]] bool empty() const noexcept { return not nrows() or not ncols(); }

  // Const index operators:
  /** Plain const index operator. */
  Complex operator()(Index r, Index c) const {  // Check if indices are valid:
    ARTS_ASSERT(0 <= r);
    ARTS_ASSERT(0 <= c);
    ARTS_ASSERT(r < mrr.mextent);
    ARTS_ASSERT(c < mcr.mextent);

    return get(r, c);
  }

  /** Get element implementation without assertions. */
  [[nodiscard]] Complex get(Index r, Index c) const {
    return *(mdata + mrr.mstart + r * mrr.mstride + mcr.mstart +
             c * mcr.mstride);
  }

  /** Get element implementation without assertions. */
  [[nodiscard]] Numeric get_real(Index r, Index c) const { return get(r, c).real(); }

  /** Get element implementation without assertions. */
  [[nodiscard]] Numeric get_imag(Index r, Index c) const { return get(r, c).imag(); }
  
  /** Get a view of the real part of the matrix */
  [[nodiscard]] ConstMatrixView real() const;

  /** Get a view of the imaginary part of the matrix */
  [[nodiscard]] ConstMatrixView imag() const;
  
  /** Get the extent of the underlying data */
  [[nodiscard]] Index get_column_extent() const {return mcr.get_extent();}

  ConstComplexMatrixView operator()(const Range& r, const Range& c) const;
  ConstComplexVectorView operator()(const Range& r, Index c) const;
  ConstComplexVectorView operator()(Index r, const Range& c) const;

  // Functions returning iterators:
  [[nodiscard]] ConstComplexIterator2D begin() const;
  [[nodiscard]] ConstComplexIterator2D end() const;

  // View on diagonal complex vector
  [[nodiscard]] ConstComplexVectorView diagonal() const;

  //! Destructor
  virtual ~ConstComplexMatrixView() = default;

  // Friends:
  friend class ComplexMatrixView;
  friend class ConstComplexVectorView;
  friend ConstComplexMatrixView transpose(ConstComplexMatrixView m);
  friend void mult(ComplexVectorView,
                   const ConstComplexMatrixView&,
                   const ConstComplexVectorView&);
  friend void mult(ComplexMatrixView,
                   const ConstComplexMatrixView&,
                   const ConstComplexMatrixView&);
  friend void mult(ComplexMatrixView,
                   const ConstMatrixView&,
                   const ConstComplexMatrixView&);
  friend void mult(ComplexMatrixView,
                   const ConstComplexMatrixView&,
                   const ConstMatrixView&);
  
  friend std::ostream& operator<<(std::ostream& os, const ConstComplexMatrixView& v);

  [[nodiscard]] Complex* get_c_array() const noexcept {return mdata;}

 protected:
  // Constructors:
  ConstComplexMatrixView() = default;
  ConstComplexMatrixView(Complex* data, const Range& r, const Range& c);
  ConstComplexMatrixView(Complex* data,
                         const Range& pr,
                         const Range& pc,
                         const Range& nr,
                         const Range& nc);

  // Data members:
  // -------------
  /** The row range of mdata that is actually used. */
  Range mrr{0, 0, 1};
  /** The column range of mdata that is actually used. */
  Range mcr{0, 0, 1};
  /** Pointer to the plain C array that holds the data */
  Complex* mdata{nullptr};
};

/** The ComplexMatrixView class
 * 
 This contains the main implementation of a ComplexMatrix. It defines    
 the concepts of ComplexMatrixView. Plus additionally the recursive
 subrange operator, which makes it possible to create a ComplexMatrixView
 from a subrange of a ComplexMatrixView. 
 
 The class ComplexMatrix is just a special case of a ComplexMatrixView
 which also allocates storage. */
class ComplexMatrixView : public ConstComplexMatrixView {
 public:
  // Make const methods visible from base class
  using ConstComplexMatrixView::begin;
  using ConstComplexMatrixView::end;
  using ConstComplexMatrixView::operator();
  using ConstComplexMatrixView::get;
  using ConstComplexMatrixView::get_imag;
  using ConstComplexMatrixView::get_real;
  using ConstComplexMatrixView::imag;
  using ConstComplexMatrixView::real;
  using ConstComplexMatrixView::diagonal;

  constexpr ComplexMatrixView(const ComplexMatrixView&) = default;

  // Typedef for compatibility with STL
  using iterator = ComplexIterator2D;

#define GETFUN(r, c) \
  *(mdata + mrr.mstart + r * mrr.mstride + mcr.mstart + c * mcr.mstride)
  // Index Operators:
  /** Plain index operator. */
  Complex& operator()(Index r, Index c) {  // Check if indices are valid:
    ARTS_ASSERT(0 <= r);
    ARTS_ASSERT(0 <= c);
    ARTS_ASSERT(r < mrr.mextent);
    ARTS_ASSERT(c < mcr.mextent);

    return GETFUN(r, c);
  }

  /** Get element implementation without assertions. */
  Complex& get(Index r, Index c) { return GETFUN(r, c); }
#undef GETFUN

  /** Get element implementation without assertions. */
  Numeric& get_real(Index r, Index c) {
    return reinterpret_cast<ComplexLayout(&)>(get(r, c)).real;
  }

  /** Get element implementation without assertions. */
  Numeric& get_imag(Index r, Index c) {
    return reinterpret_cast<ComplexLayout(&)>(get(r, c)).imag;
  }
  
  /** Get a view of the real part of the matrix */
 [[nodiscard]] MatrixView real();

  /** Get a view of the imaginary parts of the matrix */
  [[nodiscard]] MatrixView imag();

  ComplexMatrixView operator()(const Range& r, const Range& c);
  ComplexVectorView operator()(const Range& r, Index c);
  ComplexVectorView operator()(Index r, const Range& c);

  // Functions returning iterators:
  ComplexIterator2D begin();
  ComplexIterator2D end();
  
  // View on diagonal complex vector
  ComplexVectorView diagonal();

  // Assignment operators:
  ComplexMatrixView& operator=(const ConstComplexMatrixView& v);
  ComplexMatrixView& operator=(const ComplexMatrixView& v);
  ComplexMatrixView& operator=(const ComplexMatrix& v);
  ComplexMatrixView& operator=(const ConstComplexVectorView& v);
  ComplexMatrixView& operator=(Complex x);

  // Other operators:
  ComplexMatrixView& operator*=(Complex x);
  ComplexMatrixView& operator/=(Complex x);
  ComplexMatrixView& operator+=(Complex x);
  ComplexMatrixView& operator-=(Complex x);
  ComplexMatrixView& operator*=(Numeric x);
  ComplexMatrixView& operator/=(Numeric x);
  ComplexMatrixView& operator+=(Numeric x);
  ComplexMatrixView& operator-=(Numeric x);

  ComplexMatrixView& operator*=(const ConstComplexMatrixView& x);
  ComplexMatrixView& operator/=(const ConstComplexMatrixView& x);
  ComplexMatrixView& operator+=(const ConstComplexMatrixView& x);
  ComplexMatrixView& operator-=(const ConstComplexMatrixView& x);

  ComplexMatrixView& operator*=(const ConstMatrixView& x);
  ComplexMatrixView& operator/=(const ConstMatrixView& x);
  ComplexMatrixView& operator+=(const ConstMatrixView& x);
  ComplexMatrixView& operator-=(const ConstMatrixView& x);

  ComplexMatrixView& operator*=(const ConstComplexVectorView& x);
  ComplexMatrixView& operator/=(const ConstComplexVectorView& x);
  ComplexMatrixView& operator+=(const ConstComplexVectorView& x);
  ComplexMatrixView& operator-=(const ConstComplexVectorView& x);

  //! Destructor
   ~ComplexMatrixView() override = default;

  // Friends:
  friend class ComplexVectorView;
  friend ConstComplexMatrixView transpose(ConstComplexMatrixView m);
  friend ComplexMatrixView transpose(ComplexMatrixView m);

 protected:
  // Constructors:
  ComplexMatrixView();
  ComplexMatrixView(Complex* data, const Range& r, const Range& c);
  ComplexMatrixView(Complex* data,
                    const Range& pr,
                    const Range& pc,
                    const Range& nr,
                    const Range& nc);
};

/** The ComplexMatrix class. This is a ComplexMatrixView that also allocates storage
 automatically, and deallocates it when it is destroyed. We take  *
 all the functionality from ComplexMatrixView. Additionally defined here
 are: 
 
 1. Constructors and destructor.
 2. Assignment operator from scalar.
 3. Resize function. */
class ComplexMatrix : public ComplexMatrixView {
 public:
  // Constructors:
  ComplexMatrix() = default;
  ComplexMatrix(Index r, Index c);
  ComplexMatrix(Index r, Index c, Complex fill);
  ComplexMatrix(Index r, Index c, Numeric fill);
  ComplexMatrix(const ConstComplexMatrixView& v);
  ComplexMatrix(const ComplexMatrix& v);

  /** Initialization from a vector type. */
  explicit ComplexMatrix(const matpack::matrix_like_not_matrix auto& init) : ComplexMatrix(matpack::row_size(init), matpack::column_size(init)) {
    for (Index i=0; i<nrows(); i++) for (Index j=0; j<ncols(); j++) operator()(i, j) = init(i, j);
  }

  // Assignment operators:
  ComplexMatrix& operator=(ComplexMatrix x);
  ComplexMatrix& operator=(Complex x);
  ComplexMatrix& operator=(const ConstComplexVectorView& v);

  /** Set from a matrix type. */
   ComplexMatrix& operator=(const matpack::matrix_like_not_matrix auto& init) {
    return *this = ComplexMatrix(init);
  }
  
  // Inverse in place
  ComplexMatrix& inv(const lapack_help::Inverse<Complex>& help=lapack_help::Inverse<Complex>{0});

  // Resize function:
  void resize(Index r, Index c);

  // Swap function:
  friend void swap(ComplexMatrix& m1, ComplexMatrix& m2) noexcept;

  // Destructor:
   ~ComplexMatrix() noexcept override;

  Complex* get_raw_data() { return mdata; }
};

// Function declarations:
// ----------------------

ConstComplexMatrixView transpose(ConstComplexMatrixView m);

ComplexMatrixView transpose(ComplexMatrixView m);

void copy(ConstComplexIterator1D origin,
          const ConstComplexIterator1D& end,
          ComplexIterator1D target);

void copy(Complex x, ComplexIterator1D target, const ComplexIterator1D& end);

void copy(ConstComplexIterator2D origin,
          const ConstComplexIterator2D& end,
          ComplexIterator2D target);

void copy(Complex x, ComplexIterator2D target, const ComplexIterator2D& end);

void mult(ComplexVectorView y,
          const ConstComplexMatrixView& M,
          const ConstComplexVectorView& x);

void mult(ComplexMatrixView A,
          const ConstComplexMatrixView& B,
          const ConstComplexMatrixView& C);
void mult(ComplexMatrixView A,
          const ConstMatrixView& B,
          const ConstComplexMatrixView& C);
void mult(ComplexMatrixView A,
          const ConstComplexMatrixView& B,
          const ConstMatrixView& C);
void mult(ComplexMatrixView A,
          const ConstMatrixView& B,
          const ConstMatrixView& C);

Complex operator*(const ConstComplexVectorView& a,
                  const ConstComplexVectorView& b);

using ArrayOfComplexVector = Array<ComplexVector>;
using ArrayOfComplexMatrix = Array<ComplexMatrix>;

#endif

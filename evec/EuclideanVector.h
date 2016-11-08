#ifndef EUCLIDEANVECTOR_H
#define EUCLIDEANVECTOR_H

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iterator>
#include <list>
#include <ostream>
#include <utility>
#include <vector>

namespace evec
{
   class EuclideanVector
   {
   public:
      // CONSTRUCTORS
      EuclideanVector(const int = 1, const double = 0.0);
      EuclideanVector(const int numD, const int m) : EuclideanVector(static_cast<unsigned int>(numD), static_cast<double>(m)) {}
      EuclideanVector(std::initializer_list<double> list);
      template<typename Iter> EuclideanVector(Iter start, Iter end)
         : num_dimensions_{static_cast<unsigned int>(std::distance(start, end))},
           magnitudes_{new double[num_dimensions_]()}
      {
         std::copy(start, end,  magnitudes_);
      }

      EuclideanVector(const EuclideanVector&);     // Copy constructor
      EuclideanVector(EuclideanVector&&);          // Move constructor

      // DESTRUCTOR
      ~EuclideanVector()
      {
         delete[] magnitudes_;
      }

      // MEMBER FUNCTIONS
      EuclideanVector& operator=(const EuclideanVector&);   // Copy assignment
      EuclideanVector& operator=(EuclideanVector&&);        // Move assignment

      unsigned int getNumDimensions() const { return num_dimensions_; }
      double get(unsigned int i) const { return magnitudes_[i]; }
      double getEuclideanNorm() const;
      EuclideanVector createUnitVector() const;
      double& operator[](unsigned int i) const { return magnitudes_[i]; };
      double& operator[](unsigned int);
      const EuclideanVector& operator+=(const EuclideanVector&);
      const EuclideanVector& operator-=(const EuclideanVector&);
      const EuclideanVector& operator*=(const double);
      const EuclideanVector& operator/=(const double);

      operator std::vector<double>() const;
      operator std::list<double>() const;

      // FRIENDS
      friend bool operator==(const EuclideanVector&, const EuclideanVector&);
      friend bool operator!=(const EuclideanVector& a, const EuclideanVector& b) { return !(a == b); }
      friend EuclideanVector operator+(const EuclideanVector&, const EuclideanVector&);
      friend EuclideanVector operator-(const EuclideanVector&, const EuclideanVector&);

      friend double operator*(const EuclideanVector&, const EuclideanVector&);
      friend EuclideanVector operator*(const EuclideanVector&, const double);
      friend EuclideanVector operator*(const double d, const EuclideanVector& e) { return operator*(e,d); };

      friend EuclideanVector operator/(const EuclideanVector&, const double);
      friend std::ostream& operator<<(std::ostream&, const EuclideanVector&);

      friend void swap(EuclideanVector& first, EuclideanVector& second);

   private:
      unsigned int num_dimensions_;       // Size of vector
      double* magnitudes_;                // Vector stored dynamically
      mutable double euclideanNorm_{-1};  // Cached value of eNorm, will be > 0 if it is cached

      void clearEuclideanNorm() const { euclideanNorm_ = -1; }
   };
};

#endif // EUCLIDEANVECTOR_H

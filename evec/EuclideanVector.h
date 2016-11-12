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
      EuclideanVector(const unsigned int = 1U, const double = 0.0);
      EuclideanVector(const int numD, const int m) : EuclideanVector(static_cast<unsigned int>(numD), static_cast<double>(m)) {}
      EuclideanVector(std::initializer_list<double> list);
      template<typename Iter> EuclideanVector(Iter start, Iter end)
         : num_dimensions_{static_cast<unsigned int>(std::distance(start, end))},
           magnitudes_{new double[num_dimensions_]()}
      {
         std::copy(start, end,  magnitudes_);
      }

      EuclideanVector(const EuclideanVector&);
      EuclideanVector(EuclideanVector&&);

      ~EuclideanVector()
      {
         delete[] magnitudes_;
      }

      // MEMBER FUNCTIONS
      EuclideanVector& operator=(const EuclideanVector&);
      EuclideanVector& operator=(EuclideanVector&&);

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
      bool operator==(const EuclideanVector&) const;
      bool operator!=(const EuclideanVector& o) const { return !(*this == o); }
      EuclideanVector operator+(const EuclideanVector&) const;
      EuclideanVector operator-(const EuclideanVector&) const;

      double operator*(const EuclideanVector&) const;
      EuclideanVector operator*(const double) const;
      friend EuclideanVector operator*(const double d, const EuclideanVector& e) { return e*d; };

      EuclideanVector operator/(const double) const;
      friend std::ostream& operator<<(std::ostream&, const EuclideanVector&);

      void swap(EuclideanVector&);

   private:
      unsigned int num_dimensions_;       // Size of vector
      double* magnitudes_;                // Vector stored dynamically
      mutable double euclideanNorm_{-1};  // Cached value of eNorm, will be > 0 if it is cached

      void clearEuclideanNorm() const { euclideanNorm_ = -1; }
   };
};

#endif // EUCLIDEANVECTOR_H

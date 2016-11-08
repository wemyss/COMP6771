#include "EuclideanVector.h"

namespace evec
{
    // CONSTRUCTORS
    EuclideanVector::EuclideanVector(const int numD, const double m)
        : num_dimensions_{static_cast<unsigned int>(numD)},
          magnitudes_{new double[num_dimensions_]}
    {
        for (auto i = 0U; i < num_dimensions_; ++i) {
            magnitudes_[i] = m;
        }
    }

    EuclideanVector::EuclideanVector(std::initializer_list<double> list)
        : num_dimensions_{static_cast<unsigned int>(list.size())},
          magnitudes_{new double[num_dimensions_]()}
    {
        auto i = 0U;
        for (const auto m : list) {
            magnitudes_[i++] = m;
        }
    }

    // Copy constructor
    EuclideanVector::EuclideanVector(const EuclideanVector& other)
        : num_dimensions_{other.num_dimensions_},
          magnitudes_{other.num_dimensions_ ? new double[other.num_dimensions_] : nullptr}
    {
        for (auto i = 0U; i < num_dimensions_; ++i) {
            magnitudes_[i] = other.magnitudes_[i];
        }
    }

    // Move constructor
    EuclideanVector::EuclideanVector(EuclideanVector&& other)
        : num_dimensions_{0},
          magnitudes_{nullptr}
    {
        swap(*this, other);
    }

    // MEMBER FUNCTIONS
    EuclideanVector& EuclideanVector::operator=(const EuclideanVector& other) {
        EuclideanVector tmp{other};
        swap(*this, tmp);
        return *this;
    }

    // Move assignment
    EuclideanVector& EuclideanVector::operator=(EuclideanVector&& other) {
        if (this != &other) {
            delete[] magnitudes_;

            magnitudes_ = other.magnitudes_;
            num_dimensions_ = other.num_dimensions_;
            euclideanNorm_ = other.euclideanNorm_;

            other.magnitudes_ = new double[0];
            other.num_dimensions_ = 0;
            clearEuclideanNorm();
        }
        return *this;
    }


    double EuclideanVector::getEuclideanNorm() const {
        if (euclideanNorm_ == -1) {
            auto sum = 0.0;
            for (auto i = 0U; i < num_dimensions_; ++i) {
                sum += std::pow(magnitudes_[i], 2);
            }
            euclideanNorm_ = std::sqrt(sum);
        }
        return euclideanNorm_;
    }

    EuclideanVector EuclideanVector::createUnitVector() const {
        return *this / getEuclideanNorm();
    }

    double& EuclideanVector::operator[](unsigned int i) {
        clearEuclideanNorm();
        return magnitudes_[i];
    }

    const EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& e) {
        clearEuclideanNorm();
        for (auto i = 0U; i < num_dimensions_; ++i) {
            magnitudes_[i] += e.magnitudes_[i];
        }
        return *this;
    }

    const EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& e) {
        clearEuclideanNorm();
        for (auto i = 0U; i < num_dimensions_; ++i) {
            magnitudes_[i] -= e.magnitudes_[i];
        }
        return *this;
    }

    const EuclideanVector& EuclideanVector::operator*=(const double scalar) {
        clearEuclideanNorm();
        for (auto i = 0U; i < num_dimensions_; ++i) {
            magnitudes_[i] *= scalar;
        }
        return *this;
    }

    const EuclideanVector& EuclideanVector::operator/=(const double scalar) {
        clearEuclideanNorm();
        for (auto i = 0U; i < num_dimensions_; ++i) {
            magnitudes_[i] /= scalar;
        }
        return *this;
    }

    EuclideanVector::operator std::vector<double>() const {
        auto mags = std::vector<double>{};
        for (auto i = 0U; i < num_dimensions_; ++i) {
            mags.push_back(magnitudes_[i]);
        }
        return mags;
    }

    EuclideanVector::operator std::list<double>() const {
        return {magnitudes_, magnitudes_ + num_dimensions_};
    }

    // FRIENDS
    bool operator==(const EuclideanVector& a, const EuclideanVector& b) {
        if (a.num_dimensions_ != b.num_dimensions_) {
            return false;
        }
        for (auto i = 0U; i < a.num_dimensions_; ++i) {
            if (a.magnitudes_[i] != b.magnitudes_[i]) {
                return false;
            }
        }
        return true;
    }

    EuclideanVector operator+(const EuclideanVector& a, const EuclideanVector& b) {
        EuclideanVector tmp{a};
        return tmp += b;
    }

    EuclideanVector operator-(const EuclideanVector& a, const EuclideanVector& b) {
        EuclideanVector tmp{a};
        return tmp -= b;
    }

    double operator*(const EuclideanVector& a, const EuclideanVector& b) {
        auto result = 0.0;

        for (auto i = 0U; i < a.num_dimensions_; ++i) {
            result += a.magnitudes_[i] * b.magnitudes_[i];
        }
        return result;
    }

    EuclideanVector operator*(const EuclideanVector& a, const double scalar) {
        EuclideanVector tmp{a};
        return tmp *= scalar;
    }

    EuclideanVector operator/(const EuclideanVector& a, const double scalar) {
        EuclideanVector tmp{a};
        return tmp /= scalar;
    }

    std::ostream& operator<<(std::ostream& o, const EuclideanVector& e) {
        o << '[';
        for (auto i = 0U; i < e.num_dimensions_; ++i) {
            if (i > 0) {
                o << ' ';
            }
            o << e.magnitudes_[i];
        }
        o << ']';
        return o;
    }

    void swap(EuclideanVector& first, EuclideanVector& second) {
     // Assuming we can use std::swap, else could use a temp;
     std::swap(first.num_dimensions_, second.num_dimensions_);
     std::swap(first.magnitudes_, second.magnitudes_);
     std::swap(first.euclideanNorm_, second.euclideanNorm_);
  }
}

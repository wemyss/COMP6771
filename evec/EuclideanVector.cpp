#include "EuclideanVector.h"

namespace evec
{
    // CONSTRUCTORS
    EuclideanVector::EuclideanVector(const unsigned int numD, const double m)
        : num_dimensions_{numD},
          magnitudes_{new double[num_dimensions_]}
    {
        std::fill(magnitudes_, magnitudes_ + num_dimensions_, m);
    }

    EuclideanVector::EuclideanVector(std::initializer_list<double> list)
        : EuclideanVector(list.begin(), list.end())
    {
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
        other.swap(*this);
    }

    // MEMBER FUNCTIONS
    EuclideanVector& EuclideanVector::operator=(const EuclideanVector& other) {
        EuclideanVector tmp{other};
        tmp.swap(*this);
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
    bool EuclideanVector::operator==(const EuclideanVector& other) const {
        if (num_dimensions_ != other.num_dimensions_) {
            return false;
        }
        for (auto i = 0U; i < num_dimensions_; ++i) {
            if (magnitudes_[i] != other.magnitudes_[i]) {
                return false;
            }
        }
        return true;
    }

    EuclideanVector EuclideanVector::operator+(const EuclideanVector& other) const {
        EuclideanVector tmp{*this};
        return tmp += other;
    }

    EuclideanVector EuclideanVector::operator-(const EuclideanVector& other) const {
        EuclideanVector tmp{*this};
        return tmp -= other;
    }

    double EuclideanVector::operator*(const EuclideanVector& other) const {
        auto result = 0.0;

        for (auto i = 0U; i < num_dimensions_; ++i) {
            result += magnitudes_[i] * other.magnitudes_[i];
        }
        return result;
    }

    EuclideanVector EuclideanVector::operator*(const double scalar) const {
        EuclideanVector tmp{*this};
        return tmp *= scalar;
    }

    EuclideanVector EuclideanVector::operator/(const double scalar) const {
        EuclideanVector tmp{*this};
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

    void EuclideanVector::swap(EuclideanVector& other) {
     using std::swap;
     swap(num_dimensions_, other.num_dimensions_);
     swap(magnitudes_, other.magnitudes_);
     swap(euclideanNorm_, other.euclideanNorm_);
  }
}

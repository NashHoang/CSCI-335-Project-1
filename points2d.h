// --> YOUR NAME here
// Few comments describing the class Points2D

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <sstream>
// ADDING A NEW COMMENT
namespace teaching_project {

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2D {
  public:
    // Default "big five" -- you have to alter them for your assignment.
    // That means that you will remove the "= default" statement.
    //  and you will provide an implementation.

    // Zero-parameter constructor.
    // Set size to 0.
    Points2D() {
        sequence_ = nullptr;
        size_ = 0;
    }

    // Copy-constructor.
    Points2D(const Points2D &rhs) {
        size_ = rhs.size_;
        if (size_ == 0){
            sequence_ = nullptr;
        }
        else{
            sequence_ = new std::array<Object,2>[size_];
            for (size_t i = 0; i<size_; ++i){
                sequence_[i] = rhs.sequence_[i];
            }
        }
    }

    // Copy-assignment. If you have already written
    // the copy-constructor and the move-constructor
    // you can just use:
    // {
    // Points2D copy = rhs;
    // std::swap(*this, copy);
    // return *this;
    // }
    Points2D& operator=(const Points2D &rhs) {

        if (this != &rhs) {

            delete[] sequence_;

            size_ = rhs.size_;

            if (size_ == 0) {
                sequence_ = nullptr;
            } else {
                sequence_ = new std::array<Object,2>[size_];
                for (size_t i = 0; i < size_; ++i)
                    sequence_[i] = rhs.sequence_[i];
            }
        }

        return *this;
    }

    // Move-constructor.
    Points2D(Points2D &&rhs) {
        sequence_ = rhs.sequence_;
        size_ = rhs.size_;
        rhs.sequence_ = nullptr;
        rhs.size_ = 0;
    }

    // Move-assignment.
    // Just use std::swap() for all variables.
    Points2D& operator=(Points2D &&rhs) {

        if (this != &rhs) {

            delete[] sequence_;

            sequence_ = rhs.sequence_;
            size_ = rhs.size_;

            rhs.sequence_ = nullptr;
            rhs.size_ = 0;
        }

        return *this;
    }

    ~Points2D() {
        delete[] sequence_;
    }

    // End of big-five.

    // One parameter constructor.
    Points2D(const std::array<Object, 2>& item) {
        size_ = 1;
        sequence_ = new std::array<Object,2>[1];
        sequence_[0] = item;
    }

    size_t size() const {
        return size_;
    }

    // @location: an index to a location in the sequence.
    // @returns the point at @location.
    // const version.
    // abort() if out-of-range.
    const std::array<Object, 2>& operator[](size_t location) const {
        if (location >= size_){
            std::cerr << "Index out of bounds" << std::endl;
            abort();
        }
        return sequence_[location];
    }

    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //    result with the remaining part of the larger sequence.
    friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
        Points2D result;

        size_t min_size = std::min(c1.size_, c2.size_);
        size_t max_size = std::max(c1.size_, c2.size_);

        result.size_ = max_size;
        result.sequence_ = new std::array<Object,2>[max_size];

        size_t i = 0;
        for (; i < min_size; ++i) {

            result.sequence_[i][0] =
                c1.sequence_[i][0] + c2.sequence_[i][0];

            result.sequence_[i][1] =
                c1.sequence_[i][1] + c2.sequence_[i][1];
        }

        if (c1.size_ > c2.size_) {

            for (; i < max_size; ++i) result.sequence_[i] = c1.sequence_[i];
        }
        else {

            for (; i < max_size; ++i) result.sequence_[i] = c2.sequence_[i];
        }

        return result;
    }

    // Overloading the << operator.
    friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) {
        for (size_t i = 0; i < some_points.size_; ++i){
            out << "("
                << some_points.sequence_[i][0]
                << ", "
                << some_points.sequence_[i][1]
                << ")";

            if (i < some_points.size_ - 1)
            {
                out << " ";
            }
        }

        out << std::endl;
        return out;
    }

    // Overloading the >> operator.
    // Read a chain from an input stream (e.g., standard input).
    friend std::istream &operator>>(std::istream &in, Points2D &some_points) {
        size_t n;
        in >> n;
        some_points.size_ = n;

        delete[] some_points.sequence_;
        some_points.sequence_ = new std::array<Object, 2>[some_points.size_];

        for (size_t i = 0; i < some_points.size_; ++i){
            if (!(in >> some_points.sequence_[i][0] >> some_points.sequence_[i][1]))
            {
                some_points.sequence_[i][0] = Object{};
                some_points.sequence_[i][1] = Object{};
            }
        }

        return in;
    }

  private:
    // Sequence of points.
    std::array<Object, 2> *sequence_;
    // Size of sequence.
    size_t size_;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_

#pragma once
#include <iostream>

class Rational {
private:
    int numerator;    ///< Numerator of the rational number
    int denominator;  ///< Denominator of the rational number

public:
    // Constructors
    Rational() : numerator(0), denominator(1) {}
    Rational(int num) : numerator(num), denominator(1) {}
    Rational(int num, int denom) : numerator(num), denominator(denom) {
        normalize();
    }

    // Define operator<< for output
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);

    // Define operator>> for input
    friend std::istream& operator>>(std::istream& is, Rational& r);

    // Copy constructor
    Rational(const Rational& other) : numerator(other.numerator), denominator(other.denominator) {}

    // Getter methods
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    // Arithmetic operations
    Rational operator+(const Rational& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Rational(num, denom);
    }

    Rational operator-(const Rational& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Rational(num, denom);
    }

    Rational operator*(const Rational& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Rational(num, denom);
    }

    Rational operator/(const Rational& other) const {
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        return Rational(num, denom);
    }

    // Comparison operators
    bool operator==(const Rational& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator!=(const Rational& other) const {
        return !(*this == other);
    }

    bool operator<(const Rational& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    bool operator>(const Rational& other) const {
        return numerator * other.denominator > other.numerator * denominator;
    }

    bool operator<=(const Rational& other) const {
        return !(*this > other);
    }

    bool operator>=(const Rational& other) const {
        return !(*this < other);
    }

    // Normalize the rational number
    void normalize() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        int gcdVal = gcd(abs(numerator), abs(denominator));
        numerator /= gcdVal;
        denominator /= gcdVal;
    }

    /**
     * @brief Method to compute the greatest common divisor (GCD) of two integers.
     * @param a First integer.
     * @param b Second integer.
     * @return GCD of integers a and b.
     */
    int gcd(int a, int b) const {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    /**
     * @brief Static method to create a Rational number from an integer.
     * @param num Integer value to convert to a Rational.
     * @return Rational equivalent of the integer.
     */
    static Rational fromInt(int num) {
        return Rational(num, 1);
    }

    /**
     * @brief Static method to get a representation of infinity as a Rational number.
     * @return Infinity represented as a Rational number.
     */
    static Rational infinity() {
        return Rational(INT_MAX, 1); // INT_MAX is used as a large number for infinity
    }
};

// Define operator<< for output
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r.numerator;
    if (r.denominator != 1) {
        os << "/" << r.denominator;
    }
    return os;
}

// Define operator>> for input
std::istream& operator>>(std::istream& is, Rational& r) {
    char slash;
    is >> r.numerator >> slash >> r.denominator;
    if (r.denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    return is;
}

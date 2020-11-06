//
// Created by Zack on 2020/10/29.
//
#ifndef TEST7_2_COMPLEX_H
#define TEST7_2_COMPLEX_H
#include <iostream>
class Complex {
    double m_real;
    double m_imag;
public:
    Complex() = default;
    Complex(double real, double imag) :m_real(real), m_imag(imag) {}
    double real() { return m_real; }
    double imag() { return m_imag; }
    void set(double, double);
    Complex& operator = (const Complex& c);
    bool operator == (const Complex& c) { return m_real == c.m_real && m_imag == c.m_imag; }
    bool operator<(const Complex& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Complex& rhs);

};
void Complex::set(double real, double imag) {
    m_real = real;
    m_imag = imag;
}
inline bool Complex::operator<(const Complex& rhs) {
    return (m_real * m_real) + (m_imag * m_imag) > (rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag);
}

std::ostream& operator<<(std::ostream& os, const Complex& rhs) {
    if (rhs.m_imag > 0) { os << rhs.m_real << "+" << rhs.m_imag << "i"; }
    else { os << rhs.m_imag << rhs.m_imag << "i"; }
    return os;
}
Complex& Complex::operator = (const Complex& c) {
    m_real = c.m_real;
    m_imag = c.m_imag;
    return *this;
}

#endif
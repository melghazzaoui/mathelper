//
// Created by Makram.Elghazzaoui on 20/04/2023.
//

#ifndef TEST_NUMBERROUNDER_H
#define TEST_NUMBERROUNDER_H

#include <string>
#include <ostream>
#include <sstream>
#include <memory>

#define ZERO_EPSILON 0.001

class MathNumber {
protected:
    long double value;
public:
    MathNumber(long double value) : value(value) {};
    virtual ~MathNumber() {};
    virtual std::string toString() const {
        return "";
    };
    friend std::ostream& operator << (std::ostream& os, const MathNumber& nbr) {
        return os << nbr.toString();
    }
};

class BasicNumber : public MathNumber {
public:
    BasicNumber(long double value) : MathNumber(value) {};
    virtual ~BasicNumber() {};
    long double getValue() const { return value; };
    virtual std::string toString () const {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
};

/* a/b */
class Quotient {
private:
    long a;
    long b;
public:
    Quotient(long a, long b) : a(a), b(b) {};
    virtual ~Quotient() {};
    long getA() const { return a; };
    long getB() const { return b; };
    std::string toString() const {
        std::ostringstream oss;
        if (b != 1) {
            oss << a << "/" << b;
        }
        else {
            oss << a;
        }
        return oss.str();
    }
    friend std::ostream& operator << (std::ostream& os, const Quotient& q) {
        return os << q.toString();
    }
};

class TrigoNumber : public MathNumber {
private:
    Quotient quotient;
public:
    TrigoNumber(long double value, long a, long b) : MathNumber(value), quotient(a,b) {};
    virtual ~TrigoNumber() {};
    const Quotient& getQuotient() const { return quotient; };

    virtual std::string toString () const {
        std::ostringstream oss;
        if (quotient.getA() != quotient.getB())
            oss << quotient << " ";
        oss << "PI";
        return oss.str();
    };
};

class NumberRounder {
private:
    long double x;
    std::shared_ptr<MathNumber> result;
public:
    NumberRounder(long double x) : x(x) {};
    virtual ~NumberRounder() {
    }
    bool round(long double x, long double& xint) const;
    void round();
    std::string toString() const {
        if (result) {
            return result->toString();
        }
        return "";
    }

    friend std::ostream& operator << (std::ostream& os, const NumberRounder& nr) {
        return os << nr.toString();
    }

};


#endif //TEST_NUMBERROUNDER_H

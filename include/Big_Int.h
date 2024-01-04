//
// Created by HORIA on 25.11.2023.
//

#ifndef DATA_STRUCTURES_BIG_INT_H
#define DATA_STRUCTURES_BIG_INT_H
#include <vector>
#include <string>
#include <ostream>

/*
class Big_Int {
public:
    using TD = char;
    Big_Int(const std::string& s, bool neg=false) {
        for (int i {static_cast<int>(s.size())-1}; i >= 0; --i) {
            m_big_num.push_back(s[i]);
        }
        m_neg = neg;
        //remove_leading_zero();
    }
    Big_Int(const std::vector<TD>& num, bool neg=false) : m_neg{neg} {
        int j {};
        int i {static_cast<int>(num.size())-1};
        //skip the leading zeros
        while (num.size()>1 && num[i] == '0') {
            --i;
        }
        while (j <= i) {
            m_big_num.push_back(num[j++]);
        }
    }
    Big_Int operator+(const Big_Int& rhs) {
        std::vector<TD> res {};
        int carry {0};
        int i {};
        int j {};
        bool neg {false};
        while (carry || i < m_big_num.size() || j < rhs.m_big_num.size()) {
            int a {}, b {};
            if (i < m_big_num.size())
                a = {m_big_num[i++] - '0'};
            if (j < rhs.m_big_num.size())
                b = {rhs.m_big_num[j++] - '0'};
            int temp {a + b};
            if (carry) {
                ++temp;
                --carry;
            }
            if (temp > 9) {
                res.push_back((temp%10+'0'));
                ++carry;
            } else {
                res.push_back((temp + '0'));
            }
        }
        return {res, neg};
    }

    Big_Int operator-(const Big_Int& rhs) {
        std::vector<TD> res {};
        int borrowed {0};
        int i {};
        int j {};
        bool neg {*this < rhs};
        while (borrowed || i < m_big_num.size() || j < rhs.m_big_num.size()) {
            int a{}, b{};
            if (i < m_big_num.size())
                a = {m_big_num[i++] - '0'};
            if (j < rhs.m_big_num.size())
                b = {rhs.m_big_num[j++] - '0'};
            int temp {};
            if (!neg) {
                temp = a - b;
            } else {
                temp = b - a;
            }
            if (borrowed) {
                --temp;
                --borrowed;
            }
            if (temp < 0) {
                res.push_back((temp + 10 + '0'));
                ++borrowed;
            } else {
                res.push_back(temp + '0');
            }
        }
        while (i < m_big_num.size()) {
            res.push_back(m_big_num[i++]);
        }
        while (j < rhs.m_big_num.size()) {
            res.push_back(rhs.m_big_num[j++]);
        }
        return {res, neg};
    }

    bool operator<(const Big_Int& rhs) {
        if (this == &rhs) {
            return false;
        }
        if (m_big_num.size() < rhs.m_big_num.size()) {
            return true;
        }
        if (m_big_num.size() > rhs.m_big_num.size()) {
            return false;
        }
        int i {static_cast<int>(m_big_num.size())-1}, j {static_cast<int>(rhs.m_big_num.size())-1};
        while (i >= 0 && j >= 0) {
            if (m_big_num[i++] < rhs.m_big_num[j++]) {
                return true;
            }
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& out, const Big_Int& num) {
        if (num.m_neg) {
            out << '-';
        }
        for (int i {static_cast<int>(num.m_big_num.size())-1}; i >=0; --i) {
            out << num.m_big_num[i];
        }
        return out;
    }

private:
    std::vector<TD> m_big_num {};
    bool m_neg {false};
    void remove_leading_zero() {
        if (m_big_num.size() > 1) {
            if (m_big_num[m_big_num.size()-1] == 0) {
                m_big_num.pop_back();
            }
        }
    }
};
 */

class Big_Int {
public:
    //constructors
    Big_Int(const std::string& s) {
        m_digits.resize(s.length());
        unsigned long long i {}, j {s.length()-1};
        while (j != ULLONG_MAX) {
            if (!std::isdigit(s[i])) {
                throw("ERROR IT IS NOT A DIGIT: BIG INT CONSTRUCTOR!\n");
            } else
                m_digits[i++] = s[j--];
        }
    }
    Big_Int(unsigned long long n) {
        do {
            m_digits.push_back(n%10 + '0');
            n/=10;
        } while (n);
    }
    //operations
    Big_Int& operator+=(const Big_Int& rhs) {
        if(m_digits.length() < rhs.m_digits.length())
            m_digits.append(rhs.m_digits.length() - m_digits.length(), '0');
        int carry = 0;
        for (int i = 0; i < m_digits.length();i++){
            int s;
            if(i < rhs.m_digits.length())
                s = m_digits[i] - '0' + rhs.m_digits[i] - '0' + carry;
            else
                s = m_digits[i] - '0' + carry;
            carry = s / 10;
            m_digits[i] = (s % 10) + '0';
        }
        if(carry)
            m_digits.push_back(carry + '0');
        return *this;
    }

    Big_Int& operator-=(Big_Int& rhs) {
        if (*this < rhs) {
            m_neg = true;
        }
        int carry {};
        for (int i = 0; i < m_digits.length(); ++i) {
            int s;
            if (i < rhs.m_digits.length()) {
                s = (m_digits[i] - '0') - (rhs.m_digits[i] - '0') + carry;
            } else {
                s = (m_digits[i] - '0') + carry;
            } if (s < 0) {
                s += 10;
                --carry;
            } else {
                carry = 0;
            }
            m_digits[i] = (s + '0');
        }
        //remove_leading_zeroes();
        return *this;
    }

    bool operator<(const Big_Int& rhs) {
        if (m_digits.length() != rhs.m_digits.length()) {
            return m_digits.length() < rhs.m_digits.length();
        }
        for (int i = m_digits.length()-1; i >=0; --i) {
            if (m_digits[i] != rhs.m_digits[i]) {
                return m_digits[i] < rhs.m_digits[i];
            }
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& out, const Big_Int& rhs) {
        for (int i = rhs.m_digits.length(); i >= 0; --i) {
            std::cout << rhs.m_digits[i];
        }
        return out;
    }

private:
    std::string m_digits {};
    bool m_neg {false};

    void remove_leading_zeroes() {
        for (int i = m_digits.length()-1; i >=1 ; --i) {
            if (m_digits[i]-'0') {
                break;
            }
            m_digits.pop_back();
        }
    }
};
#endif //DATA_STRUCTURES_BIG_INT_H

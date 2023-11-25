//
// Created by HORIA on 25.11.2023.
//

#ifndef DATA_STRUCTURES_BIG_INT_H
#define DATA_STRUCTURES_BIG_INT_H
#include <vector>
#include <string>
#include <ostream>


class Big_Int {
public:
    Big_Int(const std::string& s) {
        for (int i {static_cast<int>(s.size())-1}; i >= 0; --i) {
            m_big_num.push_back(s[i]);
        }
    }
    Big_Int operator+(const Big_Int& rhs) {
        std::string res {};
        int carry {0};
        int i {};
        int j {};
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
        return {res};
    }

    

    friend std::ostream& operator<<(std::ostream& out, const Big_Int& num) {
        for (auto item : num.m_big_num) {
            out << item;
        }
        return out;
    }

private:
    using TD = char;
    std::vector<TD> m_big_num {};
};

#endif //DATA_STRUCTURES_BIG_INT_H

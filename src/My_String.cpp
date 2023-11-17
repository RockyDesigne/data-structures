//
// Created by HORIA on 16.11.2023.
//
#include "My_String.h"
#include <cstring>
#include <stdexcept>
#include <algorithm>

//constructors
String::String(const char *str) {
    if (!str)
        return;
    int len {static_cast<int>(std::strlen(str))};

    set_capacity((len+1) * 2);
    set_str(str);
    set_size(len);
}

//copy constructor
String::String(const String& str) {
    set_capacity(str.m_capacity);
    set_size(str.m_size);
    set_str(str.m_str);
}

//destructor
String::~String() {
    delete []m_str;
}

//operations
std::ostream& operator<<(std::ostream& out, const String& str) {
    for (int i = 0; i < str.m_size; ++i) {
        out << str.m_str[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, String& str) {
    char c {};
    in.get(c);
    while (!std::isspace(c)) {
        str.push_back(c);
        in.get(c);
    }
    return in;
}

String& String::operator=(const String &str) {
    if (this == &str) {
        throw std::exception();
    }

    set_capacity(str.m_capacity);
    set_size(str.m_size);
    set_str(str.m_str);

    return *this;
}

char& String::operator[](String::uint index) {
    if (index > m_size - 1 || m_size == 0) {
        throw std::exception();
    }
    return m_str[index];
}

String& String::operator+=(const String &str) {
    if (m_capacity < m_size + str.m_size + 1) {
        resize((m_size + str.m_size + 1) * 2);
    }
    for (int i {0}; i < str.m_size; ++i) {
        m_str[m_size++] = str.m_str[i];
    }
    return *this;
}

String& String::operator+=(const char* str) {
    String::uint len {std::strlen(str)};
    if (m_capacity < m_size + len + 1) {
        resize((m_size + len + 1) * 2);
    }
    for (int i {0}; i < len; ++i) {
        m_str[m_size++] = str[i];
    }

    return *this;
}

String String::operator+(const char* str) {
    String::uint len {std::strlen(str)};
    char s[len + m_size + 1];
    String::uint i {}, j {}, k {};
    while (i < len + m_size && j < m_size) {
        s[i++] = m_str[j++];
    }
    while (i < len + m_size && k < len) {
        s[i++] = str[k++];
    }

    return String {s};
}

String String::operator+(const String &str) {
    char s[m_size + str.m_size + 1];
    String::uint i {}, j {}, k {};
    while (i < m_size + str.m_size && j < m_size) {
        s[i++] = m_str[j++];
    }
    while (i < m_size + str.m_size && k < str.m_size) {
        s[i++] = str.m_str[k++];
    }
    return String {s};
}

/*
 * Compares two string objects lexicographically
 * Complexity: O(n logn)
 * @return bool true if equal
 */
bool String::operator==(const String& str) {
    if (!m_str && str.m_str || !str.m_str && m_str) {
        return false;
    }
    if (!m_str && !str.m_str) {
        return true;
    }
    char s1[m_size];
    char s2[str.m_size];
    std::strcpy(s1, m_str);
    std::strcpy(s2, str.m_str);
    std::sort(s1, s1+m_size);
    std::sort(s2, s2+str.m_size);
    return !(std::strcmp(s1, s2));
}

/*
 * Compares two string objects lexicographically
 * Complexity: O(n logn)
 * @return bool true if not equal
 */
bool String::operator!=(const String& str) {
    if (!m_str && str.m_str || !str.m_str && m_str) {
        return true;
    }
    if (!m_str && !str.m_str) {
        return false;
    }
    char s1[m_size];
    char s2[str.m_size];
    std::strcpy(s1, m_str);
    std::strcpy(s2, str.m_str);
    std::sort(s1, s1+m_size);
    std::sort(s2, s2+str.m_size);
    return (std::strcmp(s1, s2));
}

/*
 * Compares two string objects lexicographically
 * Complexity: O(n logn)
 * @return bool true if rhs is bigger than lhs
 */
bool String::operator<(const String& str) {
    if (!m_str && !str.m_str) {
        return false;
    }
    if (!m_str && str.m_str) {
        return true;
    }
    if (m_str && !str.m_str) {
        return false;
    }
    char s1[m_size];
    char s2[str.m_size];
    std::strcpy(s1, m_str);
    std::strcpy(s2, str.m_str);
    std::sort(s1, s1+m_size);
    std::sort(s2, s2+str.m_size);
    return (std::strcmp(s1, s2) < 0);
}

/*
 * Compares two string objects lexicographically
 * Complexity: O(n logn)
 * @return bool true if rhs is >= than lhs
 */
bool String::operator<=(const String& str) {
    if (!m_str && !str.m_str) {
        return false;
    }
    if (!m_str && str.m_str) {
        return true;
    }
    if (m_str && !str.m_str) {
        return false;
    }
    char s1[m_size];
    char s2[str.m_size];
    std::strcpy(s1, m_str);
    std::strcpy(s2, str.m_str);
    std::sort(s1, s1+m_size);
    std::sort(s2, s2+str.m_size);
    return (std::strcmp(s1, s2) <= 0);
}

/*
 * Compares two string objects lexicographically
 * Complexity: O(n logn)
 * @return bool true if lhs is bigger than rhs
 */
bool String::operator>(const String& str) {
    if (!m_str && !str.m_str) {
        return false;
    }
    if (!m_str && str.m_str) {
        return false;
    }
    if (m_str && !str.m_str) {
        return true;
    }
    char s1[m_size];
    char s2[str.m_size];
    std::strcpy(s1, m_str);
    std::strcpy(s2, str.m_str);
    std::sort(s1, s1+m_size);
    std::sort(s2, s2+str.m_size);
    return (std::strcmp(s1, s2) > 0);
}

/*
 * Compares two string objects lexicographically
 * Complexity: O(n logn)
 * @return bool true if lhs is >= than rhs
 */
bool String::operator>=(const String& str) {
    if (!m_str && !str.m_str) {
        return false;
    }
    if (!m_str && str.m_str) {
        return false;
    }
    if (m_str && !str.m_str) {
        return true;
    }
    char s1[m_size];
    char s2[str.m_size];
    std::strcpy(s1, m_str);
    std::strcpy(s2, str.m_str);
    std::sort(s1, s1+m_size);
    std::sort(s2, s2+str.m_size);
    return (std::strcmp(s1, s2) >= 0);
}

//public methods
void String::resize(String::uint cap) {
    set_capacity(cap);
    char str[cap];
    if (m_str) {
        std::strcpy(str, m_str);
    }
    set_str(str);
}

void String::push_back(char c) {
    if (!m_capacity || m_size == m_capacity-1) {
        if (!m_capacity)
            ++m_capacity;
        resize(m_capacity * 2);
    }
    m_str[m_size++] = c;
}

void String::pop_back() {
    if (m_size == 0) {
        throw std::exception();
    }
    --m_size;
}

/*
 * Complexity: O(n)
 * @returns the position of the first occurrence of the searched for element
 * @returns -1 otherwise
 */
int String::find(char c) {
    int i {};
    while (i < m_size) {
        if (m_str[i] == c) {
            return i;
        }
        ++i;
    }
    return -1;
}
/*
 * Complexity O(len(s))
 * @returns *this
 */
String& String::replace(String::uint pos, const char *s) {
    if (!s) {
        return *this;
    }
    uint i {pos}, j {}, len {std::strlen(s)};

    while (i < m_size && j < len) {
        m_str[i++] = s[j++];
    }
    return *this;
}

String::uint String::length() const {
    return m_size;
}

void String::clear() {
    m_size = 0;
}

bool String::empty() const {
    return (!m_size);
}

String::uint String::capacity() const {
    return m_capacity;
}

String::iterator String::begin() {
    return m_str;
}

String::iterator String::end() {
    return m_str + m_size;
}

//private methods
void String::set_str(const char* str) {
    if (!str) {
        return;
    }
    delete []m_str;
    m_str = new char[m_capacity-1];
    m_str[m_capacity] = '\0';
    std::strcpy(m_str, str);
}

void String::set_size(String::uint size) {
    m_size = size;
}

void String::set_capacity(String::uint cap) {
    if (cap < m_size) {
        throw std::exception();
    }
    m_capacity = cap;
}

//
// Created by HORIA on 16.11.2023.
//
#include "My_String.h"
#include <cstring>
#include <ostream>
#include <stdexcept>

//constructors
String::String(const char *str) {
    if (!str)
        return;
    int len {static_cast<int>(std::strlen(str))};

    set_capacity((len+1) * 2);
    set_str(str);
    set_size(len);
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
    if (m_size == m_capacity) {
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

String::uint String::length() const {
    return m_size;
}

//private methods
void String::set_str(const char* str) {
    if (!str) {
        return;
    }
    delete []m_str;
    m_str = new char[m_capacity];
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

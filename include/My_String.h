//
// Created by HORIA on 16.11.2023.
//

#ifndef DATA_STRUCTURES_MY_STRING_H
#define DATA_STRUCTURES_MY_STRING_H
#include <ostream>
#include <istream>

class String {
public:
    using uint = unsigned long long;

    explicit String(const char* str=nullptr);
    String(const String& str);
    ~String();

    //operations
    friend std::ostream& operator<<(std::ostream& out, const String& str);
    friend std::istream& operator>>(std::istream& in, String& str);
    String& operator=(const String& str);
    char& operator[](uint index);
    String& operator+=(const String& str);
    String& operator+=(const char* str);
    String operator+(const char* str);
    String operator+(const String& str);

    //methods
    void push_back(char c);
    void pop_back();
    void resize(uint cap);
    void clear();
    //getters
    [[nodiscard]] uint length() const;
    bool empty() const;
    uint capacity() const;

private:
    char* m_str {};
    uint m_size {};
    uint m_capacity {};

    //private methods
    void set_str(const char* str);
    void set_size(uint size);
    void set_capacity(uint cap);
};

#endif //DATA_STRUCTURES_MY_STRING_H

//
// Created by HORIA on 16.11.2023.
//

#ifndef DATA_STRUCTURES_MY_STRING_H
#define DATA_STRUCTURES_MY_STRING_H
#include <ostream>

class String {
public:
    using uint = unsigned long long;

    explicit String(const char* str=nullptr);
    ~String();

    //operations
    friend std::ostream& operator<<(std::ostream& out, const String& str);
    String& operator=(const String& str);
    char& operator[](uint index);

    //methods
    void push_back(char c);
    void pop_back();
    void resize(uint cap);
    [[nodiscard]] uint length() const;

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

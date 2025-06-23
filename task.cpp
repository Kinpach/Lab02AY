#include "string.hpp"
#include <cstring>
#include <algorithm>

String::~String() {
    delete[] Data;
}

String::String() : Data(new char[1]) {
    Data[0] = '\0';
}

String::String(const String& rhs) : Data(new char[rhs.Size() + 1]) {
    strcpy(Data, rhs.Data);
}

String::String(const char* data) {
    if (data) {
        Data = new char[strlen(data) + 1];
        strcpy(Data, data);
    } else {
        Data = new char[1];
        Data[0] = '\0';
    }
}

String& String::operator=(const String& rhs) {
    if (this != &rhs) {
        String tmp(rhs);
        swap(tmp);
    }
    return *this;
}

String& String::operator+=(const String& rhs) {
    char* newData = new char[Size() + rhs.Size() + 1];
    strcpy(newData, Data);
    strcat(newData, rhs.Data);
    delete[] Data;
    Data = newData;
    return *this;
}

String& String::operator*=(unsigned int m) {
    if (m == 0) {
        delete[] Data;
        Data = new char[1];
        Data[0] = '\0';
        return *this;
    }
    
    size_t len = Size();
    char* newData = new char[len * m + 1];
    newData[0] = '\0';
    
    for (unsigned int i = 0; i < m; ++i) {
        strcat(newData, Data);
    }
    
    delete[] Data;
    Data = newData;
    return *this;
}

bool String::operator==(const String& rhs) const {
    return strcmp(Data, rhs.Data) == 0;
}

bool String::operator<(const String& rhs) const {
    return strcmp(Data, rhs.Data) < 0;
}

size_t String::Find(const String& substr) const {
    const char* pos = strstr(Data, substr.Data);
    return pos ? pos - Data : -1;
}

void String::Replace(char oldSymbol, char newSymbol) {
    for (size_t i = 0; i < Size(); ++i) {
        if (Data[i] == oldSymbol) {
            Data[i] = newSymbol;
        }
    }
}

size_t String::Size() const {
    return strlen(Data);
}

bool String::Empty() const {
    return Size() == 0;
}

char String::operator[](size_t index) const {
    return Data[index];
}

char& String::operator[](size_t index) {
    return Data[index];
}

void String::RTrim(char symbol) {
    size_t len = Size();
    while (len > 0 && Data[len - 1] == symbol) {
        Data[--len] = '\0';
    }
}

void String::LTrim(char symbol) {
    size_t count = 0;
    while (Data[count] == symbol) {
        count++;
    }
    
    if (count > 0) {
        size_t newSize = Size() - count;
        for (size_t i = 0; i <= newSize; ++i) {
            Data[i] = Data[i + count];
        }
    }
}

void String::swap(String& oth) {
    std::swap(Data, oth.Data);
}

String operator+(const String& a, const String& b) {
    String result(a);
    result += b;
    return result;
}

String operator*(const String& a, unsigned int b) {
    String result;
    for (unsigned int i = 0; i < b; ++i) {
        result += a;
    }
    return result;
}

bool operator!=(const String& a, const String& b) {
    return !(a == b);
}

bool operator>(const String& a, const String& b) {
    return b < a;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
    return out << str.Data;
}

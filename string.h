#pragma once
#include <iostream>
#include <cstring>

class String {

private:
  char* string;
  size_t size;
  size_t capacity;

  void change_capacity(size_t new_capacity) {
    capacity = new_capacity;
    char* new_string =  new char [capacity];
    memcpy(new_string, string, size);
    delete [] string;
    string = new_string;
  }

  void check_capacity(size_t new_size) {
    if (new_size >= capacity) {
      change_capacity(new_size * 2);
    }
  }

public:

  String(const char other) {
    size = 1;
    capacity = 10;
    string = new char [capacity];
    string[0] = other;
  }

  String(const char* cstyle_sting) {
    size = strlen(cstyle_sting);
    capacity = size * 2 + 1;
    string = new char [capacity];
    memcpy(string, cstyle_sting, size);
  }

  String(const size_t n, const char other) {
    capacity = n * 2 + 1;
    size = n;
    string = new char [capacity];
    memset(string, other, size);
  }

  String() {
    size = 0;
    capacity = 10;
    string = new char [capacity];
  }

  String(const String& s) {
    size = s.size;
    capacity = s.capacity;
    string = new char [capacity];
    memcpy(string, s.string, s.size);
  }

  void pop_back() {--size;}

  char&       front()       {return string[0];}
  const char& front() const {return string[0];}

  char&       back()       {return string[size - 1];}
  const char& back() const {return string[size - 1];}

  char&       operator[](const size_t index)       {return string[index];}
  const char& operator[](const size_t index) const {return string[index];}

  bool empty() {return !size? true: false;}

  void clear() {size = 0;}

  size_t length() const {return size;}
 
  size_t find(const String& substring) const {
    for (size_t i = 0; i < size; ++i) {
      bool result = true;
      for (size_t j = 0; j < substring.size; ++j) {
        if (i + j >= size || string[i + j] != substring.string[j]) result = false;
      }
      if (result == true) return i; 
    }
    return size;
  }

  size_t rfind(const String& substring) const {
    for (size_t i = size; i != 0; --i) {
      bool result = true;
      for (size_t j = 0; j < substring.size; ++j) {
        if (i + j - 1  >= size || string[i - 1 + j] != substring.string[j]) result = false;
      }
      if (result == true) return i - 1; 
    }
    return size; 
  }

  String substr(const size_t start, const size_t count) const {
    String substring;
    substring.change_capacity(count * 2);
    substring.size = count;
    memcpy(substring.string, string + start, count);
    return substring;
  }

  String& swap(String& s) {
    std::swap(string, s.string);
    std::swap(size, s.size);
    std::swap(capacity, s.capacity);
    return *this;
  }

  String& operator=(const String& s) {
    String temp = s;
    swap(temp); 
    return *this;
  }
 
  String& operator+=(const String& s) {
    String temp = s;
    check_capacity(size + temp.size + 1);
    memcpy(string + size, temp.string, temp.size);
    size += temp.size;
    return *this;
  }

  String& operator+=(const char other) {
    push_back(other);
    return *this;
  }

  void push_back(const char other) {
    check_capacity(size + 1);
    string[size] = other;
    ++size;
    string[size] = '\0';
  } 

 
  String operator+(const char other) {
    String temp = *this;
    temp += other;
    return temp;
  }

  String operator+(const String& second_string) {
    String temp = *this;
    temp += second_string;
    return temp;
  }
  friend String operator+(const char other, const String& second_string);
  friend std::ostream& operator<<(std::ostream& stream, const String& str);
  friend std::istream& operator>>(std::istream& stream, String& str);
  friend bool operator==(const String& first_string, const String& second_string);

  ~String() {delete [] string;}
};

std::ostream& operator<<(std::ostream& stream, const String& str) {
  for (size_t i = 0; i < str.size; ++i) {
    stream << str.string[i];
  }
  return stream;
}

String operator+(const char other, const String& second_string) {
  String temp(other);
  temp += second_string;
  return temp;
}

bool operator==(const String& first_string, const String& second_string) {
  if (first_string.size != second_string.size) {
    return false;
  } else {
    bool result = true;
    for (size_t i = 0; i < first_string.size; ++i){
      if (first_string[i] != second_string[i]){
        result = false;
      }
    }
    return result;
  }
}

std::istream& operator>>(std::istream& stream, String& str) {
  str.clear();
  char ch;
  while (stream.get(ch)){
    if (ch == '\n' || ch == ' ') {break;}
    str.push_back(ch);
  }
  return stream;
}


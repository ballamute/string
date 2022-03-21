#pragma once
#include <string.h>

#include <iostream>
#include <vector>

class String {
 public:
  String();
  String(size_t size, char character);
  String(const char* c_string);

  String(const String& other);
  String& operator=(const String& other);

  ~String();
  void Clear();
  void PushBack(char character);
  void PopBack();
  void Resize(size_t new_size);
  void Resize(size_t new_size, char character);
  void Reserve(size_t new_cap);
  void ShrinkToFit();
  void Swap(String& other);

  char& operator[](int index);
  const char& operator[](int index) const;

  String& operator+=(const String& a);
  String& operator*=(const int& n);

  [[nodiscard]] const char& Front() const;
  [[nodiscard]] char& Front();
  [[nodiscard]] const char& Back() const;
  [[nodiscard]] char& Back();
  [[nodiscard]] bool Empty() const;
  [[nodiscard]] size_t Size() const;
  [[nodiscard]] size_t Capacity() const;
  [[nodiscard]] const char* Data() const;

  std::vector<String> Split(const String& delim = " ");
  String Join(const std::vector<String>& strings) const;

 private:
  size_t size_;
  size_t capacity_;
  char* data_;
};
String operator+(const String& a, const String& b);
String operator*(const String& a, const int& n);

bool operator<(const String& a, const String& b);
bool operator>(const String& a, const String& b);
bool operator<=(const String& a, const String& b);
bool operator>=(const String& a, const String& b);
bool operator==(const String& a, const String& b);
bool operator!=(const String& a, const String& b);

std::ostream& operator<<(std::ostream& out, const String& a);
std::istream& operator>>(std::istream& in, String& a);

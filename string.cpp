#include "String.hpp"

String::String() {
  size_ = 0;
  capacity_ = 1;
  data_ = (char*)calloc(capacity_, sizeof(char));
}

String::String(size_t size, char character) {
  size_ = size;
  capacity_ = size + 1;
  data_ = (char*)calloc(capacity_, sizeof(char));
  memset(data_, character, size_);
}

String::String(const char* c_string) {
  size_ = strlen(c_string);
  capacity_ = size_ + 1;
  data_ = (char*)calloc(capacity_, sizeof(char));
  memcpy(data_, c_string, size_);
}

String::String(const String& other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  data_ = (char*)calloc(capacity_, sizeof(char));
  memcpy(data_, other.data_, capacity_);
}

String& String::operator=(const String& other) {
  if (this != &other) {
    free(data_);
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = (char*)calloc(capacity_, sizeof(char));
    memcpy(data_, other.data_, capacity_);
  }
  return *this;
}

String::~String() { free(data_); }

void String::Resize(size_t new_size) { Resize(new_size, '\0'); }

void String::Resize(size_t new_size, char character) {
  Reserve(new_size);
  if (new_size > size_) {
    memset(data_ + size_, character, new_size - size_);
  } else {
    memset(data_ + new_size, '\0', size_ - new_size);
  }
  size_ = new_size;
}

void String::Reserve(size_t new_cap) {
  if (new_cap > capacity_ - 1) {
    data_ = (char*)realloc(data_, new_cap + 1);
    memset(data_ + capacity_, '\0', new_cap - capacity_ + 1);
    capacity_ = new_cap + 1;
  }
}

void String::Clear() {
  memset(data_, '\0', size_);
  size_ = 0;
}

void String::PushBack(char character) {
  if (size_ == capacity_ - 1) {
    if (capacity_ != 1) {
      Reserve((capacity_ - 1) * 2);
    } else {
      Reserve(1);
    }
  }
  data_[size_++] = character;
}

void String::PopBack() {
  if (!Empty()) {
    Resize(size_ - 1);
  }
}

void String::ShrinkToFit() {
  if (capacity_ > size_ + 1) {
    capacity_ = size_ + 1;
  }
  data_ = (char*)realloc(data_, capacity_);
}

void String::Swap(String& other) {
  char* data_buff = other.data_;
  size_t size_buff = other.size_;
  size_t capacity_buff = other.capacity_;

  other.size_ = size_;
  other.capacity_ = capacity_;
  other.data_ = data_;

  data_ = data_buff;
  size_ = size_buff;
  capacity_ = capacity_buff;
}

const char& String::Front() const { return data_[0]; }

char& String::Front() { return data_[0]; }

const char& String::Back() const { return data_[size_ - 1]; }

char& String::Back() { return data_[size_ - 1]; }

bool String::Empty() const { return Size() == 0; }

size_t String::Size() const { return size_; }

size_t String::Capacity() const { return capacity_ - 1; }

const char* String::Data() const { return data_; }

char& String::operator[](int index) { return data_[index]; }

const char& String::operator[](int index) const { return data_[index]; }

String operator+(const String& a, const String& b) {
  String res(a);
  res += b;
  return res;
}

String operator*(const String& a, const int& n) {
  String res(a);
  res *= n;
  return res;
}

bool operator<(const String& a, const String& b) {
  return strcmp(a.Data(), b.Data()) < 0;
}
bool operator>(const String& a, const String& b) {
  return strcmp(a.Data(), b.Data()) > 0;
}
bool operator<=(const String& a, const String& b) {
  return strcmp(a.Data(), b.Data()) <= 0;
}
bool operator>=(const String& a, const String& b) {
  return strcmp(a.Data(), b.Data()) >= 0;
}
bool operator==(const String& a, const String& b) {
  return strcmp(a.Data(), b.Data()) == 0;
}
bool operator!=(const String& a, const String& b) {
  return strcmp(a.Data(), b.Data()) != 0;
}

std::ostream& operator<<(std::ostream& out, const String& a) {
  for (size_t i = 0; i < a.Size(); i++) {
    out << a[i];
  }
  return out;
}

std::istream& operator>>(std::istream& in, String& a) {
  char character;
  while (in.get(character) && character != '\n') {
    a.PushBack(character);
  }
  return in;
}

String& String::operator+=(const String& a) {
  size_t n = a.size_;
  for (size_t i = 0; i < n; i++) {
    PushBack(a.data_[i]);
  }
  return *this;
}

String& String::operator*=(const int& n) {
  String s = *this;
  if (n == 0) {
    Clear();
  } else {
    for (int i = 0; i < n - 1; i++) {
      *this += s;
    }
  }
  return *this;
}

std::vector<String> String::Split(const String& delim) {
  std::vector<String> splitted_string = {""};
  char* str = data_;
  int i = 0;
  while (str[0] != 0) {
    if (str - data_ + delim.Size() <= size_ &&
        strncmp(str, delim.Data(), delim.Size()) == 0) {
      i++;
      splitted_string.push_back("");
      str += delim.Size();
      continue;
    }
    splitted_string[i].PushBack(str[0]);
    str++;
  }
  return splitted_string;
}

String String::Join(const std::vector<String>& strings) const {
  String joined_string = String();
  size_t size = strings.size();
  for (size_t i = 0; i < size; i++) {
    joined_string += strings[i];
    if (i != size - 1) {
      joined_string += *this;
    }
  }
  return joined_string;
}

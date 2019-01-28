/*
 * String.hpp
 *
 *  Created on: 26 Jan 2019
 *      Author: osboxes
 */

#ifndef SRC_STRING_HPP_
#define SRC_STRING_HPP_

#include <iostream>
namespace cus
{
class String
{
public:

    //default ctor
    String();

    //construct from C-style
    String(const char* s);

    //copy ctor
    String(const String& x);

    //move ctor
    String(String&& x);

   ~String();

    //copy assignment
    String& operator=(const String& x);

    //move asignment
    String& operator=(String&& x);

    //unchecked element access
    char& operator[](size_t n) { return p[n]; }
    char operator[](size_t n) const { return p[n]; }

    //range check element access
    char& at(size_t n) { check(n); return p[n]; }
    char at(size_t n) const { check(n); return p[n]; }

    //add character at the end
    String& operator+=(char c);
    //String& operator+=(const String& x);

    //C-style
    const char* c_str() { return p; }
    const char* c_str() const { return p; }

    //number of elements
    int size() const { return sz; }

private:
    //ancillary member function
    void check(size_t n) const;
    //expand into free store
    char* expand(const char* p, size_t n);
    void copy_from(const String& x);
    void move_from(String& x);

    //for optimization
    static const int short_max=15;
    //number of characters
    size_t sz;
    char* p;
    union {
        //unused allocated space
        size_t space;
        char ch[short_max+1];
    };
};

//char* begin(String& x);
const char* begin(const String& x);
//char* end(String& x);
const char* end(const String& x);
bool operator==(String& a, String& b);
std::ostream& operator<<(std::ostream& os, String& s);
String& operator+=(String& a, const String& b);
String operator"" _s(const char* p, size_t);

} //namespace cus

#endif /* SRC_STRING_HPP_ */

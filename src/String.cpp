/*
 * String.cpp
 *
 *  Created on: 26 Jan 2019
 *      Author: osboxes
 */

#include <cstring>
#include <stdexcept>
#include "String.hpp"

namespace cus {

String::String() : sz{0}, p{ch} {
    ch[0] = 0;
}

String::String(const char* s)
: sz{strlen(s)},
  p{(sz<=short_max) ? ch: new char[sz+1]},
  space{0} {
      //copy from source s to destination p
      strcpy(p,s);
}

String::String(const String& x) {
    copy_from(x);
}

String::String(String&& x) {
    move_from(x);
}

String::~String() {
    if (sz>short_max) {
        delete p;
    }
}

//copy assignment
String& String::operator=(const String& x) {
    if (this == &x) {
        return *this;
    }
    char* s = (sz>short_max) ? p : 0;
    copy_from(x);
    delete[] s;
    return *this;
}

//move assignment
String& String::operator=(String&& x) {
    if (this == &x) {
        return *this;
    }

    if (sz>short_max) {
        delete[] p;
    }

    move_from(x);
    return *this;
}

String& String::operator+=(char c) {
    if (sz == short_max) {
        //expand to long presentation
        int n = sz + sz + 2;
        p = expand(p, n);
        space = n - sz - 2;
    }
    else if(sz > short_max) {
        if (space == 0) {
            int n = sz + sz + 2;
            char* s = expand(p, n);
            delete[] p;
            p = s;
            space = n - sz -2;
        }
        else {
            space--;
        }
    }
    else {
        //do nothing
    }
    p[sz] = c;
    p[++sz] = 0;

    return *this;
}

//String& String::operator+=(const String& x) {
//    for(auto i : x) {
//        *this+=i;
//    }
//    return *this;
//}

void String::check(size_t n) const {
    if (n<0 || n>=sz) {
        throw std::out_of_range("String::at()");
    }
}

char* String::expand(const char* s, size_t n) {
    char* p = new char[n];
    strcpy(p,s);
    return p;
}

void String::copy_from(const String& x) {
    if (x.sz <= short_max) {
        memcpy(this, &x, sizeof(x));
        p = ch;
    }
    else {
        p = expand(x.p, x.sz+1);
        sz = x.sz;
        space = 0;
    }
}

void String::move_from(String& x) {
    if (x.sz <= short_max) {
        memcpy(this, &x, sizeof(x));
        p = ch;
    }
    else {
        p = x.p;
        sz = x.sz;
        space = x.space;
        //reset x
        x.p = x.ch;
        x.sz = 0;
        x.ch[0] = 0;
    }
}
///            outside the class         ////
bool operator==(String& a, String& b) {
    if (a.size() != b.size()) {
        return false;
    }

    for(size_t i=0; i<a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, String& s) {
    os << s.c_str();
    return os;
}

//char* begin(String& x) {
//    return x.c_str();
//}

const char* begin(const String& x) {
    return x.c_str();
}

//char* end(String& x) {
//    return x.c_str() + x.size();
//}

const char* end(const String& x) {
    return x.c_str() + x.size();
}

String& operator+=(String& a, const String& b) {
    for (auto x : b) {
        a+=x;
    }
    return a;
}

String operator"" _s(const char* p, size_t) {
    return String{p};
}

}

%module mixal
%{
#define SWIG_FILE_WITH_INIT
#define SWIG_NO_EXPORT_ITERATOR_METHODS
#include "machine.h"
using namespace std;
using namespace mixal;
%}

%include <std_vector.i>
%include <std_string.i>

%typemap(typecheck) int16_t {
$1 = PyLong_Check($input);
}

%typemap(in) int16_t {
$1 = static_cast<int16_t>(PyLong_AsLong($input));
}

%typemap(out) int16_t {
$result = PyLong_FromLong(static_cast<long>($1));
}

%typemap(typecheck) int32_t {
$1 = PyLong_Check($input);
}

%typemap(in) int32_t {
$1 = static_cast<int32_t>(PyLong_AsLong($input));
}

%typemap(out) int32_t {
$result = PyLong_FromLong(static_cast<long>($1));
}

namespace std {
  %template(VecInt) vector<int>;
  %template(VecStr) vector<string>;
}

%include "memory.h"
%include "registers.h"
%include "machine.h"

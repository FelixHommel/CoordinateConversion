#ifndef GLOBAL_H
#define GLOBAL_H

//Boost Library (may not work without the correct project settings)
#include <boost/multiprecision/cpp_dec_float.hpp>

//Global variables
constexpr auto DEBUG_MODE = true;

//Global constants
constexpr auto C_SCALE_FACTOR = 1.f;

//Typealiases
using pFloat = boost::multiprecision::cpp_dec_float_100;
using pointPairs = std::vector<std::pair<pFloat, pFloat>>;

#endif // !GLOBAL_H

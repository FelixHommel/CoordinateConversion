#ifndef GLOBAL_H
#define GLOBAL_H

//Global variables
constexpr auto DEBUG_MODE = false;

//Global constants
constexpr auto C_SCALE_FACTOR = 1.5f;

//Typealiases
using pFloat = boost::multiprecision::cpp_dec_float_100;
using pointPairs = std::vector<std::pair<pFloat, pFloat>>;

#endif // !GLOBAL_H

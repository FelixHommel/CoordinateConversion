#ifndef GLOBAL_H
#define GLOBAL_H

//Global variables
constexpr auto DEBUG_MODE = false;

//Typealiases
using pFloat = boost::multiprecision::cpp_dec_float_100;
using pointPairs = std::vector<std::pair<pFloat, pFloat>>;

#endif // !GLOBAL_H

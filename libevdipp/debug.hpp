#ifndef DEBUG_HPP
#define DEBUG_HPP

#define DEBUG

#ifdef DEBUG
#include <iostream>
#define logging std::cout
#else
#include <fstream>
#define logging std::ofstream()
#endif

#endif

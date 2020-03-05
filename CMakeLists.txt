############################################################################
# CMakeLists.txt file for building analysis code for ICAL
# @author Jim John, INO
# @mail jim.john@tifr.res.in
############################################################################
cmake_minimum_required(VERSION 3.9)
add_executable(icalanalysis analysis.cpp)
target_compile_features(icalanalysis PRIVATE cxx_lambda_init_captures)

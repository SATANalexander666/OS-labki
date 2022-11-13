# CMake generated Testfile for 
# Source directory: /home/axr/prog/OS/main/tests
# Build directory: /home/axr/prog/OS/main/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[lab2_test]=] "lab2_test")
set_tests_properties([=[lab2_test]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/axr/prog/OS/main/tests/CMakeLists.txt;24;add_test;/home/axr/prog/OS/main/tests/CMakeLists.txt;0;")
add_test([=[lab3_test]=] "lab3_test")
set_tests_properties([=[lab3_test]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/axr/prog/OS/main/tests/CMakeLists.txt;34;add_test;/home/axr/prog/OS/main/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")

@rem !/bin/msdos

@rem  Make all examples.
@rem  No Scons, no CMake, no Make or any other make tool
@rem  One line one example
@rem  Designed for easy copy/paste



@echo %cd%

cl /EHsc  -I../../../../src /D%PP2F%  rgb.cpp
cl /EHsc  -I../../../../src /D%PP2F%  bgr.cpp

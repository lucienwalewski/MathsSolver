# Testing Project Description

A testing project has been added so that you may test your files. From the root path, 
navigate to "sources", where you will find two new files (in addition to MathSolver.pro
and main.cpp), "mathsSolverTesting.pro" and "testSuite.cpp". Opening the project is done as
usual in Qt, by double clicking "mathsSolverTesting.pro". In "mathSolverTesting.pro", we add 
_all_ the files from the main project (so that the project knows what you are talking about
when you call functions from the main project in your testing files) , _in addition_ to the testing
files which will be in the folder "testingFiles" found in sources. 

If you open "testSuite.cpp", you will find that the first line is "#include QtTest", which 
includes the QtTest library in order to use some testing functions. Then, we include the necessary
testing files. We have included a sample testing class - "#include "testingFiles/sampleTestClass.hpp"".
Then in main, for every test file, we add two lines in order to execute all the tests within the
file. We first instantiate the class within our sample class. In this case, within the file "sampleTestClass.hpp", 
we defined the class "testClass" which we instantiate in the function main as the variable "ta". Having done
this, we call the function QTest::qExec() which executes all the tests within that file.

If you now navigate to sampleTestClass.hpp, you can observe how the class is defined. In the private
slots, we have the methods "initTestCase()" and "cleanupTestCase" which will be the first and last methods
executed when calling "QTest::qExec()" respectively. More documentation about this can be found here:
https://doc.qt.io/qt-5/qtest-overview.html. Then we have added two test cases, which are defined in the 
cpp file. If you navigate there, you will see that in "test_case1()", we have called QVERIFY(true);. This
will verify that the expression within QVERIFY evaluates to true and will pass the test if it does so. QTest
offers other useful testing methods. If you run the project, in "Application Output", you should see which
tests passed and which failed. In this case, all tests should pass. This is seen below.

![Image](https://github.com/lucienwalewski/MathsSolver/blob/main/scripts/build_details/Screenshot%202020-12-03%20at%2010.45.27.png)

When creating your own tests, first create a new testing class within the folder "testingFiles". Use
the same boilerplate as in the class "sampleTestClass", just replacing the name of the file and class
to something appropriate, adding the necessary includes in your cpp file and adding your tests in 
"private slots". Then add the two lines in the main function in the file "testSuite.cpp" as described above
and make sure that your file was added to the SOURCES and HEADERS in the .pro file if it was not already
done so. 


# Build details

**Updated details to come**

In order to run the project, you will need to install the following libraries. We recommend you install them all in the same location:

- OpenCV https://opencv.org/releases/ (This library takes quite some time to install and you will also have to install Cmake in order to configure the library)

You will also need to have a working version of Anaconda in order to run the conda environment for the character recognition. 

Having installed these, open the project by double-clicking on MathsSolver.pro in the sources directory and navigate to the Projects tab, then in "Additional arguments" in the "Build Steps" section, 

If on Mac:

Enter: "OPENCV_LIBRARY_INCLUDE=__root__/opencv/build/install/include/opencv4" "OPENCV_LIBRARY_PATH=__root__/opencv/build/install/lib" "ANACONDA_PATH=__condaPath__" where __root__ is the path towards the opencv library on your machine and __condaPath__ is the directory towards your Anaconda installation. In the example image below, the directory towards the opencv library is "Users/lucienwalewski/".

![Image](https://github.com/lucienwalewski/MathsSolver/blob/main/scripts/build_details/Screenshot%202020-11-22%20at%2000.06.27.png)

If on Windows: 

Enter: "OPENCV_LIBRARY_INCLUDE=__root__\opencv\release\install\include" "OPENCV_LIBRARY_PATH=__root__\opencv\release\bin\" "ANACONDA_PATH=__condaPath__ where __root__ is the path towards your opencv installation and __condaPath__ is the path towards your Anaconda installation. 

We now also need to activate the Conda environment included. First ensure you are in the root directory of the project where you should find the file ```recognition.yml```. Run the following command:

```Conda env create -f recognition.yml```


Having done this, the project should build and run.

### "bits/stdc++.h" not found

This file will not compile on Mac. The fix for this is as follows:


1. Open the terminal and paste the following line: `cd /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1/` to navigate to the directory.
2. Create a folder named `bits` by entering `mkdir bits` and then enter the directory with `cd bits`.
3. Create the file `stdc++.h` by entering `touch stdc++.h`. 
4. Open the file in Xcode by entering `open stdc++.h`
5. Copy and paste into the file the following lines of code. Save and close the file. 

Copy this:


    // C++ includes used for precompiling -*- C++ -*-
    // Copyright (C) 2003-2013 Free Software Foundation, Inc.
    //
    // This file is part of the GNU ISO C++ Library.  This library is free
    // software; you can redistribute it and/or modify it under the
    // terms of the GNU General Public License as published by the
    // Free Software Foundation; either version 3, or (at your option)
    // any later version.

    // This library is distributed in the hope that it will be useful,
    // but WITHOUT ANY WARRANTY; without even the implied warranty of
    // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    // GNU General Public License for more details.

    // Under Section 7 of GPL version 3, you are granted additional
    // permissions described in the GCC Runtime Library Exception, version
    // 3.1, as published by the Free Software Foundation.

    // You should have received a copy of the GNU General Public License and
    // a copy of the GCC Runtime Library Exception along with this program;
    // see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
    // <http://www.gnu.org/licenses/>.

    /** @file stdc++.h
     *  This is an implementation file for a precompiled header.
      */

    // Also writing "using namespace std;" here so that you dont need to write it everytime you start a cpp file

    using namespace std;

    // 17.4.1.2 Headers

    // C
    #ifndef _GLIBCXX_NO_ASSERT
    #include <cassert>
    #endif
    #include <cctype>
    #include <cerrno>
    #include <cfloat>
    #include <ciso646>
    #include <climits>
    #include <clocale>
    #include <cmath>
    #include <csetjmp>
    #include <csignal>
    #include <cstdarg>
    #include <cstddef>
    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
    #include <ctime>

    #if __cplusplus >= 201103L
    #include <ccomplex>
    #include <cfenv>
    #include <cinttypes>
    #include <cstdbool>
    #include <cstdint>
    #include <ctgmath>
    #include <cwchar>
    #include <cwctype>
    #endif

    // C++
    #include <algorithm>
    #include <bitset>
    #include <complex>
    #include <deque>
    #include <exception>
    #include <fstream>
    #include <functional>
    #include <iomanip>
    #include <ios>
    #include <iosfwd>
    #include <iostream>
    #include <istream>
    #include <iterator>
    #include <limits>
    #include <list>
    #include <locale>
    #include <map>
    #include <memory>
    #include <new>
    #include <numeric>
    #include <ostream>
    #include <queue>
    #include <set>
    #include <sstream>
    #include <stack>
    #include <stdexcept>
    #include <streambuf>
    #include <string>
    #include <typeinfo>
    #include <utility>
    #include <valarray>
    #include <vector>

    #if __cplusplus >= 201103L
    #include <array>
    #include <atomic>
    #include <chrono>
    #include <condition_variable>
    #include <forward_list>
    #include <future>
    #include <initializer_list>
    #include <mutex>
    #include <random>
    #include <ratio>
    #include <regex>
    #include <scoped_allocator>
    #include <system_error>
    #include <thread>
    #include <tuple>
    #include <typeindex>
    #include <type_traits>
    #include <unordered_map>
    #include <unordered_set>
    #endif



## Current Build Issues


# Maths Solver Project Description

The MathsSolver program will allow a user to upload a picture of a handwritten maths
problem or type the problem which will then be solved by the program.

## Members (name surname, github, trello, [role])

- Lazar Milikic, Lemmy00 , lazarmilikic , Project lead
- Lucien Walewski, lucienwalewski, lucienwalewski , Image recognition team lead, Git master
- Peixin You, hyleindex , _ , Algorithms/Equations team lead
- Constance Ferragu, constanceferragu , _ , Differential Calculator team lead
- Ghadie Nehme, ghadinehme , ghadinehme , Numerical integration team lead
- Hugo de Mascarel, hugodemascarel , hugodemascarel , GUI team lead
- Hector Devie, hector-dvi , _ , Trello master, Algorithms/Equations team
- Jean Paul Touret, jeanpaultouret2000 , _ , Differential calculator team
- Merlin Beaufils, merlinbeaufils , _ , Differential calculator team
- Wenqing Qu, QwQSama , _ , Algorithms/Equations team
- Aurele Bohbot, aurelebohbot , Aurele Bohbot , Algorithms/Equations team
- Ines Saih, inessaih , inessaih , Numerical integration team
- Marie Huynh, marie-huynh , mariehuynh6 , Differential calculator team

## Teams

**Algorithms / Equations**

- Peixin You
- Wenqing Qu
- Aurele Bohbot 
- Hector Devie

**Image recogntion**

- Lucien Walewski
- Lazar Milikic

**Differential calculator**

- Constance Ferragu
- Marie Huynh
- Merlin Beaufils
- Jean Paul Touret

**Numerical Integration**

- Ghadi Nehme
- Ines Saih

**GUI**

- Hugo de Mascarel

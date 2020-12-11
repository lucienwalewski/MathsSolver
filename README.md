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

- Eigen http://eigen.tuxfamily.org/index.php?title=Main_Page
- OpenCV https://opencv.org/releases/ (This library takes quite some time to install and you will also have to install Cmake in order to configure the library)

Having installed these, open the project by double-clicking on MathsSolver.pro in the sources directory and navigate to the Projects tab, then in "Additional arguments" in the "Build Steps" section, 

If on Mac:

Enter: "EIGEN_LIBRARY_INCLUDE=root/eigen-3.3.8" "OPENCV_LIBRARY_INCLUDE=root/opencv/build/install/include/opencv4" "OPENCV_LIBRARY_PATH=root/opencv/build/install/lib" where "root" is the path towards
both libraries on your machine. In the example image below, the directory towards the libraries is "Users/lucienwalewski/".

![Image](https://github.com/lucienwalewski/MathsSolver/blob/main/scripts/build_details/Screenshot%202020-11-22%20at%2000.06.27.png)

If on Windows: 

Enter: "EIGEN_LIBRARY_INCLUDE=root\eigen-3.3.8" "OPENCV_LIBRARY_INCLUDE=root\opencv\release\install\include" "OPENCV_LIBRARY_PATH=root\opencv\release\bin\" where "root" is the path towards both libraries on your machine. 

Then, scroll down to line 34 in MathsSolver.pro and follow the instructions. Having done this, the project should now build and run. Make sure to uncomment any source or header files in MathsSolver.pro if they are still commented. 

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

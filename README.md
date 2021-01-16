# MathsSolver

## Description

The MathsSolver program will allow a user to upload a picture of a handwritten maths
problem or type the problem which will then be solved by the program.

## Prerequisites

- QT 4.13.3 or newer

> Note: The Project was tested with macOS Big Sur 11.2 Beta with QT 4.13.3 and Windows 10 (without Image Recognition)

## Installation

Run the command

```git clone https://github.com/lucienwalewski/MathsSolver```

In order to run the project, you will need to install the following libraries. We recommend you install them all in the same location:

- OpenCV https://opencv.org/releases/
> This library takes quite some time to install and you will also have to install Cmake in order to configure the library. We include two potentially helpful videos. For Mac (https://www.youtube.com/watch?v=SIXnD-9uh1k). For Windows (https://www.youtube.com/watch?v=ZOSu-2Oju-A)

You will also need to have a working version of Anaconda in order to run the conda environment for the character recognition. 

Having installed these, open the Qt project by double-clicking the file ```MathsSolver.pro``` in the ```sources``` directory. Then, navigate to the Projects tab, then in "Additional arguments" in the "Build Steps" section, 

If on **Mac**:

Enter: "OPENCV_LIBRARY_INCLUDE=__root__/opencv/build/install/include/opencv4" "OPENCV_LIBRARY_PATH=__root__/opencv/build/install/lib" "ANACONDA_PATH=__condaPath__" where __root__ is the path towards the opencv library on your machine and __condaPath__ is the directory towards your Anaconda installation. In the example image below, the directory towards the opencv library is "Users/lucienwalewski/".

![Image](https://github.com/lucienwalewski/MathsSolver/blob/main/scripts/build_details/Screenshot%202020-11-22%20at%2000.06.27.png)

If on **Windows**: 

Enter: "OPENCV_LIBRARY_INCLUDE=__root__\opencv\release\install\include" "OPENCV_LIBRARY_PATH=__root__\opencv\release\bin\" "ANACONDA_PATH=__condaPath__ where __root__ is the path towards your opencv installation and __condaPath__ is the path towards your Anaconda installation. 

> Note: The project can build and run on both Mac and Windows (not tested on Linux) but the ImageRecognition part will not work on Windows.

#### For Image Recognition 

This is only necessary if running the Image Recognition (only from Mac!). We need to install the Conda environment included. First ensure you are in the root directory of the project where you should find the file ```recognition.yml```. Run the following command:

```Conda env create -f recognition.yml```

Having done this, the project should build and run.

## Instructions

- Please only use x as variable! Usual functions that can be used:
    ```exp(x)```, ```ln(x)```, ```log(x)```, ```sin(x)```, ```cos(x)```, ```tan(x)```, ```sqrt(x)```
- To find the derivative of a function: ```(f(x))'```
    - Example: ```(x^2 + 5x + exp(x^3))'```
- To get the value of the integral of a function: ```int{a}{b}{f(x)}```
    - Example: ```int{0}{1}{exp(x)}``` means integral from 0 to 1 of ```exp(x)```.
- To find the root at point a of a function ```f(x) = a```.
    - Example: ```x^3 - 2x^2 - x + 2 = 0```
- To solve a system of equations: ```sys{your system}```
    - Example: ```sys{2 ; 5 ;  2  = -38 | 3 ; -2; 4 = 17 | -6; 1; -7 = -12 }``` means solving the following system of equations: ```2x0 + 5x1 + 2x2 = -38, 3x0 - 5x1 + 4x2 = 17, -6x0 + x1 - 7x2 = -12```. Each coefficient should be separated by a semi-colon and a new equation is obtained by entering '|'.
- To get the inverse of a matrix: ```inv{matrix}```
    - Example: ```inv{-5; 3; 1 | 4; -1; 5 | 2; -2; 3}```. Each coefficient should be separated by a semmi-colon and a new row is obtained by entering '|'.
- To get the determinant of a matrix: ```det{matrix}```
    - Example: ```det{-5; 3; 1 | 4; -1; 5 | 2; -2; 3}```. Each coefficient should be separated by a semi-colon and a new row is obtained by entering '|'.
- To get the product of matrices: ```mult{matrix1}{matrix2}```
    - Example: ```mult{8; 2}{3 | 4}```. Each coefficient should be separated by a semi-colon and a new row is obtained by entering '|'.
- To divide two polynomials: ```(polynomial1) : (polynomial2)```
    - Example: ```(x^3 - 2x^2 - x + 2) : (x^2 - 1)```
- To multiply two polynomials: ```(polynomial1) * (polynomial2)```
    - Example: ```(x^3 - 2x^2 - x + 2) * (x^2 - 1)```
    
### Screenshots

Example usecases

![Image](https://github.com/lucienwalewski/MathsSolver/blob/main/scripts/build_details/pic1.png)
![Image](https://github.com/lucienwalewski/MathsSolver/blob/main/scripts/build_details/pic2.png)

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


### Testing Project Description (for development)

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

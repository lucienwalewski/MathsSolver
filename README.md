# Build details

In order to run the project, you will need to install the following libraries. We recommend you install them all in the same location:

- Eigen http://eigen.tuxfamily.org/index.php?title=Main_Page
- OpenCV https://opencv.org/releases/ (This library takes quite some time to install and you will also have to install Cmake in order to configure the library)

Having installed these, open the project by double-clicking on MathsSolver.pro in the sources directory and navigate to the Projects tab, then in "Additional arguments" in the "Build Steps" section, 

If on Mac:

Enter: "EIGEN_LIBRARY_INCLUDE=root/eigen-3.3.8" "OPENCV_LIBRARY_INCLUDE=root/opencv/build/install/include/opencv4" where "root" is the path towards
both libraries on your machine. In the example image below, the directory towards the libraries is "Users/lucienwalewski/".

![Image](https://github.com/lucienwalewski/MathsSolver/blob/main/scripts/build_details/Screenshot%202020-11-22%20at%2000.06.27.png)

If on Windows: 

Enter: "EIGEN_LIBRARY_INCLUDE=root\eigen-3.3.8" "OPENCV_LIBRARY_INCLUDE=root\opencv\release\install\include" "OPENCV_LIBRARY_PATH=root\opencv\release\bin\" where "root" is the path towards both libraries on your machine. 

Then, scroll down to line 34 in MathsSolver.pro and follow the instructions. Having done this, the project should now build and run. Make sure to uncomment any source or header files in MathsSolver.pro if they are still commented. 

## Current Build Issues

- Will not build if derivates.hpp is included in main.cpp. Reason: Unknown. Unresolved. 


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
- Peixin You

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
- Hector Devie

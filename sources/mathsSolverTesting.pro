QT += testlib
QT += gui
QT += core gui
CONFIG += qt warn_on depend_includepath testcase

QMAKE_POST_LINK += ./${TARGET}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += \
    testSuite.cpp \
#    Derivatives/Tokenizer.cpp \
#    Derivatives/derivatives.cpp \
#    ImageRecognition/imagePreprocessing.cpp \
#    ImageRecognition/cnn.cpp \
#    ImageRecognition/util.cpp \
#    MainWindow/mainwindow.cpp \
    testclass.cpp \
#    tstFunc.cpp

HEADERS += \
#    Derivatives/Tokenizer.hpp \
#    Derivatives/derivatives.hpp \
#    ImageRecognition/imagePreprocessing.hpp \
#    ImageRecognition/cnn.hpp \
#    ImageRecognition/util.hpp \
#    MainWindow/mainwindow.h \
    testclass.hpp

FORMS += \
    MainWindow/mainwindow.ui


#INCLUDEPATH += $${EIGEN_LIBRARY_INCLUDE}
#LIBS += -L$${EIGEN_LIBRARY_PATH} -lcommon

# ON WINDOWS UNCOMMENT THE TWO LINES BELOW

#INCLUDEPATH += $${OPENCV_LIBRARY_INCLUDE}
#LIBS += -L$${OPENCV_LIBRARY_PATH} -lopencv_core450 -lopencv_highgui450 -lopencv_imgcodecs450 -lopencv_imgproc450 -lopencv_calib3d450


## -L path tells the linker to look for library files inside OPENCV_LIBRARY_PATH
## -lopencv_core450 tells to link agains libopencv_core450 (this syntax is portable across platforms)

# ON MAC UNCOMMENT THE TWO LINES BELOW

#INCLUDEPATH += $${OPENCV_LIBRARY_INCLUDE}
#LIBS += -L$${OPENCV_LIBRARY_PATH} \
#        -l"opencv_world"

#INCLUDEPATH += "/Users/lucienwalewski/opencv/build/install/include/opencv4"
#LIBS += -L"/Users/lucienwalewski/opencv/build/install/lib" \
#        -l"opencv_world"

# Individual team member lines:

# Lucien :
#"OPENCV_LIBRARY_INCLUDE=/Users/lucienwalewski/opencv/build/install/include/opencv4" "OPENCV_LIBRARY_PATH=/Users/lucienwalewski/opencv/build/install/lib" "EIGEN_LIBRARY_INCLUDE=/Users/lucienwalewski/eigen-3.3.8"

# Lazar :
#

# ...


QT += core gui

# For opencv use:
# Go to projects, build steps, qmake, additional arguments and enter:
# "OPENCV_LIBRARY_INCLUDE=root/opencv/build/install/include/opencv4"
# where root is the path to opencv on your machine. Uncomment lines
# 20,27,37-38.

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Derivatives/derivatives.cpp \
    # Uncomment the line below if using opencv
    #ImageRecognition/imagePreprocessing.cpp \
    #ImageRecognition/cnn.cpp \
    #ImageRecognition/util.cpp \
    main.cpp \
    MainWindow/mainwindow.cpp

HEADERS += \
    Derivatives/derivatives.hpp \
    # Uncomment the line below if using opencv
    #ImageRecognition/imagePreprocessing.hpp \
    #ImageRecognition/cnn.hpp \
    #ImageRecognition/util.hpp \
    MainWindow/mainwindow.h

FORMS += \
    MainWindow/mainwindow.ui



# Uncomment the first four lines to use Eigen and openCV

#INCLUDEPATH += $${EIGEN_LIBRARY_INCLUDE}
#LIBS += -L$${EIGEN_LIBRARY_PATH} -lcommon
#INCLUDEPATH += $${OPENCV_LIBRARY_INCLUDE}
#LIBS += -L$${OPENCV_LIBRARY_PATH} -lopencv_core450 -lopencv_highgui450 -lopencv_imgcodecs450 -lopencv_imgproc450 -lopencv_calib3d450
## -L path tells the linker to look for library files inside OPENCV_LIBRARY_PATH
## -lopencv_core450 tells to link agains libopencv_core450 (this syntax is portable across platforms)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

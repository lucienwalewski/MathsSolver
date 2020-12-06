QT += core gui
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Derivatives/Tokenizer.cpp \
    Derivatives/derivatives.cpp \
#    ImageRecognition/imagePreprocessing.cpp \
#    ImageRecognition/cnn.cpp \
#    ImageRecognition/util.cpp \
#    MainWindow/mainwindow.cpp
    main.cpp \


HEADERS += \
    Derivatives/Tokenizer.hpp \
    Derivatives/derivatives.hpp \
#    Derivatives/tokenizer_testing.hpp \
#    ImageRecognition/imagePreprocessing.hpp \
#    ImageRecognition/cnn.hpp \
#    ImageRecognition/util.hpp \
#    MainWindow/mainwindow.h

FORMS += \
    MainWindow/mainwindow.ui


# Eigen path

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

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../../libtensorflow/lib/release/ -ltensorflow.2.3.1
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../../libtensorflow/lib/debug/ -ltensorflow.2.3.1
#else:unix: LIBS += -L$$PWD/../../../../../../../../libtensorflow/lib/ -ltensorflow.2.3.1

#INCLUDEPATH += $$PWD/../../../../../../../../libtensorflow/include
#DEPENDPATH += $$PWD/../../../../../../../../libtensorflow/include

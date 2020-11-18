rm -rf build
mkdir build
cd build
qmake ../sources/MathsSolver.pro
make -j8

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make clean
make
cp src/clustersim ..

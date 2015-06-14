rm -rf build/
gyp build.gyp --depth . --generator-output=build -DTARGET=release
cd build/
make
cp out/Default/clustersim ..

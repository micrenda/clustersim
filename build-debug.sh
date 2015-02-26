rm -rf build/
gyp build.gyp --depth . --generator-output=build -DTARGET=debug
cd build/
make
cp out/Default/clustersim ..

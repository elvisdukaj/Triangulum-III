cd ${TRIANGULUM_HOME}/server && mkdir -p build && cd build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE:String=Debug -DBOX2D_INSTALL=0 -DBOX2D_BUILD_EXAMPLES=0 -DENTITYX_BUILD_TESTING=0 -DENTITYX_BUILD_SHARED=0
make

# Build demo project

## Pre-requisite
Install emcc by following: https://emscripten.org/docs/getting_started/downloads.html

Compile wasmtbb https://github.com/hpcwasm/wasmtbb by:

git clone https://github.com/hpcwasm/wasmtbb

in the root folder

emmake make tbb

## Build demo project

make sure TBB include path correctly points to WASMTBB in cmakelist:
set(TBB_INCLUDE_DIR "/home/ubuntu/wasmtbb/include")

ubuntu@ubuntu2004:~/wasmtbbdemo$ mkdir buildwasm
ubuntu@ubuntu2004:~/wasmtbbdemo$ cd buildwasm/
ubuntu@ubuntu2004:~/wasmtbbdemo/buildwasm$ emmake cmake ..
make: cmake ..
-- The C compiler identification is Clang 13.0.0
-- The CXX compiler identification is Clang 13.0.0
-- Check for working C compiler: /home/ubuntu/emsdk/upstream/emscripten/emcc
-- Check for working C compiler: /home/ubuntu/emsdk/upstream/emscripten/emcc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /home/ubuntu/emsdk/upstream/emscripten/em++
-- Check for working CXX compiler: /home/ubuntu/emsdk/upstream/emscripten/em++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/ubuntu/wasmtbbdemo/buildwasm
ubuntu@ubuntu2004:~/wasmtbbdemo/buildwasm$ make
Scanning dependencies of target tbbdemo
[ 50%] Building CXX object CMakeFiles/tbbdemo.dir/tbbdemo.cpp.o
em++: warning: linker setting ignored during compilation: 'ERROR_ON_UNDEFINED_SYMBOLS' [-Wunused-command-line-argument]
em++: warning: linker setting ignored during compilation: 'NO_FILESYSTEM' [-Wunused-command-line-argument]
em++: warning: linker setting ignored during compilation: 'WASM' [-Wunused-command-line-argument]
em++: warning: linker setting ignored during compilation: 'ALLOW_MEMORY_GROWTH' [-Wunused-command-line-argument]
em++: warning: linker setting ignored during compilation: 'PTHREADS_DEBUG' [-Wunused-command-line-argument]
em++: warning: linker setting ignored during compilation: 'PTHREAD_POOL_SIZE' [-Wunused-command-line-argument]
em++: warning: linker setting ignored during compilation: 'TOTAL_MEMORY' [-Wunused-command-line-argument]
em++: warning: linker setting ignored during compilation: 'WASM_MEM_MAX' [-Wunused-command-line-argument]
In file included from /home/ubuntu/wasmtbbdemo/tbbdemo.cpp:11:
In file included from /home/ubuntu/wasmtbb/include/tbb/task_group.h:20:
In file included from /home/ubuntu/wasmtbb/include/tbb/task.h:21:
/home/ubuntu/wasmtbb/include/tbb/tbb_machine.h:115:2: warning: "WASMPORT: tbb_machine.h" [-W#warnings]
#warning "WASMPORT: tbb_machine.h"
 ^
/home/ubuntu/wasmtbb/include/tbb/tbb_machine.h:239:10: warning: "wasmport machine/linux_wasm32.h" [-W#warnings]
        #warning "wasmport machine/linux_wasm32.h"
         ^
In file included from /home/ubuntu/wasmtbbdemo/tbbdemo.cpp:11:
In file included from /home/ubuntu/wasmtbb/include/tbb/task_group.h:20:
In file included from /home/ubuntu/wasmtbb/include/tbb/task.h:21:
In file included from /home/ubuntu/wasmtbb/include/tbb/tbb_machine.h:257:
/home/ubuntu/wasmtbb/include/tbb/machine/linux_common.h:21:2: warning: "WASMPORT: linux_common.h" [-W#warnings]
#warning "WASMPORT: linux_common.h"
 ^
3 warnings generated.
em++: warning: argument unused during compilation: '' [-Wunused-command-line-argument]
[100%] Linking CXX executable tbbdemo.js
[100%] Built target tbbdemo
ubuntu@ubuntu2004:~/wasmtbbdemo/buildwasm$ node tbbdemo
Allocating a new web worker from /home/ubuntu/wasmtbbdemo/buildwasm/tbbdemo.worker.js
Allocating a new web worker from /home/ubuntu/wasmtbbdemo/buildwasm/tbbdemo.worker.js
Allocating a new web worker from /home/ubuntu/wasmtbbdemo/buildwasm/tbbdemo.worker.js
Allocating a new web worker from /home/ubuntu/wasmtbbdemo/buildwasm/tbbdemo.worker.js
Allocating a new web worker from /home/ubuntu/wasmtbbdemo/buildwasm/tbbdemo.worker.js
Allocating a new web worker from /home/ubuntu/wasmtbbdemo/buildwasm/tbbdemo.worker.js
Allocating a new web worker from /home/ubuntu/wasmtbbdemo/buildwasm/tbbdemo.worker.js
Allocating a new web worker from /home/ubuntu/wasmtbbdemo/buildwasm/tbbdemo.worker.js
test
Example::init(2)
0.001
created 64 tasks
0
runParallel done 
7.616
runSerial done 
15.106
threadInit
cmake_minimum_required(VERSION 3.4)

SET(CMAKE_CXX_FLAGS "-std=c++14 -mmutable-globals" CACHE STRING "compile flags" FORCE)

# WebAssembly Config for emscripten
###############
set(BUILD_WASM true CACHE BOOL "build webassembly")
set(TBB_INCLUDE_DIR "/home/ubuntu/wasmtbb/include")

# Project setup
###############
PROJECT(tbbdemo)


SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O0 -g -ferror-limit=1")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -ferror-limit=1")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g -ferror-limit=1")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--shared-memory")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-check-features")


add_definitions(-DBUILD_WASM)
add_definitions(-D__wasm32__) 
add_definitions(-D__emscripten__) 
add_definitions(-D__TBB_DYNAMIC_LOAD_ENABLED=0) 
add_definitions(-D__TBB_SOURCE_DIRECTLY_INCLUDED=1) 

set(Boost_LIBRARIES "-lboost_system -lboost_filesystem -lboost_iostreams")
set(Boost_INCLUDE_DIR ${WASM_BOOST_INCLUDE_DIR})

# INCLUDE_DIRECTORIES(${WASM_BOOST_INCLUDE_DIR})
# INCLUDE_DIRECTORIES(${WASM_VDB_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${TBB_INCLUDE_DIR})
# INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})


# LINK_DIRECTORIES(${WASM_BOOST_LIB_DIR})
# LINK_DIRECTORIES(${WASM_VDB_LIB_DIR})
# LINK_DIRECTORIES(${WASM_TBB_LIB_DIR})

# INCLUDE_DIRECTORIES(".")

# INCLUDE_DIRECTORIES("")

# FIND_PACKAGE ( Threads REQUIRED )
# ADD_DEFINITIONS ( -pthread -v)
ADD_DEFINITIONS ( -pthread)



# add_library(libtest STATIC libtest.cpp)
# target_link_libraries(libtest ${Tbb_TBB_LIBRARY}   )
# set_target_properties(libtest PROPERTIES 
# COMPILE_FLAGS " --bind -v \
# -pthread \
# -Wl,--shared-memory,--no-check-features \
# -s NO_FILESYSTEM=1 \
# -s ERROR_ON_UNDEFINED_SYMBOLS=0 \
# -s WASM=1 \
# -s ALLOW_MEMORY_GROWTH=0 \
# -s USE_PTHREADS=1 \
# -s PTHREAD_POOL_SIZE=2 \
# -s USE_ZLIB=1 \
# -s TOTAL_MEMORY=536870912 \
# -s WASM_MEM_MAX=536870912 \
# -s \"BINARYEN_TRAP_MODE='allow'\"")

# FIND_PACKAGE(Threads)

# add_executable(demo demo.cpp)


# target_link_libraries(demo ${WASM_VDB_LIBRARY} ${Tbb_TBB_LIBRARY} ${Boost_LIBRARIES}   )

# # USE_PTHREADS


# set(WASM_SUFFIX ".html")
# set_target_properties(demo PROPERTIES 
# SUFFIX "${WASM_SUFFIX}" 
# COMPILE_FLAGS " --bind -v \
# -pthread \
# -Wl,--shared-memory,--no-check-features \
# -s NO_FILESYSTEM=1 \
# -s ERROR_ON_UNDEFINED_SYMBOLS=0 \
# -s WASM=1 \
# -s ALLOW_MEMORY_GROWTH=0 \
# -s USE_PTHREADS=1 \
# -s PTHREAD_POOL_SIZE=2 \
# -s USE_ZLIB=1 \
# -s TOTAL_MEMORY=536870912 \
# -s WASM_MEM_MAX=536870912 \
# -s \"BINARYEN_TRAP_MODE='allow'\"")

set( OBJDIR "/home/ubuntu/wasmtbb/build/linux_wasm32_emscripten_emscripten_wasm32_release/")
FILE(GLOB MYOBJECTS ${OBJDIR}/*.o)

add_executable(tbbdemo tbbdemo.cpp  ${MYOBJECTS}  )


# target_link_libraries(tbbdemo    )
# target_link_libraries(tbbdemo ${Boost_LIBRARIES}  ${Tbb_TBB_LIBRARY}  "${OBJDIR}task_group_context.o" "${OBJDIR}governor.o" "${OBJDIR}tbb_misc.o" "${OBJDIR}task.o" "${OBJDIR}cache_aligned_allocator.o"  "${OBJDIR}arena.o" "${OBJDIR}scheduler.o" "${OBJDIR}observer_proxy.o"  "${OBJDIR}spin_rw_mutex.o"  "${OBJDIR}tbb_misc_ex.o"  "${OBJDIR}tbb_main.o" "${OBJDIR}dynamic_link.o" "${OBJDIR}rml_tbb.o"  "${OBJDIR}market.o"  "${OBJDIR}concurrent_monitor.o" "${OBJDIR}private_server.o"  -static )
# target_link_libraries(tbbdemo ${Tbb_TBB_LIBRARY} )
# USE_PTHREADS


set(WASM_SUFFIX ".js")
set_target_properties(tbbdemo PROPERTIES 
SUFFIX "${WASM_SUFFIX}" 
# LINK_FLAGS "--bind -Wl,--shared-memory,--no-check-features -s USE_PTHREADS=1  -s PTHREAD_POOL_SIZE=2 -s USE_ZLIB=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0"
# LINK_FLAGS "--bind -s USE_PTHREADS=1" 
COMPILE_FLAGS "--bind -Wl, -s USE_PTHREADS=1  -s USE_ZLIB=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0 \
-O0 \
-s NO_FILESYSTEM=0 \
-s WASM=1 \
-s ALLOW_MEMORY_GROWTH=0 \
-s PTHREADS_DEBUG=1 \
-s PTHREAD_POOL_SIZE=8 \
-s TOTAL_MEMORY=536870912 \
-s WASM_MEM_MAX=536870912"
LINK_FLAGS "--bind -Wl,  -s USE_PTHREADS=1  -s USE_ZLIB=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0 \
-O0 \
-s NO_FILESYSTEM=0 \
-s WASM=1 \
-s ALLOW_MEMORY_GROWTH=0 \
-s PTHREADS_DEBUG=1 \
-s PTHREAD_POOL_SIZE=8 \
-s TOTAL_MEMORY=536870912 \
-s WASM_MEM_MAX=536870912")
# -s PTHREAD_POOL_SIZE=4 \

INSTALL(FILES "${CMAKE_CURRENT_LIST_DIR}/SimpleHTTPServer.py" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
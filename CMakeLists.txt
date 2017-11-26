if (${CMAKE_CURRENT_SOURCE_DIR} MATCHES ${CMAKE_CURRENT_BINARY_DIR})
    message( FATAL_ERROR "Run cmake from the './build' directory" )
endif()

cmake_minimum_required(VERSION 3.4.3)
project (hello-sdl)

set(WASM ON CACHE BOOL "If we should be compiling for WebAssembly.")

message(STATUS "Compiling for WebAssembly? ${WASM}")

if (WASM)
    message(STATUS "SETTING WASM COMPILE CONFIGS WASM: ${WASM}")
    set(CMAKE_SYSTEM_NAME Linux)
    # which C and C++ compiler to use
    set(EMCC_LINKER_FLAGS "-g -s -s WASM=1 -s USE_SDL=2 --preload-file resources/hello.bmp")
    set(CMAKE_REQUIRED_FLAGS "${EMCC_LINKER_FLAGS}")
    set(CMAKE_C_COMPILER   emcc)
    set(CMAKE_CXX_COMPILER em++)
    set(CMAKE_AR           emar)
    set(CMAKE_RANLIB       emranlib)
endif()

# Emscripten includes its own version of SDL.
if (NOT WASM)
    message(STATUS "adding SDL WASM status ${WASM}")
    add_subdirectory(deps/SDL)
    include_directories(deps/SDL/include)
endif()

if (WASM)
    message(STATUS "Setting up main.js executable ${WASM}")
    add_executable(
        main.js
        src/main.c
    )
    set_target_properties(main.js PROPERTIES LINK_FLAGS "${EMCC_LINKER_FLAGS}")
else()
    message(STATUS "Setting up main executable ${WASM}")
    add_executable(
        main
        src/main.c
    )
endif()

configure_file(resources/hello.bmp resources/hello.bmp COPYONLY)
configure_file(src/index.html index.html COPYONLY)

if (NOT WASM)
    target_link_libraries(main SDL2 ${SDL2_LIBRARIES})
endif()


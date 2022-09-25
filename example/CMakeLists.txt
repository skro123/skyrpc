
include_directories(${PROJECT_SOURCE_DIR})
link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(/usr/local/bin)

include_directories(/usr/local/include/yaml-cpp)
link_directories(/usr/local/lib)

set(LIBS
        skyrpc
        dl
        pthread
        yaml-cpp
        )

#echo_server
skyrpc_add_executable(echo_server echo_server.cpp skyrpc ${LIBS})

#consumer.cpp
skyrpc_add_executable(consumer rpc/consumer.cpp skyrpc ${LIBS})

#consumer.cpp
skyrpc_add_executable(provider rpc/provider.cpp skyrpc ${LIBS})

#consumer.cpp
skyrpc_add_executable(registry rpc/registry.cpp skyrpc ${LIBS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/example)
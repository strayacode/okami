set(KERNEL_SOURCES
    kernel.c
    boot.s
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-T${CMAKE_SOURCE_DIR}/kernel/linker.ld")

message(${CMAKE_BINARY_DIR})

add_executable(kernel ${KERNEL_SOURCES})
set_target_properties(kernel PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/kernel/linker.ld)
set_target_properties(kernel PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
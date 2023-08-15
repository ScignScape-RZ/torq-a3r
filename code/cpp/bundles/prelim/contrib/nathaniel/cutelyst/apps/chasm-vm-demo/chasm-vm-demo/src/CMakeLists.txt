file(GLOB_RECURSE chasm_vm_demo_SRCS *.cpp *.h)

set(chasm_vm_demo_SRCS
 ${chasm_vm_demo_SRCS}
 ${TEMPLATES_SRC}
)

# Create the application
add_library(chasm_vm_demo SHARED ${chasm_vm_demo_SRCS})

# Link to Cutelyst
target_link_libraries(chasm_vm_demo
 Cutelyst::Core
 Qt5::Core
 Qt5::Network
)


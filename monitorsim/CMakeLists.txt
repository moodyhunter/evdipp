set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6Widgets)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

set(monitorsim_SOURCES
  monitorsim.cpp
  qevdiscreen.cpp
  screenpreview.cpp
)

add_executable(monitorsim ${monitorsim_SOURCES})
target_include_directories(monitorsim PRIVATE
  ../
)
target_link_libraries(monitorsim Qt6::Widgets evdipp)

install(TARGETS monitorsim RUNTIME DESTINATION bin)

set(libevdipp_SOURCES
  buffer.cpp
  evdi.cpp
  screen.cpp
)
add_library(evdipp STATIC ${libevdipp_SOURCES})

install(TARGETS evdipp
  ARCHIVE DESTINATION lib
)
install(FILES buffer.hpp screen.hpp evdi.hpp
  DESTINATION include/libevdipp
)
target_include_directories(evdipp PUBLIC ../evdi/library)
target_link_libraries(evdipp PUBLIC -levdi)

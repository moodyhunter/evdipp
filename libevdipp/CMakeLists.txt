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
target_link_libraries(evdipp PUBLIC evdi_lib)
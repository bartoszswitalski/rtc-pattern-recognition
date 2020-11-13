link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(
	${GTKMM_INCLUDE_DIRS}
	../include
)

add_executable(disp displayer.cpp displaywindow.cpp pqueue.cpp semaphoreop.cpp)

target_link_libraries(disp ${GTKMM_LIBRARIES})

set (TARGET_NAME sm_viewer)

file (GLOB SOURCE_FILES *.cpp)
file (GLOB HEADER_FILES *.hpp)

include_directories (${CMAKE_CURRENT_SOURCE_DIR} ${SHARE_INCLUDES} ${Boost_INCLUDE_DIRS})

share_add_executable(${TARGET_NAME} SOURCE_FILES HEADER_FILES TRUE)

share_target_link_libraries(${TARGET_NAME} ${PLATFORM_LIBS}  )

share_add_dependency(${TARGET_NAME} ${SHARE_LIBRARIES})


		
		
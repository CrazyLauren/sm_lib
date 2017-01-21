file (GLOB SOURCE_FILES *.cpp)
file (GLOB HEADER_FILES *.hpp)

set (TARGET_NAME example_sm_server)
include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(${LOGGING_DEFENITIONS})
add_executable (${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})
#add_dependencies(${TARGET_NAME} ${SHARE_TARGET_NAME})
include_directories (${SHARE_INCLUDES} ${LOGGING_INCLUDES} ${Boost_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} ${PLATFORM_LIBS} ${SHARE_LIBRARIES} )


install (TARGETS ${TARGET_NAME} 
             RUNTIME DESTINATION "bin" )	


		
		
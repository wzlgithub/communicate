ADD_EXECUTABLE(commute main.cpp clientNet.cpp motion_state.cpp)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)                                   
INCLUDE_DIRECTORIES(../include)


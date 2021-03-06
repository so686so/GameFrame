CMAKE_MINIMUM_REQUIRED( VERSION 3.16 )
PROJECT( GameByC )

# Compile Option #
ADD_COMPILE_OPTIONS( -W -Wall )
SET ( CMAKE_C_COMPILER "gcc" )

# SET VAR #
SET( ROOT       ${CMAKE_CURRENT_LIST_DIR}/.. )
SET( LIB_DIR    ${ROOT}/lib )
SET( INC_DIR    ${ROOT}/inc )
SET( MAIN_DIR   ${ROOT}/main )
SET( INS_DIR    ${ROOT}/out )
SET( OUTPUT     runFile )

# Main Source Files #
SET( SOURCE     ${MAIN_DIR}/main.c )

# Library Files #
ADD_LIBRARY( basic  ${LIB_DIR}/basic.c )
ADD_LIBRARY( key    ${LIB_DIR}/key.c )
ADD_LIBRARY( map    ${LIB_DIR}/map.c )
ADD_LIBRARY( user   ${LIB_DIR}/user.c )

# Set Library List # 
SET( LIB_NAME basic key map user )

# Include #
INCLUDE_DIRECTORIES( ${INC_DIR} )

# Build Setting #
ADD_EXECUTABLE( ${OUTPUT} ${SOURCE} )

# # Library Link #
TARGET_LINK_LIBRARIES( map       PRIVATE  basic       )
TARGET_LINK_LIBRARIES( user      PRIVATE  map         )
TARGET_LINK_LIBRARIES( ${OUTPUT} PUBLIC   ${LIB_NAME} )

# # Install #
INSTALL( TARGETS ${OUTPUT} DESTINATION ${INS_DIR} )
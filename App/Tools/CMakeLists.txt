### 	VARIABLES	 ###
set(TOOLS_NAME "Tools")

set(TOOLS_PRIVATE "Source/Private/${TOOLS_NAME}/")
set(TOOLS_PUBLIC "Source/Public/${TOOLS_NAME}/")

set(TOOLS_SOURCES
	${TOOLS_PUBLIC}Tools.h		${TOOLS_PRIVATE}Tools.cpp
	${TOOLS_PUBLIC}Singelton.h		${TOOLS_PRIVATE}Singelton.cpp
	${TOOLS_PUBLIC}RKeyCodes.h
)

# creer les fichier qui n'existe pas dans la liste MOTEUR_SOURCES
create_non_existing("${TOOLS_SOURCES}" "${CMAKE_CURRENT_SOURCE_DIR}" ${TOOLS_NAME})


### 	FONCTION	 ###
add_library(${TOOLS_NAME} STATIC ${TOOLS_SOURCES}) # pour ajouter les library

# 'source_group' Ensure than Visual Studio Solution respect File Hierarchy in filters
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TOOLS_SOURCES})

target_include_directories(${TOOLS_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Public/"
										 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source/Private/") # pour pouvoir faire les includes dans le projet

### 	VARIABLES	 ###
set(MOTEUR_NAME "Moteur")

set(MOTEUR_PRIVATE "Source/Private/${MOTEUR_NAME}/")
set(MOTEUR_PUBLIC "Source/Public/${MOTEUR_NAME}/")

set(MOTEUR_SOURCES
	${MOTEUR_PRIVATE}main.cpp
	${MOTEUR_PUBLIC}pch.h
	${MOTEUR_PUBLIC}/Tools/Debug/AYCDebugLayer.h		${MOTEUR_PRIVATE}/Tools/Debug/AYCDebugLayer.cpp
	${MOTEUR_PUBLIC}/Tools/Debug/AYCLog.h		${MOTEUR_PRIVATE}/Tools/Debug/AYCLog.cpp
	${MOTEUR_PUBLIC}/Tools/Debug/AYC_Context.h		${MOTEUR_PRIVATE}/Tools/Debug/AYC_Context.cpp
	${MOTEUR_PUBLIC}/Handler/WindowHandler.h		${MOTEUR_PRIVATE}/Handler/WindowHandler.cpp
)

# creer les fichier qui n'existe pas dans la liste MOTEUR_SOURCES
create_non_existing("${MOTEUR_SOURCES}" "${CMAKE_CURRENT_SOURCE_DIR}" ${MOTEUR_NAME})

### 	FONCTION	 ###
add_executable(${MOTEUR_NAME} ${MOTEUR_SOURCES}) # pour ajouter l'executable

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${MOTEUR_NAME} PROPERTY CXX_STANDARD 20)
endif() # pour etre sur d'etre a jour de cmake

configure_file("CMake_Source/Public/Gen_App/Config/AppConfig.h.in" "Gen_SRC/Public/Gen_App/Config/AppConfig.h")

target_link_libraries(${MOTEUR_NAME} PUBLIC "Tools" "d3d12.lib" "dxgi.lib" "dxguid.lib") # pour rajouter la librairie a l'executable

target_include_directories(${MOTEUR_NAME} PUBLIC "${PROJECT_BINARY_DIR}/${MOTEUR_NAME}/Gen_SRC/Public/"
												 "${CMAKE_CURRENT_SOURCE_DIR}/Source/Public/"
										 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source/Private/") # pour pouvoir faire les includes dans le projet
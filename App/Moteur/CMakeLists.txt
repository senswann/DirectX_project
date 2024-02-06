### 	VARIABLES	 ###
set(MOTEUR_NAME "Moteur")

set(MOTEUR_PRIVATE "Source/Private/${MOTEUR_NAME}/")
set(MOTEUR_PUBLIC "Source/Public/${MOTEUR_NAME}/")

set(MOTEUR_SOURCES
	${MOTEUR_PRIVATE}main.cpp
)

### 	FONCTION	 ###
add_executable(${MOTEUR_NAME} ${MOTEUR_SOURCES}) # pour ajouter l'executable

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${MOTEUR_NAME} PROPERTY CXX_STANDARD 20)
endif() # pour etre sur d'etre a jour de cmake

target_link_libraries(${MOTEUR_NAME} PUBLIC "Tools") # pour rajouter la librairie a l'executable

target_include_directories(${MOTEUR_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Public/"
										 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source/Private/") # pour pouvoir faire les includes dans le projet
### 	VARIABLES	 ###
set(MOTEUR_NAME "Moteur")

set(MOTEUR_PRIVATE "Source/Private/${MOTEUR_NAME}/")
set(MOTEUR_PUBLIC "Source/Public/${MOTEUR_NAME}/")

set(MOTEUR_SOURCES
	${MOTEUR_PRIVATE}main.cpp
	${MOTEUR_PUBLIC}pch.h
	 ${MOTEUR_PUBLIC}Geometry/AYCTransform3D.h						${MOTEUR_PRIVATE}Geometry/AYCTransform3D.cpp
	${MOTEUR_PUBLIC}Geometry/AYCShaderStructs3D.h					${MOTEUR_PRIVATE}Geometry/AYCShaderStructs3D.cpp
	${MOTEUR_PUBLIC}Geometry/AYCMesh3D.h							${MOTEUR_PRIVATE}Geometry/AYCMesh3D.cpp
	${MOTEUR_PUBLIC}Geometry/AYCBasicShapFactory.h							${MOTEUR_PRIVATE}Geometry/AYCBasicShapFactory.cpp
	${MOTEUR_PUBLIC}/Tools/Shader.h									${MOTEUR_PRIVATE}/Tools/Shader.cpp
	${MOTEUR_PUBLIC}/Tools/Debug/AYCDebugLayer.h					${MOTEUR_PRIVATE}/Tools/Debug/AYCDebugLayer.cpp
	${MOTEUR_PUBLIC}/Tools/Debug/AYCLog.h							${MOTEUR_PRIVATE}/Tools/Debug/AYCLog.cpp
	${MOTEUR_PUBLIC}/Tools/Debug/AYC_Context.h						${MOTEUR_PRIVATE}/Tools/Debug/AYC_Context.cpp
	${MOTEUR_PUBLIC}/Handler/WindowHandler.h						${MOTEUR_PRIVATE}/Handler/WindowHandler.cpp
	${MOTEUR_PUBLIC}/Handler/Pipeline/AYCPipelineHandler3D.h		${MOTEUR_PRIVATE}/Handler/Pipeline/AYCPipelineHandler3D.cpp
)

set(MOTEUR_SOURCES_SHADER_PIPELINE
  ${MOTEUR_PRIVATE}/Shaders/BasicPipeline3D.hlsli
)
set(MOTEUR_SOURCES_SHADER_ROOTSIG
  ${MOTEUR_PRIVATE}/Shaders/BasicRootSignature3D.hlsl
)

# List of included shaders
set(MOTEUR_SOURCES_SHADER_VERTEX
  ${MOTEUR_PRIVATE}/Shaders/Basic3DVS.hlsl
)
# List of included shaders
set(MOTEUR_SOURCES_SHADER_PIXEL
  ${MOTEUR_PRIVATE}/Shaders/Basic3DPS.hlsl
)

set(MOTEUR_SOURCES_SHADER_ALL ${MOTEUR_SOURCES_SHADER_PIPELINE} ${MOTEUR_SOURCES_SHADER_ROOTSIG} ${MOTEUR_SOURCES_SHADER_VERTEX} ${MOTEUR_SOURCES_SHADER_PIXEL})

### 	FONCTION	 ###
# creer les fichier qui n'existe pas dans la liste MOTEUR_SOURCES
create_non_existing("${MOTEUR_SOURCES}" "${CMAKE_CURRENT_SOURCE_DIR}" ${MOTEUR_NAME})
create_non_existing("${MOTEUR_SOURCES_SHADER_ALL}" "${CMAKE_CURRENT_SOURCE_DIR}" ${MOTEUR_NAME})

add_executable(${MOTEUR_NAME} ${MOTEUR_SOURCES} ${MOTEUR_SOURCES_SHADER_ALL}) # pour ajouter l'executable

#  VS_SHADER_ENTRYPOINT main_vert # To Set Entry function name
set_source_files_properties(${MOTEUR_SOURCES_SHADER_ROOTSIG} PROPERTIES VS_SHADER_MODEL rootsig_1.1 VS_SHADER_TYPE RootSignature)
set_source_files_properties(${MOTEUR_PRIVATE}Shaders/BasicRootSignature3D.hlsl PROPERTIES VS_SHADER_ENTRYPOINT ROOTSIG3D)

set_source_files_properties(${MOTEUR_SOURCES_SHADER_PIPELINE} PROPERTIES VS_SHADER_MODEL 6.0)
set_source_files_properties(${MOTEUR_SOURCES_SHADER_VERTEX} PROPERTIES VS_SHADER_MODEL 6.0 VS_SHADER_TYPE Vertex)
set_source_files_properties(${MOTEUR_SOURCES_SHADER_PIXEL} PROPERTIES VS_SHADER_MODEL 6.0 VS_SHADER_TYPE Pixel)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${MOTEUR_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${MOTEUR_SOURCES_SHADER_ALL})

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${MOTEUR_NAME} PROPERTY CXX_STANDARD 20)
endif() # pour etre sur d'etre a jour de cmake

configure_file("CMake_Source/Public/Gen_App/Config/AppConfig.h.in" "Gen_SRC/Public/Gen_App/Config/AppConfig.h")

target_link_libraries(${MOTEUR_NAME} PUBLIC "Tools" "d3d12.lib" "dxgi.lib" "dxguid.lib") # pour rajouter la librairie a l'executable

target_include_directories(${MOTEUR_NAME} PUBLIC "${PROJECT_BINARY_DIR}/${MOTEUR_NAME}/Gen_SRC/Public/"
												 "${CMAKE_CURRENT_SOURCE_DIR}/Source/Public/"
										 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source/Private/") # pour pouvoir faire les includes dans le projet
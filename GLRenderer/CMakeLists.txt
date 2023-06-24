target_sources(yttrium PRIVATE ${CMAKE_CURRENT_LIST_DIR}/GLShaderManager.cpp
                       PRIVATE ${CMAKE_CURRENT_LIST_DIR}/GLWindow.cpp
                       PRIVATE ${CMAKE_CURRENT_LIST_DIR}/GLRenderer.cpp
                       PRIVATE ${CMAKE_CURRENT_LIST_DIR}/GLShaderSetup.cpp
                       
                       PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Texture/GLTextureAtlas.cpp
                       PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Texture/GLTextureManager.cpp
                       
                       PRIVATE ${CMAKE_CURRENT_LIST_DIR}/GLResourceManager.cpp)

include(${CMAKE_CURRENT_LIST_DIR}/Resources/CMakeLists.txt)
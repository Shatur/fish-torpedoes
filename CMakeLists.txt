cmake_minimum_required(VERSION 3.6)

set(APP_NAME FishTorpedoes)
project(${APP_NAME})

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
if(NOT USE_COCOS_PREBUILT)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif()

# Fix compiling freetype on Linux
if(LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")
endif()

set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# Source
list(APPEND GAME_SOURCE
    Classes/AppDelegate.cpp
    Classes/ConfigParser.cpp
    Classes/Scenes/SplashScene.cpp
    Classes/Scenes/MainMenuScene.cpp
    Classes/Scenes/SettingsScene.cpp
    Classes/Scenes/GameScene.cpp
    Classes/Scenes/PauseScene.cpp
    Classes/Scenes/EndScene.cpp
    Classes/Objects/Background.cpp
    Classes/Objects/Fish.cpp
    Classes/Objects/KillerFish.cpp
    Classes/Objects/Torpedo.cpp
    )

# Headers
list(APPEND GAME_HEADER
    Classes/AppDelegate.h
    Classes/ConfigParser.h
    Classes/Scenes/SplashScene.h
    Classes/Scenes/MainMenuScene.h
    Classes/Scenes/SettingsScene.h
    Classes/Scenes/GameScene.h
    Classes/Scenes/PauseScene.h
    Classes/Scenes/EndScene.h
    Classes/Objects/Background.h
    Classes/Objects/Fish.h
    Classes/Objects/KillerFish.h
    Classes/Objects/Torpedo.h
    )

if(LINUX)
    list(APPEND GAME_SOURCE
        Linux/Main.cpp
        )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
        Windows/Main.h
        Windows/Resource.h
        )
    list(APPEND GAME_SOURCE
        Windows/Main.cpp
        Windows/Game.rc
        ${common_res_files}
        )
endif()

# Mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )

add_executable(${APP_NAME} ${all_code_files})

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
    PRIVATE Classes
    PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
    )

# Mark app resources
setup_cocos_app_config(${APP_NAME})
if(WINDOWS)
    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_RES_DIR}/..)
endif()

cocos_copy_res(COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})


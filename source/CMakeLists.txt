## The game library that forms the core of the game ##
set (LIB_NAME GameLib)
set (LIB_NAME ${LIB_NAME} PARENT_SCOPE)

project(${LIB_NAME}
        DESCRIPTION "The game library used to power this epic game"
        LANGUAGES CXX)

## glob is useful but not reliant in compilation so just use it for headers ##
file(GLOB_RECURSE HEADER_LIST
        LIST_DIRECTORIES TRUE
        CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/include/*.hpp
        ${CMAKE_SOURCE_DIR}/include/*.h)

## make an automatic library - will be static or dynamic based on user setting ##
add_library(
        ${LIB_NAME} ${HEADER_LIST}
        ## add your CPP files here ##
        components/GameObject.cpp
        components/Rect.cpp
        components/SpriteComponent.cpp
        components/Vector.cpp
        components/GCNetClient.cpp
        components/GCNetServer.cpp
        components/StateSystem/State.cpp
        components/StateSystem/MenuState.cpp
        components/GameData.cpp
        components/Random.cpp
        components/StateSystem/StartUpState.cpp
        components/StateSystem/OptionsState.cpp
        components/StateSystem/LobbyState.cpp
        components/StateSystem/InWorldState.cpp
        components/StateSystem/InBattleState.cpp
        components/UISystem/UIManager.cpp
        components/UISystem/UIObject.cpp
        components/UISystem/UIPanel.cpp
        components/UISystem/UIButton.cpp
        components/UISystem/UILabel.cpp
        components/UISystem/UITextBox.cpp
        components/TileComponent.cpp
        components/ObjectPooler.cpp
        components/ParticleComponent.cpp
        components/Scenes/MapScene.cpp
        components/Scenes/DungeonScene.cpp
        components/Player/Entity.cpp
        components/Player/Enemy.cpp
        components/Player/Inventory.cpp
        components/Player/Weapon.cpp
        components/Player/Utility.cpp
        components/Handlers/WeaponHandler.cpp
        components/Handlers/TurnHandler.cpp
        components/Handlers/UtilityHandler.cpp
        components/Handlers/TreasureHandler.cpp
        components/Handlers/EnemyHandler.cpp
        components/StateSystem/StateManager.cpp
        components/StateSystem/State.cpp
        components/StateSystem/StartUpState.cpp
        components/Sound/Sound.cpp
        components/Sound/SoundManager.cpp
        components/Sound/PlayList.cpp
        components/Lobby.cpp
        components/Command.cpp
        components/Player/PlayerClasses.cpp ../include/gamelib/Player/PlayerClasses.h)


set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${LIB_NAME} PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(${LIB_NAME} PROPERTIES CXX_CLANG_TIDY ${CLANG_TIDY})

## we need this directory, and users of our library will need it too ##
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

## all users of this library will need at least C++17 ##
target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)

## IDEs should put the headers in a nice place ##
source_group(TREE "${CMAKE_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})

## helper scripts for this game library ##
include(libs/netlib)

## logging levels for library ##
target_compile_definitions(
        ${LIB_NAME} PRIVATE
        "$<$<CONFIG:Debug>:LOGGING_LEVEL_DEBUG>"
        "$<$<CONFIG:Release>:LOGGING_LEVEL_ERROR>")

## enable compiler warnings and debug flags ##
target_compile_options(
        ${LIB_NAME} PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:${BUILD_FLAGS_FOR_CXX}>
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Debug>>:${DEBUG_BUILD_FLAGS_FOR_CXX}>)

## if sound is enabled link against the soloud libs ##
if (ENABLE_SOUND)
    add_dependencies(${LIB_NAME} soloud)
    target_link_libraries(${LIB_NAME} PRIVATE soloud)
endif()

## enable json support if enabled ##
if (ENABLE_JSON)
    add_dependencies(${LIB_NAME} jsonlib)
    target_link_libraries(${LIB_NAME} PUBLIC jsonlib)
endif()


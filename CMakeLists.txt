cmake_minimum_required(VERSION 3.12)
project(kappapride)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "sfml/lib/cmake/SFML")
set(CMAKE_FIND_LIBRARY_SUFFIXES  ".a")
set(BUILD_SHARED_LIBS OFF)
#set(CMAKE_EXE_LINKER_FLAGS -static)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SORCE_DIR}/Install CACHE PATH "install here" FORCE)
find_package(SFML 2.5.1 COMPONENTS graphics audio window system REQUIRED)

add_executable(kappapride main.cpp
        App/App.cpp App/App.h App/Team.cpp App/Import.cpp App/AI.cpp App/AI.h
        StateMachine/State.h StateMachine/Machine.cpp StateMachine/Machine.h
        GameObjects/Object.cpp GameObjects/Object.h
        GameObjects/Entities/Entity.cpp GameObjects/Entities/Entity.h
        GameObjects/Entities/Building.cpp GameObjects/Entities/Building.h
        GameObjects/Entities/Unit.cpp GameObjects/Entities/Unit.h
        GameObjects/Entities/Spell.cpp GameObjects/Entities/Spell.h

        GameObjects/Effects/Effect.cpp GameObjects/Effects/Effect.h
        GameObjects/Effects/Ability.cpp GameObjects/Effects/Ability.h
        GameObjects/Effects/Upgrade.cpp GameObjects/Effects/Upgrade.h

        GameObjects/Spaces/Space.cpp GameObjects/Spaces/Space.h
        GameObjects/Spaces/Node.cpp GameObjects/Spaces/Node.h
        GameObjects/Spaces/Lane.cpp GameObjects/Spaces/Lane.h

        GameObjects/Interface/Interface.cpp GameObjects/Interface/Interface.h
        GameObjects/Interface/Button.cpp GameObjects/Interface/Button.h
        GameObjects/Interface/Text.cpp GameObjects/Interface/Text.h
        GameObjects/Interface/Buttons/ButtonUnit.cpp GameObjects/Interface/Buttons/ButtonUnit.h
        GameObjects/Interface/Buttons/ButtonBuild.cpp GameObjects/Interface/Buttons/ButtonBuild.h
        GameObjects/Interface/Buttons/ButtonUpgrade.cpp GameObjects/Interface/Buttons/ButtonUpgrade.h
        GameObjects/Interface/Buttons/ButtonTexture.cpp GameObjects/Interface/Buttons/ButtonTexture.h

        GameObjects/Mouse.cpp GameObjects/Mouse.h
        Pathing/Pathing.cpp Pathing/PathData.h
        Pathing/Heap.h
        Pathing/Pathfinder.cpp Pathing/Pathfinder.h
        StateMachine/States/stateStart.cpp StateMachine/States/stateStart.h
        StateMachine/States/stateMenu.cpp StateMachine/States/stateMenu.h
        StateMachine/States/stateSplash.cpp StateMachine/States/stateSplash.h
        StateMachine/States/stateSettings.cpp StateMachine/States/stateSettings.h
        StateMachine/States/statePause.cpp StateMachine/States/statePause.h
        StateMachine/States/stateGameEnd.cpp StateMachine/States/stateGameEnd.h

        Layer/Layer.cpp Layer/Layer.h
        Map/Map.cpp Map/Map.h
        Sprite/Sprite.cpp Sprite/Sprite.h
        tools/tools.cpp tools/tools.h)


target_link_libraries (kappapride sfml-graphics sfml-window sfml-audio sfml-system jsoncpp thor)
#target_link_libraries(kappapride libstd++-6 libgcc_s_seh-1 -static)
add_custom_target(test SORCES )

#install(TARGETS kappapride DESTINATION deb CONFIGURATIONS Debug)
install(TARGETS kappapride DESTINATION rel CONFIGURATIONS Release)
install(FILES ${JSON} ${THOR} DESTINATION rel)
install(DIRECTORY Fonts res MusicAndSound MapData DESTINATION rel)
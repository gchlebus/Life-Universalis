include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Eigen_INCLUDE_DIRS})

#define groups
source_group(Game\\GameEnvironment\\DayTime DayTimeEntity.*)
source_group(Game\\GameEnvironment\\Managers\\BuildingManager BuildingManagerEntity.*)
source_group(Game\\GameEnvironment\\Managers\\HumanManager HumanManagerEntity.*)
source_group(Game\\GameObjectComponents\\Building\\Test BuildingTestComponent.*)
source_group(Game\\GameObjectComponents\\Human\\AI\\HumanAIComponent HumanAIComponent.*)
source_group(Game\\GameObjectComponents\\Human\\LifeParameters HumanParametersComponent.*)
source_group(Game\\Transform Transform.*)

source_group(GameEngine\\Kernel\\Settings Settings.*)
source_group(GameEngine\\Kernel\\Timer Timer.*)
source_group(GameEngine\\Kernel Kernel.*)
source_group(GameEngine\\Scene\\GameEnvironment\\GameEnvironmentEntity GameEnvironmentEntity.*)
source_group(GameEngine\\Scene\\GameEnvironment GameEnvironment.*)
source_group(GameEngine\\Scene\\GameObject\\GameObjectComponent GameObjectComponent.*)
source_group(GameEngine\\Scene\\GameObject GameObject.*)
source_group(GameEngine\\Scene Scene.*)
source_group(GameEngine GameEngine.*)

#gather all *.h and *.cpp files
file(GLOB SRC *.h *.cpp)

add_library(LifeUniversalis SHARED ${SRC})
target_link_libraries(LifeUniversalis ${Boost_LIBRARIES})

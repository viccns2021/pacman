project(pacman)
add_executable(${PROJECT_NAME} camera.cpp cube.cpp ground.cpp main.cpp pacman.cpp window.cpp)
enable_abcg(${PROJECT_NAME})

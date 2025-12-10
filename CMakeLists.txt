cmake_minimum_required(VERSION 3.21)
project(EmotionPieChart VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.10 REQUIRED COMPONENTS Widgets Designer)

add_library(EmotionPieChartWidget STATIC
    src/EmotionPieChartWidget.cpp
    src/EmotionPieChartWidget.h
)

target_link_libraries(EmotionPieChartWidget PRIVATE Qt6::Widgets)

target_include_directories(EmotionPieChartWidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

auto_moc_target_dependencies(EmotionPieChartWidget)

add_library(EmotionPieChartDesignerPlugin SHARED
    src/EmotionPieChartPlugin.cpp
    src/EmotionPieChartPlugin.h
)

target_link_libraries(EmotionPieChartDesignerPlugin PRIVATE Qt6::Designer EmotionPieChartWidget Qt6::Widgets)

target_include_directories(EmotionPieChartDesignerPlugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(EmotionPieChartDesignerPlugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/designer
)

auto_moc_target_dependencies(EmotionPieChartDesignerPlugin)

add_executable(EmotionPieChartDemo
    demo/main.cpp
)

target_link_libraries(EmotionPieChartDemo PRIVATE EmotionPieChartWidget Qt6::Widgets)

auto_moc_target_dependencies(EmotionPieChartDemo)

install(TARGETS EmotionPieChartWidget EmotionPieChartDesignerPlugin
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION plugins/designer
    ARCHIVE DESTINATION lib
)

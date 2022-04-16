cmake_minimum_required(VERSION 3.14)

project(test_appstream LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
include(FeatureSummary)

find_package(Qt5 5.15 CONFIG REQUIRED COMPONENTS Core)
find_package(AppStreamQt 0.15 CONFIG REQUIRED)

add_executable(test_appstream
    main.cpp
)

target_link_libraries(test_appstream PRIVATE
    Qt5::Core
    AppStreamQt
)

install(TARGETS test_appstream
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/test_appstream
)

feature_summary(INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES WHAT ALL)

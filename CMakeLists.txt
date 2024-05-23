cmake_minimum_required(VERSION 3.12)

project(Phys)


add_executable(Phys
	src/main.cpp
)

target_include_directories(Phys PUBLIC include)

target_compile_features(Phys PUBLIC cxx_std_20)

find_package(Siv3D)
target_link_libraries(Phys PUBLIC Siv3D::Siv3D)

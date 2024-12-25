find_package(SDL3 CONFIG REQUIRED)

if(WIN32)
	find_package(directxtk CONFIG REQUIRED)
else()

endif()

add_executable (${PROJECT_NAME} "main.cpp" "renderer.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE "main.hpp")

if(WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE 
		SDL3::SDL3
		d3d11
		dxgi
		d3dcompiler
		Microsoft::DirectXTK
	)
else()

endif()

if(WIN32)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
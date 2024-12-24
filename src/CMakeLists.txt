#find_package(SDL2 CONFIG REQUIRED)

if(WIN32)
	#find_package(directxtk CONFIG REQUIRED)
endif()

add_executable (${PROJECT_NAME} "main.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE "main.hpp")

if(WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE 
		#SDL2::SDL2main
		#SDL2::SDL2
		d3d11
		dxgi
		d3dcompiler
		#Microsoft::DirectXTK
	)
endif()

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
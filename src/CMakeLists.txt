find_package(SDL3 CONFIG REQUIRED)

if(WIN32)
	find_package(directxtk CONFIG REQUIRED)

	add_executable (${PROJECT_NAME} "main.cpp" "windows_renderer.cpp")

	target_link_libraries(${PROJECT_NAME} PRIVATE 
		SDL3::SDL3
		d3d11
		dxgi
		d3dcompiler
		Microsoft::DirectXTK
	)

	target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
elseif(UNIX)
	find_package(glm CONFIG REQUIRED)

	add_executable (${PROJECT_NAME} "main.cpp" "linux_renderer.cpp")

	target_link_libraries(${PROJECT_NAME} PRIVATE 
		SDL3::SDL3
		glm::glm
	)

	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE src)
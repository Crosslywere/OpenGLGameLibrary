workspace "OpenGLGameLibrary"
	configurations { "Debug", "Release" }
	platforms "x64"

	startproject "GameLibrary"

	project "glfw"
		location "vendors/glfw"
		kind "StaticLib"
		language "C"
		cdialect "C17"
		targetdir "bin/%{prj.name}"
		objdir "obj/%{prj.name}"
		files {
			"vendors/glfw/src/**.c",
			"vendors/glfw/include/**.h"
		}
		vpaths {
			["Header"] = "**.h",
			["Source"] = "**.c"
		}
		defines { "_GLFW_WIN32", "_CRT_SECURE_NO_WARNINGS" }

	project "GameLibrary"
		location "%{prj.name}"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		targetdir "bin/%{prj.name}"
		objdir "obj/%{prj.name}"
		files {
			"%{prj.name}/**.h",
			"%{prj.name}/**.cpp",
			"vendors/glad/src/glad.c"
		}
		vpaths {
			["Header"] = "**.h",
			["Source"] = { "**.c", "**.cpp" }
		}
		includedirs {
			"%{prj.name}/include",
			"vendors/glad/include",
			"vendors/glfw/include",
			"vendors/glm"
		}
		links "glfw"

		filter "configurations:Debug"
			defines "DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "NDEBUG"
			optimize "On"

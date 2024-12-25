workspace "OpenGLGameLibrary"
	configurations { "Debug", "Release" }
	platforms "x64"

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
			"vendors/glm"
		}

		filter "configurations:Debug"
			defines "DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "NDEBUG"
			optimize "On"

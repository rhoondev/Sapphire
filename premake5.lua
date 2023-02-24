workspace "Sapphire"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Sapphire/vendor/GLFW"

project "Sapphire"
	location "Sapphire"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "sppch.h"
	pchsource "Sapphire/src/sppch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"Sapphire/vendor/GLFW/include"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SP_PLATFORM_WINDOWS",
			"SP_BUILD_DLL"
		}

		postbuildcommands
		{
			--"{COPYFILE} ../bin/" .. outputdir .. "/Sapphire/Sapphire.dll ../bin/" .. outputdir .. "/Sandbox"
			"copy /B /Y ..\\bin\\" .. outputdir .. "\\Sapphire\\Sapphire.dll ..\\bin\\" .. outputdir .. "\\Sandbox\\ > nul"
		}
	
	filter "configurations:Debug"
		defines "SP_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "SP_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "SP_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Sapphire/vendor/spdlog/include",
		"Sapphire/src"
	}

	links
	{
		"Sapphire"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SP_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "SP_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "SP_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "SP_DIST"
		buildoptions "/MD"
		optimize "On"
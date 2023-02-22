workspace "Sapphire"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SAPPHIRE_PLATFORM_WINDOWS",
			"SAPPHIRE_BUILD_DLL"
		}

		postbuildcommands
		{
			"{COPYDIR} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
			--("copy /B /Y ..\\bin\\" .. outputdir .. "\\Hazel\\Hazel.dll ..\\bin\\" .. outputdir .. "\\Sandbox\\ > nul")
		}
	
	filter "configurations:Debug"
		defines "SAPPHIRE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SAPPHIRE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SAPPHIRE_DIST"
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
			"SAPPHIRE_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "SAPPHIRE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SAPPHIRE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SAPPHIRE_DIST"
		optimize "On"
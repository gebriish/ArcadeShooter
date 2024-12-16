project "GLAD"
	kind "StaticLib"
	language "C"
	staticruntime "off"
	
	targetdir "%{wks.location}/bin/%{cfg.name}"
	objdir    "%{wks.location}/obj/%{cfg.name}"

	files {
		"GLAD/src/glad.c"
	}

	includedirs {
		"GLAD/include"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		runtime "Release"
		optimize "speed"

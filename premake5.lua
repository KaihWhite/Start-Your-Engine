workspace "Start-Your-Engine"
   configurations { "Debug", "Release" }
   startproject "Start-Your-Engine"
   architecture "x64"

   -- Path to the Dependencies directory
   IncludeDir = {}
   IncludeDir["GLFW"] = "Dependencies/GLFW"  -- Base GLFW path
   IncludeDir["Glad"] = "Dependencies/Glad/include"
   IncludeDir["glm"] = "Dependencies/glm"

project "Start-Your-Engine"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
   objdir "bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"

   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

   -- Windows specific include and lib directories
   filter "system:windows"
      includedirs { "include", IncludeDir["GLFW"] .. "/Windows/include", IncludeDir["Glad"], IncludeDir["glm"] }
      libdirs { IncludeDir["GLFW"] .. "/Windows/lib-vc2022" }
      systemversion "latest"
      defines { "PLATFORM_WINDOWS" }
      links { "glfw3_mt", "Glad", "opengl32" }
      staticruntime "On"

   -- MacOS specific include and lib directories
   filter "system:macosx"
      includedirs { "include", IncludeDir["GLFW"] .. "/MacOS/include", IncludeDir["Glad"], IncludeDir["glm"] }
      libdirs { IncludeDir["GLFW"] .. "/MacOS/lib-arm64" }
      architecture "arm64" -- or "x64" for Intel, "arm64" for M1 specifically, or "universal"
      systemversion "latest"
      defines { "PLATFORM_MACOS" }
      links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework" }
      staticruntime "On"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      runtime "MDd"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      runtime "MD"

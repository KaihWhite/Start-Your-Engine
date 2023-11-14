workspace "Start-Your-Engine"
   configurations { "Debug", "Release" }
   startproject "Start-Your-Engine"

   -- Path to the Dependencies directory
   IncludeDir = {}
   IncludeDir["GLFW"] = "Dependencies/GLFW"  -- Base GLFW path
   IncludeDir["Glad"] = "Dependencies/GLAD/include"
   IncludeDir["glm"] = "Dependencies/glm"
   IncludeDir["box2D"] = "Dependencies/box2D/include"

project "Start-Your-Engine"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   staticruntime "on"

   targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
   objdir "bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"

   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp", "%{prj.name}/src/**.c" }

   -- Windows specific settings
   filter "system:windows"
      includedirs { "%{prj.name}/src", "Dependencies", IncludeDir["GLFW"] .. "/Windows/include/GLFW", IncludeDir["Glad"], IncludeDir["glm"], IncludeDir["box2D"] }
      libdirs { IncludeDir["GLFW"] .. "/Windows/lib-vc2022", IncludeDir["Glad"] }
      architecture "x64"
      systemversion "latest"
      defines { "PLATFORM_WINDOWS" }
      links { "glfw3_mt", "Glad", "opengl32" }

   -- MacOS specific settings
   filter "system:macosx"
      includedirs { "%{prj.name}/src", "Dependencies", IncludeDir["GLFW"] .. "/MacOS/include", IncludeDir["Glad"], IncludeDir["glm"], IncludeDir["box2D"] }
      libdirs { IncludeDir["GLFW"] .. "/MacOS/lib-arm64" }
      links { "glfw3", "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework" }
      architecture "arm64" -- or "x64" for Intel, "arm64" for M1 specifically, or "universal"
      systemversion "latest"
      defines { "PLATFORM_MACOS" }

   -- General settings for Debug and Release configurations
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

   filter {"system:windows", "configurations:Release"}
      buildoptions "/MT"
   filter {"system:windows", "configurations:Debug"}
      buildoptions "/MTd"

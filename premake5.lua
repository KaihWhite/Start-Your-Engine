workspace "Start-Your-Engine"
   configurations { "Debug", "Release" }
   startproject "Start-Your-Editor"

   -- Path to the Dependencies directory
   IncludeDir = {}
   IncludeDir["GLFW"] = "Dependencies/GLFW"  -- Base GLFW path
   IncludeDir["Glad"] = "Dependencies/GLAD/include"
   IncludeDir["glm"] = "Dependencies/glm"
   IncludeDir["box2d"] = "Dependencies/box2d/include"
   IncludeDir["Start-Your-Engine"] = "Start-Your-Engine/src"
   IncludeDir["imgui"] = "Dependencies/imgui/include"

project "Start-Your-Editor"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   staticruntime "on"

   targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
   objdir "bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"

   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp", "%{prj.name}/src/**.c","Dependencies/imgui/include/*.h","Dependencies/imgui/src/*.cpp" }

   -- Windows specific settings
   filter "system:windows"
      includedirs {IncludeDir["GLFW"] .. "/Windows/include",IncludeDir["imgui"], IncludeDir["Start-Your-Engine"]}
      libdirs {IncludeDir["GLFW"] .. "/Windows/lib-vc2022"}
      architecture "x64"
      systemversion "latest"
      defines { "PLATFORM_WINDOWS" }
      links {"glfw3_mt","Start-Your-Engine"}

      
   -- MacOS specific settings
   -- filter "system:macosx"
   --    includedirs { IncludeDir["GLFW"] .. "/MacOS/include",IncludeDir["imgui"],IncludeDir["Start-Your-Engine"] }
   --    libdirs { IncludeDir["GLFW"] .. "/MacOS/lib-arm64" }
   --    links { "glfw3", "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework","Start-Your-Engine" }
   --    architecture "arm64" -- or "x64" for Intel, "arm64" for M1 specifically, or "universal"
   --    systemversion "latest"
   --    defines { "PLATFORM_MACOS" }

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

project "Start-Your-Engine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   staticruntime "on"

   targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
   objdir "bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"

   files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

   -- Windows specific settings
   filter "system:windows"
      includedirs { IncludeDir["GLFW"] .. "/Windows/include", IncludeDir["Glad"], IncludeDir["glm"], IncludeDir["box2d"] }
      libdirs { IncludeDir["GLFW"] .. "/Windows/lib-vc2022", IncludeDir["box2d"] }
      architecture "x64"
      systemversion "latest"
      defines { "PLATFORM_WINDOWS" }
      links { "glfw3_mt", "opengl32", "box2d"}

   -- MacOS specific settings
   -- filter "system:macosx"
   --    includedirs { IncludeDir["GLFW"] .. "/MacOS/include", IncludeDir["Glad"], IncludeDir["glm"], IncludeDir["box2d"] }
   --    libdirs { IncludeDir["GLFW"] .. "/MacOS/lib-arm64", IncludeDir["box2d"] }
   --    links { "glfw3", "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework" }
   --    architecture "arm64" -- or "x64" for Intel, "arm64" for M1 specifically, or "universal"
   --    systemversion "latest"
   --    defines { "PLATFORM_MACOS" }

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
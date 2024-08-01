workspace "Arcane"
    architecture "x64"
    startproject "ArcaneTest"
    configurations { "Debug", "Release" }
    flags { "MultiProcessorCompile" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {
        Arcane = "Arcane/src",
        tomlpp = "Vendor/toml++/include/"
    }

    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines {
            "ARC_BUILD_DEBUG",
            "ARC_PROFILE"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines {
            "ARC_BUILD_RELEASE"
        }
        runtime "Release"
        optimize "speed"

    function setupProject(projectName, projectKind)
        location(projectName)
        kind(projectKind)

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files {
            "%{prj.location}/src/**.h",
            "%{prj.location}/src/**.cpp",
            "%{prj.location}/src/**.hpp"
        }

        includedirs {
            "%{IncludeDir.Arcane}",
            "%{IncludeDir.tomlpp}",
        }

        defines { "_CRT_SECURE_NO_WARNINGS" }
    end

-- Projects
    project "Arcane"
        setupProject("Arcane", "StaticLib")
        postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/ArcaneTest") }

    project "ArcaneTest"
        setupProject("ArcaneTest", "SharedLib")
        links { "Arcane" }

        filter "system:windows"
            linkoptions { "/SUBSYSTEM:WINDOWS" }

        defines { "ARCANE_TEST_EXPORTS" }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Loom/")
        }

    project "Loom"
        setupProject("Loom", "ConsoleApp")
        links { "Arcane", "ArcaneTest" }

        filter "system:windows"
            linkoptions { "/SUBSYSTEM:WINDOWS", "/ENTRY:wWinMainCRTStartup" }

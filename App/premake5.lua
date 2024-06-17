local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("Application")
kind("ConsoleApp")
language("C++")
cppdialect("C++17")

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../build/" .. outputdir .. "/%{prj.name}")

files({
    "source/**.h",
    "source/**.cpp",
})

includedirs({
    "../Break-Core/source",
    "../vendor/raylib/include",
})

libdirs({
    "../vendor/raylib/lib",
})

links({
    "Break-Core",
    "raylib",
})

postbuildcommands({
    "cp -r assets/ %{cfg.buildtarget.directory}",
})

filter("system:linux")
system("linux")
systemversion("latest")
defines({
    "PLATFORM_LINUX",
})

filter("configurations:Debug")
defines("DEBUG")
symbols("on")

filter("configurations:Release")
defines("RELEASE")
optimize("on")

filter("configurations:Dist")
defines("DIST")
optimize("on")
kind("WindowedApp")

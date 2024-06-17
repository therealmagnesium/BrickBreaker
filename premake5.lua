workspace("BrickBreaker")
architecture("x64")

configurations({
    "Debug",
    "Release",
    "Dist",
})

include("Break-Core")
include("App")

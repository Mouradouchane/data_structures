

workspace("ds_workspace")
    configurations { "Debug", "Release" }

project "tester"
   
    location "tester"
    
    includedirs { 
        "arrays/static_array/",
        "arrays/dynamic_array/",
        "stacks/static_stack/",
        "stacks/dynamic_stack/",
    }

    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "tester/tester.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "Off"


project "arrays"
   
    location "arrays"
    files { "arrays/**" }
    removefiles {
        "arrays/*.vcxproj",
        "arrays/*.vcxproj.filters",
        "arrays/*.vcxproj.user",
    }
    
    vpaths { 
        ["static_array/*" ] = "arrays/static_array/*",   
        ["dynamic_array/*"] = "arrays/dynamic_array/*",
    }
    
    kind "SharedLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

   filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "Off"



project "stacks"
   
    location "stacks"
    files { "stacks/**" }
    removefiles {
        "stacks/*.vcxproj",
        "stacks/*.vcxproj.filters",
        "stacks/*.vcxproj.user",
    }
    
    vpaths { 
        ["static_stack/*" ] = "stacks/static_stack/*",   
        ["dynamic_stack/*"] = "stacks/dynamic_stack/*",
    }
    
    kind "SharedLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

   filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "Off"
  

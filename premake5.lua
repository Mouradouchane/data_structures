

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


lib_name = "static_stack"
lib_path = "stacks/static_stack/"

project(lib_name)
   
    location(lib_path)
    
    files { 
      lib_path .. "*.hpp" , lib_path .. "*.cpp"
    }

    removefiles {
        lib_path .. "*.vcxproj",
        lib_path .. "*.vcxproj.filters",
        lib_path .. "*.vcxproj.user",
    }
    
    -- virtual folders in IDE
    vpaths { 
        -- [ lib_name .. "/*" ] = lib_path .. "*",   
        [ lib_name .. "/tests" ] = lib_path .. "tests/*"
    }

    print(lib_path .. "tests/")
    
    kind "StaticLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "Off"
  

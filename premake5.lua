
-- worksapce config's

print("\nstart generating workspace")

workspace("ds_workspace")
configurations { "Debug", "Release" }

print("generating workspace done !\n")

-- include external build file
include "tester/tester.lua"

-- function act like template , for generating porject's
function make_project_for_lib( 
  lib_name , lib_path , lib_type
) 
    
    -- check parameters   
    lib_type = lib_type or "StaticLib"
   
    print("\n[ " .. lib_name .. " ] : generate project ! ")

    -- project name
    project(lib_name)

    -- project path 
    location(lib_path)
  
    -- seleceted folders
    files { 
      lib_path .. "*.hpp" , 
      lib_path .. "*.cpp" , 
      lib_path .. "tests/*.cpp",
    }

    -- ignored files/folders
    removefiles {
        lib_path .. "*.vcxproj",
        lib_path .. "*.vcxproj.filters",
        lib_path .. "*.vcxproj.user",
    }
    
    -- virtual folders in IDE
    vpaths { 
        [ lib_name .. "/*" ] = lib_path .. "**",
    }

    -- project type/deatilis
    kind(lib_type)
    language("C++")

    targetdir("bin/%{cfg.buildcfg}")

    filter("configurations:Debug")
        defines { "DEBUG" }
        symbols("On")

    filter("configurations:Release")
        defines { "NDEBUG" }
        optimize("Off")
  
    print( "\n[ " .. lib_name .. " ] : finished !\n" )

end

make_project_for_lib("static_stack" , "stacks/static_stack/")
make_project_for_lib("dynamic_stack" , "stacks/dynamic_stack/")



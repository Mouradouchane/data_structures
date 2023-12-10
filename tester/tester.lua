print("\n[ tester ] : generate project !")

tester_scope = {}

project("tester")
   
    location("./")
    
    includedirs { 
        "../arrays/static_array/",
        "../arrays/dynamic_array/",
        "../stacks/static_stack/",
        "../stacks/dynamic_stack/",
    }

    kind("ConsoleApp")
    language("C++")
    targetdir("bin/%{cfg.buildcfg}")

    files { "*.cpp", "*.hpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols ("On")

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize("Off")

        
print("\n[ tester ] : finsished !\n")

return tester_scope


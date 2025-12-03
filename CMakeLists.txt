cmake_minimum_required(VERSION 3.26)
project(Project3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project3
        main.cpp
        hashclass.cpp
        hashclass.h
        List.cpp
        List.h
        bloomfilterClass.cpp
        bloomfilterClass.h
        PasswordManager.cpp
        PasswordManager.h
)

add_custom_command(TARGET Project3 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/100000-most-common-passwords.txt
        $<TARGET_FILE_DIR:Project3>/100000-most-common-passwords.txt)

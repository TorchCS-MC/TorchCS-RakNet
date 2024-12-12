cmake_minimum_required(VERSION 3.27)
project(ModernRakNet C)

set(CMAKE_C_STANDARD 11)

add_executable(ModernRakNet
        main.c
        src/Base64.c
        src/RakNetSocket_Windows.c
        src/RakPeer.c
        src/BitStream.c
)

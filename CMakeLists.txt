cmake_minimum_required(VERSION 3.27)
project(TorchCS-RakNet C)

set(CMAKE_C_STANDARD 11)

add_executable(ModernRakNet
        main.c
        utils/Base64.c
        socket/raknet/RakNetSocket_Windows.c
        socket/raknet/RakPeer.c
        socket/UDPSocket_Windows.c
        socket/UDPSocket_Linux.c
)

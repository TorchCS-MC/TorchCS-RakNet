#ifndef TORCHCSRAKNET_UDPSOCKET_H
#define TORCHCSRAKNET_UDPSOCKET_H

typedef struct UDPSocket {
    const char* ip;
    int port_v4;
    int port_v6;


    int (*create_udp_socket)(struct UDPSocket* self);
    int (*send_packet)(struct UDPSocket* self, const char* message, size_t length);
    int (*receive)(struct UDPSocket* self, char* buffer, size_t buffer_size);

    void (*init)();
    void (*cleanup)();

    int socket_fd;
} UDPSocket;

#endif // TORCHCSRAKNET_UDPSOCKET_H

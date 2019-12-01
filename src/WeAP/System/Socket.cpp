#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <assert.h>
#include "socket.h"

#include "Error.h"
#include "Exception.h"

namespace WeAP { namespace System {

Socket::Socket()
:  _socket_fd(INVALID_SOCKET)
{
    this->error_text[0] = '\0';

    reset_buf();
}

Socket::~Socket()
{
    close();
}

int Socket::create(int socket_type)
{
    _socket_fd =::socket(AF_INET, socket_type, 0);
    if (_socket_fd < 0) 
    {
        _socket_fd = INVALID_SOCKET;
        snprintf(this->error_text, sizeof(this->error_text), "create: %s", strerror(errno));
        throw Exception(Error::Socket_Create_Failed, this->error_text);
    }

    return 0;
}

void Socket::get_peer_name(string & peer_address, uint16_t & peer_port)
{
    struct sockaddr name;
    struct sockaddr_in *p = (struct sockaddr_in *) &name;
    socklen_t namelen = sizeof(name);

    bzero(&name, sizeof(struct sockaddr));

    get_peer_name(name, namelen);

    char addr[INET_ADDRSTRLEN];
    peer_address = inet_ntop(AF_INET, &p->sin_addr, addr, sizeof(addr));
    peer_port = ntohs(p->sin_port);

    return;
}

void Socket::get_peer_name(struct sockaddr &name, socklen_t & namelen)
{
    if (::getpeername(_socket_fd, &name, &namelen) < 0) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "get_peer_name: %s", strerror(errno));
        throw Exception(Error::Socket_Get_Peer_Name_Failed, this->error_text);
    }

    return;
}

void Socket::get_sock_name(string & socket_address, uint16_t & socket_port)
{
    struct sockaddr name;
    struct sockaddr_in *p = (struct sockaddr_in *) &name;
    socklen_t namelen = sizeof(name);

    bzero(&name, sizeof(struct sockaddr));
    get_sock_name(name, namelen);

    char addr[INET_ADDRSTRLEN];
    socket_address = inet_ntop(AF_INET, &p->sin_addr, addr, sizeof(addr));
    socket_port = ntohs(p->sin_port);

    return;
}

void Socket::get_sock_name(struct sockaddr &name, socklen_t & namelen)
{
    if (::getsockname(_socket_fd, &name, &namelen) < 0) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "get_sock_name: %s", strerror(errno));
        throw Exception(Error::Socket_Get_Sock_Name_Failed, this->error_text);
    }

    return;
}

void Socket::set_sock_opt(int optname, const void *optval,
                     socklen_t optlen, int level /*= SOL_SOCKET*/ )
{
    if (setsockopt(_socket_fd, level, optname, optval, optlen) < 0) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "set_sock_opt: %s", strerror(errno));
        throw Exception(Error::Socket_Set_Sock_Opt_Failed, this->error_text);
    }

    return;
}

void Socket::get_sock_opt(int optname, void *optval,
                     socklen_t * optlen, int level /*= SOL_SOCKET*/ )
{
    if (getsockopt(_socket_fd, level, optname, optval, optlen) < 0) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "get_sock_opt: %s", strerror(errno));
        throw Exception(Error::Socket_Set_Sock_Opt_Failed, this->error_text);
    }

    return;
}

int Socket::accept(Socket & client_socket,
               struct sockaddr *addr /*= NULL*/ ,
               socklen_t * addrlen /*= NULL*/ )
{
    int client_fd;

    assert(client_socket._socket_fd == INVALID_SOCKET);

    if (addr != NULL) 
    {
        bzero(addr, sizeof(struct sockaddr));
    }
    while ((client_fd =::accept(_socket_fd, addr, addrlen)) < 0
           && errno == EINTR);

    if (client_fd < 0) {
        client_socket._socket_fd = INVALID_SOCKET;
        snprintf(this->error_text, sizeof(this->error_text), "accept: %s", strerror(errno));

        if (errno == EWOULDBLOCK || errno == ECONNABORTED
            || errno == EPROTO || errno == EINTR || errno == EAGAIN) 
        {
            return errno;
        }
        else 
        {
            throw Exception(Error::Socket_Accept_Failed, this->error_text);
        }
    }

    client_socket._socket_fd = client_fd;
    client_socket.this->error_text[0] = '\0';

    return 0;
}

void Socket::get_in_addr(const char * address,
        struct in_addr& sinaddr,
        const char * func_name)
{
        int ret = inet_pton(AF_INET, address, &sinaddr);
        if (ret < 0)
        {
            snprintf(this->error_text, sizeof(this->error_text), "%s: inet_pton(%s): %s",
                    func_name, address, strerror(errno));
            throw Exception(Error::Socket_Get_In_Addr_Failed, this->error_text);
        }
        else if (ret == 0) 
        {
            struct hostent hostent;
            struct hostent *hostent_ptr;
            char buf[2048];
            int herror;
            gethostbyname_r(address,
                &hostent,
                buf,
                sizeof(buf),
                &hostent_ptr,
                &herror);
            if (hostent_ptr == NULL) 
            {
                snprintf(this->error_text, sizeof(this->error_text), "%s: gethostbyname_r(%s): %s",
                        func_name, address, hstrerror(herror));
                throw Exception(Error::Socket_Get_In_Addr_Failed, this->error_text);
            }
            else 
            {
                sinaddr = *(struct in_addr *) hostent_ptr->h_addr;
            }
        }

        return;
}

void Socket::bind(uint16_t port, const char *server_address /*= NULL*/ )
{
    struct sockaddr bind_addr;
    socklen_t addrlen = sizeof(bind_addr);
    struct sockaddr_in *p = (struct sockaddr_in *) &bind_addr;

    bzero(&bind_addr, sizeof(struct sockaddr));

    p->sin_family = AF_INET;
    p->sin_port = htons(port);
    if (server_address == NULL) 
    {
        p->sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else 
    {
        get_in_addr(server_address, p->sin_addr, "bind");
    }

    bind(bind_addr, addrlen);
}

void Socket::bind(const struct sockaddr &bind_addr, socklen_t addrlen)
{
    if (::bind(_socket_fd, &bind_addr, addrlen) < 0) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "bind: %s", strerror(errno));
        throw Exception(Error::Socket_Bind_Failed,this->error_text);
    }
}

void Socket::close()
{
    if (_socket_fd != INVALID_SOCKET) 
    {
        ::close(_socket_fd);
        _socket_fd = INVALID_SOCKET;
    }
}

void Socket::connect(const char *address, uint16_t port)
{
    if (address == NULL) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "connect: address == NULL");
        throw Exception(Error::Socket_Connect_Failed, this->error_text);
    }

    struct sockaddr serveraddr;
    struct sockaddr_in *p = (struct sockaddr_in *) &serveraddr;

    bzero(&serveraddr, sizeof(serveraddr));

    p->sin_family = AF_INET;
    get_in_addr(address, p->sin_addr, "connect");
    p->sin_port = htons(port);

    this->connect(serveraddr, sizeof(serveraddr));
}

void Socket::connect(const struct sockaddr &serv_addr, socklen_t addrlen)
{
    if (::connect(_socket_fd, &serv_addr, addrlen) < 0) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "connect: %s", strerror(errno));
        throw Exception(Error::Socket_Connect_Failed, this->error_text);
    }

    return;
}

void Socket::listen(int connection_baklog)
{
    if (::listen(_socket_fd, connection_baklog) < 0) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "listen: %s", strerror(errno));
        throw Exception(Error::Socket_Listen_Failed, this->error_text);
    }
}

int Socket::receive(void *buf, size_t len, int flag)
{
    int bytes;

    if ((bytes =::recv(_socket_fd, buf, len, flag)) < 0) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "receive: %s", strerror(errno));
        throw Exception(Error::Socket_Receive_Failed, this->error_text);
    }

    return bytes;
}

int Socket::receive_from(void *buf, size_t len,
                     string & from_address, uint16_t & from_port, int flags)
{
    struct sockaddr from;
    socklen_t fromlen = sizeof(struct sockaddr);
    struct sockaddr_in *p = (struct sockaddr_in *) &from;

    bzero(&from, sizeof(struct sockaddr));

    int bytes = receive_from(buf, len, from, fromlen, flags);
    if (bytes < 0)
    {
        throw Exception(Error::Socket_Receive_From_Failed,this->error_text);
    }

    char addr[INET_ADDRSTRLEN];
    from_address = inet_ntop(AF_INET, &p->sin_addr, addr, sizeof(addr));
    from_port = ntohs(p->sin_port);

    return bytes;
}

int Socket::receive_from(void *buf, size_t len,
                     struct sockaddr &from, socklen_t & fromlen, int flags)
{
    int bytes =::recvfrom(_socket_fd, buf, len, flags, &from, &fromlen);

    if (bytes < 0) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "receive_from: %s", strerror(errno));
        throw Exception(Error::Socket_Receive_From_Failed,this->error_text);
    }

    return bytes;
}

int Socket::send(const void *buf, size_t len, int flag)
{
    int bytes;

    if ((bytes =::send(_socket_fd, buf, len, flag)) < 0) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "send: %s", strerror(errno));
        throw Exception(Error::Socket_Send_Failed, this->error_text);
    }

    return bytes;
}

int Socket::send_to(const void *msg, size_t len,
                uint16_t port, const char *host_address /*= NULL*/ ,
                int flags /* = 0 */ )
{
    struct sockaddr toaddr;
    struct sockaddr_in *p = (struct sockaddr_in *) &toaddr;

    bzero(&toaddr, sizeof(struct sockaddr));

    p->sin_family = AF_INET;

    if (host_address == NULL) 
    {
        p->sin_addr.s_addr = htonl(INADDR_BROADCAST);
    }
    else 
    {
        get_in_addr(host_address, p->sin_addr, "send_to");
    }

    p->sin_port = htons(port);

    return send_to(msg, len, toaddr, sizeof(toaddr), flags);
}

int Socket::send_to(const void *msg, size_t len,
                const struct sockaddr &to, socklen_t tolen,
                int flags /* = 0 */ )
{
    int bytes;

    if ((bytes =::sendto(_socket_fd, msg, len, flags, &to, tolen)) < 0) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "send_to: %s", strerror(errno));
        throw Exception(Error::Socket_Send_To_Failed,this->error_text);
    }

    return bytes;
}

void Socket::shutdown(int how)
{
    if (::shutdown(_socket_fd, how) < 0) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "send_to: %s", strerror(errno));
        throw Exception(Error::,this->error_text);
    }
}

void Socket::set_nonblock()
{
    int val;

    if ((val = fcntl(_socket_fd, F_GETFL, 0)) == -1) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "set_nonblock: %s", strerror(errno));
        throw Exception(Error::Socket_Set_Nonblock_Failed,this->error_text);
    }

    if (fcntl(_socket_fd, F_SETFL, val | O_NONBLOCK) == -1) 
    {
        snprintf(this->error_text, sizeof(this->error_text), "set_nonblock: %s", strerror(errno));
        throw Exception(Error::Socket_Set_Nonblock_Failed, this->error_text);
    }
}

void Socket::reset_buf()
{
    _read_count = 0;
    _read_ptr = NULL;
    _read_buf[0] = '\0';
}

ssize_t Socket::buf_read(char &ch)
{
    if (_read_count <= 0) 
    {
      again:
        _read_count =::read(_socket_fd, _read_buf, sizeof(_read_buf));
        if (_read_count < 0) 
        {
            if (errno == EINTR)
                goto again;
            else
                return -1;
        }
        else if (_read_count == 0) 
        {
            return 0;
        }

        _read_ptr = _read_buf;
    }

    _read_count--;
    ch = *_read_ptr++;
    return 1;
}

int Socket::gets(char *str, size_t maxlen)
{
    size_t len;
    int rc;
    char ch;
    char *ptr;

    ptr = str;
    for (len = 1; len < maxlen; ++len) 
    {
        if ((rc = buf_read(ch)) == 1) 
        {
            if (ch == '\n')
                break;
            *ptr++ = ch;
        }
        else if (rc == 0) 
        {
            return 0;
        }
        else 
        {
            //snprintf(this->error_text, sizeof(this->error_text), "gets: %s", strerror(errno));
            this->SetLastError();
            throw Exception(Error::Socket_Gets_Failed, this->GetLastError());
        }
    }
    *ptr = '\0';
    if (ptr > str)
    {
        *(--ptr) = '\0';        // remove '\n'
    }
        
    return len;
}


void Socket::SetLastError(const string& errorInfo, const char* methodName)
{
    if (errorInfo.empty())
    {
        snprintf(this->error_text, sizeof(this->error_text), "%s: %s", methodName, strerror(errno));
    }
    else
    {
        snprintf(this->error_text, sizeof(this->error_text), "%s: %s", methodName, errorInfo.c_str());

    }
    
    
}



}}
#ifndef __WeAP_Socket_H__
#define __WeAP_Socket_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <string>

namespace WeAP { namespace System {

class Socket: public Object
{
private:
    Socket(const Socket& sock);
    void operator = (const Socket& sock);

public:
    Socket();
    virtual ~Socket();    
    int create(int socket_type = SOCK_STREAM);

public:
    int fd() const {return _socket_fd;};
    bool socket_is_ok() const {return (_socket_fd != INVALID_SOCKET);}

    void get_peer_name(string& peer_address, uint16_t& peer_port);
    void get_peer_name(struct sockaddr& name, socklen_t& namelen);

    void get_sock_name(string& socket_address, uint16_t& socket_port);
    void get_sock_name(struct sockaddr& name , socklen_t& namelen);

    void set_sock_opt(int optname, const void *optval,
            socklen_t optlen, int level = SOL_SOCKET);

    void get_sock_opt(int optname, void *optval,
            socklen_t *optlen, int level = SOL_SOCKET);

    const char * GetLastError() const { return this->error_text; }


public:
    virtual int accept(Socket& client_socket,
            struct sockaddr *addr = NULL, socklen_t *addrlen = NULL);

    void bind(uint16_t port, const char * server_address = NULL);
    void bind(const struct sockaddr& bind_addr, socklen_t addrlen);

    virtual void close();

    void connect(const char * addr, uint16_t port);
    void connect(const struct sockaddr& serv_addr, socklen_t addrlen);

    void listen(int connection_baklog = 5);

    virtual int receive(void * buf, size_t len, int flag = 0);

    int receive_from(void * buf, size_t len,
            string& from_address, uint16_t& from_port, int flags = 0);
    int receive_from(void  *buf, size_t len,
            struct sockaddr& from, socklen_t& fromlen, int flags = 0);
    
    virtual int send(const void * buf, size_t len, int flag = 0);

    int send_to(const void *msg, size_t len,
            uint16_t port, const char * host_address = NULL, int flags = 0);
    int send_to(const  void  *msg,  size_t len,
            const struct sockaddr& to, socklen_t tolen, int flags = 0);

    virtual void reset_buf();
    virtual int gets(char * str, size_t maxlen);

    virtual int puts(char * str) { return send((void *) str, strlen(str)); }
    
    enum en_how{ receives = 0, sends = 1, both = 2 };
    void shutdown(int how = 1);

    void set_nonblock();

protected:
    void SetLastError(const string& errorInfo = "", const char* methodName = __FUNCTION__);

private:
    void get_in_addr(const char * address, struct in_addr& sinaddr, const char * func_name);
    ssize_t buf_read(char& ch);
    
protected:
    static const int INVALID_SOCKET = -1;
    static const int MAX_LINE = 1024;

    int _socket_fd;
    
    char error_text[128];

    int _read_count;
    char * _read_ptr;
    char _read_buf[MAX_LINE];
};


}}

#endif

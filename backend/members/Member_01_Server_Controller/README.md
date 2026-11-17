# Member 01: Core HTTP Web Server & Network Controller

## 👤 Member Information
- **Name / Assignee:** Member 01
- **Role:** Network Architecture & HTTP Socket Server
- **Files Owned:** `HttpServer.hpp`, `HttpServer.cpp`
- **Core Technology:** C++17, POSIX Sockets (`<sys/socket.h>`, `<netinet/in.h>`), Multithreading (`<thread>`)

---

## 🎯 Contribution Overview
Member 01 engineered the high-performance **C++ HTTP Server** that connects PIXORA's C++ core engine to web browsers:
1. **Low-Level Socket Programming**:
   - Creates and binds a TCP streaming socket (`AF_INET`, `SOCK_STREAM`).
   - Uses `setsockopt(SO_REUSEADDR)` to avoid port-binding collisions.
   - Listens and accepts incoming HTTP client connections asynchronously using modern detached `std::thread` workers.
2. **REST API Endpoint Dispatcher**:
   - Routes `GET /api/pins`, `GET /api/pins/:id`, `POST /api/pins`
   - Handles social action routes: `/api/pins/:id/like`, `/api/pins/:id/save`, `/api/pins/:id/comment`
   - Dispatches profile & board updates: `/api/profile`, `/api/boards`
3. **Static Web File Serving**:
   - Dynamically resolves and serves HTML, CSS, JavaScript, and image assets from `frontend/` with accurate MIME headers (`text/html`, `text/css`, `application/javascript`, `image/svg+xml`).
4. **CORS Protocol Handling**:
   - Responds to browser `OPTIONS` preflight requests with `Access-Control-Allow-Origin: *`.

---

## 💻 Key Methods
- `HttpServer::start()`: Initializes socket, binds to specified port, begins listening loop.
- `HttpServer::handleClient(int clientSocket)`: Reads HTTP request headers & body from socket, dispatches response.
- `HttpServer::routeRequest(method, path, body)`: Matches URI path and invokes appropriate business logic.
- `HttpServer::serveStaticFile(path)`: Reads local disk file into buffer using binary `std::ifstream` and crafts HTTP 200 response.

---

## 🎓 C++ Viva / Oral Exam Questions & Answers
- **Q1: How does your C++ server handle multiple simultaneous web requests?**  
  *Answer:* Through multithreading. When `accept()` receives a new client socket descriptor, it launches a worker thread via `std::thread([this, clientSocket]{ handleClient(clientSocket); }).detach()`. This prevents one slow request from blocking other users.
- **Q2: What socket system calls are used to establish the server?**  
  *Answer:* `socket()` creates the endpoint, `bind()` associates it with an IP and port, `listen()` sets the connection queue backlog, and `accept()` waits for incoming client connections.
- **Q3: What is the benefit of a C++ web server over a Node.js or Python backend?**  
  *Answer:* C++ compiles directly to machine code with zero interpreter overhead. It uses minimal memory, executes socket I/O at near-hardware speeds, and provides predictable CPU utilization.

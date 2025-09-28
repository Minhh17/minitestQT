# Engineering Notebook

This engineering notebook documents the development of the mini test FPGA-PC communication example.

## Entry 1 – 2025‑09‑27: Phân tích yêu cầu 

- I reviewed the mini‑test specification. The Qt program will send commands from PC to an FPGA and receive a 2params×16‑bit response for plotting. 
- Because I dont have a FPGA, I will implement a simulated FPGA with two port to test communication. 
- I decided to use TCP/IP over Ethernet first instead of RS‑422 because it can run entirely on a single computer and easier.  I looked up the Qt network classes and noted that QTcpServer can listen for connections and emit a newConnection signal.  For the client I will use QTcpSocket.



## Entry 2 – 2025‑09‑21: Design draft

Drafted a high‑level architecture.  There will be two separate
applications: a console **server** and a GUI **client**.  The
server will accept connections, generate random data on demand,
pack it into a 4‑byte message and send it back.  The client will
connect, send a command, read the 4 bytes and extract two
16‑bit values.  I considered using `QSerialPort` but postponed
serial support to a future iteration.

## Entry 3 – 2025‑09‑22: Implementing the server

Implemented the server in C++ with Qt.  I created a `Fpgaserver`
class that wraps a `QTcpServer`.  In the `onNewConnection` slot
it calls `nextPendingConnection()` to obtain the socket.  I
connected `readyRead()` to a lambda that reads incoming data,
generates two random numbers using `QRandomGenerator`, serializes
them with `QDataStream` (big‑endian) and writes them to the
socket.  Verified that the server listens and responds correctly
using `nc` in the terminal.

## Entry 4 – 2025‑09‑23: Building the GUI client

Started the GUI client.  I created a `MainWindow` with host and
port fields, Connect and Send buttons, and a status label.  I
factored the socket code into a separate `NetworkClient` class
that wraps `QTcpSocket`.  The client sends a one‑byte command
0x01 when the user clicks Send.  On `readyRead` it reads data
into a buffer until at least four bytes are present, then uses
`QDataStream` to extract two `quint16` values.  I added a
`PlotWidget` class to store points and draw them using
`QPainter`.

## Entry 5 – 2025‑09‑24: Testing and refinements

Tested the integrated system.  The client connected to the server
and plotted the points.  I observed that the points tended to
cluster around the top left corner because the raw values ranged
from 0 to 65535 while the widget was smaller.  Added scaling in
`PlotWidget` to map the raw values to the widget’s width and
height.  Added error handling in `NetworkClient` to display
messages when the connection fails.

## Entry 6 – 2025‑09‑25: Documentation

Compiled the design notes into `docs/DESIGN.md` and wrote this
notebook.  Made sure to number and date each entry and to
document decisions such as choosing TCP and generating random
data.  Cited the Qt documentation and engineering notebook
guidelines where appropriate【280627883494165†L64-L94】【787370860010465†L231-L244】.
Prepared `TESTING.md` with the test plan.

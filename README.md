# minitestQT

ứng dụng Qt mô phỏng quy trình điều khiển FPGA từ PC gồm:

- **Client Qt PC**: giao diện chính `MainWindow` cho phép lựa chọn cổng Serial hoặc địa chỉ TCP, và hộp thoại `FpgaControlDialog` dùng để cấu hình, gửi lệnh và vẽ dữ liệu phản hồi.
- **FPGA giả lập**:`FPGADialog` đóng vai trò FPGA ảo, nhận gói lệnh từ Serial/TCP rồi phản hồi ngẫu nhiên hai giá trị 16-bit theo cùng định dạng giao thức.

Toàn bộ giao tiếp dùng khung dữ liệu 8 byte `[Header 'A'][Command][Data 4B][CRC][Footer 'B']` và thuật toán CRC-8 đa thức `0x8C` đã được tái sử dụng thông qua mô-đun `protocolutils`.

## Hướng dẫn chạy

### Yêu cầu

- >= Qt 5.15 với các module Widgets, SerialPort và Network.
- C++17.

### Biên dịch

### Chạy thử

1. Mở **Client** (ứng dụng chính), chọn cổng Serial/TCP phù hợp và nhấn **Open** hoặc **onnect**.
2. Chạy trong QtCreator cũng đồng thời mở **FPGADialog** để giả lập thiết bị, FPGA giả lập này sẽ tự động lắng nghe cổng Ethernet - TCP/IP hoặc ấn nút Connect để kết nối cổng Serial 
3. Sử dụng các textEdit, nút cấu hình trong `FpgaControlDialog` để phát lệnh. Điểm đo phản hồi sẽ được vẽ trên biểu đồ (2 điểm ngẫu nhiêu).

## Tài liệu kèm theo

- `docs/DESIGN.md`: kiến trúc, class diagram và sequence diagram.
- `docs/NOTEBOOK.md`: nhật ký.
- `docs/TESTING.md`: kiểm thử và kết quả.

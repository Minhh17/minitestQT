# Thiết kế hệ thống

## 1. Tổng quan kiến trúc

Giải pháp gồm hai phần mềm Qt chạy trên cùng máy tính:

- **Ứng dụng Client** gồm `MainWindow` và hộp thoại `FpgaControlDialog`. Người vận hành lựa chọn kênh kết nối (Serial/TCP), gửi lệnh điều khiển và quan sát dữ liệu phản hồi trên biểu đồ scatter.
- **Thiết bị mô phỏng** `FPGADialog` đóng vai trò FPGA, tiếp nhận gói lệnh từ cả Serial lẫn TCP, sinh dữ liệu 16-bit ngẫu nhiên và phản hồi theo đúng giao thức để Client có thể kiểm thử end-to-end.

Giao thức truyền thông thống nhất 8 byte với CRC-8 đa thức `0x8C`. Mọi logic đóng gói/giải mã, tính CRC đều nằm trong mô-đun `protocolutils` giúp loại bỏ lặp mã và giảm sai sót.

## 2. Thành phần chính

- **DeviceControl**: điều khiển cổng Serial, chuyển lệnh người dùng thành khung dữ liệu và phát đi.
- **SerialPort**: lớp bao bọc `QSerialPort`, cấu hình mặc định 115200-8N1, tự động phát tín hiệu khi có dữ liệu về hoặc khi mất kết nối.
- **SocketControl**: bao bọc `QTcpSocket`, hỗ trợ tái sử dụng kết nối và phát tín hiệu trạng thái phục vụ UI.
- **FpgaControlDialog**: nhận thông báo kết nối từ `MainWindow`, phát lệnh cấu hình tới Serial/TCP, đồng thời phân tích phản hồi để vẽ điểm và cập nhật UI.
- **FPGADialog**: server mô phỏng, lắng nghe TCP và Serial, xác thực CRC rồi trả về hai giá trị 16-bit bất kỳ.
- **protocolutils**: hàm tính CRC-8, đóng gói khung lệnh, rút gói từ buffer. Tập trung hóa giúp hai phía Client/FPGA dùng chung quy tắc.

## 3. Sơ đồ lớp
<img width="2176" height="1134" alt="minitestClassDetail" src="https://github.com/user-attachments/assets/ca421b9f-8dcd-47ee-9cd4-e1ce44e39ba2" />

## 4. Chuỗi trao đổi dữ liệu
<img width="1412" height="1660" alt="minitestSequenDetail" src="https://github.com/user-attachments/assets/200f54a5-5fb5-4949-8e39-72c3fe71ab8b" />

## 5. Lý do thiết kế

- **Tái sử dụng giao thức**: đặt các hàm CRC/đóng gói vào `protocolutils` để loại bỏ ba bản sao giống nhau, giảm trùng lặp dài dòng. 
- **Quản lý tài nguyên an toàn**: dùng `std::unique_ptr` ở `MainWindow` để nắm quyền sở hữu `DeviceControl`/`SocketControl`, tránh rò rỉ khi bấm Open/Connect nhiều lần.
- **Buffer phân tầng**: `FPGADialog` và `FpgaControlDialog` duy trì buffer riêng cho Serial và TCP để xử lý gói không trọn vẹn mà không mất dữ liệu.

hật ký phát triển dự án mô phỏng giao tiếp PC–FPGA.

## Phân tích yêu cầu
- Đề bài mini test: cần ứng dụng Qt gửi lệnh xuống FPGA, nhận 2 giá trị 16-bit phản hồi để hiển thị vẽ hình.
- Đọc hiểu đánh giá repo sample: code đã hoạt động cơ bản nhưng còn nhiều phần trùng lặp (CRC, đóng gói dữ liệu) và quản lý bộ nhớ thủ công.
- Ghi chú các vấn đề ưu tiên: chuẩn hóa giao thức, dọn dẹp con trỏ raw, bổ sung tài liệu kỹ thuật.

## Tái cấu trúc tầng giao tiếp
- Tạo mô-đun `protocolutils` gom logic tính CRC-8 và dựng/giải mã frame 8 byte cho cả Serial lẫn TCP.
- Refactor `SerialPort`, `DeviceControl`, `SocketControl` sang sử dụng RAII (đối tượng thành viên + `std::unique_ptr`) để tránh rò rỉ và bảo toàn tín hiệu Qt.【F:serialport.cpp†L5-L64】【F:DeviceControl.cpp†L6-L82】
- Chuẩn hóa kết nối tín hiệu trong `MainWindow`, hiển thị rõ trạng thái khi kết nối thất bại.【F:mainwindow.cpp†L6-L93】

## Chuẩn hóa phía thiết bị mô phỏng & UI
- Áp dụng `protocolutils` cho `FPGADialog` và `FpgaControlDialog` để xử lý buffer và phản hồi thống nhất.【F:FPGADialog.cpp†L1-L189】【F:fpgacontroldialog.cpp†L1-L207】
- Loại bỏ việc xoá thủ công đối tượng được truyền qua tín hiệu, tránh crash khi UI còn sử dụng.【F:fpgacontroldialog.cpp†L84-L111】
- Cải tiến log hiển thị, bảo đảm UI cập nhật trạng thái “Connected/Disconnected” chính xác.

## Hoàn thiện tài liệu & kế hoạch kiểm thử
- Viết README bằng tiếng Việt, hướng dẫn build/run rõ ràng.【F:README.md†L1-L34】
- Biên soạn tài liệu thiết kế với sơ đồ lớp, sequence diagram và lập luận lựa chọn kiến trúc.【F:docs/DESIGN.md†L1-L94】
- Lập nhật ký kiểm thử và checklist test tay để chứng minh chức năng cốt lõi.【F:docs/TESTING.md†L1-L64】

## Next task
- Có thể mở rộng `protocolutils` để hỗ trợ nhiều phiên bản giao thức (ví dụ big-endian) nếu yêu cầu thay đổi.
- Xem xét bổ sung unit test cho CRC bằng Qt Test hoặc GoogleTest khi có thời gian.

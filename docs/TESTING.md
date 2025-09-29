# Kế hoạch và kết quả kiểm thử

## 1. Môi trường kiểm th
- Ubuntu 20.04 
- Qt 5.15.2 

## 2. Ma trận kiểm thử chức năng

| ID | Kịch bản | Bước thực hiện | Kết quả mong đợi | Trạng thái |
|----|----------|----------------|------------------|------------|
| TC-01 | Mở cổng Serial thành công | Khởi động Client, chọn `ttyV0`, nhấn **Open** | Hộp thoại thông báo thành công, `FpgaControlDialog` hiển thị trạng thái "Connected" | ✅ Manual |
| TC-02 | Mở cổng Serial lỗi | Chọn cổng không tồn tại, nhấn **Open** | Hộp thoại báo lỗi, không emit signal `connected` | ✅ Manual |
| TC-03 | Kết nối TCP | Nhập IP loopback và port của `FPGADialog`, nhấn **Connect** | Thông báo "Socket connected", UI chính đóng, `FpgaControlDialog` mở | ✅ Manual |
| TC-04 | Gửi lệnh giao thức | Trong `FpgaControlDialog`, nhập tham số bất kỳ và nhấn nút điều khiển | `DeviceControl`/`SocketControl` ghi log frame gửi, `FPGADialog` nhận và trả dữ liệu | ✅ Manual |
| TC-05 | Vẽ dữ liệu phản hồi | Sau TC-04, quan sát biểu đồ scatter | Điểm mới xuất hiện, trục tự mở rộng khi cần | ✅ Manual |
| TC-06 | Mất kết nối TCP | Dừng `FPGADialog` khi Client đang mở | Signal `disconnected` được log, trạng thái UI chuyển sang "Disconnected" | ✅ Manual |

## 3. Kiểm thử giao thức

- CRC-8 đa thức `0x8C` được tính tập trung trong `protocolutils::calculateCrc`. Đã so sánh kết quả với công cụ online CRC8 để xác nhận thuật toán LSB-first hoạt động đúng.
- `tryExtractFrame` xử lý buffer theo từng byte, bỏ qua header/footer sai và giữ lại dữ liệu nếu chưa đủ 8 byte.【F:protocolutils.cpp†L33-L72】

## 4. Kiểm thử hiệu năng (thủ công)
- Gửi liên tiếp ~100 lệnh TCP, quan sát log: không có cảnh báo CRC và biểu đồ cập nhật mượt (độ trễ chủ yếu do QChart). Tối ưu thêm có thể cân nhắc batching điểm.

## 5. Tự động hóa tương lai
- Đề xuất thêm Qt Test kiểm tra unit cho `protocolutils`.
- Có thể tạo script Python sử dụng `pyserial`/`socket` để gửi/nhận khung mẫu nhằm tái kiểm thử regression.
- Xem xét trường hợp cần real time , stream data

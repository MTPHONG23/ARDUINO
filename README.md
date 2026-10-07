# Thiết kế hệ thống khóa cửa thông minh bằng Arduino

> Báo cáo đồ án / bài tập thực hành hệ thống nhúng sử dụng vi điều khiển Arduino.

## 📋 Tổng quan dự án
Đồ án này xây dựng một hệ thống khóa cửa thông minh hoàn chỉnh dựa trên board mạch **Arduino Uno**, kết hợp với bàn phím ma trận, màn hình LCD, còi báo động (Buzzer), module Relay và khóa điện từ (Solenoid Lock). Hệ thống mang lại giải pháp an ninh tự động, cho phép người dùng mở khóa bằng mật khẩu dạng số và tự động kích hoạt còi cảnh báo khi có hành vi nhập sai mật khẩu nhiều lần liên tiếp.

---

## 🛠️ Linh kiện và phần cứng sử dụng
* **Board mạch điều khiển:** Arduino Uno (sử dụng chip ATmega328P, cung cấp các chân I/O số và tương tự).
* **Giao tiếp hiển thị:** Màn hình LCD 16x2 kết hợp Module I2C (giảm số chân kết nối với Arduino).
* **Bàn phím nhập liệu:** Matrix Keypad 4x4 (gồm 16 nút bấm bố trí thành 4 hàng và 4 cột, sử dụng thuật toán quét phím).
* **Thiết bị chấp hành & Cảnh báo:** 
  * Khóa chốt điện Solenoid Lock (12V/24VDC) để đóng/mở cửa vật lý.
  * Module Relay 1 kênh (điều khiển nguồn điện cho khóa điện từ).
  * Buzzer Module (còi báo động âm thanh).
* **Nguồn cấp:** Nguồn pin hoặc adapter phù hợp cho hệ thống vi điều khiển và khóa điện từ.

---

## 🚀 Nguyên lý hoạt động
1. **Nhập mật khẩu:** Người dùng thao tác nhập mật khẩu gồm 3 ký tự trên bàn phím ma trận 4x4. Các ký tự nhập vào sẽ hiển thị trực tiếp lên màn hình LCD 16x2.
2. **Xác thực và Điều khiển:** 
   * **Đúng mật khẩu:** Hệ thống phát tín hiệu qua chân GPIO điều khiển Relay mở khóa điện từ trong khoảng thời gian định mức, màn hình hiển thị thông báo "CORRECT!".
   * **Sai mật khẩu (dưới 3 lần):** Hệ thống yêu cầu nhập lại từ đầu.
   * **Sai mật khẩu (đạt hoặc vượt quá 3 lần):** Hệ thống kích hoạt còi báo động (Buzzer) trong 5 giây và tạm khóa hệ thống nhằm ngăn chặn hành vi dò mật khẩu trái phép.

---

## 💻 Mã nguồn chương trình (Firmware Highlights)
Chương trình được lập trình trên **Arduino IDE**, sử dụng các thư viện chuyên dụng:
* `<Keypad.h>`: Quản lý và đọc giá trị từ bàn phím ma trận 4x4.
* `<LiquidCrystal_I2C.h>`: Điều khiển màn hình LCD qua giao tiếp I2C.
* `<Wire.h>`: Hỗ trợ giaoτιếp I2C chuẩn.

Các hàm chính trong mã nguồn:
* `setup()`: Khởi tạo cấu hình các chân phần cứng (`pinMode`), khởi tạo màn hình LCD và giao tiếp Serial.
* `checkPassword()`: Hàm kiểm tra chuỗi ký tự nhập vào từ mảng `enterPassword` so với mật khẩu lưu trữ `password`.
* `loop()`: Đọc liên tục phím bấm từ người dùng, cập nhật trạng thái hiển thị LCD, xử lý điều kiện mở khóa hoặc kích hoạt còi báo động khi nhập sai quá giới hạn (`maxcount = 3`).

---

## 👥 Thành viên nhóm thực hiện
* **Lê Văn Đạt** – N21DCVT021
* **Mạch Thế Phong** – N21DCVT072
* **Lê Thị Ngọc Trâm** – N21DCVT106

# Test case CN 2, CN 3, CN 4 (Test 02–04 của đề)

- Người phụ trách: K26DTCN089 – Vũ Trọng Hanh. **Khôi (K26DTCN100) soạn và chạy hộ** ngày 25/11/2026 vì Hanh bận, đã xin phép nhóm.
- Chạy trên nhánh `khoi-ho-tro-hanh` (gồm `main` `f837d3a` và bản sửa CN 2–4 cùng PR), g++ `-std=c++11`, Linux.
- **Chưa chụp ảnh trên Dev-C++**: cần chụp lại trên Windows, đặt tên ảnh theo mã test (ví dụ `TC02-01.png`).
- Dữ liệu ban đầu: `accounttypes.txt`, `bankaccounts.txt` mẫu trên `main` (T01 Savings, T02 Checking, T03 Student; A01, A04 dùng T01).

## 1. Test case CN 2 – Add a new AccountType (Test 02 của đề)

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TC02-01 | Mã trùng (kể cả khác hoa/thường) | Dữ liệu mẫu | 1. Chọn `2`<br>2. Mã nhập `T01`, rồi `t02`, rồi `T04`<br>3. Nhập `Premium`, `USD`, `0.02`<br>4. Chọn `1` | `T01` và `t02` bị báo trùng, cho nhập lại; `T04` được thêm, có trong bảng CN 1 | `[Error] ID already exists.` 2 lần; `AccountType added.`; bảng CN 1 có dòng `T04 \| Premium \| USD` | ✅ |
| TC02-02 | Trường rỗng | Dữ liệu mẫu | 1. Chọn `2`, mã `T04`<br>2. typeName nhập rỗng, rồi chỉ dấu cách, rồi `Premium`<br>3. currency nhập rỗng, rồi `USD`; lãi `0.02` | Mỗi lần rỗng báo lỗi, cho nhập lại | `[Error] Input cannot be empty.` 3 lần; `AccountType added.` | ✅ |
| TC02-03 | Lãi suất sai | Dữ liệu mẫu | 1. Chọn `2`, `T04`, `Premium`, `USD`<br>2. Lãi nhập `abc`, `0`, `-0.5`, `12abc`, rồi `0.02` | Chữ và số có chữ theo sau: báo sai định dạng; ≤ 0: báo phải > 0; cho nhập lại | `[Error] Invalid number format.` (`abc`, `12abc`); `[Error] Value must be greater than 0.` (`0`, `-0.5`); `AccountType added.` | ✅ |

## 2. Test case CN 3 – Search AccountType by ID (Test 03 của đề)

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TC03-01 | Tìm thấy | Dữ liệu mẫu | Chọn `3`, nhập `T02` | Hiện đủ thông tin T02 | `Found: T02, Checking, VND, 0.001` | ✅ |
| TC03-02 | Tìm không phân biệt hoa/thường | Dữ liệu mẫu | Chọn `3`, nhập `t03` | Vẫn tìm ra T03 | `Found: T03, Student, VND, 0.015` | ✅ |
| TC03-03 | Không tìm thấy | Dữ liệu mẫu | Chọn `3`, nhập `T99` | Báo không tìm thấy, quay về menu | `AccountType T99 not found.` | ✅ |

## 3. Test case CN 4 – Update AccountType (Test 04 của đề)

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TC04-01 | Mã không tồn tại | Dữ liệu mẫu | Chọn `4`, nhập `T99` | Báo lỗi, quay về menu | `Error: AccountType T99 not found.` | ✅ |
| TC04-02 | Sửa hợp lệ, xác nhận dữ liệu | Dữ liệu mẫu | 1. Chọn `4`, nhập `T01` (hiện dữ liệu cũ)<br>2. Mã mới `T02` (trùng loại khác), rồi giữ `T01`<br>3. Nhập `Savings Plus`, `VND`, `0.05`<br>4. Chọn `1`, `6`, `5` | Hiện dữ liệu cũ; `T02` báo trùng; sửa xong CN 1 hiện dữ liệu mới; A01, A04 hiện tên loại mới; lưu file đúng | `Current: T01, Savings, VND, 0.045`; `[Error] ID already exists.`; `AccountType updated.`; CN 1: `T01 \| Savings Plus \| VND \| 0.0500 \| 5.00%`; CN 6: `A01 \| Savings Plus …`, `A04 \| Savings Plus …`; file: `T01, Savings Plus, VND, 0.05` | ✅ |
| TC04-03 | Đổi mã loại, tài khoản đi theo, chạy lại không mất dữ liệu | Dữ liệu mẫu | 1. Chọn `4`, nhập `t01` (chữ thường)<br>2. Mã mới `T09`, giữ `Savings`, `VND`, `0.045`<br>3. Chọn `11`, `5`, `0`<br>4. Chạy lại, chọn `6` | A01, A04 chuyển sang `T09`; sau khi chạy lại vẫn đủ 4 tài khoản | `AccountType updated.`; file: `A01, T09, …`, `A04, T09, …`, `T09, Savings, VND, 0.045`; chạy lại: `Loaded 3 account type(s) and 4 bank account(s).`, CN 6 đủ A01–A04 | ✅ |

## 4. Tổng hợp

| Nhóm | Số test | Đạt |
|---|---|---|
| CN 2 | 3 | 3 |
| CN 3 | 3 | 3 |
| CN 4 | 3 | 3 |
| **Cộng** | **9** | **9** |

Ghi chú: trước bản sửa này, `searchID` phân biệt hoa/thường nên TC02-01 (`t02` được nhận thành loại mới), TC03-02 và TC04-03 (`t01`, `t03` báo không tìm thấy) **không đạt**. Khi cho tìm không phân biệt hoa/thường, CN 4 phải đồng bộ tài khoản theo mã đang lưu (`T01`) chứ không theo mã người dùng gõ (`t01`); TC04-03 kiểm tra đúng điểm này.

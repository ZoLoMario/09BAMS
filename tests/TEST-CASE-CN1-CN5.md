## 1. Test case CN 1 – List all AccountTypes

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TC01-01 | Hiển thị 3 AccountType (**Test 01 của đề**) | `accounttypes.txt` có 3 loại | 1. Chạy chương trình<br>2. Chọn `1` | Hiện bảng 3 dòng T01 Savings, T02 Checking, T03 Student; có tiêu đề cột, các cột thẳng hàng; cuối bảng ghi `Tong so: 3 AccountType.` | | |
| TC01-02 | Danh sách rỗng | Đổi tên `accounttypes.txt` thành `accounttypes.bak` | 1. Chạy chương trình<br>2. Chọn `1` | Hiện `Danh sach AccountType trong!`, chương trình không bị dừng | | |
| TC01-03 | Hiển thị loại vừa thêm | `accounttypes.txt` có 3 loại | 1. Chọn `2`, nhập `T04`, `Premium`, `USD`, `0.02`<br>2. Chọn `1` | Bảng có thêm dòng T04 Premium USD ở cuối, `Tong so: 4 AccountType.` | | |

## 2. Test case CN 5 – Save AccountTypes

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TC05-01 | Lưu danh sách hiện có (**Test 05 của đề**) | `accounttypes.txt` có 3 loại | 1. Chọn `5`<br>2. Mở `accounttypes.txt` bằng Notepad, đối chiếu với CN 1 | Màn hình: `Saved AccountTypes to accounttypes.txt.`<br>File có 3 dòng dữ liệu giống bảng CN 1, các trường cách nhau bằng dấu `, ` | | |
| TC05-02 | Lưu sau khi thêm loại mới | `accounttypes.txt` có 3 loại | 1. Chọn `2`, nhập `T04`, `Premium`, `USD`, `0.02`<br>2. Chọn `5`<br>3. Mở `accounttypes.txt` | File có thêm dòng `T04, Premium, USD, 0.02` ở cuối | | |

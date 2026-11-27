# Test case CN 1, CN 5 (Test 01, Test 05 của đề)

- Người viết, người chạy: K26DTCN019 – Nguyễn Quốc Khánh
## 1. Test case CN 1 – List all AccountTypes

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TC01-01 | Hiển thị 3 AccountType (**Test 01 của đề**) | `accounttypes.txt` có 3 loại | 1. Chạy chương trình<br>2. Chọn `1` | Hiện bảng 3 dòng T01 Savings, T02 Checking, T03 Student; có tiêu đề cột, các cột thẳng hàng; cuối bảng ghi `Tong so: 3 AccountType.` | `Loaded 3 account type(s) and 4 bank account(s).`; bảng có tiêu đề `TypeID \| TypeName \| Currency \| InterestRate \| Rate(%)`, 3 dòng `T01 \| Savings \| VND \| 0.0450 \| 4.50%`, `T02 \| Checking \| VND \| 0.0010 \| 0.10%`, `T03 \| Student \| VND \| 0.0150 \| 1.50%`, cột thẳng hàng; `Tong so: 3 AccountType.` | ✅ |
| TC01-02 | Danh sách rỗng | Đổi tên `accounttypes.txt` thành `accounttypes.bak` | 1. Chạy chương trình<br>2. Chọn `1` | Hiện `Danh sach AccountType trong!`, chương trình không bị dừng | Lúc nạp: `Error: cannot open accounttypes.txt. Starting with an empty AccountType list.` (4 tài khoản bị bỏ qua vì không có loại); chọn `1`: `Danh sach AccountType trong!`, hiện lại menu, chọn `0` thoát bình thường | ✅ |
| TC01-03 | Hiển thị loại vừa thêm | `accounttypes.txt` có 3 loại | 1. Chọn `2`, nhập `T04`, `Premium`, `USD`, `0.02`<br>2. Chọn `1` | Bảng có thêm dòng T04 Premium USD ở cuối, `Tong so: 4 AccountType.` | `AccountType added.`; dòng cuối bảng `T04 \| Premium \| USD \| 0.0200 \| 2.00%`; `Tong so: 4 AccountType.` | ✅ |

## 2. Test case CN 5 – Save AccountTypes

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TC05-01 | Lưu danh sách hiện có (**Test 05 của đề**) | `accounttypes.txt` có 3 loại | 1. Chọn `5`<br>2. Mở `accounttypes.txt` bằng Notepad, đối chiếu với CN 1 | Màn hình: `Saved AccountTypes to accounttypes.txt.`<br>File có 3 dòng dữ liệu giống bảng CN 1, các trường cách nhau bằng dấu `, ` | `Saved AccountTypes to accounttypes.txt.`; file giữ dòng tiêu đề `# accountTypeID, …` và 3 dòng `T01, Savings, VND, 0.045`, `T02, Checking, VND, 0.001`, `T03, Student, VND, 0.015`, khớp bảng CN 1 | ✅ |
| TC05-02 | Lưu sau khi thêm loại mới | `accounttypes.txt` có 3 loại | 1. Chọn `2`, nhập `T04`, `Premium`, `USD`, `0.02`<br>2. Chọn `5`<br>3. Mở `accounttypes.txt` | File có thêm dòng `T04, Premium, USD, 0.02` ở cuối | `AccountType added.`, `Saved AccountTypes to accounttypes.txt.`; dòng cuối file `T04, Premium, USD, 0.02`. Chạy lại, chọn `1`: `Loaded 4 account type(s) …`, bảng có T04, `Tong so: 4 AccountType.` | ✅ |

## 3. Tổng hợp

| Nhóm | Số test | Đạt |
|---|---|---|
| CN 1 | 3 | 3 |
| CN 5 | 2 | 2 |
| **Cộng** | **5** | **5** |
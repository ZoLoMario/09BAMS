# Test case CN 6 – List all BankAccounts sorted by typeName (Test 06 của đề)

- Người viết, người chạy: K26DTCN107 – Nguyễn Thanh Phong. Ngày viết: 26/11/2026.
- Chạy trên nhánh `phong-bankaccount` (gồm `main` `d70f232` và bản sửa `toString`/`screenString`, `searchID`). **Chưa chạy**: cột "Thực tế" và "Đạt?" để trống, điền sau khi chạy.
- Cần chụp ảnh trên Dev-C++, đặt tên theo mã test (ví dụ `TC06-01.png`).
- Dữ liệu ban đầu: `accounttypes.txt`, `bankaccounts.txt` mẫu trên `main` (T01 Savings, T02 Checking, T03 Student; A01, A04 cùng loại Savings).
- Hàm liên quan: `BankAccount::compareTo`, `operator<`, `screenString`, `screenHeader`; `BankAccountList::sortAccounts` (`std::sort`), `listBankAccounts`.
- Mỗi test bắt đầu lại từ dữ liệu mẫu (chạy lại chương trình, **không** chọn `11` lưu file).

## 1. Test case

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TC06-01 | Hiển thị dữ liệu mẫu, sắp xếp theo typeName, trùng typeName thì theo ID (**Test 06 của đề**) | Dữ liệu mẫu | 1. Chạy chương trình<br>2. Chọn `6` | Bảng có tiêu đề cột, các cột thẳng hàng. Thứ tự: `A02` (Checking), `A01`, `A04` (Savings), `A03` (Student). Cuối bảng `Total: 4 account(s).` Xem bảng đầy đủ ở mục 2 | | |
| TC06-02 | Trùng typeName: tài khoản mới thêm có ID nhỏ hơn phải đứng đầu nhóm | Dữ liệu mẫu | 1. Chọn `8`, chọn loại `T01`, nhập `A00`, `Hoang Em`, `AC10000`, `1000000`<br>2. Chọn `6` | Nhóm Savings theo thứ tự `A00`, `A01`, `A04` (A00 thêm sau nhưng đứng trước). `Total: 5 account(s).` | | |
| TC06-03 | So sánh typeName không phân biệt hoa/thường | Dữ liệu mẫu | 1. Chọn `2`, nhập `T04`, `basic`, `VND`, `0.01`<br>2. Chọn `8`, chọn loại `T04`, nhập `A05`, `Vo Gia`, `AC10005`, `200000`<br>3. Chọn `6` | `A05` (basic) đứng **đầu** bảng, trước `A02` (Checking). Nếu so sánh phân biệt hoa/thường thì `Checking` sẽ đứng trước `basic`, vì `'C'` (67) < `'b'` (98) | | |
| TC06-04 | Sắp xếp lại sau khi sửa BankAccount (CN 10) | Dữ liệu mẫu | 1. Chọn `10`, nhập `A03`, giữ mã `A03`, chọn loại `T02`, nhập `Le Chi`, `AC10003`, `800000`<br>2. Chọn `6` | Nhóm Checking có `A02`, `A03`; không còn nhóm Student. Thứ tự: `A02`, `A03`, `A01`, `A04` | | |
| TC06-05 | Sắp xếp lại sau khi đổi tên AccountType (CN 4) | Dữ liệu mẫu | 1. Chọn `4`, nhập `T01`, giữ mã `T01`, nhập `Basic Savings`, `VND`, `0.045`<br>2. Chọn `6` | `A01`, `A04` hiện loại `Basic Savings` và chuyển lên **đầu** bảng. Thứ tự: `A01`, `A04`, `A02`, `A03` | | |
| TC06-06 | File nạp vào không theo thứ tự vẫn hiển thị đúng thứ tự | Sửa `bankaccounts.txt` cho các dòng theo thứ tự `A04`, `A03`, `A02`, `A01` | 1. Chạy chương trình<br>2. Chọn `6` | Thứ tự giống TC06-01: `A02`, `A01`, `A04`, `A03` | | |
| TC06-07 | Danh sách rỗng | Đổi tên `bankaccounts.txt` thành `bankaccounts.bak` | 1. Chạy chương trình<br>2. Chọn `6` | Báo `Error: cannot open bankaccounts.txt. ...` khi khởi động; CN 6 in `No bank accounts.`, chương trình không dừng | | |
| TC06-08 | Số dư lớn và số lẻ hiển thị dạng số thường | Dữ liệu mẫu | 1. Chọn `8`, chọn loại `T02`, nhập `A06`, `Do Hai`, `AC10006`, `123456789.5`<br>2. Chọn `6` | Dòng `A06` có số dư `123456789.50 VND`, không phải dạng `1.23457e+08`; cột số dư căn phải thẳng hàng | | |

## 2. Kết quả mong đợi đầy đủ của TC06-01

```
--- BANK ACCOUNTS (ID | typeName | owner | number | balance) ---
ID      Type        Owner                 Number                 Balance Currency
---------------------------------------------------------------------------------
A02     Checking    Tran Binh             AC10002             3000000.00 VND
A01     Savings     Nguyen An             AC10001            12000000.00 VND
A04     Savings     Pham Dung             AC10004             5000000.00 VND
A03     Student     Le Chi                AC10003              800000.00 VND
Total: 4 account(s).
```

## 3. Ghi chú

- accountID được so sánh theo chuỗi, nên `A10` đứng trước `A9`. Dữ liệu mẫu dùng mã đủ 2 chữ số (`A01`, `A02`, …) nên không bị ảnh hưởng.
- `ownerName` dài hơn 21 ký tự hoặc `typeName` dài hơn 11 ký tự sẽ làm lệch cột (`std::setw` không cắt chuỗi). Tên tiếng Việt có dấu (UTF-8) cũng có thể lệch cột trên console.

## 4. Tổng hợp

| Nhóm | Số test | Đạt |
|---|---|---|
| CN 6 | 8 | |

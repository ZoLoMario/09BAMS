# Test case CN 10, Test 12 (phần nạp file) và Exit

- Người viết, người chạy: K26DTCN100 – Vũ Đăng Khôi
- Chạy lần 1: 18/11/2026 trên nhánh `khoi-main-tich-hop`. **Chạy lại: 25/11/2026 trên `main` commit `1ece4c0`** (đã có code của Phong, Khánh, Đạt). Cột "Thực tế" dưới đây là kết quả lần chạy lại.
- Môi trường: g++ `-std=c++11`, Linux. **Chưa chụp ảnh trên Dev-C++**: cần chụp lại trên Windows, đặt tên ảnh theo mã test (ví dụ `TC10-01.png`).
- Dữ liệu ban đầu: `accounttypes.txt`, `bankaccounts.txt` mẫu trên `main` (T01–T03; A01–A04, trong đó A01 và A04 cùng loại Savings).

## 1. Test case CN 10 – Update BankAccount by ID (Test 10 của đề)

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TC10-01 | Mã không tồn tại | Dữ liệu mẫu | 1. Chọn `10`<br>2. Nhập `A99` | Báo không tìm thấy, quay về menu | `Error: accountID A99 not found.` rồi hiện lại menu | ✅ |
| TC10-02 | Mã mới trùng mã của tài khoản khác | Dữ liệu mẫu | 1. Chọn `10`, nhập `A02`<br>2. Mã mới nhập `A01`<br>3. Nhập lại `A02`, nhập tiếp hợp lệ | Báo trùng, cho nhập lại mã | `[Error] ID already exists. Please try again.` | ✅ |
| TC10-03 | Chọn AccountType không tồn tại | Dữ liệu mẫu | 1. Chọn `10`, nhập `A02`, giữ mã `A02`<br>2. Chọn loại `T09`<br>3. Chọn lại `T02` | Báo lỗi, cho chọn lại loại | `[Error] AccountType ID not found. Please try again.` | ✅ |
| TC10-04 | Số dư âm, số dư không phải số | Dữ liệu mẫu | 1. Chọn `10`, nhập `A02` và các trường hợp lệ<br>2. Số dư nhập `-5`, rồi `abc`, rồi `3000000` | Báo lỗi từng lần, cho nhập lại | `[Error] Value must be greater than or equal to 0` rồi `[Error] Invalid number format` | ✅ |
| TC10-05 | Sửa hợp lệ, danh sách sắp xếp lại | Dữ liệu mẫu | 1. Chọn `10`, nhập `A02`<br>2. Nhập `A05`, `T01`, `Tran Binh Moi`, `AC20002`, `4500000`<br>3. Chọn `6` | `BankAccount updated.` A05 nằm trong nhóm Savings, sau A01, A04 | `A01, A04, A05` (Savings) rồi `A03` (Student). Dòng A05: `A05 \| Savings \| Tran Binh Moi \| AC20002 \| 4500000.00` | ✅ |
| TC10-06 | Dữ liệu sửa được lưu và nạp lại đúng | Như TC10-05 | 1. Sửa A02 thành A05, số dư `12345678.9`<br>2. Chọn `11`, chọn `0`<br>3. Chạy lại, chọn `6` | File ghi đúng số dư, không mất chữ số; lần chạy sau vẫn còn A05 | File: `A05, T01, Tran Binh Moi, AC20002, 12345678.90`. Chạy lại: `A05 \| Savings \| … \| 12345678.90` | ✅ (lần 1 ngày 18/11 số dư bị ghi dạng `4.5e+06`; Đạt đã sửa ở PR #4) |

## 2. Test case Test 12 – Nạp file lỗi

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TC12-01 | Thiếu cả hai file dữ liệu | Thư mục chạy không có `accounttypes.txt`, `bankaccounts.txt` | 1. Chạy chương trình<br>2. Chọn `1`, `6`, `0` | Báo rõ thiếu file, chương trình vẫn chạy với danh sách rỗng | `Error: cannot open accounttypes.txt. Starting with an empty AccountType list.` (tương tự với `bankaccounts.txt`), `Loaded 0 account type(s) and 0 bank account(s).`, CN 1 in `Danh sach AccountType trong!` | ✅ |
| TC12-02 | File có nhiều dòng sai | Hai file như mục 4 dưới đây | 1. Chạy chương trình<br>2. Chọn `1`, `6` | Mỗi dòng sai bị bỏ qua, báo số dòng và lý do; dòng đúng vẫn được nạp | 10 dòng `Warning: … line N skipped (<lý do>)`, đúng 10 dòng sai. `Loaded 2 account type(s) and 2 bank account(s).` (T01, T07; A01, A04) | ✅ |
| TC12-03 | Nhập sai ở menu (phần menu của Trung, chạy thử kèm) | Dữ liệu mẫu | Ở menu lần lượt nhập `abc`, `99`, `-1`, (rỗng), `3x`, rồi `1` | Báo lỗi, không dừng chương trình, lần nhập đúng vẫn chạy | `[Error] Invalid integer.` (3 lần: `abc`, rỗng, `3x`); `[Error] Please enter a number between 0 and 14.` (2 lần: `99`, `-1`); sau đó CN 1 chạy bình thường | ✅ |

## 3. Test case Exit (chọn 0)

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TC00-01 | Thoát khi còn thay đổi chưa lưu, không tự ghi file | Dữ liệu mẫu | 1. Chọn `2` thêm `T04`; chọn `9` xoá `A03`<br>2. Chọn `0`, trả lời `n`<br>3. Chọn `0`, trả lời `y` | Cảnh báo còn thay đổi chưa lưu, hỏi y/n; `n` quay về menu; `y` thoát; **hai file không đổi** | `Warning: you have unsaved changes [AccountTypes: use 5] [BankAccounts: use 11].` rồi `Exit without saving? (y/n)`; `n` về menu, `y` in `Goodbye!`; md5 của hai file trước và sau giống nhau | ✅ |

## 4. Dữ liệu dùng cho TC12-02

`accounttypes.txt` (6 dòng sai, đánh số theo dòng trong file):

```
# accountTypeID, typeName, currency, interestRate
T01, Savings, VND, 0.045          <- dong 2: dung
T02, Checking, VND                <- dong 3: thieu truong
T03, Student, VND, abc            <- dong 4: lai suat khong phai so
T04, , VND, 0.01                  <- dong 5: typeName rong
T05, Zero, VND, 0                 <- dong 6: lai suat = 0
T01, Dup, VND, 0.02               <- dong 7: trung ma T01
T06, Premium, USD, 12abc          <- dong 8: so co chu theo sau
T07, Business, VND, 0.03          <- dong 9: dung
```

`bankaccounts.txt` (4 dòng sai):

```
# accountID, accountType, ownerName, accountNumber, balance
A01, T01, Nguyen An, AC10001, 12000000      <- dong 2: dung
A02, T99, Tran Binh, AC10002, 3000000       <- dong 3: loai T99 khong ton tai
A03, T01, Le Chi, AC10003, -500             <- dong 4: so du am
A04, T07, Pham Dung, AC10004, 5000000       <- dong 5: dung
A01, T07, Trung Ma, AC10005, 100            <- dong 6: trung ma A01
A06, T01, Thieu Truong, AC10006             <- dong 7: thieu truong
```

Khi chạy thật, xoá phần `<- …` ở cuối mỗi dòng.

## 5. Tổng hợp

| Nhóm | Số test | Đạt |
|---|---|---|
| CN 10 | 6 | 6 |
| Test 12 (nạp file, menu) | 3 | 3 |
| Exit | 1 | 1 |
| **Cộng** | **10** | **10** |

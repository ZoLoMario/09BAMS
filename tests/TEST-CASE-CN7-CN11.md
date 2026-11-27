# Test case CN 7 và CN 11

- Người viết: K26DTCN008 – Nguyễn Thành Đạt
- Chạy: 26/11/2026 trên nhánh `dat-bankaccountlist` đã merge `main` commit `d70f232` (đã có code của Phong, Khánh, Khôi). Cột "Thực tế" dưới đây là kết quả lần chạy này.
- Môi trường: clang++ (Apple clang 17) `-std=c++11`, macOS. Các bước nhập được nạp sẵn vào chương trình, không gõ tay. **Chưa chụp ảnh trên Dev-C++**: cần chạy lại bằng tay trên Windows và chụp ảnh, đặt tên ảnh theo mã test (ví dụ `TC07-01.png`).
- Dữ liệu ban đầu: `accounttypes.txt`, `bankaccounts.txt` mẫu trên `main` (T01–T03; A01–A04, trong đó A01 và A04 cùng loại Savings). Mỗi test chạy trên bản dữ liệu mẫu mới, trừ khi cột "Điều kiện đầu" ghi khác.

## 1. Test case CN 7 – Search BankAccounts by partial typeName (Test 07 của đề)

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TC07-01 | Chuỗi một phần, có kết quả (**Test 07 của đề**) | Dữ liệu mẫu | 1. Chọn `7`<br>2. Nhập `Sav` | Hiện đúng 2 tài khoản loại Savings (A01, A04) theo thứ tự mã; A02, A03 không hiện | `A01 \| Savings \| Nguyen An \| AC10001 \| 12000000.00` và `A04 \| Savings \| Pham Dung \| AC10004 \| 5000000.00` | ✅ |
| TC07-02 | Không phân biệt hoa/thường | Dữ liệu mẫu | 1. Chọn `7`, nhập `SAV`<br>2. Chọn `7`, nhập `cHeCk` | `SAV` ra A01, A04; `cHeCk` ra A02 | `SAV`: A01, A04 (Savings). `cHeCk`: `A02 \| Checking \| Tran Binh \| AC10002 \| 3000000.00` | ✅ |
| TC07-03 | Chuỗi nằm giữa tên, khớp nhiều loại; sắp theo typeName rồi mã | Dữ liệu mẫu | 1. Chọn `7`<br>2. Nhập `ing` | Hiện A02 (Checking) trước, rồi A01, A04 (Savings); A03 (Student) không hiện | Thứ tự `A02`, `A01`, `A04`; không có A03 | ✅ |
| TC07-04 | Nhập đủ tên loại | Dữ liệu mẫu | 1. Chọn `7`<br>2. Nhập `Student` | Chỉ hiện A03 | `A03 \| Student \| Le Chi \| AC10003 \| 800000.00` | ✅ |
| TC07-05 | Chuỗi không có kết quả (**Test 07 của đề**) | Dữ liệu mẫu | 1. Chọn `7`<br>2. Nhập `zzz` | Báo không có tài khoản nào khớp, quay về menu | `No BankAccount matches "zzz".` rồi hiện lại menu | ✅ |
| TC07-06 | Khoảng trắng ở đầu và cuối | Dữ liệu mẫu | 1. Chọn `7`<br>2. Nhập `  sav  ` (hai dấu cách mỗi đầu) | Kết quả giống TC07-01 | A01, A04 (Savings) | ✅ |
| TC07-07 | Nhập rỗng | Dữ liệu mẫu | 1. Chọn `7`<br>2. Nhấn Enter, không nhập gì<br>3. Nhập `sav` | Báo lỗi, cho nhập lại; sau đó tìm bình thường | `[Error] Input cannot be empty. Please try again.` rồi hỏi lại; `sav` ra A01, A04 | ✅ |
| TC07-08 | Danh sách tài khoản rỗng | Đổi tên `bankaccounts.txt` thành `bankaccounts.bak` | 1. Chạy chương trình<br>2. Chọn `7`, nhập `sav` | Báo thiếu file lúc khởi động; tìm không có kết quả, chương trình không dừng | `Error: cannot open bankaccounts.txt. Starting with an empty BankAccount list.`, `Loaded 3 account type(s) and 0 bank account(s).`, rồi `No BankAccount matches "sav".` | ✅ |
| TC07-09 | Tìm sau khi đổi tên loại bằng CN 4 | Dữ liệu mẫu | 1. Chọn `4`, nhập `T01`; mã mới `T01`, tên mới `Gold`, tiền tệ `VND`, lãi suất `0.045`<br>2. Chọn `7`, nhập `gold`<br>3. Chọn `7`, nhập `sav`<br>4. Chọn `0`, trả lời `y` | `gold` ra A01, A04 với tên loại mới `Gold`; `sav` không còn kết quả | `gold`: `A01 \| Gold \| Nguyen An \| …` và `A04 \| Gold \| Pham Dung \| …`. `sav`: `No BankAccount matches "sav".` | ✅ |

## 2. Test case CN 11 – Save BankAccounts (Test 11 của đề)

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TC11-01 | Lưu dữ liệu mẫu, đối chiếu file (**Test 11 của đề**) | Dữ liệu mẫu | 1. Chọn `11`<br>2. Chọn `0`<br>3. Mở `bankaccounts.txt` bằng Notepad | Màn hình `Saved BankAccounts to bankaccounts.txt.`<br>File có dòng tiêu đề `#` và 4 dòng dữ liệu theo thứ tự typeName rồi mã, các trường cách nhau bằng `, `, số dư 2 chữ số thập phân, không có `e+` | `Saved BankAccounts to bankaccounts.txt.`<br>File: `# accountID, accountType, ownerName, accountNumber, balance`, `A02, T02, Tran Binh, AC10002, 3000000.00`, `A01, T01, Nguyen An, AC10001, 12000000.00`, `A04, T01, Pham Dung, AC10004, 5000000.00`, `A03, T03, Le Chi, AC10003, 800000.00` | ✅ |
| TC11-02 | Số dư lớn không mất chữ số, không ghi dạng `e+` | Dữ liệu mẫu | 1. Chọn `8`, chọn loại `T01`, nhập `A05`, `Test User`, `AC10005`, `12345678.55`<br>2. Chọn `8`, chọn loại `T02`, nhập `A06`, `Big Money`, `AC10006`, `1234567890`<br>3. Chọn `11`, chọn `0`<br>4. Mở `bankaccounts.txt` | File có thêm 2 dòng với số dư đủ chữ số | `A06, T02, Big Money, AC10006, 1234567890.00` và `A05, T01, Test User, AC10005, 12345678.55` (bản cũ ghi `1.23457e+07`) | ✅ |
| TC11-03 | Chạy lại chương trình, dữ liệu đúng như trước khi lưu (**Test 11 của đề**) | Sau TC11-02 | 1. Chạy lại chương trình<br>2. Chọn `6` | Không có dòng `Warning`; nạp đủ 6 tài khoản, số dư đúng | `Loaded 3 account type(s) and 6 bank account(s).`, không có `Warning`; A05 `12345678.55`, A06 `1234567890.00` | ✅ |
| TC11-04 | Lưu sau khi xoá | Dữ liệu mẫu | 1. Chọn `9`, nhập `A03`<br>2. Chọn `11`, chọn `0`<br>3. Mở `bankaccounts.txt` | File còn 3 dòng dữ liệu, không còn A03 | Còn `A02`, `A01`, `A04` | ✅ |
| TC11-05 | Lưu sau khi đổi mã loại (lưu cả hai file) | Dữ liệu mẫu | 1. Chọn `4`, nhập `T01`; mã mới `T09`, tên `Savings`, tiền tệ `VND`, lãi suất `0.045`<br>2. Chọn `5`, rồi chọn `11`, rồi chọn `0`<br>3. Chạy lại, chọn `6` | Hai file đều ghi `T09`; lần chạy sau nạp đủ 4 tài khoản, không có `Warning` | `accounttypes.txt`: `T09, Savings, VND, 0.045`. `bankaccounts.txt`: A01, A04 đều `T09`. Chạy lại: `Loaded 3 account type(s) and 4 bank account(s).` | ✅ |
| TC11-06 | Không ghi được file | `bankaccounts.txt` đặt thuộc tính chỉ đọc (Read-only) | 1. Chọn `9`, nhập `A03`<br>2. Chọn `11`<br>3. Chọn `0`, trả lời `n`<br>4. Chọn `0`, trả lời `y` | Báo không ghi được; khi thoát vẫn cảnh báo còn thay đổi chưa lưu; nội dung file không đổi | `Error: cannot write bankaccounts.txt.`; hai lần `Warning: you have unsaved changes [BankAccounts: use 11].` rồi `Exit without saving? (y/n)`; md5 của file trước và sau giống nhau | ✅ |
| TC11-07 | Lưu danh sách rỗng | Dữ liệu mẫu | 1. Chọn `9` lần lượt `A01`, `A02`, `A03`, `A04`<br>2. Chọn `11`, chọn `0`<br>3. Chạy lại, chọn `6` | File chỉ còn dòng tiêu đề; lần chạy sau không báo lỗi, danh sách rỗng | File chỉ có `# accountID, accountType, ownerName, accountNumber, balance`. Chạy lại: `Loaded 3 account type(s) and 0 bank account(s).`, không có `Error` hay `Warning` | ✅ |

## 3. Tổng hợp

| Nhóm | Số test | Đạt |
|---|---|---|
| CN 7 (Test 07) | 9 | 9 |
| CN 11 (Test 11) | 7 | 7 |
| **Cộng** | **16** | **16** |

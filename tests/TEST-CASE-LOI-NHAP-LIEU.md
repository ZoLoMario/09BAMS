# Test case sửa lỗi nhập liệu và lưu file (bổ sung Test 02, 08, 10, 11, 12)

- Người viết, người chạy: K26DTCN100 – Vũ Đăng Khôi
- Chạy: 27/11/2026 trên nhánh `khoi-sua-loi-nhap-lieu` (tách từ `main` `68b31b5`, đã gộp PR #8, #9). g++ 13 `-std=c++11 -Wall -Wextra -pedantic`, không cảnh báo.
- Dữ liệu ban đầu: `accounttypes.txt`, `bankaccounts.txt` mẫu trên `main`. Mỗi test chạy trên bản dữ liệu mẫu mới.
- **Chưa chụp ảnh trên Dev-C++.** Khi chụp, đặt tên ảnh theo mã test (ví dụ `TCLN-01.png`).

## 1. Lỗi đã sửa

| # | Lỗi trên `main` trước khi sửa | Chỗ sửa |
|---|---|---|
| 1 | Nhập `nan`, `inf` ở số dư, lãi suất, số tiền nạp/rút vẫn được nhận (`nan < 0` là false nên lọt mọi phép kiểm). Lưu xong mở lại thì tài khoản số dư `nan` bị bỏ qua, mất tài khoản. Lãi suất `nan` còn nạp lại được từ file | `Utils::inputDouble`, `DataFile::parseNumber` |
| 2 | Nhập `0x10` được hiểu là 16 | như trên |
| 3 | Hết đầu vào (Ctrl+Z / Ctrl+D, hoặc file nhập hết dòng) thì vòng nhập lặp vô hạn, in hàng triệu dòng, phải tắt cưỡng bức | `Utils::readLine` + `Utils::InputEnded`, `AccountTypeList::getUserChoice`, `Menu::getChoice`, `BankAccountManager::run` |
| 4 | Lưu (CN 5, CN 11) xoá trắng file ngay khi mở; ghi hỏng giữa chừng thì file còn 0 byte | `saveToFile` của 2 lớp danh sách: ghi ra `*.tmp` rồi mới thay file thật (`DataFile::canWrite`, `DataFile::replaceFile`) |
| 5 | File lưu bằng Notepad dạng "UTF-8 có BOM" mà không có dòng tiêu đề thì mã đầu tiên (T01) không khớp, mất T01 và mọi tài khoản thuộc T01 | `DataFile::removeBom`, gọi ở dòng 1 của 2 hàm `loadFromFile` |

## 2. Test case

| Mã | Mục đích | Điều kiện đầu | Các bước | Kết quả mong đợi | Thực tế | Đạt? |
|---|---|---|---|---|---|---|
| TCLN-01 | Số dư không phải số thường (Test 08) | Dữ liệu mẫu | 1. Chọn `8`, chọn `T01`, nhập `A09`, `Test`, `AC9`<br>2. Số dư lần lượt `nan`, `inf`, `0x10`, `-inf`, `1e400`, rồi `500`<br>3. Chọn `6` | 5 lần đầu báo lỗi và hỏi lại; `500` được nhận; A09 có số dư 500.00 | 5 lần `[Error] Invalid number format. Please try again.`, rồi `BankAccount added.`; `A09  Savings  Test  AC9  500.00 VND` | ✅ |
| TCLN-02 | Nạp tiền `nan` | Dữ liệu mẫu | 1. Chọn `12`, nhập `A01`<br>2. Số tiền `nan`, rồi `100` | `nan` bị từ chối; số dư A01 thành 12000100.00 | `Invalid number format`, rồi `New balance: A01 … 12000100.00 VND` | ✅ |
| TCLN-03 | Lãi suất `NaN` (Test 02) | Dữ liệu mẫu | 1. Chọn `2`, nhập `T09`, `X`, `VND`<br>2. Lãi suất `NaN`, rồi `0.02` | `NaN` bị từ chối, `0.02` được nhận | `Invalid number format`, rồi `AccountType added.` | ✅ |
| TCLN-04 | File có lãi suất `nan` và số dư `0x10` (Test 12) | Thêm dòng `T09, Bad, VND, nan` vào cuối `accounttypes.txt` và `A09, T01, Hex, AC9, 0x10` vào cuối `bankaccounts.txt` | Chạy chương trình | Hai dòng bị bỏ qua, có cảnh báo; nạp 3 loại, 4 tài khoản | `Warning: accounttypes.txt line 5 skipped (interestRate is not a number)`, `Warning: bankaccounts.txt line 6 skipped (balance is not a number)`, `Loaded 3 account type(s) and 4 bank account(s).` | ✅ |
| TCLN-05 | Hết đầu vào ở menu (Test 12) | Dữ liệu mẫu | Chạy, bấm Ctrl+Z rồi Enter (Windows) hoặc Ctrl+D (Linux) ngay ở `Your choice:` | Báo hết đầu vào rồi thoát, không lặp | `Input ended.` `Goodbye!`, thoát mã 0 (output 22 dòng; bản cũ: 73 nghìn dòng trong 3 giây và không tự thoát) | ✅ |
| TCLN-06 | Hết đầu vào giữa lúc nhập tài khoản | Dữ liệu mẫu | 1. Chọn `8`, chọn `T01`, nhập `A09`<br>2. Bấm Ctrl+Z ở `Enter ownerName:` | Thoát gọn, không thêm tài khoản | `Input ended.` `Goodbye!` (bản cũ: 9 triệu dòng trong 3 giây) | ✅ |
| TCLN-07 | Hết đầu vào lúc chọn loại tài khoản | Dữ liệu mẫu | 1. Chọn `8`<br>2. Bấm Ctrl+Z ở `Enter accountTypeID:` | Thoát gọn | `Input ended.` `Goodbye!` | ✅ |
| TCLN-08 | Hết đầu vào khi còn thay đổi chưa lưu | Dữ liệu mẫu | 1. Chọn `12`, nhập `A01`, `100`<br>2. Bấm Ctrl+Z ở menu | Thoát, báo rõ thay đổi chưa được lưu, file không đổi | `Input ended. Unsaved changes were NOT saved.` `Goodbye!` | ✅ |
| TCLN-09 | Ghi hỏng giữa chừng không làm mất file cũ (Test 05, 11) | Dữ liệu mẫu; giả lập không ghi được dữ liệu (`ulimit -f 0` trên Linux) | 1. Chọn `12`, nạp 100 vào `A01`, chọn `11`<br>2. Chọn `4`, đổi tên T01 thành `Gold`, chọn `5`<br>3. Chọn `0`, trả lời `y` | Báo không ghi được; hai file giữ nguyên nội dung cũ; không còn file `.tmp` | `Error: cannot write bankaccounts.txt.`, `Error: cannot write accounttypes.txt.`; md5 hai file trước và sau giống nhau; thư mục chỉ còn 2 file txt (bản cũ: cả hai file còn 0 byte) | ✅ |
| TCLN-10 | File chỉ đọc (lặp lại TC11-06 của Đạt) | `bankaccounts.txt` đặt Read-only | 1. Chọn `9`, nhập `A03`<br>2. Chọn `11`<br>3. Chọn `0`, trả lời `y` | Báo không ghi được, file không đổi | `Error: cannot write bankaccounts.txt.`; md5 không đổi | ✅ |
| TCLN-11 | Lưu bình thường vẫn đúng (Test 05, 11) | Dữ liệu mẫu | 1. Chọn `8`, `T02`, `A05`, `Big Money`, `AC5`, `1234567890.5`, rồi chọn `11`<br>2. Chọn `2`, `T04`, `Premium`, `USD`, `0.02`, rồi chọn `5`, chọn `0`<br>3. Chạy lại, chọn `6` | Hai file có dòng mới; không còn `.tmp`; chạy lại không cảnh báo | File có `A05, T02, Big Money, AC5, 1234567890.50` và `T04, Premium, USD, 0.02`; `Loaded 4 account type(s) and 5 bank account(s).`, không có `Warning` | ✅ |
| TCLN-12 | File UTF-8 có BOM, không có dòng tiêu đề (Test 01, 12) | Lưu cả 2 file bằng Notepad, chọn "UTF-8 with BOM", xoá dòng `#` | Chạy chương trình | Nạp đủ 3 loại, 4 tài khoản, không cảnh báo | `Loaded 3 account type(s) and 4 bank account(s).` (bản cũ: mất T01, chỉ nạp được 2 tài khoản) | ✅ |
| TCLN-13 | Dùng bình thường không đổi | Dữ liệu mẫu | Chạy 4 phiên phủ cả 14 chức năng (thêm/tìm/sửa/lưu loại, liệt kê, tìm, thêm, xoá, sửa, lưu tài khoản, nạp, rút quá số dư, tính lãi, nhập sai nhiều kiểu, thoát có/không lưu) trên bản cũ `49150ad` và bản sửa | Màn hình và 2 file sau khi chạy giống hệt nhau | `diff` cả 4 phiên: giống hệt (146, 207, 181, 21 dòng) | ✅ |

## 3. Tổng hợp

| Nhóm | Số test | Đạt |
|---|---|---|
| Số không hợp lệ (TCLN-01 → 04) | 4 | 4 |
| Hết đầu vào (TCLN-05 → 08) | 4 | 4 |
| Lưu file (TCLN-09 → 11) | 3 | 3 |
| BOM (TCLN-12) | 1 | 1 |
| Không đổi hành vi (TCLN-13) | 1 | 1 |
| **Cộng** | **13** | **13** |

## 4. Còn lại, chưa làm trong lần sửa này

- Xoá rồi đổi tên file (`replaceFile`) có một khoảng rất ngắn giữa hai bước. Nếu mất điện đúng lúc đó thì file thật chưa có, dữ liệu nằm trong `*.tmp`; đổi tên lại là dùng được.
- `Menu::getChoice` đã chặn lặp khi hết đầu vào, nhưng class `Menu` vẫn chưa được dùng ở đâu (phần 3.9 của Trung).

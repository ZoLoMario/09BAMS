# Tiến độ Nhóm 7 – Topic 09

> **Cập nhật lần cuối:** 18/11/2026, Khôi (sau khi gộp PR #1)
> **Mốc:** họp lần 2 / code freeze **22/11 20h00** · họp lần 3 / demo thử **28/11 20h00** · nộp bài **29/11** (hạn chót 30/11)
> Cách cập nhật file này: xem mục [Theo dõi tiến độ](README.md#theo-dõi-tiến-độ) trong README.

**Trạng thái:** ✅ Xong · 👀 Chờ review/duyệt · 🔄 Đang làm · ⏳ Chưa tới hạn · ⚠️ Quá hạn

## Tổng quan

| Giai đoạn | Thời gian | Phụ trách | Trạng thái |
|---|---|---|---|
| GĐ1 Phân tích yêu cầu | 11/11 – 13/11 | Hanh (duyệt: Phong) | 🔄 |
| GĐ2 Thiết kế (UML, file txt, repo) | 13/11 – 15/11 | Hanh, Trung (duyệt: Phong) | 👀 |
| GĐ3 Lập trình | 15/11 – **22/11** | Cả nhóm (review chéo) | 🔄 |
| GĐ4 Kiểm thử & sửa lỗi | 21/11 – 25/11 | Trung + cả nhóm (duyệt: Khánh) | ⏳ |
| GĐ5 Báo cáo & slide | 23/11 – 27/11 | Đạt tổng hợp (duyệt: Hanh, Tài) | ⏳ |
| GĐ6 Demo thử & nộp | 27/11 – 29/11 | Khôi + cả nhóm | ⏳ |

## Việc từng người

| # | Việc | Người làm | Duyệt | Hạn | Trạng thái | Sản phẩm / ghi chú |
|---|---|---|---|---|---|---|
| 1.1 | Phân tích 11 chức năng, ràng buộc, giả mã | Hanh | Phong | 13/11 | 🔄 | Bản đầu: Drive `1.Document/Nhom_7_Phan_tich_yeu_cau_Hanh.docx`. Đang rà lại theo menu 11 chức năng của đề |
| 2.1 | UML Class Diagram 6 class | Hanh | Phong | 14/11 | 👀 | Bản nháp: [`docs/`](docs/) (`.png`, `.drawio`) |
| 2.2 | Chốt chữ ký hàm, file `.h` | Hanh | | 15/11 | ✅ | Có trên `main` |
| 2.3 | `accounttypes.txt`, `bankaccounts.txt` | Trung | | 15/11 | 👀 | Trên `main` đã dùng dữ liệu mẫu của đề (PR #1), chờ Trung xác nhận |
| 2.4 | Repo GitHub | Khôi | | 15/11 | ✅ | Đủ 7 thành viên |
| 3.1 | `AccountType`; CN 1, 5 | Khánh | Trung | 19/11 | 🔄 | Còn: `toString()` hiện lãi suất 3–4 chữ số thập phân |
| 3.2 | CN 2–4, `getUserChoice` | Hanh | Khánh | 19/11 | 🔄 | Còn: `searchID` không phân biệt hoa/thường |
| 3.3 | `BankAccount`; CN 6 | Phong | Hanh | 19/11 | 🔄 | Còn: `operator<`, `screenString()` |
| 3.4 | CN 7, CN 11 | Đạt | Phong | 20/11 | 🔄 | Còn: tìm theo **một phần** typeName; `saveToFile` ghi số dư dạng thường (không `e+07`) |
| 3.5 | CN 8–9 | Tài | Đạt | 20/11 | ✅ | |
| 3.6 | Kiểm tra lỗi khi nạp file | Khôi | Tài | 20/11 | ✅ | Đã gộp vào `main` ([PR #1](https://github.com/ZoLoMario/09BAMS/pull/1), 18/11). Tài vẫn review và điền phần duyệt trong comment |
| 3.7 | CN 10; `BankAccountManager`/`main()` | Khôi | Tài | 22/11 | ✅ | Đã gộp vào `main` (PR #1). Menu đủ 11 chức năng + 0 Exit |
| 3.8 | Mở rộng: nạp/rút, lãi | Khôi | Tài | 22/11 | ✅ | Đã gộp vào `main` (PR #1), menu 12–14 |
| 3.9 | `Menu` template, nhập an toàn, ngoại lệ | Trung | Khôi | 17/11 | 🔄 | `Utils.h` đã có; còn `Menu` template (`int_getChoice`/`ref_getChoice`) |
| 3.10 | Comment đầu tệp/hàm đúng mẫu (MSSV, người duyệt) | Cả nhóm | | 22/11 | 🔄 | Mỗi người sửa phần mình |
| 3.11 | **Code freeze**: Dev-C++ build không lỗi, đủ 11 chức năng | Khôi | Cả nhóm | **22/11** | ⏳ | |
| 4.1 | Bảng test case | Trung | | 22/11 | ⏳ | |
| 4.2 | Chạy test phần mình (bảng dưới) | Từng người | | 24/11 | 🔄 | |
| 4.3 | Tổng hợp lỗi, chụp ảnh 11 chức năng | Trung | Khánh | 25/11 | ⏳ | |
| 5.1 | Báo cáo Phần I–III, VIII–IX | Đạt | Hanh | 26/11 | 🔄 | |
| 5.2 | Báo cáo Phần IV–V | Hanh | Hanh | 25/11 | ⏳ | |
| 5.3 | Báo cáo Phần VI + hướng dẫn chạy | Khôi | Hanh | 25/11 | 🔄 | Mỗi người gửi Khôi mô tả hàm mình viết |
| 5.4 | Báo cáo Phần VII | Trung | Hanh | 25/11 | ⏳ | |
| 5.5 | Slide 6 trang | Đạt | Tài | 27/11 | ⏳ | |
| 6.1 | Demo thử, tập thuyết trình | Cả nhóm | | 28/11 | ⏳ | |
| 6.2 | Checklist, đánh giá đóng góp, nộp | Khôi, Đạt | Cả nhóm | 29/11 | ⏳ | |

## Họp và báo cáo tiến độ

| Việc | Ai | Hạn | Trạng thái |
|---|---|---|---|
| Họp lần 1: thống nhất kế hoạch, phân công | Cả nhóm | 13/11 | ✅ Có mặt 7/7 |
| Biên bản họp lần 1 (ghi kết quả, ảnh) | Đạt | 14/11 | 🔄 |
| Phiếu báo cáo tiến độ kỳ 1 | Từng người | 15/11 | ⚠️ |
| Phiếu báo cáo tiến độ kỳ 2 | Từng người | 22/11 | ⏳ |
| Họp lần 2: code freeze | Cả nhóm | 22/11 20h00 | ⏳ |
| Phiếu báo cáo tiến độ kỳ 3 | Từng người | 28/11 | ⏳ |
| Họp lần 3: demo thử | Cả nhóm | 28/11 20h00 | ⏳ |

## 11 chức năng theo đề

| CN | Chức năng | Người | Trạng thái |
|---|---|---|---|
| 1 | List all AccountTypes | Khánh | ✅ |
| 2 | Add a new AccountType | Hanh | ✅ |
| 3 | Search AccountType by ID | Hanh | ✅ |
| 4 | Update AccountType | Hanh | ✅ |
| 5 | Save AccountTypes | Khánh | ✅ |
| 6 | List BankAccounts sorted by typeName | Phong | 🔄 (còn `operator<`) |
| 7 | Search BankAccounts by partial typeName | Đạt | 🔄 |
| 8 | Add a new BankAccount | Tài | ✅ |
| 9 | Remove BankAccount by ID | Tài | ✅ |
| 10 | Update BankAccount by ID | Khôi | ✅ |
| 11 | Save BankAccounts | Đạt | 🔄 |
| 0 | Exit (không tự ghi đè) | Khôi | ✅ |

## 12 test case bắt buộc

| Test | Nội dung | Người chạy | Trạng thái |
|---|---|---|---|
| 01 | Nạp và hiển thị 3 AccountType | Khánh | ⏳ |
| 02 | Thêm AccountType: mã trùng, tên rỗng, số sai | Hanh | ⏳ |
| 03 | Tìm AccountType: ID có / không có | Hanh | ⏳ |
| 04 | Sửa AccountType, xác nhận dữ liệu | Hanh | ⏳ |
| 05 | Lưu accounttypes.txt, mở lại đối chiếu | Khánh | ⏳ |
| 06 | Sắp xếp theo typeName rồi ID (có typeName trùng) | Phong | ⏳ |
| 07 | Tìm theo một phần typeName: có / không có kết quả | Đạt | ⏳ |
| 08 | Thêm BankAccount: mã trùng, tham chiếu sai | Tài | ⏳ |
| 09 | Xoá BankAccount: ID có / không có | Tài | ⏳ |
| 10 | Cập nhật BankAccount: hợp lệ / không hợp lệ | Khôi | ✅ |
| 11 | Lưu bankaccounts.txt, chạy lại, kiểm tra | Đạt | ⏳ |
| 12 | Tệp thiếu, dòng sai định dạng | Khôi | ✅ |
| 12 | Menu nhập chữ thay vì số | Trung | ⏳ |

## Checklist nộp bài (29/11)

- [ ] Mã nguồn C++ có `main()`, build được trên Dev-C++
- [ ] `accounttypes.txt`, `bankaccounts.txt`: đúng định dạng, mỗi file ít nhất 3 bản ghi
- [ ] UML Class Diagram (attributes, methods, visibility, relationships)
- [ ] `Nhom_7_Bao_cao.docx` đủ Phần I–IX, có ảnh kiểm thử 11 chức năng
- [ ] `Nhom_7_Slides.pptx`
- [ ] Biên bản họp 3 lần
- [ ] Đổi hết tên tệp mẫu `Nhom_X_…` thành `Nhom_7_…`
- [ ] Mỗi thành viên giải thích được class mình phụ trách

## Nhật ký cập nhật

| Ngày | Người | Nội dung |
|---|---|---|
| 18/11 | Khôi | Tạo bảng tiến độ |
| 18/11 | Khôi | Gộp PR #1 vào `main`: 3.6, 3.7, 3.8, CN 3/5/10/0, Test 10, Test 12 (file) xong |

# UndoRedo – Quản lý lịch sử lệnh điều khiển thiết bị (Undo/Redo)

Chương trình console mô phỏng một “thiết bị” có các tham số **gain / range / mode**.
Người dùng có thể nhập lệnh trực tiếp hoặc chạy lệnh từ file script. Hệ thống lưu lịch sử thao tác và hỗ trợ **Undo/Redo nhiều bước**, **Save/Load phiên làm việc**, **Search lịch sử theo từ khóa**, và **Export báo cáo CSV**.

## 1) Chức năng (đối chiếu rubric)
- Thực thi lệnh và cập nhật trạng thái thiết bị: `set`, `show`
- Undo/Redo nhiều bước: `undo`, `redo`
- Lưu/khôi phục phiên: `save`, `load`
- Tìm kiếm lịch sử theo từ khóa: `search`
- Xuất báo cáo: `export` (CSV)
- Chạy lệnh từ file script: `run`

## 2) Cú pháp lệnh
- `set gain <int>`
- `set range <int>`
- `set mode <string>`
- `show`
- `undo [k]`  (mặc định k=1)
- `redo [k]`  (mặc định k=1)
- `search <keyword>`
- `save <path>`          (ví dụ: `data/out/snapshot.txt`)
- `load <path>`
- `export <csv_path>`    (ví dụ: `data/out/report.csv`)
- `run <script_path>`    (ví dụ: `tests/scripts/tc1_basic.txt`)
- `help`
- `exit`

> Quy tắc bắt buộc: **Sau khi `undo`, nếu thực thi lệnh mới (không phải redo) thì redo-stack phải bị xóa.**

## 3) Build & Run

### Cách 1: dùng Makefile (MSYS2 / Git Bash)
```bash
cd /c/UndoRedo
make
./build/app.exe
```

### Cách 2: compile tay bằng g++
```bash
cd /c/UndoRedo
mkdir -p build
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude -o build/app.exe $(find src -name "*.cpp")
./build/app.exe
```

## 4) Demo nhanh (để giảng viên chấm)
Chạy các lệnh sau trong chương trình:

```
set gain 10
set range 5
set mode AUTO
show
undo 2
show
redo 1
show
export data/out/report.csv
save data/out/snapshot.txt
```

## 5) Test
Chạy test bằng input script:

```bash
make
./build/app.exe < tests/scripts/tc1_basic.txt > tests/out/tc1.out
# (tuỳ chọn) so sánh kết quả:
# diff -u tests/expected/tc1.out tests/out/tc1.out
```

## 6) Output
- Báo cáo: `data/out/report.csv`
- Snapshot: `data/out/snapshot.txt`

## 7) Cấu trúc thư mục
```
include/   # header (core/ds/app/io)
src/       # implementation
docs/      # báo cáo + thiết kế + big-o
tests/     # script test + expected
data/      # input/out
```

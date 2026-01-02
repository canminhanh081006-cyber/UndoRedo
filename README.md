# UndoRedo

## Build (MSYS2 / Git Bash)

> Mở Git Bash (hoặc MSYS2 UCRT64) và cd vào thư mục project (nơi có Makefile).

```bash
cd /c/UndoRedo
mkdir -p build
g++ -std=c++17 -O2 -Iinclude -o build/app.exe $(find src -name "*.cpp")

# UndoRedo - Quản lý lịch sử lệnh điều khiển thiết bị

## Mô tả
Chương trình giả lập thiết bị với các tham số gain/range/mode. Hỗ trợ thực thi lệnh, Undo/Redo nhiều bước, lưu/khôi phục phiên, tìm kiếm lịch sử, và xuất báo cáo CSV.

## Lệnh hỗ trợ
- set <gain|range|mode> <value>
- show
- undo | redo
- search <keyword>
- save <path> | load <path>
- report/export <csv_path>
- run <script_path>
- exit

## Build (MSYS2 / Git Bash)
```bash
cd /c/UndoRedo
mkdir -p build
g++ -std=c++17 -O2 -Iinclude -o build/app.exe $(find src -iname "*.cpp")


## Output
- data/out/report.csv
- data/out/snapshot.txt



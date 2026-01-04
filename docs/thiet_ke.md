# Thiết kế & Cấu trúc dữ liệu (tự cài) + Big-O

## 1) Mô hình dữ liệu
**DeviceState**
- gain: int
- range: int
- mode: string

**Command**
- type: SET_GAIN | SET_RANGE | SET_MODE
- old_value: (int/string)
- new_value: (int/string)
- apply(state): thực thi new_value
- revert(state): hoàn tác về old_value

## 2) Cấu trúc dữ liệu bắt buộc
### 2.1 Undo/Redo (2 stack tự cài)
- undoStack: Stack<Command>
- redoStack: Stack<Command>

Quy tắc:
- Khi execute lệnh mới: push vào undoStack, **clear redoStack**
- Undo: pop undoStack → revert → push sang redoStack
- Redo: pop redoStack → apply → push sang undoStack

### 2.2 Lịch sử lệnh (LinkedList tự cài hoặc ArrayList tự cài)
- Lưu chuỗi mô tả lệnh + thời điểm + kết quả (tuỳ bạn)
- Phục vụ search và export.

## 3) Thuật toán & độ phức tạp
- Execute 1 lệnh: O(1)
- Undo/Redo 1 bước: O(1)
- Search keyword (duyệt lịch sử tuyến tính): O(n * m)
  - n: số bản ghi lịch sử
  - m: độ dài chuỗi/keyword
- Save snapshot: O(1) nếu lưu state; O(n) nếu lưu log toàn bộ
- Load snapshot: O(1) hoặc O(n) tương ứng

## 4) File format
### 4.1 Snapshot (gợi ý dạng key=value)
gain=10
range=5
mode=AUTO

### 4.2 Report CSV (gợi ý)
time,command,result,gain,range,mode
...

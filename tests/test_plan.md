# Test plan (10%)

## TC1 – Basic + Undo/Redo
Input: tests/scripts/tc1_basic.txt
Kỳ vọng:
- Sau `undo 2`, trạng thái quay về đúng 2 bước.
- Sau `redo 1`, trạng thái tiến lại 1 bước.
- Export tạo được file CSV, Save tạo snapshot.

## TC2 – Clear redo after new command
Input: tests/scripts/tc2_redo_clear.txt
Kỳ vọng:
- Sau `undo 2` rồi `set gain 99`, lệnh `redo 1` **không làm gì** (redo stack đã bị xóa).
- `show` phải thể hiện gain=99.

## TC3 – Save/Load
Input: tests/scripts/tc3_save_load.txt
Kỳ vọng:
- Sau khi load snapshot, trạng thái quay về gain=7, range=8, mode=MANUAL.

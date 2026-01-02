**Cấu trúc dữ liệu và phân tích Big-O (UndoRedo)**

1\. Cấu trúc dữ liệu sử dụng

&nbsp; 1.1. DeviceState (Trạng thái thiết bị)



&nbsp;  Thiết bị giả lập được biểu diễn bởi DeviceState gồm:



&nbsp;  gain (int)



&nbsp;  range (int)



&nbsp;  mode (string)



Lệnh show dùng để hiển thị trạng thái hiện tại.



Lý do chọn: mô hình hóa trực tiếp trạng thái thiết bị, thao tác cập nhật nhanh, thuận tiện khi save/load.



1.2. CommandRecord (Bản ghi lệnh cho Undo/Redo)



Mỗi lệnh thay đổi trạng thái (ví dụ set gain 10) được lưu dưới dạng CommandRecord gồm:



param: tên tham số (gain/range/mode)



oldValue: giá trị trước khi thay đổi



newValue: giá trị sau khi thay đổi



rawText: chuỗi lệnh gốc (phục vụ search/report)



Chức năng:



apply(state): áp dụng newValue (khi thực thi/redo)



unapply(state): khôi phục oldValue (khi undo)



Lý do chọn: Undo/Redo chỉ cần áp giá trị cũ/mới, không phải tính toán lại.



1.3. Hai stack tự cài: undoStack và redoStack



undoStack: lưu các CommandRecord đã thực thi.



redoStack: lưu các CommandRecord đã undo để có thể redo.



Quy tắc hoạt động:



Khi thực thi lệnh mới (set): push record vào undoStack và xóa redoStack.



Khi undo: pop từ undoStack → unapply() → push sang redoStack.



Khi redo: pop từ redoStack → apply() → push lại undoStack.



Lý do chọn: Stack theo LIFO đúng bản chất Undo/Redo, thao tác push/pop nhanh.



1.4. Linked list tự cài: history



Danh sách history lưu toàn bộ chuỗi lệnh người dùng đã nhập theo thứ tự thời gian.



Dùng cho search <keyword>: tìm lệnh theo từ khóa.



Dùng cho report/export: xuất lịch sử ra file CSV.



Lý do chọn: đáp ứng yêu cầu linked list tự cài; thêm cuối danh sách hiệu quả (nếu có con trỏ tail).



2\. Phân tích độ phức tạp Big-O



Ký hiệu:



L: độ dài chuỗi lệnh.



U: số phần tử trong undoStack.



R: số phần tử trong redoStack.



H: số dòng trong history.



N: số dòng lệnh trong file script (lệnh run).



2.1. set <param> <value>



Parse lệnh: O(L)



Cập nhật DeviceState + tạo record: O(1) (chuỗi mode tính thêm chi phí copy nếu xét chi tiết)



undoStack.push: O(1)



Xóa redoStack: O(1) nếu reset top/size (khuyến nghị triển khai)



history.push\_back: O(1) nếu linked list có tail



Big-O tổng (khuyến nghị/chuẩn): O(L)

(Ghi chú: nếu xóa redo bằng pop từng phần tử thì là O(L + R).)



2.2. show



In trạng thái hiện tại.



Big-O: O(1)



2.3. undo



undoStack.pop: O(1)



unapply(state): O(1)



redoStack.push: O(1)



Big-O: O(1)



2.4. redo



redoStack.pop: O(1)



apply(state): O(1)



undoStack.push: O(1)



Big-O: O(1)



2.5. search <keyword>



Duyệt H dòng lịch sử, mỗi dòng kiểm tra chứa keyword (tìm chuỗi trung bình O(L)).



Big-O: O(H \* L)



2.6. save <path>



Nếu lưu snapshot trạng thái: ghi vài giá trị.



Big-O: O(1) (hoặc tính theo độ dài chuỗi mode nếu xét chi tiết)



2.7. load <path>



Đọc snapshot và cập nhật trạng thái.



Big-O: O(1)

(Thông thường sẽ reset undo/redo/history để đồng bộ phiên.)



2.8. report/export <csv\_path>



Xuất trạng thái + duyệt toàn bộ H dòng lịch sử và ghi file.



Big-O: O(H \* L)



2.9. run <script\_path>



Đọc N dòng và xử lý từng dòng như nhập tay.



Big-O xấp xỉ: O(N \* L) (đối với script chủ yếu là set/show)



3\. Độ phức tạp bộ nhớ (Space Complexity)



DeviceState: O(1)



undoStack: O(U)



redoStack: O(R)



history: O(H \* L)



Tổng: O(U + R + H\*L)


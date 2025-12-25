
# Workflow nhóm (UndoRedo - BTL DSA đề 4)

## Nhánh
- Nhánh làm việc chung: `dev`
- Không commit trực tiếp lên `main`

## Mỗi người làm trên nhánh riêng
- Minh Anh: `feature/docs-workflow`
- Hồng An: `feature/save-load-session`
- Khánh Linh: `feature/find-history-report`

## Bắt đầu làm
```bash
git checkout dev
git pull --rebase
git checkout -b feature/<ten-nhanh>


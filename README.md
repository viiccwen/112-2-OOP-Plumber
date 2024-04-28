# 112-2 Project 1 - Plumber
<專案描述，隨便你寫>
## Member
B11215005 温冠華(組長)
B11215063 吳盛偉
## Quick Start
<描述專案該如何啟動，比方說需不需要安裝其他的 plugins>
如果有使用到外部的 Library、Visual Studio 以外的工具等，需提供build script
.ps1 / .bat / .sh / CMake Config / Make File / Ninja 等格式<僅使用 Visual Studio，就寫”Visual Studio 編譯並執行”即可>
## Contribution

### 温冠華
- 規劃專案架構
- 選擇模式（讀盤面檔、隨機/輸入寬高生成盤面）
- 生成盤面（隨機/輸入寬高生成盤面）
- 讀取並識別盤面檔案
- 印出盤面
- 使用者輸入動作
- 透過DFS產生解答路線
- 優化產解功能
- 解Bug:
    1. 產解不完全
    2. Merge後造成的衝突
    3. 修正隨機盤面無解答
### 吳盛瑋
- 水管旋轉及對接功能
- BFS 水流演算法
- 前後端架構規劃
- CLI 後端轉換
    - 取得盤面接口
    - 旋轉水管接口 
    - 遊戲開始接口
- 水管圖片製作
- 前端開發
    - 遊戲模式選擇介面
    - 盤面生成及對接
- BGM 播放
- 遊戲音效
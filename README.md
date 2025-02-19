<div align="center">

# 112-2 Project 1 - Plumber

  <img width="200" src="/Plumber-Backend/Plumber-Backend/public/assests/img/cross-shape-watered.png" alt="logo" style="border-radius:1em">

### 瘋狂接水管

</div>


## Member
* B11215005 温冠華(組長)
* B11215063 吳盛瑋

## Quick Start
1. 使用 Visual Studio 編譯並執行
2. 將執行畫面中的 `Game URL` 後面的網址使用瀏覽器打開 (需使用 Chromium 瀏覽器，Edge 即可)
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
- 前端開發
    1. 修改UI
    2. 新增鼠標動畫
- 解Bug:
    1. 產解不完全
    2. Merge後造成的衝突
    3. 修正隨機盤面無解答
### 吳盛瑋
- 水管旋轉及對接功能
- BFS 水流演算法
- 前後端架構規劃
- CLI<->後端轉換
    - 取得盤面接口
    - 旋轉水管接口 
    - 遊戲開始接口
    - OPTIONS method handle (for JS CORS)
- 水管圖片製作
- 前端開發
    - 遊戲模式選擇介面及後端串接
    - 盤面生成及接口對接
    - 動態調整水管大小
    - 水管動畫及後端串接
    - 盤面更新 (注水)
    - 遊戲結束介面
- 音效播放
    - BGM 播放 
    - 水管旋轉音效
    - 遊戲結束音效
- 改使用 CppRest 統一架設前端及 API
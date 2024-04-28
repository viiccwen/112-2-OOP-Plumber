// script.js
document.getElementById('game-mode').addEventListener('change', function() {
    var selectedMode = this.value;
    var boardSizeSelection = document.getElementById('board-size-selection');

    console.log(selectedMode)

    if (selectedMode === 'customBoard') {
        boardSizeSelection.style.display = 'block';
    } else {
        boardSizeSelection.style.display = 'none';
    }
});

document.getElementById('start-button').addEventListener('click', function() {
    var gameMode = document.getElementById('game-mode').value;
    var boardRow = document.getElementById('board-row').value;
    var boardColumn = document.getElementById('board-column').value;

    startGame(gameMode, boardRow, boardColumn);
});

function startGame(gameMode, boardRow, boardColumn){
    var board = [];

    document.getElementById('game-option-container').style.display = 'none';
    document.getElementById('game-board-container').style.display = 'block';

    generateBoard(gameMode, boardRow, boardColumn);
}


function generateBoard(gameMode, boardRow, boardColumn) {
    var boardContainer = document.getElementById('game-board-container');

    boardContainer.innerHTML = ''; // 清空現有的遊戲面板

    console.log('Starting game with mode: ' + gameMode + ' and board size: ' + boardRow + 'x' + boardColumn);

    for (var i = 0; i < boardRow; i++) {
        var row = document.createElement('div');
        row.className = 'row';

        let types= ["cross", "straight", "elbow", "t"];
        
        for (var j = 0; j < boardColumn; j++) {
            pipe = generatePipe(types[Math.floor(Math.random() * types.length)]);
            row.appendChild(pipe);
        }

        boardContainer.appendChild(row);
    }
}


function generatePipe(type){
    var pipe = document.createElement('div');
    pipe.className = 'pipe';

    if (type === 'cross') {
        pipe.classList.add('cross-pipe');
    }
    if (type === 'straight') {
        pipe.classList.add('straight-pipe');
    }
    if (type === 'elbow') {
        pipe.classList.add('elbow-pipe');
    }
    if (type === 't') {
        pipe.classList.add('t-pipe');
    }

    pipe.addEventListener('click', function() {
        rotatePipe(pipe);
    });
    return pipe;
}
    
function rotatePipe(pipe) {
    if (!pipe.style.transform) {
        pipe.style.transform = 'rotate(90deg)';
    } else {
        let currentRotation = parseInt(pipe.style.transform.replace('rotate(', '').replace('deg)', ''));
        currentRotation += 90;
        pipe.style.transform = `rotate(${currentRotation}deg)`;
    }
    var sound = document.getElementById('rotate-sound');
    sound.currentTime = 0; // 重置音效播放時間，確保可以連續播放
    sound.play();
}

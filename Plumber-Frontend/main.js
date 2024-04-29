const rootURL = 'http://localhost:8080';

var board = {};

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

    

    const modes = ['customBoard','randomBoard','readBoardFile']
    var modeIndex =  modes.indexOf(gameMode);

    if (modeIndex === 0) {
        if(boardRow < 3 || boardRow > 20 || boardColumn < 3 || boardColumn > 20) {
            alert("請輸入3~20的數字!")
            return;
        }
        
        startGame(modeIndex+1, boardRow, boardColumn);
    }else{
        startGame(modeIndex+1, 0, 0);
    }
});

document.getElementById('restart-button').addEventListener('click', function() {
    document.getElementById('game-over-container').style.display = 'none';
    document.getElementById('game-option-container').style.display = 'block';
    document.getElementById('game-board-container').style.display = 'none';
});

function startGame(gameMode, boardRow, boardColumn) {
    console.log('Starting game with mode: ' + gameMode + ' and board size: ' + boardRow + 'x' + boardColumn);
    fetch(`${rootURL}/newGame`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ mode: parseInt(gameMode), n: parseInt(boardRow), m: parseInt(boardColumn) })
    }).then(response => {
        if (response.ok) {
            return response.json();
        } else {
            throw new Error('Network response was not ok.');
        }
    })
    .then(data => {
        console.log(data);
        if (data.status) {
            return fetchBoard();
        } else {
            console.error('Failed to start new game');
        }
    }).then(() => {
        document.getElementById('game-option-container').style.display = 'none';
        document.getElementById('game-board-container').style.display = 'block';
        generateBoard(gameMode, boardRow, boardColumn);
        updateBoard();
    })
    .catch(error => console.error('Error starting new game:', error));
}

function fetchBoard() {
    return fetch(`${rootURL}/board`)
        .then(response => {
            if (response.ok) {
                return response.json();
            } else {
                throw new Error('Failed to fetch board');
            }
        })
        .then(data => {
            if (data.status) {
                board = data;
                console.log('Fetched board:', board);
            } else {
                console.error('Failed to fetch board');
            }
        })
        .catch(error => console.error('Error fetching board:', error));
}

function generateBoard(gameMode, boardRow, boardColumn) {
    var boardContainer = document.getElementById('game-board-container');
    boardContainer.innerHTML = ''; // 清空現有的遊戲面板

    board.board.forEach((row, i) => {
        const domRow = document.createElement('div');
        domRow.className = 'row';

        row.forEach((pipeData, j) => {
            const pipe = generatePipe(pipeData,i,j);
            domRow.appendChild(pipe);
        });
        boardContainer.appendChild(domRow);
    });
}

function generatePipe(data,x,y){
    var pipe = document.createElement('div');
    pipe.className = 'pipe';

    pipe.classList.add(data.type+'-pipe'+(data.isWatered ? '-watered' : ''));

    if (data.isStartPosition) {
        pipe.classList.add('start-position');
    }

    if (data.isEndPosition) {
        pipe.classList.add('end-position');
    }

    if (data.isSolution && !data.isStartPosition && !data.isEndPosition) {
        pipe.classList.add('solution-position');
    }

    pipe.style.transform = `rotate(${data.rotation}deg)`;

    pipe.addEventListener('click', function() {
        rotatePipe(pipe,x,y);
    });
    return pipe;
}
    
function rotatePipe(pipe,x,y) {
    fetch(`${rootURL}/rotate`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ x: x, y: y })
    }).then(response => response.json())
    .then(data => {
        if (data.status) {
            fetchBoard(); 
        } else {
            console.error('Failed to rotate pipe');
        }
    }).then(() => {
        let currentRotation = parseInt(pipe.style.transform.replace('rotate(', '').replace('deg)', ''));
        currentRotation += 90;
        pipe.style.transform = `rotate(${currentRotation}deg)`;
        
        var sound = document.getElementById('rotate-sound');
        sound.currentTime = 0; // 重置音效播放時間，確保可以連續播放
        sound.play();
        updateBoard();
    })
    .catch(error => console.error('Error rotating pipe:', error));
}

function updateBoard() {
    fetch(`${rootURL}/board`)
        .then(response => response.json())
        .then(data => {
            if (data.status) {
                board = data;
                console.log('Updated board:', board);

                const boardContainer = document.getElementById('game-board-container');
                const rows = boardContainer.getElementsByClassName('row');

                board.board.forEach((row, rowIndex) => {
                    const pipes = rows[rowIndex].getElementsByClassName('pipe');
                    row.forEach((pipeData, columnIndex) => {
                        const pipe = pipes[columnIndex];
                        
                        pipe.classList.remove('cross-pipe', 'straight-pipe', 'elbow-pipe', 't-pipe');
                        pipe.classList.remove('cross-pipe-watered', 'straight-pipe-watered', 'elbow-pipe-watered', 't-pipe-watered');
                        pipe.classList.add(pipeData.type +'-pipe' + (pipeData.isWatered ? '-watered' : ''));
                    });
                });

                if (board.isGameOver) {
                    // document.getElementById('game-board-container').style.display = 'none';
                    console.log("stage clear!");
                    document.getElementById('game-over-container').style.display = 'block';
                }

            } else {
                console.error('Failed to update board');
            }
        })
        .catch(error => console.error('Error updating board:', error));
}
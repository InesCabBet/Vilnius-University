export const DOM = {
  renderBoard(gameboard, container, showShips = false, clickHandler = null) {
    container.innerHTML = '';
    
    for (let i = 0; i < 10; i++) {
      for (let j = 0; j < 10; j++) {
        const cell = document.createElement('div');
        cell.className = 'cell';
        cell.dataset.x = i;
        cell.dataset.y = j;

        const coordStr = `${i},${j}`;
        
        if (gameboard.hits.includes(coordStr)) {
          cell.classList.add('hit');
        } else if (gameboard.missedShots.includes(coordStr)) {
          cell.classList.add('miss');
        } else if (showShips && gameboard.board[i][j]) {
          cell.classList.add('ship');
        }

        if (clickHandler) {
          cell.addEventListener('click', clickHandler);
        }

        container.appendChild(cell);
      }
    }
  },

  displayMessage(message) {
    const messageEl = document.getElementById('message');
    if (messageEl) {
      messageEl.textContent = message;
    }
  },

  showGameOver(winner) {
    const messageEl = document.getElementById('message');
    if (messageEl) {
      messageEl.textContent = `¡${winner} won!`;
      messageEl.style.fontSize = '24px';
      messageEl.style.fontWeight = 'bold';
      messageEl.style.color = '#d32f2f';
    }
  }
};
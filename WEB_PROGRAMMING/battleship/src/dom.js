// src/dom.js
export const DOMController = (() => {
  const renderBoard = (gameboard, container, isPlayerBoard) => {
    container.innerHTML = '';
    
    for (let x = 0; x < 10; x++) {
      for (let y = 0; y < 10; y++) {
        const cell = document.createElement('div');
        cell.classList.add('cell');
        cell.dataset.x = x;
        cell.dataset.y = y;

        const coord = `${x},${y}`;
        
        if (gameboard.hits.includes(coord)) {
          cell.classList.add('hit');
        } else if (gameboard.missedShots.includes(coord)) {
          cell.classList.add('miss');
        } else if (isPlayerBoard && gameboard.board[x][y]) {
          cell.classList.add('ship');
        }

        container.appendChild(cell);
      }
    }
  };

  const showMessage = (message) => {
    const messageDiv = document.getElementById('message');
    if (messageDiv) {
      messageDiv.textContent = message;
    }
  };

  const showGameOver = (winner) => {
    const message = winner === 'player' 
      ? 'Congratulations! You won!' 
      : 'Game Over! Computer wins!';
    showMessage(message);
    
    const modal = document.getElementById('game-over-modal');
    const modalMessage = document.getElementById('modal-message');
    if (modal && modalMessage) {
      modalMessage.textContent = message;
      modal.style.display = 'flex';
    }
  };

  const hideGameOver = () => {
    const modal = document.getElementById('game-over-modal');
    if (modal) {
      modal.style.display = 'none';
    }
  };

  return {
    renderBoard,
    showMessage,
    showGameOver,
    hideGameOver
  };
})();
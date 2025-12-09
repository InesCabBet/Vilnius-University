import { Player } from './player.js';
import { DOM } from './dom.js';

export class Game {
  constructor() {
    this.player = new Player('Player', false);
    this.computer = new Player('Computer', true);
    this.currentTurn = 'player';
    this.gameOver = false;
    this.setupGame();
  }

  setupGame() {
    // Colocar barcos del jugador
    this.placeShipsRandomly(this.player.gameboard);
    
    // Colocar barcos de la computadora
    this.placeShipsRandomly(this.computer.gameboard);
  }

  placeShipsRandomly(gameboard) {
    const shipLengths = [5, 4, 3, 3, 2];
    
    shipLengths.forEach(length => {
      let placed = false;
      while (!placed) {
        const x = Math.floor(Math.random() * 10);
        const y = Math.floor(Math.random() * 10);
        const isHorizontal = Math.random() > 0.5;
        placed = gameboard.placeShip(length, x, y, isHorizontal);
      }
    });
  }

  handlePlayerAttack(x, y) {
    if (this.gameOver || this.currentTurn !== 'player') return;

    const coordStr = `${x},${y}`;
    if (this.computer.gameboard.hits.includes(coordStr) || 
        this.computer.gameboard.missedShots.includes(coordStr)) {
      DOM.displayMessage('You have already attack this square');
      return;
    }

    const hit = this.computer.gameboard.receiveAttack(x, y);
    
    if (hit) {
      DOM.displayMessage('Boom!');
    } else {
      DOM.displayMessage('Water...');
    }

    this.render();

    if (this.checkGameOver()) return;

    this.currentTurn = 'computer';
    setTimeout(() => this.computerTurn(), 1000);
  }

  computerTurn() {
    if (this.gameOver) return;

    const { x, y, result } = this.computer.randomAttack(this.player.gameboard);
    
    if (result) {
      DOM.displayMessage(`Computer has hit you in (${x}, ${y})`);
    } else {
      DOM.displayMessage(`Computer has failed in (${x}, ${y})`);
    }

    this.render();

    if (this.checkGameOver()) return;

    this.currentTurn = 'player';
    DOM.displayMessage('Your turn');
  }

  checkGameOver() {
    if (this.player.gameboard.allShipsSunk()) {
      this.gameOver = true;
      DOM.showGameOver('Computer');
      return true;
    }

    if (this.computer.gameboard.allShipsSunk()) {
      this.gameOver = true;
      DOM.showGameOver('Player');
      return true;
    }

    return false;
  }

  render() {
    const playerBoard = document.getElementById('player-board');
    const computerBoard = document.getElementById('computer-board');

    DOM.renderBoard(this.player.gameboard, playerBoard, true);
    
    DOM.renderBoard(
      this.computer.gameboard, 
      computerBoard, 
      false, 
      (e) => {
        if (this.gameOver || this.currentTurn !== 'player') return;
        const x = parseInt(e.target.dataset.x);
        const y = parseInt(e.target.dataset.y);
        this.handlePlayerAttack(x, y);
      }
    );
  }

  restart() {
    this.player = new Player('Jugador', false);
    this.computer = new Player('Computadora', true);
    this.currentTurn = 'player';
    this.gameOver = false;
    this.setupGame();
    this.render();
    DOM.displayMessage('¡Nuevo juego! Tu turno');
  }
}
// src/game.js
import { Player } from './player.js';

export class Game {
  constructor() {
    this.player = new Player('Player');
    this.computer = new Player('Computer', true);
    this.currentTurn = 'player';
    this.gameOver = false;
    this.winner = null;
  }

  setupGame() {
    // Player ships
    this.placeRandomShips(this.player.gameboard);
    
    // Computer ships
    this.placeRandomShips(this.computer.gameboard);
  }

  placeRandomShips(gameboard) {
    const ships = [5, 4, 3, 3, 2]; // Carrier, Battleship, Cruiser, Submarine, Destroyer
    
    ships.forEach(length => {
      let placed = false;
      while (!placed) {
        const x = Math.floor(Math.random() * 10);
        const y = Math.floor(Math.random() * 10);
        const orientation = Math.random() > 0.5 ? 'horizontal' : 'vertical';
        placed = gameboard.placeShip(length, x, y, orientation);
      }
    });
  }

  playerAttack(x, y) {
    if (this.gameOver || this.currentTurn !== 'player') return null;

    const result = this.player.attack(this.computer.gameboard, x, y);
    
    if (result === false) return null;

    if (this.computer.gameboard.allShipsSunk()) {
      this.gameOver = true;
      this.winner = 'player';
      return { hit: result, gameOver: true, winner: 'player' };
    }

    this.currentTurn = 'computer';
    return { hit: result };
  }

  computerAttack() {
    if (this.gameOver || this.currentTurn !== 'computer') return null;

    const result = this.computer.randomAttack(this.player.gameboard);
    
    if (this.player.gameboard.allShipsSunk()) {
      this.gameOver = true;
      this.winner = 'computer';
      return { ...result, gameOver: true, winner: 'computer' };
    }

    this.currentTurn = 'player';
    return result;
  }

  reset() {
    this.player = new Player('Player');
    this.computer = new Player('Computer', true);
    this.currentTurn = 'player';
    this.gameOver = false;
    this.winner = null;
    this.setupGame();
  }
}
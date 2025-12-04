// src/gameboard.js
import { Ship } from './ship.js';

export class Gameboard {
  constructor() {
    this.board = Array(10).fill(null).map(() => Array(10).fill(null));
    this.ships = [];
    this.missedShots = [];
    this.hits = [];
  }

  placeShip(length, x, y, orientation = 'horizontal') {
    if (!this.isValidPlacement(length, x, y, orientation)) {
      return false;
    }

    const ship = new Ship(length);
    const coordinates = [];

    for (let i = 0; i < length; i++) {
      const newX = orientation === 'horizontal' ? x : x + i;
      const newY = orientation === 'horizontal' ? y + i : y;
      this.board[newX][newY] = ship;
      coordinates.push([newX, newY]);
    }

    this.ships.push({ ship, coordinates });
    return true;
  }

  isValidPlacement(length, x, y, orientation) {
    if (x < 0 || x >= 10 || y < 0 || y >= 10) return false;

    for (let i = 0; i < length; i++) {
      const newX = orientation === 'horizontal' ? x : x + i;
      const newY = orientation === 'horizontal' ? y + i : y;

      if (newX >= 10 || newY >= 10) return false;
      if (this.board[newX][newY] !== null) return false;
    }

    return true;
  }

  receiveAttack(x, y) {
    if (x < 0 || x >= 10 || y < 0 || y >= 10) return false;
    
    const coord = `${x},${y}`;
    if (this.missedShots.includes(coord) || this.hits.includes(coord)) {
      return false;
    }

    const target = this.board[x][y];

    if (target instanceof Ship) {
      target.hit();
      this.hits.push(coord);
      return true;
    } else {
      this.missedShots.push(coord);
      return false;
    }
  }

  allShipsSunk() {
    return this.ships.length > 0 && this.ships.every(({ ship }) => ship.isSunk());
  }
}
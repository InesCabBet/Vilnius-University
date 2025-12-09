import { Ship } from './ship.js';

export class Gameboard {
  constructor() {
    this.board = Array(10).fill(null).map(() => Array(10).fill(null));
    this.ships = [];
    this.missedShots = [];
    this.hits = [];
  }

  placeShip(length, x, y, isHorizontal = true) {
    if (!this.isValidPlacement(length, x, y, isHorizontal)) {
      return false;
    }

    const ship = new Ship(length);
    const coordinates = [];

    for (let i = 0; i < length; i++) {
      const coordX = isHorizontal ? x : x + i;
      const coordY = isHorizontal ? y + i : y;
      this.board[coordX][coordY] = ship;
      coordinates.push([coordX, coordY]);
    }

    this.ships.push({ ship, coordinates });
    return true;
  }

  isValidPlacement(length, x, y, isHorizontal) {
    if (x < 0 || x >= 10 || y < 0 || y >= 10) return false;

    for (let i = 0; i < length; i++) {
      const coordX = isHorizontal ? x : x + i;
      const coordY = isHorizontal ? y + i : y;

      if (coordX >= 10 || coordY >= 10) return false;
      if (this.board[coordX][coordY] !== null) return false;
    }

    return true;
  }

  receiveAttack(x, y) {
    if (x < 0 || x >= 10 || y < 0 || y >= 10) return false;
    
    const coordStr = `${x},${y}`;
    if (this.missedShots.some(coord => coord === coordStr) || 
        this.hits.some(coord => coord === coordStr)) {
      return false; // Already attacked
    }

    const target = this.board[x][y];

    if (target) {
      target.hit();
      this.hits.push(coordStr);
      return true; // Hit
    } else {
      this.missedShots.push(coordStr);
      return false; // Miss
    }
  }

  allShipsSunk() {
    return this.ships.length > 0 && this.ships.every(({ ship }) => ship.isSunk());
  }
}
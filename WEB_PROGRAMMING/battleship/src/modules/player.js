import { Gameboard } from './gameboard.js';

export class Player {
  constructor(name, isComputer = false) {
    this.name = name;
    this.isComputer = isComputer;
    this.gameboard = new Gameboard();
    this.attackedCoordinates = [];
  }

  attack(enemyGameboard, x, y) {
    return enemyGameboard.receiveAttack(x, y);
  }

  randomAttack(enemyGameboard) {
    let x, y;
    do {
      x = Math.floor(Math.random() * 10);
      y = Math.floor(Math.random() * 10);
    } while (this.attackedCoordinates.some(coord => coord === `${x},${y}`));

    this.attackedCoordinates.push(`${x},${y}`);
    return { x, y, result: enemyGameboard.receiveAttack(x, y) };
  }
}
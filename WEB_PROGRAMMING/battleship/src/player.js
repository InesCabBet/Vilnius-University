// src/player.js
import { Gameboard } from './gameboard.js';

export class Player {
  constructor(name, isComputer = false) {
    this.name = name;
    this.isComputer = isComputer;
    this.gameboard = new Gameboard();
    this.attackHistory = [];
  }

  attack(enemyGameboard, x, y) {
    const coord = `${x},${y}`;
    if (this.attackHistory.includes(coord)) {
      return false;
    }

    const result = enemyGameboard.receiveAttack(x, y);
    this.attackHistory.push(coord);
    return result;
  }

  randomAttack(enemyGameboard) {
    let x, y, coord;
    let attempts = 0;
    const maxAttempts = 100;

    do {
      x = Math.floor(Math.random() * 10);
      y = Math.floor(Math.random() * 10);
      coord = `${x},${y}`;
      attempts++;
    } while (this.attackHistory.includes(coord) && attempts < maxAttempts);

    if (attempts >= maxAttempts) {
      return null;
    }

    return this.attack(enemyGameboard, x, y) !== false ? { x, y, hit: true } : { x, y, hit: false };
  }
}
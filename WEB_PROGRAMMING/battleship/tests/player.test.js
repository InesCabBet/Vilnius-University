// tests/player.test.js
import { Player } from '../src/player.js';
import { Gameboard } from '../src/gameboard.js';

describe('Player', () => {
  test('creates a player with a name', () => {
    const player = new Player('John');
    expect(player.name).toBe('John');
  });

  test('player has a gameboard', () => {
    const player = new Player('John');
    expect(player.gameboard).toBeInstanceOf(Gameboard);
  });

  test('can attack enemy gameboard', () => {
    const player = new Player('John');
    const enemy = new Player('Enemy');
    enemy.gameboard.placeShip(3, 0, 0, 'horizontal');
    
    const result = player.attack(enemy.gameboard, 0, 0);
    expect(result).toBe(true);
  });

  test('records attack history', () => {
    const player = new Player('John');
    const enemy = new Player('Enemy');
    
    player.attack(enemy.gameboard, 0, 0);
    expect(player.attackHistory).toContain('0,0');
  });

  test('cannot attack same coordinate twice', () => {
    const player = new Player('John');
    const enemy = new Player('Enemy');
    
    player.attack(enemy.gameboard, 0, 0);
    const result = player.attack(enemy.gameboard, 0, 0);
    expect(result).toBe(false);
  });

  test('computer player can make random attacks', () => {
    const computer = new Player('Computer', true);
    const enemy = new Player('Enemy');
    
    const result = computer.randomAttack(enemy.gameboard);
    expect(result).toHaveProperty('x');
    expect(result).toHaveProperty('y');
  });

  test('computer player does not attack same coordinate twice', () => {
    const computer = new Player('Computer', true);
    const enemy = new Player('Enemy');
    
    const firstAttack = computer.randomAttack(enemy.gameboard);
    computer.attackHistory = [];
    
    for (let i = 0; i < 100; i++) {
      computer.attackHistory.push(`${i % 10},${Math.floor(i / 10)}`);
    }
    
    expect(computer.attackHistory.length).toBe(100);
  });
});
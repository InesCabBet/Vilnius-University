import { Player } from '../src/modules/player.js';

describe('Player', () => {
  test('should create a player with a gameboard', () => {
    const player = new Player('Test Player');
    expect(player.name).toBe('Test Player');
    expect(player.gameboard).toBeDefined();
    expect(player.isComputer).toBe(false);
  });

  test('should create a computer player', () => {
    const computer = new Player('Computer', true);
    expect(computer.isComputer).toBe(true);
  });

  test('should allow player to attack enemy gameboard', () => {
    const player = new Player('Player');
    const enemy = new Player('Enemy');
    
    enemy.gameboard.placeShip(3, 0, 0, true);
    const result = player.attack(enemy.gameboard, 0, 0);
    
    expect(result).toBe(true);
  });

  test('computer should make random attacks', () => {
    const computer = new Player('Computer', true);
    const enemy = new Player('Enemy');
    
    const attack = computer.randomAttack(enemy.gameboard);
    
    expect(attack.x).toBeGreaterThanOrEqual(0);
    expect(attack.x).toBeLessThan(10);
    expect(attack.y).toBeGreaterThanOrEqual(0);
    expect(attack.y).toBeLessThan(10);
  });

  test('computer should not attack same coordinate twice', () => {
    const computer = new Player('Computer', true);
    const enemy = new Player('Enemy');
    
    const attacks = new Set();
    
    for (let i = 0; i < 10; i++) {
      const attack = computer.randomAttack(enemy.gameboard);
      const coord = `${attack.x},${attack.y}`;
      expect(attacks.has(coord)).toBe(false);
      attacks.add(coord);
    }
  });
});
// tests/gameboard.test.js
import { Gameboard } from '../src/gameboard.js';

describe('Gameboard', () => {
  test('creates a 10x10 board', () => {
    const gameboard = new Gameboard();
    expect(gameboard.board.length).toBe(10);
    expect(gameboard.board[0].length).toBe(10);
  });

  test('can place a ship horizontally', () => {
    const gameboard = new Gameboard();
    const result = gameboard.placeShip(3, 0, 0, 'horizontal');
    expect(result).toBe(true);
    expect(gameboard.ships.length).toBe(1);
  });

  test('can place a ship vertically', () => {
    const gameboard = new Gameboard();
    const result = gameboard.placeShip(3, 0, 0, 'vertical');
    expect(result).toBe(true);
    expect(gameboard.ships.length).toBe(1);
  });

  test('cannot place ship out of bounds horizontally', () => {
    const gameboard = new Gameboard();
    const result = gameboard.placeShip(5, 0, 8, 'horizontal');
    expect(result).toBe(false);
  });

  test('cannot place ship out of bounds vertically', () => {
    const gameboard = new Gameboard();
    const result = gameboard.placeShip(5, 8, 0, 'vertical');
    expect(result).toBe(false);
  });

  test('cannot place overlapping ships', () => {
    const gameboard = new Gameboard();
    gameboard.placeShip(3, 0, 0, 'horizontal');
    const result = gameboard.placeShip(3, 0, 1, 'horizontal');
    expect(result).toBe(false);
  });

  test('receiveAttack hits a ship', () => {
    const gameboard = new Gameboard();
    gameboard.placeShip(3, 0, 0, 'horizontal');
    const result = gameboard.receiveAttack(0, 0);
    expect(result).toBe(true);
    expect(gameboard.ships[0].ship.hits).toBe(1);
  });

  test('receiveAttack records missed shots', () => {
    const gameboard = new Gameboard();
    gameboard.receiveAttack(5, 5);
    expect(gameboard.missedShots).toContain('5,5');
  });

  test('cannot attack same coordinate twice', () => {
    const gameboard = new Gameboard();
    gameboard.receiveAttack(5, 5);
    const result = gameboard.receiveAttack(5, 5);
    expect(result).toBe(false);
  });

  test('allShipsSunk returns false when ships are not sunk', () => {
    const gameboard = new Gameboard();
    gameboard.placeShip(2, 0, 0, 'horizontal');
    expect(gameboard.allShipsSunk()).toBe(false);
  });

  test('allShipsSunk returns true when all ships are sunk', () => {
    const gameboard = new Gameboard();
    gameboard.placeShip(2, 0, 0, 'horizontal');
    gameboard.receiveAttack(0, 0);
    gameboard.receiveAttack(0, 1);
    expect(gameboard.allShipsSunk()).toBe(true);
  });
});
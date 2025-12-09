import { Gameboard } from '../src/modules/gameboard.js';

describe('Gameboard', () => {
  let gameboard;

  beforeEach(() => {
    gameboard = new Gameboard();
  });

  test('should create a 10x10 board', () => {
    expect(gameboard.board.length).toBe(10);
    expect(gameboard.board[0].length).toBe(10);
  });

  test('should place a ship horizontally', () => {
    const result = gameboard.placeShip(3, 0, 0, true);
    expect(result).toBe(true);
    expect(gameboard.ships.length).toBe(1);
  });

  test('should place a ship vertically', () => {
    const result = gameboard.placeShip(3, 0, 0, false);
    expect(result).toBe(true);
    expect(gameboard.ships.length).toBe(1);
  });

  test('should not place ship out of bounds', () => {
    const result = gameboard.placeShip(5, 8, 8, true);
    expect(result).toBe(false);
  });

  test('should not place overlapping ships', () => {
    gameboard.placeShip(3, 0, 0, true);
    const result = gameboard.placeShip(3, 0, 1, false);
    expect(result).toBe(false);
  });

  test('should register a hit on a ship', () => {
    gameboard.placeShip(3, 0, 0, true);
    const result = gameboard.receiveAttack(0, 0);
    expect(result).toBe(true);
    expect(gameboard.hits.length).toBe(1);
  });

  test('should register a miss', () => {
    gameboard.placeShip(3, 0, 0, true);
    const result = gameboard.receiveAttack(5, 5);
    expect(result).toBe(false);
    expect(gameboard.missedShots.length).toBe(1);
  });

  test('should not allow attacking the same coordinate twice', () => {
    gameboard.receiveAttack(5, 5);
    const result = gameboard.receiveAttack(5, 5);
    expect(result).toBe(false);
  });

  test('should report when all ships are sunk', () => {
    gameboard.placeShip(2, 0, 0, true);
    expect(gameboard.allShipsSunk()).toBe(false);
    
    gameboard.receiveAttack(0, 0);
    gameboard.receiveAttack(0, 1);
    
    expect(gameboard.allShipsSunk()).toBe(true);
  });

  test('should not report all ships sunk if one survives', () => {
    gameboard.placeShip(2, 0, 0, true);
    gameboard.placeShip(2, 2, 0, true);
    
    gameboard.receiveAttack(0, 0);
    gameboard.receiveAttack(0, 1);
    
    expect(gameboard.allShipsSunk()).toBe(false);
  });
});
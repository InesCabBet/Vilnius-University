// tests/ship.test.js
import { Ship } from '../src/player.js';

describe('Ship', () => {
  test('creates a ship with correct length', () => {
    const ship = new Ship(3);
    expect(ship.length).toBe(3);
  });

  test('ship starts with 0 hits', () => {
    const ship = new Ship(3);
    expect(ship.hits).toBe(0);
  });

  test('hit() increases hits by 1', () => {
    const ship = new Ship(3);
    ship.hit();
    expect(ship.hits).toBe(1);
  });

  test('hit() can be called multiple times', () => {
    const ship = new Ship(3);
    ship.hit();
    ship.hit();
    expect(ship.hits).toBe(2);
  });

  test('isSunk() returns false when hits < length', () => {
    const ship = new Ship(3);
    ship.hit();
    expect(ship.isSunk()).toBe(false);
  });

  test('isSunk() returns true when hits equal length', () => {
    const ship = new Ship(2);
    ship.hit();
    ship.hit();
    expect(ship.isSunk()).toBe(true);
  });

  test('isSunk() returns true when hits exceed length', () => {
    const ship = new Ship(2);
    ship.hit();
    ship.hit();
    ship.hit();
    expect(ship.isSunk()).toBe(true);
  });
});
import { Ship } from '../src/modules/ship.js';

describe('Ship', () => {
  test('should create a ship with correct length', () => {
    const ship = new Ship(3);
    expect(ship.length).toBe(3);
    expect(ship.hits).toBe(0);
  });

  test('should increase hits when hit() is called', () => {
    const ship = new Ship(3);
    ship.hit();
    expect(ship.hits).toBe(1);
    ship.hit();
    expect(ship.hits).toBe(2);
  });

  test('should not be sunk initially', () => {
    const ship = new Ship(3);
    expect(ship.isSunk()).toBe(false);
  });

  test('should be sunk when hits equal length', () => {
    const ship = new Ship(2);
    ship.hit();
    ship.hit();
    expect(ship.isSunk()).toBe(true);
  });

  test('should remain sunk even with more hits', () => {
    const ship = new Ship(2);
    ship.hit();
    ship.hit();
    ship.hit();
    expect(ship.isSunk()).toBe(true);
  });
});
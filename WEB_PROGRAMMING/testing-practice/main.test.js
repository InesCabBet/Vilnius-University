// main.test.js
const {
  capitalize,
  reverseString,
  calculator,
  caesarCipher,
  analyzeArray
} = require('./main');

test('capitalize capitalizes first letter', () => {
  expect(capitalize('hello')).toBe('Hello');
  expect(capitalize('')).toBe('');
  expect(capitalize('a')).toBe('A');
});

test('reverseString reverses string', () => {
  expect(reverseString('hello')).toBe('olleh');
  expect(reverseString('')).toBe('');
});

describe('calculator', () => {
  test('add', () => expect(calculator.add(2,3)).toBe(5));
  test('subtract', () => expect(calculator.subtract(5,3)).toBe(2));
  test('multiply', () => expect(calculator.multiply(4,3)).toBe(12));
  test('divide', () => expect(calculator.divide(10,2)).toBe(5));
  test('divide by zero throws', () => expect(() => calculator.divide(5,0)).toThrow());
});

test('caesarCipher shifts letters correctly', () => {
  expect(caesarCipher('abc', 1)).toBe('bcd');
  expect(caesarCipher('xyz', 3)).toBe('abc');  // wrap around
  expect(caesarCipher('Hello, World!', 3)).toBe('Khoor, Zruog!');
  expect(caesarCipher('HeLLo', 3)).toBe('KhOOr'); // preserve case
});

test('analyzeArray returns correct object', () => {
  const arr = [1, 8, 3, 4, 2, 6];
  expect(analyzeArray(arr)).toEqual({
    average: 4,
    min: 1,
    max: 8,
    length: 6
  });
});

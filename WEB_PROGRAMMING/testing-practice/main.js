// main.js
function capitalize(str) {
  if (typeof str !== 'string' || str.length === 0) return '';
  return str[0].toUpperCase() + str.slice(1);
}

function reverseString(str) {
  return str.split('').reverse().join('');
}

const calculator = {
  add: (a, b) => a + b,
  subtract: (a, b) => a - b,
  multiply: (a, b) => a * b,
  divide: (a, b) => {
    if (b === 0) throw new Error('Division by zero');
    return a / b;
  }
};

function caesarCipher(str, shift) {
  // shift may be larger than 26 or negative
  const shiftNormalized = ((shift % 26) + 26) % 26;
  return str.split('').map(char => {
    const code = char.charCodeAt(0);

    // uppercase A-Z
    if (code >= 65 && code <= 90) {
      const newCode = ((code - 65 + shiftNormalized) % 26) + 65;
      return String.fromCharCode(newCode);
    }
    // lowercase a-z
    if (code >= 97 && code <= 122) {
      const newCode = ((code - 97 + shiftNormalized) % 26) + 97;
      return String.fromCharCode(newCode);
    }
    // non-letter
    return char;
  }).join('');
}

function analyzeArray(arr) {
  if (!Array.isArray(arr) || arr.length === 0) return null;
  const length = arr.length;
  const min = Math.min(...arr);
  const max = Math.max(...arr);
  const sum = arr.reduce((acc, v) => acc + v, 0);
  const average = sum / length;
  return { average, min, max, length };
}

module.exports = { capitalize, reverseString, calculator, caesarCipher, analyzeArray };

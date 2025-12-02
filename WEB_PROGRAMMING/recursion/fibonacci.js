// fibonacci.js

// Fibonacci iterativo
function fibs(n) {
  if (n === 0) return [0];
  if (n === 1) return [0, 1];

  const arr = [0, 1];
  for (let i = 2; i < n; i++) {
    arr.push(arr[i - 1] + arr[i - 2]);
  }
  return arr;
}

// Fibonacci recursivo
function fibsRec(n) {
  if (n === 1) return [0];
  if (n === 2) return [0, 1];

  const previous = fibsRec(n - 1);
  return [...previous, previous[previous.length - 1] + previous[previous.length - 2]];
}

// Testing:
console.log("Iterative:", fibs(8));
console.log("Recursive:", fibsRec(8));

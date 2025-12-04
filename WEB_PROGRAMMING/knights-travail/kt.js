function knightMoves(start, end) {
  const moves = [
    [1, 2], [1, -2], [-1, 2], [-1, -2],
    [2, 1], [2, -1], [-2, 1], [-2, -1],
  ];

  const isValid = ([x, y]) =>
    x >= 0 && x < 8 && y >= 0 && y < 8;

  // BFS queue holds whole paths
  const queue = [[start]];
  const visited = new Set([start.toString()]);

  while (queue.length > 0) {
    const path = queue.shift();
    const [x, y] = path[path.length - 1];

    // If we reached the target, print + return the path
    if (x === end[0] && y === end[1]) {
      console.log(
        `You made it in ${path.length - 1} moves!  Here's your path:`
      );
      path.forEach(pos => console.log(`  [${pos[0]},${pos[1]}]`));
      return path;
    }

    // Explore all possible knight moves
    for (const [dx, dy] of moves) {
      const next = [x + dx, y + dy];
      const key = next.toString();
      if (isValid(next) && !visited.has(key)) {
        visited.add(key);
        queue.push([...path, next]);
      }
    }
  }

  return null; // Should never happen
}

// ---------------------
// Example calls:
// ---------------------

knightMoves([3,3],[4,3]);
console.log();
knightMoves([0,0],[1,2]);
console.log();
knightMoves([0,0],[3,3]);
console.log();
knightMoves([0,0],[7,7]);

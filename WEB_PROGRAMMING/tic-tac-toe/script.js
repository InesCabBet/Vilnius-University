const form = document.getElementById("players-input");
const player1Input = document.getElementById("player1-name");
const player2Input = document.getElementById("player2-name");
const textHolder = document.querySelector(".text-holder");
const whosPlaying = document.querySelector(".whos-playing .player");
const cells = document.querySelectorAll(".cell");

let player1 = "";
let player2 = "";
let currentPlayer = "";
let gameActive = false;
let board = ["", "", "", "", "", "", "", "", ""];

// --- START GAME ---
form.addEventListener("submit", (e) => {
  e.preventDefault();
  player1 = player1Input.value.trim();
  player2 = player2Input.value.trim();
  if (!player1 || !player2) return;

  textHolder.textContent = "Game started!";
  whosPlaying.textContent = `${player1} playing (X)`;
  currentPlayer = player1;
  gameActive = true;

  // limpiar tablero
  board.fill("");
  cells.forEach((cell) => {
    cell.textContent = "";
    cell.style.pointerEvents = "auto";
  });
});

// --- GAME LOGIC ---
cells.forEach((cell, index) => {
  cell.addEventListener("click", () => {
    if (!gameActive || cell.textContent !== "") return;

    const symbol = currentPlayer === player1 ? "X" : "O";
    cell.textContent = symbol;
    board[index] = symbol;

    if (checkWinner(symbol)) {
      showResult(`${currentPlayer} wins!`);
      gameActive = false;
      return;
    }

    if (board.every((c) => c !== "")) {
      showResult("It's a draw!");
      gameActive = false;
      return;
    }

    // Cambiar turno
    currentPlayer = currentPlayer === player1 ? player2 : player1;
    whosPlaying.textContent =
      `${currentPlayer} playing (${currentPlayer === player1 ? "X" : "O"})`;
  });
});

// --- CHECK WINNER ---
function checkWinner(symbol) {
  const winPatterns = [
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8],
    [0, 3, 6],
    [1, 4, 7],
    [2, 5, 8],
    [0, 4, 8],
    [2, 4, 6],
  ];

  return winPatterns.some(
    (pattern) => pattern.every((index) => board[index] === symbol)
  );
}

// --- SHOW RESULT POPUP ---
function showResult(message) {
  const overlay = document.createElement("div");
  overlay.style.position = "fixed";
  overlay.style.top = 0;
  overlay.style.left = 0;
  overlay.style.width = "100%";
  overlay.style.height = "100%";
  overlay.style.background = "rgba(0, 0, 0, 0.7)";
  overlay.style.display = "flex";
  overlay.style.justifyContent = "center";
  overlay.style.alignItems = "center";
  overlay.style.zIndex = 999;

  const popup = document.createElement("div");
  popup.style.background = "white";
  popup.style.padding = "30px 50px";
  popup.style.borderRadius = "12px";
  popup.style.textAlign = "center";
  popup.style.fontSize = "24px";
  popup.style.fontWeight = "bold";
  popup.style.display = "flex";
  popup.style.flexDirection = "column";
  popup.style.gap = "20px";
  popup.innerHTML = `
    <p>${message}</p>
    <button class="restart-btn">Restart Game</button>
  `;

  overlay.appendChild(popup);
  document.body.appendChild(overlay);

  const restartBtn = popup.querySelector(".restart-btn");
  restartBtn.style.background = "rgb(37, 90, 63)";
  restartBtn.style.color = "white";
  restartBtn.style.padding = "10px 20px";
  restartBtn.style.border = "none";
  restartBtn.style.borderRadius = "8px";
  restartBtn.style.cursor = "pointer";
  restartBtn.style.fontSize = "20px";

  restartBtn.addEventListener("click", () => {
    overlay.remove();
    resetGame();
  });
}

// --- RESET GAME ---
function resetGame() {
  board.fill("");
  cells.forEach((cell) => {
    cell.textContent = "";
    cell.style.pointerEvents = "auto";
  });
  currentPlayer = player1;
  whosPlaying.textContent = `${player1} playing (X)`;
  gameActive = true;
}

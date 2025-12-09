import './styles/style.css';
import { Game } from './modules/game.js';

let game;

document.addEventListener('DOMContentLoaded', () => {
  game = new Game();
  game.render();

  const restartBtn = document.getElementById('restart-btn');
  restartBtn.addEventListener('click', () => {
    game.restart();
  });
});
let gridSize = 16;
let mode = 'black';
const gridContainer = document.getElementById('grid');
const btnBlack = document.getElementById('blackMode');
const btnRandom = document.getElementById('colorRandom');
const btnReset = document.getElementById('reset');
const btnChange = document.getElementById('changeSize');

function getRandomColor() {
  const r = Math.floor(Math.random() * 256);
  const g = Math.floor(Math.random() * 256);
  const b = Math.floor(Math.random() * 256);
  return `rgb(${r}, ${g}, ${b})`;
}

function createGrid(size){
  gridContainer.innerHTML = '';
  gridContainer.style.gridTemplateColumns=`repeat(${size}, 1fr)`;
  gridContainer.style.gridTemplateRows=`repeat(${size}, 1fr)`;
  const totalCells = size * size;
  for (let i = 0; i < totalCells; i++){
    const celda = document.createElement('div');
    celda.classList.add('celda');
    celda.addEventListener('mouseenter', () => {
      if (mode === 'black'){
        celda.style.backgroundColor = '#000000';
      } else if (mode === 'random') {
        celda.style.backgroundColor = getRandomColor();
      }
    });
    gridContainer.appendChild(celda);
  }
}

function updateActiveButtons() {
  btnBlack.classList.remove('active');
  btnRandom.classList.remove('active');
  if (mode === 'black'){
    btnBlack.classList.add('active');
  } else if (mode === 'random'){
    btnRandom.classList.add('active');
  }
}

btnBlack.addEventListener('click', () => {
  mode = 'black';
  updateActiveButtons();
});

btnRandom.addEventListener('click', () => {
  mode = 'random';
  updateActiveButtons();
});

btnReset.addEventListener('click', () => {
  createGrid(gridSize);
});

btnChange.addEventListener('click', () => {
  let new_size = prompt('Select new grid size (1-100): ');
  new_size = parseInt(new_size);
  if (new_size && new_size > 0 && new_size <= 100){
    gridSize = new_size;
    createGrid(gridSize);
  } else {
    alert('Please enter a number between 1 and 100');
  }
});

createGrid(gridSize);
updateActiveButtons();
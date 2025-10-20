let firstOperand = '';
let secondOperand = '';
let currentOperation = null;
let shouldReset = false;

const currentOperandDisplay = document.querySelector('.current-operand');
const previousOperand = document.querySelector('.previous-operand');
const btnNumber = document.querySelectorAll('.number');
const btnOperator = document.querySelectorAll('.operator');
const btnEqual = document.querySelector('.equals');
const btnClear = document.querySelector('.clear');
const btnDelete = document.querySelector('.delete');

function add(number1, number2) {
  return number1 + number2;
}

function sub(number1, number2){
  return number1 - number2;
}

function mult(number1, number2){
  return number1 * number2;
}

function div(number1, number2){
  if (number2 === 0){
    return 'Error';
  }
  return number1 / number2;
}

function operate(operator, a, b){
  a = parseFloat(a);
  b = parseFloat(b);
  switch(operator){
    case '+':
      return add(a,b);
    case '-':
      return sub(a,b);
    case 'x':
      return mult(a,b);
    case '/':
      return div(a,b);
    default:
      return null;
  }
}

function updateDisplay() {
  currentOperandDisplay.textContent = currentOperand || '0';
  if (currentOperation != null && firstOperand !== ''){
    previousOperand.textContent = `${firstOperand} ${currentOperation}`;
  } else {
    previousOperand.textContent='';
  }
}

function appendNumber(number){
  if (currentOperand === '0' && number !== '.'){
    currentOperand = number;
  } else if (number === '.' && currentOperand.includes('.')){
    return;
  } else if (shouldReset){
    currentOperand = number === '.' ? '0.' : number;
    shouldReset = false;
  } else {
    currentOperand += number;
  }
  updateDisplay();
}

function setOperation(operator){
  if (currentOperation !== null && !shouldReset){
    evaluate();
  }
  firstOperand = currentOperand;
  currentOperation = operator;
  shouldReset = true;
}

function evaluate() {
  if(currentOperation === null || shouldReset) return;
  secondOperand = currentOperand;
  const result = operate(currentOperation, firstOperand, secondOperand);
  currentOperand = result.toString();
  if (currentOperand.includes('.') && currentOperand.split('.')[1]){
    currentOperand = parseFloat(currentOperand).toFixed(8).replace(/\.?0+$/, '');
  }
  currentOperation = null;
  firstOperand = '';
  shouldReset = true;
  updateDisplay();
}

function clear() {
  currentOperand = '0';
  firstOperand = '';
  secondOperand = '';
  currentOperation = null;
  shouldReset = false;
  updateDisplay();
}

function deleteNumber() {
  if (shouldReset) return;
  currentOperand = currentOperand.slice(0, -1);
  if (currentOperand === '' || currentOperand === '-'){
    currentOperand ='0';
  }
  updateDisplay();
}

// EventListeners
btnNumber.forEach(button => {
  button.addEventListener('click', () => {
    appendNumber(button.textContent);
  });
});

btnOperator.forEach(button => {
  button.addEventListener('click', () => {
    setOperation(button.textContent);
  });
});

btnEqual.addEventListener('click', evaluate);
btnClear.addEventListener('click', clear);
btnDelete.addEventListener('click', deleteNumber);

let currentOperand ='0';
updateDisplay();
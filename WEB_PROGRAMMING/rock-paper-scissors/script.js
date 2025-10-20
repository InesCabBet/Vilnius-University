function getComputerChoice() {
  const choices = ['rock', 'paper', 'scissors'];
  const randomIndex = Math.floor(Math.random() * choices.length);
  console.log("Computer's choice:",choices[randomIndex]);
  return choices[randomIndex];
}

function getHumanChoice() {
  let choice = prompt("Choose an option:\nRock = 0\nPaper = 1\nScissors = 2.\n");
  if (choice === "0") {
    console.log("Your choice: rock\n");
    return "rock";
  }
  if (choice === "1") {
    console.log("Your choice: paper\n");
    return "paper";
  }
  if (choice === "2") {
    console.log("Your choice: scissors\n");
    return "scissors";
  }
  console.log("Invalid input");
  return null;
}

function playRound(human, computer) {
  let result = "";
  let hscore = 0;
  let cscore = 0;
  if (human === computer){
    hscore++; cscore++;
    result = "It's a tie";
  } else if ((human === "rock" && computer === "scissors") ||(human === "scissors" && computer === "paper")
    || (human === "paper" && computer === "rock")) {
    hscore++;
    result = "You win";
  } else {
    cscore++;
    result = "You lose";
  }
  console.log(result);
   return { hscore, cscore };
}

function playGame() {
  let humaScore = 0;
  let computerScore = 0;
  for (let i=0; i < 5; i++){
    const humanSelection = getHumanChoice();
    const computerSelection = getComputerChoice();
    const result = playRound(humanSelection, computerSelection);
    humaScore += result.hscore;
    computerScore += result.cscore;
  }
  if (humaScore > computerScore){
    console.log("YOU WIN :)");
  } else {
    console.log("YOU LOSE :(");
  }
}

playGame();
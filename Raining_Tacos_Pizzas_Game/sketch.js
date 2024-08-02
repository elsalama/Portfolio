
var food = [];
var trash;
var gameOver;
var time = 0;
var tacosPic;
var lives = 5;
var pizzaPic;


function preload() {
  tacosPic = loadImage('taquito.png');
  pizzaPic = loadImage('pizza.png');
}

function setup() {
  createCanvas(600, 450);
  for (var i = 0; i < 6; i++) {
    append(food, new Food(random(0, 600), 0, tacosPic, 'taco'));
  }
  for (var j = 0; j < 3; j++) {
    append(food, new Food(random(0, 600), 0, pizzaPic, 'pizza'));
  }
  gameOver = false
  trash = new Trash(width / 2, 450);
}



function draw() {
  background(0, 0, 200);
  if (!gameOver)
    gameOn();
  else
    stop();

}

function gameOn() {
  textSize(25);
  fill(255)
  textAlign(LEFT);
  text("Taco + 1 point\nPizza + 10 points\nUse keys AD to move\nScore: " + time, 0, 20);
  text("Lives:" + lives, 0, 140);
  trash.paint();
  time += trash.checkTrashInt(food);
  for (var i = 0; i < food.length; i++) {
    if (food[i].update()) {
      lives = lives - 1
    }
    food[i].display();
  }
  if (lives == 0) {
    gameOver = true
    stop();
  }

  if (keyIsDown(65)) {
    trash.x -= 5;
  }
  if (keyIsDown(68)) {
    trash.x += 5;
  }
}

function stop() {
  textSize(60);
  fill(255);
  textAlign(CENTER);
  text("GAME OVER\nScore:" + time, width / 2, height / 2)
}

function checkBounds() {
  if (trash.x < 2.25 * trash.w) {
    trash.x = 2.25 * trash.w;
  }
  if (trash.x > width - 3.25 * trash.w) {
    trash.x = width - 3.25 * trash.w;
  }
}
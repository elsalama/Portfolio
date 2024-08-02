class Trash {
  constructor(x, y) {
    this.x = x;
    this.y = y;
    this.w = 10;
    this.h = 20;
  }
  paint() {
    checkBounds();
    ellipseMode(CENTER);
    circle(this.x + 0.5 * this.w, this.y - 2 * this.h, 6 * this.h);
  }
  checkTrashInt(food) {
    let foodX, foodY
    let r = 6 * this.h

    for (var i = 0; i < food.length; i++) {
      foodX = food[i].x
      foodY = food[i].y
      let d = dist(foodX, foodY, this.x + 0.5 * this.w, this.y - 2 * this.h);
      if (d < (r)) {
        food[i].y = 0 - 10;
        if (food[i].type == 'taco')
          return 1;
        else if (food[i].type == 'pizza')
          return 10;
      }
    }
    return 0;
  }
}
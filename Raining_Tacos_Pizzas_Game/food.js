class Food {
  constructor(xPos, yPos, img, type) {
    this.x = xPos;
    this.y = yPos;
    this.image = img;
    this.xVelocity = 0;
    this.yVelocity = map(random(5), 1, 4, 1, 2);
    this.type = type; 
    
  }
  display() {
    image(this.image, this.x, this.y, 80, 80);
  }
  update() {
    this.y += this.yVelocity;

    this.x += this.xVelocity;
    if(this.y + 80 >= height)
    {
      this.y = 0 - 10;
      return true 
    }
    return false
  }   
}
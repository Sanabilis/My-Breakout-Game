LIFE AND SCORING
- Implemented scoring system
   - During the game, the player can earn score by destroying bricks and collecting power-ups.
   - Score is rendered in the bottom-left corner of the screen.
- Implemented lives system
   - Player starts with three lives
   - Each ball escaping the play area lowers the lives by 1.
   - Reaching 0 health results in game over.
   - Player can increase their lives by collecting power-ups.
   - Lives are render in the bottom-right corner of the screen as a heart for each life.


BRICKS DURABILITY
- Each brick has randomly chosen durability in range 1-3.
- Depending on the remaining durability, the bricks become more broken by changing its texture.
- Destroying a brick provides 10 * initial_durability score


POWER-UPS
- Each destroyed brick has a chance to spawn a power-up that starts at the brick's position and travels to the edge of the play area.
- Catching this power-up with any paddle provides its benefits.
- Yellow power-ups provide 100 score.
- Green power-ups give the player 1 life.


ADVANCED GRAPHICS
- Implemented advanced graphics
   - I have implemented the transparency of bricks that occlude the ball in a circular area around the ball object.
   - I have implemented shadow mapping for a single light source.
   - I have (previously) implemented Phong shading model.
- Additionally to the extension, I have implemented the following:
   - UVs for more complex mesh (paddles, balls).
   - Normal mapping to improve the shading of models.
   - Skybox to add background to the scene.
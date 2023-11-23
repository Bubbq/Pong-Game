#include <stdio.h>
#include <raylib.h>

// object representing the ball in the pong game
struct Ball{
    // cartiesian coordinates of the ball
    float X, Y;
    // movement of the ball is variable
    float speedX;
    float speedY;    
};

// object representing a single paddle1
struct Paddle{
    // how much the coordinaties move by
    float speedY;
    // cartesian coordinates of the paddle1
    float x, y;
    // player's score of the game
    int  score;
};

int main() {

    struct Ball ball;
    struct Paddle paddle1;
    struct Paddle paddle2;

    // to create a window in the terminal 
    InitWindow(700, 700, "Pong Game");

    // ball will start at the center of the screen
    ball.X = (GetScreenWidth() / 2.0);
    ball.Y = (GetScreenHeight() / 2.0);
    // how much the ball will move off its x and y axis
    ball.speedX = 300.0;
    ball.speedY = 100.0;

    // setting player ones attributes
    paddle1.x = 50;
    paddle1.y = (GetScreenHeight() / 2.0) - 50;
    paddle1.speedY = 100.0;

    // setting player 2's attributes
    paddle2.x = GetScreenWidth() - 50 - 10;
    paddle2.y = (GetScreenHeight() / 2.0) - 50;
    paddle2.speedY = 100.0;


    // limits the FPS to prevent screen tearing
    SetWindowState(FLAG_VSYNC_HINT);

    // essentiall saying while window should NOT close, the entire application is based of whats inside this while loop...
    while(!WindowShouldClose()){
        // starting the rendering phase
        BeginDrawing();

        // ball will move at slope of -x as the game is running, frame time makes the speed the same no matter the referesh rate
        ball.X += ball.speedX * GetFrameTime();
        ball.Y += ball.speedY * GetFrameTime();

        // reversing the speed to go backwards when we hit the tops and bottom of the screen
        if(ball.Y > GetScreenHeight() || ball.Y < 0)
            ball.speedY *= -1;

        // moving the left paddle based on userInput (W or S)
        if(IsKeyDown(KEY_W))
            paddle1.y -= (paddle1.speedY / 10.0);
        if(IsKeyDown(KEY_S))
            paddle1.y += (paddle1.speedY / 10.0);

        // moving the right paddle based on arrow keys
        if(IsKeyDown(KEY_DOWN))
            paddle2.y += (paddle2.speedY / 10.0);
        if(IsKeyDown(KEY_UP))
            paddle2.y -= (paddle2.speedY / 10.0);


        // Rectangle representation of paddles needed for collision checking
        Rectangle p1 = {paddle1.x + 5, paddle1.y, 10, 100};
        Rectangle p2 = {paddle2.x - 5, paddle2.y, 10, 100};

        // circular rep for collision check
        Vector2 ballPos = {ball.X, ball.Y};

        if(CheckCollisionCircleRec(ballPos, 5, p1)){
            // change the horizontal direction of the ball
            ball.speedX *= -1;
            ball.speedX += 20;
        }

        if(CheckCollisionCircleRec(ballPos, 5, p2)){
            // change the horizontal direction of the ball
            ball.speedX *= -1;
            // make ball faster upon every hit
            ball.speedX -= 20;
        }

        // if one of the player's win, the ball is out of bounds in the x position
        if(ball.X > GetScreenWidth() || ball.X < 0){
            DrawText("Game Over", GetScreenWidth() / 5.5, 50, 50, WHITE);
            // pressing space resets the game, ball position, and speed
            if(IsKeyDown(KEY_SPACE)){
                paddle1.score += 1;
                // reset ball speed
                ball.speedX = 300.0;
                ball.speedY = 100.0;
                // make ball go back to center
                ball.X = GetScreenWidth() / 2.0;
                ball.Y = GetScreenHeight() / 2.0;
            }
        }

        DrawText("Player 1", 50, 20, 30, WHITE);
        DrawText("Player 2", GetScreenWidth() - 200, 20, 30, BLUE);

        // giving the window a black background
        ClearBackground(BLACK);

        // drawing a circle, the ball in this case
        DrawCircle(ball.X,ball.Y, 5, WHITE);

        // player 1's rectagle, the screen draws from the top left, have to subtract by the half of the height to make it move up
        DrawRectangle(paddle1.x, paddle1.y, 10, 100, WHITE);
        // player 2's rectangle
        DrawRectangle(paddle2.x,paddle2.y, 10, 100, BLUE);

        // shows the FPS of the screen
        DrawFPS(50,50);

        // ending the rendering phase
        EndDrawing();
    }


    // like file reading, should always close to prevent a memory leak
    CloseWindow();
    return 0;
}

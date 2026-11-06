#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

int screen_x = 1136;
int screen_y = 896;


void generatebullet(float startX, float startY, int direction, float bullX[], float bullY[], bool bullAlive[], int bullDir[], int maxBull)
{
    for(int i = 0; i < maxBull; i++) 
    {
        if(bullAlive[i] == false) 
        {
            bullX[i] = startX; 
            bullY[i] = startY + 15; 
            bullDir[i] = direction; 
            bullAlive[i] = true;
            break; 
        }
    }
}

void movebullets(float bullX[], float bullY[], bool bullAlive[], int bullDir[], int maxBull, char** lvl, int cell_size)
{
    for(int i = 0; i < maxBull; i++) 
    {
        if(bullAlive[i] == true) 
        {
            bullX[i] += (7 * bullDir[i]); 
            int col = bullX[i] / cell_size; 
            int row = bullY[i] / cell_size;
            if(col < 0 || col > 18 || lvl[row][col] == '#') 
            	bullAlive[i] = false; 
        }
    }
}

void generateBall(float startX, float startY, int direction, float ballX[], float ballY[], bool isBallAlive[], int ballDir[], int ballType[], int typeToThrow, int maxBalls)
{
    for(int i=0; i<maxBalls; i++) {
        if(!isBallAlive[i]) {
            ballX[i] = startX;
            ballY[i] = startY + 10;
            ballDir[i] = direction;
            ballType[i] = typeToThrow; 
            isBallAlive[i] = true;
            break;
        }
    }
}


void moveBalls(float ballX[], float ballY[], bool isBallAlive[], int ballDir[], int maxBalls, char** lvl, int cell_size, float enemyX[], float enemyY[], bool isAlive[], int totalEnemies, int& score)
{
    for(int i=0; i<maxBalls; i++) {
        if(isBallAlive[i]) {
            ballX[i] += (10 * ballDir[i]); 
            int col = ballX[i] / cell_size; int row = ballY[i] / cell_size;

            if(col < 0 || col > 18 || lvl[row][col] == '#') {
                isBallAlive[i] = false;
            }

            for(int j=0; j<totalEnemies; j++) {
                if(isAlive[j]) {
                    if(abs(ballX[i] - enemyX[j]) < 40 && abs(ballY[i] - enemyY[j]) < 40) {
                        isAlive[j] = false; 
                        isBallAlive[i] = false; 
                        score += 100; 
                        break;
                    }
                  }
                }
              }
            }
          }

//ye function bilkul phla wali screen ko show krwata hai

void startscreen(RenderWindow& window,Sprite& playgamescreenSprite){
    Event ev;
    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
        
            if (ev.type == Event::Closed) window.close();
            
            if (ev.type == Event::KeyPressed){ 
                 if(Keyboard::isKeyPressed(Keyboard::Enter)) 
                 {
                 	return;
                 }
            }
        }
        window.clear();
        window.draw(playgamescreenSprite);
        window.display();
    }
}

//This is the interface function in which i am creating the # for the blocks

void interface(char** lvl , int& level ,const int height ,const int width ){

    if(level==1){
        lvl[3][4] = '#'; lvl[3][5] = '#'; lvl[3][6] = '#'; lvl[3][7] = '#';lvl[3][8] = '#'; lvl[3][9] = '#';
        lvl[3][10] = '#';lvl[3][11] = '#'; lvl[3][12] = '#'; lvl[3][13] = '#';  lvl[4][8] = '#'; lvl[4][9] = '#';
        lvl[5][1] = '#'; lvl[5][2] = '#'; lvl[5][3] = '#'; lvl[5][4] = '#';
        lvl[5][13] = '#'; lvl[5][14] = '#'; lvl[5][15] = '#'; lvl[5][16] = '#';
        lvl[6][7] = '#'; lvl[6][8] = '#'; lvl[6][9] = '#'; lvl[6][10] = '#';
        lvl[11][3] ; lvl[11][4] = '#'; lvl[11][5] = '#'; lvl[11][6] = '#'; lvl[11][7] = '#'; lvl[11][8] = '#';
    lvl[11][9] = '#'; lvl[11][10] = '#'; lvl[11][11] = '#'; lvl[11][12] = '#'; lvl[11][13] = '#'; lvl[11][14]; lvl[5][7] = '#'; lvl[5][8] = '#'; lvl[5][9] = '#'; lvl[5][10] = '#';
        lvl[7][7] = '#'; lvl[7][8] = '#'; lvl[7][9] = '#'; lvl[7][10] = '#';
        lvl[8][7] = '#'; lvl[8][8] = '#'; lvl[8][9] = '#'; lvl[8][10] = '#';
        lvl[9][7] = '#'; lvl[9][8] = '#'; lvl[9][9] = '#'; lvl[9][10] = '#';
        lvl[10][8] = '#'; lvl[10][9] = '#';
        lvl[7][1] = '#'; lvl[7][2] = '#'; lvl[7][3] = '#'; lvl[7][4] = '#';
        lvl[7][13] = '#'; lvl[7][14] = '#'; lvl[7][15] = '#'; lvl[7][16] = '#';
        lvl[9][1] = '#'; lvl[9][2] = '#'; lvl[9][3] = '#'; lvl[9][4] = '#';
        lvl[9][13] = '#'; lvl[9][14] = '#'; lvl[9][15] = '#';lvl[9][16]='#';
        return ;
    }
    
    if(level==2){
     //these variables are basically about the slant generation
        // least wale ye kr rhe hain k kam sa kma col 2 sa shru ho aur row 2 sa shru ho
          int least_col=2; 
          int least_row=2;
        //zyda sa syda width-5 aur height-5  ye -5 iss liye rkha hai take screen sa gaib na hojye   
          int most_col=width-5; 
          int most_row=height-5;
  //in this slant c r mein rand function is basically giving the start of r and c    
          int slant_c=(least_col+(rand()%(most_col-least_col-5)));
          int slant_r=(least_row+(rand()%(most_row/3)));
          
     //the lenght is basically the random function in which the length can be between 4 to 8     
          int slant_length= 4+(rand()%5);
          
    //ab ye loop ek ek row aur column agge half half bnaata jai ga       
          for(int i=0 ; i<slant_length ; i++){
             int c = (slant_c+i); 
             int r = (slant_r+i);
             
             if( (r>=(height-1)) || (c>=(width-1)) )
              break; 
   // jo r and c bnye hain unko character store krwane hain k jab !  ho tou upper half draw if ^  tou lower half draw
          //ye ^  -1 iss liye hai k ye phla shru hota hai        
             lvl[r][c]='!'; 
             lvl[r-1][c]='^' ;                     
          }
          
          
          lvl[3][1]='#' ;lvl[3][2]='#' ;lvl[3][3]='#' ;
          lvl[5][1]='#' ; lvl[7][1]='#' ; lvl[7][2]='#' ; lvl[7][3]='#' ; lvl[7][4]='#' ; lvl[7][5]='#' ; lvl[7][6]='#' ; lvl[7][7]='#' ; 
          lvl[9][1]='#' ;lvl[9][2]='#' ;lvl[9][3]='#' ;lvl[9][4]='#' ;
          lvl[11][4]='#' ;lvl[11][5]='#' ;lvl[11][6]='#' ;lvl[11][7]='#' ;lvl[11][8]='#' ;lvl[11][9]='#' ;lvl[11][10]='#' ;lvl[11][11]='#' ;lvl[11][12]='#' ;lvl[11][13]='#' ;
          lvl[3][8] = '#'; lvl[3][9] = '#'; lvl[3][10] = '#'; lvl[3][11] = '#'; lvl[3][12] = '#'; lvl[3][13] = '#'; lvl[3][14] = '#'; 
          lvl[5][9]='#' ;lvl[5][8]='#' ;lvl[5][7]='#' ;lvl[5][10]='#' ;lvl[5][11]='#' ;lvl[5][14]='#' ;lvl[5][15]='#' ;lvl[5][16]='#' ;
          lvl[7][11]='#' ;lvl[7][10]='#' ;lvl[7][15]='#' ; lvl[7][12]='#' ; lvl[7][13]='#' ; lvl[7][14]='#' ;lvl[7][15]='#' ;lvl[7][16]='#' ;

          return ;
     }
    //interface for the level 3 
     if(level==3)
     {

	lvl[2][1] = '#' ;lvl[2][2] = '#' ;lvl[2][3] = '#' ;lvl[2][4] = '#' ;lvl[2][5] = '#' ;lvl[2][6] = '#' ;lvl[2][16] = '#' ;
	lvl[2][15] = '#' ;lvl[2][14] = '#' ;lvl[2][13] = '#' ;lvl[2][12] = '#' ;lvl[2][11] = '#' ;lvl[4][3] = '#' ;lvl[4][2]='#';
	lvl[4][1] = '#' ;lvl[4][6] = '#' ;lvl[4][7] = '#' ;lvl[4][8] = '#' ;lvl[4][9] = '#' ;lvl[4][10] = '#' ;lvl[4][11] = '#' ;
	lvl[4][16] = '#' ;lvl[4][15] = '#' ;lvl[4][14] = '#';lvl[6][1] = '#' ;lvl[6][2] = '#' ;lvl[6][16] = '#' ;lvl[6][15] = '#';
	lvl[8][1] = '#' ;lvl[8][2] = '#' ;lvl[8][3] = '#' ;lvl[8][16] = '#' ;lvl[8][15] = '#' ;lvl[8][14] = '#' ;lvl[8][4] = '#' ;
	lvl[8][13] = '#' ;lvl[11][4]='#'; lvl[11][5] = '#' ;lvl[11][6] = '#' ;lvl[11][7] = '#' ;lvl[11][8] = '#' ;
	lvl[11][9] = '#' ;lvl[11][10] = '#' ;lvl[11][11] = '#' ;lvl[11][12] = '#' ;lvl[11][13] = '#'; 

     return ;     
     }   
}

//this is basically the vaccuam setup function in which vaccuam is setting up


void vacuumsetup(RenderWindow& window, char** lvl , Texture vacuumTexture, Sprite vacuumSprite, float& player_x, float player_y, float enemyx[], float enemyy[],bool isalive[], int enemydir[], int enemytype[], const int totenemy,Sprite ghostSprite, Sprite skeletonSprite, int level, int currentenemy, int& caught_enemy_count, int& Pwidth, int& Pheight, Sprite PlayerSprite, int& playerdirection, int& choice , int& score, float suction_speed, int range_new, int capturedEnemies[], int& enemies) 
{


    int range = range_new * Pwidth; 
 //deffining  that in lvl 1 and 2 how many capturing capacity   
    int capacity = (level == 1) ? 3 : 5;
    int playerdirectiony = 0; 

//x and y position
    float vacuumx;
    float vacuumy;

//vaccuam facing right
    if(Keyboard::isKeyPressed(Keyboard::D)) {
        if(playerdirection != -1){
         playerdirection = -1;
          PlayerSprite.setScale(-1.5,1.5);
          PlayerSprite.setPosition(player_x + Pwidth, player_y);
          }
    }
    
//vaccuam facing left    
    else if(Keyboard::isKeyPressed(Keyboard::A)){
        if(playerdirection != 1){
         playerdirection = 1;
         PlayerSprite.setScale(1.5,1.5); 
         PlayerSprite.setPosition(player_x + Pwidth, player_y);
           }
    }
    
        
    if(Keyboard::isKeyPressed(Keyboard::W)) //up 
    {
         playerdirectiony = -1;
         
    }
    
    else if(Keyboard::isKeyPressed(Keyboard::S))   //down
    {
        playerdirectiony = 1; 
 
    }
    
    
    if(Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl)){
    
    //agr player ki dir 1 hogi to vaccum ki ye postion hogi
        if(playerdirection == 1) {
            vacuumx = player_x - Pwidth + 10; 
            vacuumy = player_y + 0.4 * Pheight;
             vacuumSprite.setScale(1,1);
        } 
        
   //agr player ki direction -1 hogi to vaccuam ki x and y ye hogi     
        else if(playerdirection == -1)
        {
            vacuumx = player_x + 1.5 * Pwidth + 20; 
            vacuumy = player_y + 0.4 * Pheight; 
            vacuumSprite.setScale(-1,1);
        }
        
        
        else if(playerdirectiony == -1)
        {
                vacuumx = player_x + (playerdirection == 1)?(0.5 * Pwidth):(-0.5 * Pwidth)  + 5;
	        vacuumy = player_y - 5;
	        vacuumSprite.setScale(1,1);
        }
        
        else if(playerdirectiony == 1)
        {
                vacuumx = player_x + (playerdirection == 1)?(0.5 * Pwidth):(-0.5 * Pwidth)  + 5;
		vacuumy = player_y + Pheight + 5;
		//Texture 
		vacuumSprite.setScale(1,1);
        }
        
        vacuumSprite.setPosition(vacuumx,vacuumy);
        window.draw(vacuumSprite);

//in this loop hum ye dkh rhe hain k player k right side pr knse enemies pre huy hain

        if(playerdirection == -1) // Right
        {
            for(int i = 0; i < currentenemy; i++) {
            
            //this is checking k player ki suction range mein koi enenmy pra hia ya ni
                if((enemyx[i] > (player_x + Pwidth)) && (enemyx[i] <= (player_x + range)) && isalive[i]) {   
                        //player ki row mein hi hia ya kahin aur  (checking in y axis)
                    if((player_y <= (enemyy[i] + 0.5 * Pheight)) && (player_y >= (enemyy[i] - 0.5 * Pheight))) {
                        enemyx[i] -= suction_speed;  
                        //yahan hum check kr rhe hain k enemy ko gaib kb krna hai       
                        if(enemyx[i] <= (player_x + Pwidth + 40)) {
                            if(enemies < capacity) {
                                capturedEnemies[enemies] = enemytype[i];
                                enemies++;
                                isalive[i] = false;
                                
                                caught_enemy_count++;
                      // ye enemmy ki type k hsaab sa score set ho rha ha          
                                if(enemytype[i]==0){
                                 score+=50;
                                 }
                                if(enemytype[i]==1) {
                                score+=75;
                                }
                                if(enemytype[i]==2){
                                 score+=150;
                                 }
                                if(enemytype[i]==3){
                                 score+=200;
                                 }
                            }
                        }
                    }
                }
            }
        }
        
    //same here for left    
        else // Left
        {
            for(int i = 0; i < currentenemy; i++) {
                if((enemyx[i] < player_x ) && (enemyx[i] > (player_x - range)) && isalive[i]) {   
                    if((player_y <= (enemyy[i] + 0.5 * Pheight)) && (player_y >= (enemyy[i] - 0.5 * Pheight))) {
                        enemyx[i] += suction_speed; 
                        if(enemyx[i] >= (player_x - 40)){
                            if(enemies < capacity) {
                                capturedEnemies[enemies] = enemytype[i];
                                enemies++;
                                isalive[i] = false;
                                
                                caught_enemy_count++;
                                
                                if(enemytype[i]==0){
                                 score+=50;
                                 }
                                 
                                if(enemytype[i]==1){
                                 score+=75;
                                 }
                                 
                                if(enemytype[i]==2){
                                 score+=150;
                                 }
                                 
                                if(enemytype[i]==3){
                                 score+=200;
                                 }
                            }
                         }
                    }
                }
            }
        }                   
    }       
}                                                                     
                                                    
//player selection screen function                                                                
                  
void player_selection(RenderWindow& window, int& choice, Sprite& greenSprite, Sprite& yellowSprite){

    int current_player=1;
    Texture playerselectTexture;
    Sprite playerselectSprite;
    playerselectTexture.loadFromFile("Data/selectplayer.png");
    playerselectSprite.setTextureRect(IntRect(844, 48 ,1132,896));
    playerselectSprite.setTexture(playerselectTexture);
    playerselectSprite.setPosition(0,0);
    
    Event ev;
    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) window.close();
            
       //left side pr green select hota hai aur uska scale brh jta hai     
            if(Keyboard::isKeyPressed(Keyboard::Left)){
           // aur dusre ka ka kam ho jata hia
             greenSprite.setScale(10,10);
              yellowSprite.setScale(7,7);
               current_player=1; 
               }
            if(Keyboard::isKeyPressed(Keyboard::Right)){ 
            yellowSprite.setScale(10,10); 
            greenSprite.setScale(7,7);
             current_player=2; 
             }
            if(Keyboard::isKeyPressed(Keyboard::Space)||Keyboard::isKeyPressed(Keyboard::Enter)){ 
            choice = current_player; 
            return;
             }   
        }
        window.clear();
        window.draw(playerselectSprite);
        greenSprite.setPosition(200, 300); window.draw(greenSprite);
        yellowSprite.setPosition(800, 300); window.draw(yellowSprite);
        window.display();
    }
}
 
 //ye screen level select kr rhi hai   
void level_selection(RenderWindow& window , int& level){

    Texture levelselectionTexture;
    Sprite levelselectionSprite;
    levelselectionTexture.loadFromFile("Data/levelselect1.png");
    levelselectionSprite.setTexture(levelselectionTexture);
    levelselectionSprite.setTextureRect(IntRect(0,0,1136,896));
    levelselectionSprite.setPosition(0,0);      
    
    Event ev;
    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) window.close();
            if (ev.type == Event::KeyPressed) 
            {
                if (ev.key.code == Keyboard::Num1) { 
                level = 1; 
                return;
                 }
                if (ev.key.code == Keyboard::Num2) 
                { 
                level = 2; 
                return;
                }
                if (ev.key.code == Keyboard::Num3) 
                { 
                	level = 3; 
                	return;
            	}
            }
        }
        window.clear();
        window.draw(levelselectionSprite);
        window.display();
    } 
}

// ye display level ka function hai
void display_level(RenderWindow& window, char** lvl, Texture& bgTex, Sprite& bgSprite, Texture& blockTexture, Sprite& blockSprite, const int height, const int width, const int cell_size , int& level ,Texture& upTexture , Texture& lowTexture)
{
    window.draw(bgSprite);
    for (int i = 0; i < height; i += 1) 
    {
        for (int j = 0; j < width; j += 1) {
        
        //# ye kr rha hai k full block bnao
            if (lvl[i][j] == '#') {
                blockSprite.setTexture(blockTexture);
                blockSprite.setPosition(j * cell_size, i * cell_size);
                window.draw(blockSprite);
            }
            
       //! ye kr rha hia k up half bne      
           else if(lvl[i][j]=='!'){
                blockSprite.setTexture(upTexture);
                blockSprite.setPosition(j * cell_size, i * cell_size);
                window.draw(blockSprite);
            }
            
      //^  ye kr rha hia low half k liye      
           else if(lvl[i][j]=='^'){
                blockSprite.setTexture(lowTexture);
                blockSprite.setPosition(j * cell_size, i * cell_size);
                window.draw(blockSprite);
            }
        }
    }
}


//ye function player ki gravuty ko set kr rha ha
void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, const float& gravity, float& terminal_Velocity, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth,bool isdownkeypressed)
{

    velocityY += gravity;
    
 //velocity y ko clamp kr rhe hai   
    if (velocityY > terminal_Velocity){
     velocityY = terminal_Velocity;
     }
     
 //offsety ye chk kr rha hai player k agla frame mein uski value kia hogi   
    offset_y = player_y + velocityY;
    
    
    int left_col = (player_x + 15) / cell_size;
    int right_col = (player_x + Pwidth - 15) / cell_size;
    int mid_col = (player_x + Pwidth/2 ) / cell_size;
    
    if(left_col < 1 || right_col > 17 ) {
     player_y = offset_y; 
     return; 
     }


    if (velocityY > 0) {
        int feet_row = (offset_y + Pheight)/cell_size;
        if(feet_row > 14) { 
        player_y = 13 * cell_size - Pheight;
         velocityY = 0; 
         onGround = true; 
         return; 
         }
         
     //paon k niche next kia hai wo chk kr rha hai niche wala column    
        if(feet_row > 0) {
            bool bottomcheck = (lvl[feet_row][mid_col] == '#' || lvl[feet_row][left_col] == '#' || lvl[feet_row][right_col] == '#'  );
            if(bottomcheck) {
                bool isdrop = false;
                if (isdownkeypressed) {   
                    int belowrow = feet_row + 1;
                    if(belowrow < 14) 
                    if(lvl[belowrow][mid_col] != '#' && lvl[belowrow][left_col] != '#' && lvl[belowrow][right_col] != '#' ) 
                    isdrop = true;
                }
                if(isdrop) { 
                player_y = offset_y;
                 onGround = false;
                  }
                else {
                 velocityY = 0; onGround = true;
                  player_y = feet_row * cell_size - Pheight ;
                   }
            } 
            else { 
            player_y = offset_y; 
            onGround = false; 
            }
        }
    }
    
 //ye jumping k liye    
    else if (velocityY < 0) {
        if(offset_y < 0) {
         player_y = 0;
          velocityY = 0; 
          return;
           }
           
         //  ye uper wala head chekc kr rha hai
        int head_row = (offset_y)/cell_size;
        if(head_row >= 0 && head_row < 14) {
            if(lvl[head_row][mid_col] == '#' || lvl[head_row][left_col] == '#' || lvl[head_row][right_col] == '#') {   
                bool headercheck = false;
                if(head_row == 0) 
                headercheck = true;
                //ye upr wale sa upr wala blockchk rkr rah hai
                else if(lvl[head_row - 1][mid_col] == '#' || lvl[head_row - 1][left_col] == '#' || lvl[head_row - 1][right_col] == '#' ) {
                headercheck = true;
                }
                if(headercheck) { 
                velocityY = 0; 
                player_y = (head_row + 1) * cell_size; 
                }
                else { 
                player_y = offset_y ; 
                onGround = false;
                 }
            } 
            else { 
            player_y = offset_y ;
             onGround = false;
              }
        }   
    }
}


//ye left right movement k liye hai
void updatemovement(char** lvl,Sprite PlayerSprite , float& offset_x, float speed, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth, int& player_direction, bool& ismoving)
{   
    if(Keyboard :: isKeyPressed(Keyboard :: Right)) {   
    
        player_direction = -1;
        offset_x = ((player_x + speed + Pwidth) / cell_size) ;
        
        int top = player_y / cell_size;
         int bottom = (player_y + Pheight - 10) / cell_size; 
         
        if((lvl[top][static_cast<int>(offset_x) ] != '#') && ( lvl[bottom][static_cast<int>(offset_x)] != '#')) {
        
            player_x += speed; 
            ismoving = true;
            
        }
    } 
    else if(Keyboard :: isKeyPressed(Keyboard :: Left)) {   
        player_direction = 1;
        offset_x = ((player_x - speed) / cell_size) ;
        int top = player_y / cell_size; 
        int bottom = (player_y + Pheight - 10) / cell_size;
        if((lvl[top][static_cast<int>(offset_x)] != '#')&&( lvl[bottom][static_cast<int>(offset_x)] != '#')) {
            player_x -= speed; 
            ismoving = true;
        }   
    }
     else {
      ismoving = false;
       }
}

//is function mien hum enemy ko x and y psotion de rhe hain
void enemysetup(float enemyx[], float enemyy[], int enemyWidth[], int enemyHeight[], bool isalive[], int enemydir[], int enemytype[], const int totenemy, Sprite ghostSprite, Sprite skeletonSprite, Sprite chelnovSprite, Sprite invisiblemanSprite, int& currentenemy, int level, char** lvl, int cell_size)
{
    if (level == 1)
    {
        currentenemy = 12;
        for (int i = 0; i < currentenemy; i++)
        {
            isalive[i] = true;
            enemydir[i] = (rand() % 2 == 0) ? 1 : -1;
            if (i < 8)
            {
                enemytype[i] = 0;
                enemyHeight[i] = 45;
                enemyWidth[i] = 53;
                if (i < 4)
                {
                    enemyx[i] = 240 + 130*i;
                    enemyy[i] = 145;
                }
                else if (i > 3  && i < 6)
                {
                    enemyx[i] = 70 + 128 * (i - 4);
                    enemyy[i] = 273;
                }
                else
                {
                    enemyx[i] = 840 + 128 * (i - 6);
                    enemyy[i] = 400;
                }
            }
            if (i > 7 && i < 12)
            {
                enemytype[i] = 1;
                enemyHeight[i] = 57;
                enemyWidth[i] = 48;
                if (i < 10)
                {
                    enemyx[i] = 256 + 150 * (i - 7);
                    enemyy[i] = 100;
                }
                if(i > 9 && i < 12)
                {
                    enemyx[i] = 256 + 150 * (i - 6);
                    enemyy[i] = 690;
                }
            }
        }
    }
    
    
    //iss level mein hum random sa position de rhew hian
    else if (level == 2)
    {
        currentenemy = 20;
        for (int i = 0; i < currentenemy; i++)
        {
            isalive[i] = true;
            enemydir[i] = (rand() % 2 == 0) ? 1 : -1;

            if (i < 4)
            {
                enemytype[i] = 0;
                enemyHeight[i] = 45;
                enemyWidth[i] = 53;
            }
            else if (i < 13)
            {
                enemytype[i] = 1;
                enemyHeight[i] = 57;
                enemyWidth[i] = 48;
            }
            else if (i < 17)
            {
                enemytype[i] = 3;
                enemyHeight[i] = 57;
                enemyWidth[i] = 38;
            }
            else
            {
                enemytype[i] = 2;
                enemyHeight[i] = 57;
                enemyWidth[i] = 38;
            }

            bool validSpotFound = false;
            while (!validSpotFound)
            {
                int r = 2 + (rand() % 10);
                int c = 2 + (rand() % 14);

                float pX = c * cell_size;
                float pY = r * cell_size;

                if (lvl[r][c] != '#' && lvl[r + 1][c] == '#')
                {
                    if (abs(pX - 550) > 200 || abs(pY - 150) > 200)
                    {
                        enemyx[i] = pX;
                        enemyy[i] = pY;
                        validSpotFound = true;
                    }
                }
            }
        }
    }
    
    
}


//ye enemy ko move krane k liye 

void enemymovement(char** lvl, const int cell_size, const int height, const int width, int enemyWidth[], int enemyHeight[], float enemyx[], float enemyy[], bool isalive[], int enemydir[], int enemytype[], const int totenemy, Sprite ghostSprite, Sprite skeletonSprite, Sprite chelnovSprite, Sprite invisiblemanSprite, int& currentenemy, int level, int chelnovtimer[], float bulletX[], float bulletY[], bool isBulletAlive[], int bulletDir[])
{
    for(int i = 0; i < currentenemy; i++)
    {
    //ye if iss liye hia chk kro k enewmy zinda bhi hia k nai
        if(isalive[i] == true)
        {
            int up_col = (enemyy[i]) / cell_size; 
            int down_col = (enemyy[i] + enemyHeight[i]) / cell_size;
            int row = (enemyx[i] + ((enemydir[i] > 0) ? enemyWidth[i] : 0) + enemydir[i]) / cell_size;

            if(((row > 0) && (row < width)) && ((down_col > 0) && (down_col < (height - 1))))
            {
                int decider = rand() % 30 + 1;
                // SKELETON JUMP
                if(enemytype[i] == 1 && decider == 20) {
                
                    int head = (enemyy[i] - cell_size - 20) / cell_size;
                    if((lvl[down_col][row] == '#') && (head > 0) && (lvl[head - 1][row] != '#')){ 
                    	enemyy[i] -= (cell_size - 12);
                    }
                }
                // CHELNOV FIRE
                if(enemytype[i] == 3) {
                
                    chelnovtimer[i]++;
                    if(chelnovtimer[i] > 200) {
                        if(chelnovtimer[i] == 205) {
                            chelnovSprite.setTextureRect(IntRect(12, 6, 23, 36)); 
                            generatebullet(enemyx[i], enemyy[i], enemydir[i], bulletX, bulletY, isBulletAlive, bulletDir, 20);
                        }
                        if(chelnovtimer[i] >= 300) chelnovtimer[i] = 0;
                        else continue;
                    }
                }
                
                // INVISIBLE MAN
                if(enemytype[i] == 2) {
                    if(chelnovtimer[i] == 0) {
                        if(rand() % 100 == 5) { 
                        chelnovtimer[i] = 1;
                         enemyx[i] = -1000; 
                         enemyy[i] = -1000;
                          }
                    } 
                    else
                     {
                        chelnovtimer[i]++;
                        if(chelnovtimer[i] > 100) {
                            int attempts = 0;
                            while(attempts < 10) {
                                int rCol = 2 + (rand() % 15); 
                                int rRow = 2 + (rand() % 10);
                                if(lvl[rRow][rCol] != '#') { 
                                enemyx[i] = rCol * cell_size;
                                 enemyy[i] = rRow * cell_size; 
                                 chelnovtimer[i] = 0;
                                  break;
                                   }
                                attempts++;
                                
                            }
                            if(attempts >= 10) 
                            chelnovtimer[i] = 101;
                        }
                        continue;
                    }
                }
                // MOVE
                if(((lvl[up_col][row] != '#') && (lvl[down_col][row] != '#')))
                 enemyx[i] += enemydir[i];
                else {
                 enemydir[i] = (-1) * enemydir[i];
                  enemyx[i] += enemydir[i];
                   }
            }
             else { 
             enemydir[i] = (-1) * enemydir[i];
              enemyx[i] += enemydir[i];
               }
        }
    }
}


// ye enemy ko gravity de rha hian
void enemygravity(char** lvl, const int cell_size , const int height, const int width, int enemyWidth[], int enemyHeight[], float enemyx[], float enemyy[], bool isalive[], int enemydir[], int enemytype[], const int totenemy,Sprite ghostSprite, Sprite skeletonSprite, Sprite  chelnovSprite, Sprite invisiblemanSprite, int& currentenemy, int level)
{ 
  
    for(int i=0;i < currentenemy;i++) {
    
      //ye enemy ki future position de rha hain
        int enemyoffset = enemyy[i] + 3;
        if(isalive[i]==true){
        
            if(enemytype[i] == 0) 
            continue;
            else {
            
            int left_col = (enemyx[i] + 15) / cell_size;
            
             int right_col = (enemyx[i] + enemyWidth[i] - 15) / cell_size;
             
            int mid_col = (enemyx[i] + enemyWidth[i]/2 ) / cell_size;
            
            if(left_col < 1 || right_col > 17 ) {
             enemyy[i] = enemyoffset; 
            continue; 
            }
            
            int feet_row = (enemyoffset + enemyHeight[i])/cell_size;
            
            if(feet_row > 14) { 
            enemyy[i] = 13 * cell_size - enemyHeight[i];
             continue; 
             }
            if((feet_row < 0) || (lvl[feet_row][mid_col] == '#' || lvl[feet_row][left_col] == '#' || lvl[feet_row][right_col] == '#' ))
             continue ;
            else
             enemyy[i] += 2;
            }
        }
    }           
}


//ye functionn enemy ko screen pa drwa krwa rhe hian
void enemydrawfun(RenderWindow& window, float enemyx[], float enemyy[], bool isalive[], int enemyWidth[], int enemyHeight[], int enemydir[],int enemytype[], const int totenemy,Sprite ghostSprite, Sprite skeletonSprite,Sprite  chelnovSprite, Sprite invisiblemanSprite, int currentenemy, int level)
{
    for(int i=0; i < currentenemy; i++) {
        if(isalive[i] == true) {
        
            Sprite* currentSprite = nullptr;
            if(enemytype[i] == 0)
             currentSprite = &ghostSprite;
             
            else if(enemytype[i] == 1)
             currentSprite = &skeletonSprite; 
             
            else if(enemytype[i] == 2) 
            currentSprite = &invisiblemanSprite;
            
            else if(enemytype[i] == 3)
             currentSprite = &chelnovSprite;
            

            if(currentSprite != nullptr) {
                if(enemydir[i] == 1) {
                
                 (*currentSprite).setScale(-1.5f,1.5f);
                  (*currentSprite).setPosition(enemyx[i] + enemyWidth[i],enemyy[i]);
                  
                   }
                else { 
               (*currentSprite).setScale(1.5f,1.5f);
               (*currentSprite).setPosition(enemyx[i],enemyy[i]); 
                 }
                window.draw(*currentSprite);
            }
        }
    }
}

void fontsetter(Font& font, Text& scoretext, Text& timertext, Text& livestext) {

//ye font load krwa rha hu
    font.loadFromFile("Data/font.ttf");
  
  //ye score ka sarra set kr rha hia position wgira  
    scoretext.setFont(font);
    scoretext.setCharacterSize(25);
    scoretext.setFillColor(Color::White);
    scoretext.setPosition(20, 20);
    scoretext.setString("SCORE: 0");
  
  //ye timer kaa  
    timertext.setFont(font);
    timertext.setCharacterSize(25);
    timertext.setFillColor(Color::Yellow);
    timertext.setPosition(800, 20);
    timertext.setString("TIME: 0");
  
  // ye lives ka   
    livestext.setFont(font);
    livestext.setCharacterSize(25);
    livestext.setFillColor(Color::Red);
    livestext.setPosition(450, 20);
    livestext.setString("LIVES: 3");
}		


void levelbonuses(int& level , float& timeelapse , int& score ){
//ye bonus daal rha hu
    if(level==1) 
    score+=1000; 
    
    else if(level==2) 
    score+=2000; 
    
    else if(level==3) 
    score+=3000;
   
   //ye agr time sa phla kr deta hia tou uska bonus hai 
    if (level == 1) 
    { 
    
    	if(timeelapse<30) 
    		score += 2000; 
    	else if(timeelapse<45) 
    		score += 1000; 
    	else if(timeelapse<60) 
    		score += 500; 
    	}
    	
    else if (level == 2) 
    { 
    
    	if(timeelapse<60) 
    		score += 3000; 
    	else if(timeelapse<90) 
    		score += 1500; 
    	else if(timeelapse<120) 
    	        score += 750; 
    	        
    	}
}

		
//ye function iss liye hai k agr player dubara khelna chye time eneded k baad		
bool again(RenderWindow& window) {	

    Texture againtexture; 
    Sprite againsprite;
    againtexture.loadFromFile("Data/again.png");
     againsprite.setTexture(againtexture); 
     againsprite.setPosition(0, 0);
     
    Event ev;
    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) { 
            window.close();
             return false;
              }
            if (ev.type == Event::KeyPressed) { 
            if (ev.key.code == Keyboard::Enter) 
            return true; 
            }
        }
        window.clear(Color::Black); 
        window.draw(againsprite); 
        window.display();
    }
    return false;
}

//ye function saara setup again kr rha ha iuf the player plays again
void enemyagain(float& player_x, float& player_y, int& score, int& caught_enemy_count, Clock& gameClock, float enemyx[], float enemyy[], bool isalive[], int enemydir[], int enemytype[], int enemyWidth[], int enemyHeight[], int totenemy, Sprite& ghostSprite, Sprite& skeletonSprite,Sprite& chelnovSprite,Sprite& invisiblemanSprite, int& currentenemy, int level, bool& levelbonus, char** lvl, int cell_size) {

    player_x = 900; 
    player_y = 150;
    score = 0; 
    caught_enemy_count = 0; 
    levelbonus = false;
    gameClock.restart();
    
    enemysetup(enemyx, enemyy, enemyWidth, enemyHeight, isalive, enemydir, enemytype, totenemy, ghostSprite, skeletonSprite, chelnovSprite, invisiblemanSprite, currentenemy, level, lvl, cell_size);
    
}


//ye function powerups ko dkh rha hia 
void managePowerups(RenderWindow& window, Sprite& powerupSprite, float& skate_x, float& skate_y, bool& skate_active, float& gun_x, float& gun_y, bool& gun_active,float& battery_x, float& battery_y, bool& battery_active, float& star_x, float& star_y, bool& star_active,float player_x, float player_y, int Pwidth, int Pheight, float& current_speed, int& range_mod, float& suction_speed, int& lives)
{

    if(skate_active) {
    
        powerupSprite.setTextureRect(IntRect(16,384,32,26));
         powerupSprite.setPosition(skate_x, skate_y);
          window.draw(powerupSprite);
          
        if (player_x < skate_x + 32 && player_x + Pwidth > skate_x && player_y < skate_y + 32 && player_y + Pheight > skate_y) { 
        skate_active = false; 
        current_speed = current_speed * 2;
         }
    }
    
    if(gun_active) {
        powerupSprite.setTextureRect(IntRect(382,384,31,26)); 
        powerupSprite.setPosition(gun_x, gun_y); 
        window.draw(powerupSprite);
        
        if (player_x < gun_x + 32 && player_x + Pwidth > gun_x && player_y < gun_y + 32 && player_y + Pheight > gun_y) { 
        gun_active = false; 
        range_mod = 5;
         }
    }
    if(battery_active) {
        powerupSprite.setTextureRect(IntRect(119,384,31,26));
         powerupSprite.setPosition(battery_x, battery_y); 
         window.draw(powerupSprite);
         
        if (player_x < battery_x + 32 && player_x + Pwidth > battery_x && player_y < battery_y + 32 && player_y + Pheight > battery_y){
         battery_active = false;
          suction_speed = 8.0f; 
          }
    }
    if(star_active) {
        powerupSprite.setTextureRect(IntRect(941,383,30,27)); 
        powerupSprite.setPosition(star_x, star_y);
         window.draw(powerupSprite);
         
        if (player_x < star_x + 32 && player_x + Pwidth > star_x && player_y < star_y + 32 && player_y + Pheight > star_y) {
         star_active = false;
          lives++; 
          }
    }
}

void setupPowerups(float& skate_x, float& skate_y, bool& skate_active, float& gun_x, float& gun_y, bool& gun_active, float& battery_x, float& battery_y, bool& battery_active, float& star_x, float& star_y, bool& star_active) {

    skate_x = 300;
     skate_y = 650; 
     skate_active = true;
    gun_x = 800; 
    gun_y = 400; 
    gun_active = true;
    battery_x = 550;
     battery_y = 200; 
     battery_active = true;
    star_x = 100; 
    star_y = 750;
     star_active = true;
}

//ye function  level 3 k andr jo cup hai uski movement ko handle kr rha hia
void cupcreation(RenderWindow& window, Sprite& cupSprite, float& cup_x, float& cup_y, int& cup_dir)
{

    float cupspeed = 0.5f; 
    
    cup_y += (cupspeed*cup_dir);
//ye ocillation k liye set kia hai
        if(cup_y >= 470) {
        cup_dir = -1;
    }
    else if(cup_y <= 430) {
        cup_dir = 1;
    }
   
    cupSprite.setPosition(cup_x-200,cup_y-200);
    window.draw(cupSprite);
}

bool winscreen(RenderWindow& window) {
    Texture winTexture;
    Sprite winSprite;
    
    // Make sure you have this image in your Data folder!
    if (winTexture.loadFromFile("Data/winscreen.png")) {
        winSprite.setTexture(winTexture);
        winSprite.setPosition(0,0); 
    }
    
    Event ev;
    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                window.close();
                return false;
            }
            if (ev.type == Event::KeyPressed) {
                if (Keyboard::isKeyPressed(Keyboard::Enter)) 
                
                return true;  // dubara play
                if (Keyboard::isKeyPressed(Keyboard::Escape))               
                 return false; // khtm
            }
        }
        window.clear(Color::Black);
        window.draw(winSprite);
        window.display();
    }
    return false;
}



int main()
{
    RenderWindow window(VideoMode(screen_x, screen_y), "Tumble-POP", Style::Resize);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    srand(time(0)); 
    const int cell_size = 64;
    const int height = 14;
    const int width = 18;
    char** lvl;
    int level;
   
   //ye kuch new variables hain 
    Font font;
    Text timertext;
    Text scoretext;
    Text livestext;
    int score = 0;
    bool levelbonus = false;
    Clock gameClock;
    
    Texture playgamescreenTexture;
    Sprite playgamescreenSprite;
    playgamescreenTexture.loadFromFile("Data/playgame.png");
    playgamescreenSprite.setTexture(playgamescreenTexture);
    playgamescreenSprite.setTextureRect(IntRect(198,39,1132,896));
    playgamescreenSprite.setPosition(0,0);
    
    //music credentials
    Music lvlMusic;
    if(lvlMusic.openFromFile("Data/mus.ogg")) { 
    lvlMusic.setVolume(20);
     lvlMusic.play(); 
     lvlMusic.setLoop(true);
      }
      

    float player_x = 900;
    float player_y = 150;
    float speed = 5;
    const float jumpStrength = -20; 
    const float gravity = 1;
     float offset_x = 0;
    int PlayerHeight =60;
     int PlayerWidth = 48;
      bool ismoving = false ;
      
 //   ye player sprites ka scene set kr rhw hu
     Texture playermove; 
     Texture playerstop;
     playermove.loadFromFile("Data/tumblepop.png");
      playerstop.loadFromFile("Data/player.png");
     Sprite PlayerSprite; PlayerSprite.setTexture(playerstop);
      Texture PlayerTexture;
    PlayerSprite.setScale(1.5,1.5);
     PlayerSprite.setPosition(player_x, player_y);

    bool onGround = false;
     float velocityY = 0; 
     float terminal_Velocity = 15;
    float offset_y = 0; 
    bool isdownkeypressed = false;
    
    

    Texture greenTexture; 
    Sprite greenSprite; 
    Texture yellowTexture; 
    Sprite yellowSprite;
    
    greenTexture.loadFromFile("Data/tumblepop.png"); 
    greenSprite.setTexture(greenTexture);
    greenSprite.setTextureRect(IntRect(16,42,32,39));
     greenSprite.setScale(10,10);
      greenSprite.setPosition(100, 300);
      
      
    yellowTexture.loadFromFile("Data/tumblepop.png");
     yellowSprite.setTexture(yellowTexture);
    yellowSprite.setTextureRect(IntRect(16,231,32,39)); 
    yellowSprite.setScale(10,10);
     yellowSprite.setPosition(800, 300);
     
    //yahan pr kuch screens k functions ko call kr rha hu
    int choice;
    startscreen( window, playgamescreenSprite);
    player_selection(window, choice, greenSprite, yellowSprite);
    level_selection(window ,  level);
    fontsetter(font, scoretext , timertext, livestext);
   
   //ye chz background textures and blocks ko load kr rhi hai    
    Texture bgTex;
     Sprite bgSprite;
      Texture blockTexture;
       Sprite blockSprite; 
       Texture upTexture; 
       Texture lowTexture;
     
   //ye levels k hsaab sa background load kr rhi hai    
    if(level==1) 
    bgTex.loadFromFile("Data/bglvl1.png");
    
    if(level==2)
     bgTex.loadFromFile("Data/bglvl2.png");
     
    if(level==3)
     bgTex.loadFromFile("Data/bglvl5.png");
     
     
    bgSprite.setTexture(bgTex);
    
    //ye levels k hsaab sa block load kr rhi ha
    if(level==1) 
    blockTexture.loadFromFile("Data/blocklvl1.png");
    
    if(level==2) 
    blockTexture.loadFromFile("Data/blocklvl2.png");
    
    if(level==3)
     blockTexture.loadFromFile("Data/blocklvl5.png");
     
    
    upTexture.loadFromFile("Data/upp.png"); 
    lowTexture.loadFromFile("Data/lo.png");
    blockSprite.setTexture(blockTexture);
     
     //ye choice k hsaab sa player select kr rhi hai   
    if(choice == 1)
    {
    
    PlayerTexture.loadFromFile("Data/tumblepop.png"); 
    PlayerSprite.setTexture(PlayerTexture); 
    PlayerSprite.setTextureRect(IntRect(16,42,32,39)); 
    
    }
    else { 
    
    PlayerTexture.loadFromFile("Data/tumblepop.png"); 
    PlayerSprite.setTexture(PlayerTexture);
     PlayerSprite.setTextureRect(IntRect(16,231,32,39));
      speed = 7; 
      
      }
      
      
    PlayerSprite.setScale(1.5f,1.5f); 
    PlayerSprite.setPosition(player_x, player_y);
    
    lvl = new char* [height];
    for (int i = 0; i < height; i++) { 
    lvl[i] = new char[width]; 
    
    for(int j=0; j<width; j++) 
    lvl[i][j] = ' '; 
    
    }
    for(int i=0; i<height; i++) {
     for(int j=0; j<width; j++) { 
     if(i==0 || j==0 || i==height-1 || j==width-1) lvl[i][j] = '#'; 
     }    
     }
     
 
    
    int playerdirection = 1;
    int caught_enemy_count = 0;
    Texture vacuumTexture; 
    Sprite vacuumSprite;
    vacuumTexture.loadFromFile("Data/tumblepop.png"); 
    vacuumSprite.setTexture(vacuumTexture);
    vacuumSprite.setTextureRect(IntRect(529, 338, 45, 29));
  
    const int totenemy = 20;
    float enemyx[totenemy]; 
    float enemyy[totenemy]; 
    bool isalive[totenemy];
    int enemydir[totenemy]; 
    int enemytype[totenemy]; 
    int enemytimer[totenemy];
    int enemyWidth[totenemy]; 
    int enemyHeight[totenemy];
    
    Texture ghostTexture; Sprite ghostSprite;
    ghostTexture.loadFromFile("Data/ghost.png"); 
    ghostSprite.setTexture(ghostTexture);
    ghostSprite.setTextureRect(IntRect(8,8,35,30));
    
    Texture skeletonTexture; Sprite skeletonSprite;
    skeletonTexture.loadFromFile("Data/skeletons.png"); 
    skeletonSprite.setTexture(skeletonTexture);
    skeletonSprite.setTextureRect(IntRect(8,34,32,38));
    
    Texture invisiblemanTexture; 
    Sprite invisiblemanSprite;
    invisiblemanTexture.loadFromFile("Data/invisibleman.png"); 
    invisiblemanSprite.setTexture(invisiblemanTexture);
    invisiblemanSprite.setTextureRect(IntRect(9,18,27,38));
    
    Texture chelnovTexture; 
    Sprite chelnovSprite;
    int chelnovtimer[totenemy] = {0};
    chelnovTexture.loadFromFile("Data/Chelnov.png");
    chelnovSprite.setTexture(chelnovTexture);
    chelnovSprite.setTextureRect(IntRect(12,6,24,36));
    
    int currentenemy = 0;
    //ye wo bullets k credentials hain jo chelnov throw kr rha hai
    const int maxBullets = 20; 
    float bulletX[maxBullets]; 
    float bulletY[maxBullets]; 
    bool isBulletAlive[maxBullets] = {false}; 
    int bulletDir[maxBullets] = {0};

    Sprite bulletSprite; 
    Texture bulletTex;
    bulletTex.loadFromFile("Data/Chelnov.png"); 
    bulletSprite.setTexture(bulletTex);
    bulletSprite.setTextureRect(IntRect(13,13,233,61));
    bulletSprite.setScale(0.5, 0.5); 

    
    int capturedEnemies[5];
    int enemiesInPocket = 0;
    const int maxBalls = 20;
    float ballX[maxBalls]; 
    float ballY[maxBalls];
    bool isBallAlive[maxBalls] = {false}; 
    int ballDir[maxBalls] = {0};
    int ballType[maxBalls] = {0}; 
    
    
    //for level 3 dynamic array creation credentials 
    int size = 0;
    int framecounter = 0;
    float* enemyxptr = nullptr;
    float* enemyyptr = nullptr;
    int* enemytypeptr = nullptr;
    int* enemydirptr = nullptr;
    bool* enemisaliveptr = nullptr;
    float* enemyheightptr = nullptr;
    float* enemywidthptr = nullptr;
    
    interface(lvl,level,height,width);
    enemysetup(enemyx, enemyy, enemyWidth, enemyHeight, isalive, enemydir, enemytype, totenemy, ghostSprite, skeletonSprite, chelnovSprite, invisiblemanSprite, currentenemy, level, lvl, cell_size);
   
   //ye powerups  fucntions k liye kuch variables hain 
    float skate_x, skate_y;
     bool skate_active = false;
    float gun_x, gun_y;  
       bool gun_active = false;
    float battery_x, battery_y;
     bool battery_active = false;
    float star_x, star_y; 
      bool star_active = false;

    // Player Stats
    int range_new = 2;       
    float suction_speed = 3;   
    int lives = 3;
    
    if(level == 2) {
        setupPowerups(skate_x, skate_y, skate_active, gun_x, gun_y, gun_active, battery_x, battery_y, battery_active, star_x, star_y, star_active);
    }

//ye pup sprite wali file k varibales hain
    Sprite pupSprite;
     pupSprite.setTexture(PlayerTexture); 
     pupSprite.setScale(1.5, 1.5);
    
    //deg credentials

    float cup_x = 530; 
    float cup_y = 450; 
    int cup_dir = 1;   

    Texture cupTexture;
    Sprite cupSprite;

    // Load texture only if Level is 3
    if(level == 3) {
    cupTexture.loadFromFile("Data/bowl.png");
        cupSprite.setTexture(cupTexture);
        cupSprite.setScale(0.5f,0.5f);
    }
    
    Event ev;
    int timelimit;
    
    //ye level k hsaabsa time select hain 
    if(level==1) 
    timelimit=120;
    
    if(level==2)
     timelimit=180;
     
    if(level==3)
     timelimit=240;
     
    
   while (window.isOpen())
    {
        while (window.pollEvent(ev)) { if (ev.type == Event::Closed) window.close(); }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
        
        // SHOOT LOGIC (F Key)
        if (Keyboard::isKeyPressed(Keyboard::F)) 
        {
            if(enemiesInPocket > 0) 
            {
                enemiesInPocket--; 
                generateBall(player_x, player_y, -playerdirection, ballX, ballY, isBallAlive, ballDir, ballType, capturedEnemies[enemiesInPocket], 20);
            }
        }


        window.clear(Color::Yellow);
        
        display_level(window, lvl, bgTex, bgSprite, blockTexture, blockSprite, height, width, cell_size,level,upTexture,lowTexture);
        
        float timeelapse = gameClock.getElapsedTime().asSeconds();
        
        
     //ab yahan sa ye set ho rha hai k agr player saare enemies maar de tou tou usko ek screen show hogi tou uss sa player enter kre ga tou level screen escape pr khtm 
        bool allEnemiesDead = false; 

   if(currentenemy > 0){
      allEnemiesDead = true; 
     for(int i = 0; i<currentenemy; i++){
            if(isalive[i] == true){
            
                  allEnemiesDead = false;
                      break;
                      
                }
              }
            }        

     
            if(allEnemiesDead){
            
            if (!levelbonus) {
                levelbonuses(level, timeelapse, score);
                levelbonus = true;
            }


            bool playagain=winscreen(window);

            if (playagain) {
          //agr user dubara play krna chahta hai to ye sb kuch dubara sa reset kr rha hun  
          
                level_selection(window, level);

                // Reset Score and Lives
                score = 0;
                lives = 3;
                caught_enemy_count = 0;
                enemiesInPocket = 0;
                levelbonus = false;
                gameClock.restart();
                
                player_x = 900; 
                player_y = 150; 
                PlayerSprite.setPosition(player_x, player_y);


                if(level==1) 
                bgTex.loadFromFile("Data/bglvl1.png");
                
                if(level==2)
                 bgTex.loadFromFile("Data/bglvl2.png");
                 
                if(level==3) 
                bgTex.loadFromFile("Data/bglvl5.png");

                if(level==1) 
                blockTexture.loadFromFile("Data/blocklvl1.png");
                
                if(level==2)
                 blockTexture.loadFromFile("Data/blocklvl2.png");
                 
                if(level==3)
                 blockTexture.loadFromFile("Data/blocklvl5.png");
                
                if(level == 3) {
                     cupTexture.loadFromFile("Data/bowl.png");
                     cupSprite.setTexture(cupTexture);
                     cupSprite.setScale(0.5f,0.5f);
                }


                for(int i=0; i<height; i++) { 
                    for(int j=0; j<width; j++)
                     lvl[i][j] = ' '; 
                }

                for(int i=0; i<height; i++) { 
                    for(int j=0; j<width; j++) { 
                        if(i==0 || j==0 || i==height-1 || j==width-1) lvl[i][j] = '#'; 
                    } 
                }
                

                interface(lvl, level, height, width);


     enemysetup(enemyx, enemyy, enemyWidth, enemyHeight, isalive, enemydir, enemytype, totenemy, ghostSprite, skeletonSprite, chelnovSprite, invisiblemanSprite, currentenemy, level, lvl, cell_size);

//ye level 2 k power ups sett ho rhe hain
                if(level == 2) {
                    setupPowerups(skate_x, skate_y, skate_active, gun_x, gun_y, gun_active, battery_x, battery_y, battery_active, star_x, star_y, star_active);
                }


                for(int k=0; k<20; k++) { 
                isBulletAlive[k] = false; 
                isBallAlive[k] = false; 
                }

                continue; 
            } 
            else
             {
   //agr player excape dba de to booooom 
                window.close();
            }
        }


        updatemovement( lvl, PlayerSprite , offset_x, speed, player_x, player_y, cell_size, PlayerHeight, PlayerWidth, playerdirection, ismoving);
        
        isdownkeypressed = (Keyboard::isKeyPressed(Keyboard::Down));
        
        if (Keyboard::isKeyPressed(Keyboard::Up) && onGround) { 
        velocityY = jumpStrength; 
        onGround = false; 
        }
    
        int timeleft = (timelimit - timeelapse);
        if (timeelapse<0) 
        timeleft=0;
        
       // ye sb kuch font k liye hian
        scoretext.setString("SCORE: " + to_string(score));
        timertext.setString("TIME: " + to_string(timeleft));
        livestext.setString("LIVES: " + to_string(lives));
  
        if (timeelapse >= timelimit) 
        {
            bool startagain = again(window);
            if (startagain)
            {
               enemyagain(player_x, player_y, score, caught_enemy_count, gameClock, enemyx, enemyy, isalive, enemydir, enemytype, enemyWidth, enemyHeight, totenemy, ghostSprite, skeletonSprite,chelnovSprite , invisiblemanSprite, currentenemy, level, levelbonus, lvl, cell_size);
               continue; 
            } 
            else
            {
             break; 
            }
        }
        
        if(level == 2) 
        {
             managePowerups(window, pupSprite, skate_x, skate_y, skate_active, gun_x, gun_y, gun_active, battery_x, battery_y, battery_active, star_x, star_y, star_active, player_x, player_y, PlayerWidth, PlayerHeight, speed, range_new, suction_speed, lives);
        }
        
        if(level == 3)
        {
          	cupcreation(window, cupSprite, cup_x, cup_y, cup_dir);
          	++framecounter;
          	
        }
 
        
          
        player_gravity(lvl, offset_y, velocityY, onGround, gravity, terminal_Velocity, player_x, player_y, cell_size, PlayerHeight, PlayerWidth,  isdownkeypressed);
        
        
        for(int i=0; i<currentenemy; i++) {
        
            if(isalive[i]) {
            
                if(abs(player_x - enemyx[i]) < 40 && abs(player_y - enemyy[i]) < 40) {
                    lives--;
                    if(lives > 0) 
                    { 
                    	player_x = 550; player_y = 150; 
                    }
                    else 
                    {  
                    	window.close(); 
                    }
                    break;
                }
            }
        }

//yahan mein functions jo kaafi kaam k hain wo call kr rha hun
        enemydrawfun( window, enemyx, enemyy, isalive , enemyWidth, enemyHeight, enemydir, enemytype, totenemy, ghostSprite, skeletonSprite, chelnovSprite, invisiblemanSprite, currentenemy, level);
        
        enemymovement(lvl, cell_size, height, width, enemyWidth, enemyHeight, enemyx, enemyy, isalive, enemydir, enemytype,  totenemy,  ghostSprite, skeletonSprite, chelnovSprite, invisiblemanSprite,  currentenemy, level, chelnovtimer, bulletX, bulletY, isBulletAlive, bulletDir);
        
        enemygravity(lvl, cell_size, height, width, enemyWidth, enemyHeight, enemyx, enemyy, isalive, enemydir, enemytype,  totenemy,  ghostSprite, skeletonSprite, chelnovSprite, invisiblemanSprite,  currentenemy, level);
    
        vacuumsetup( window, lvl , vacuumTexture, vacuumSprite, player_x, player_y, enemyx, enemyy, isalive, enemydir, enemytype, totenemy, ghostSprite,  skeletonSprite, level, currentenemy, caught_enemy_count, PlayerWidth, PlayerHeight, PlayerSprite, playerdirection, choice , score , suction_speed , range_new, capturedEnemies, enemiesInPocket);

        // BULLETS
        movebullets(bulletX, bulletY, isBulletAlive, bulletDir, 20, lvl, cell_size);
        for(int i = 0; i < 20; i++) { 
            if(isBulletAlive[i]) { 
            
                bulletSprite.setPosition(bulletX[i], bulletY[i]); 
                window.draw(bulletSprite); 
                
                // Bullet Hits Player
                if (abs(bulletX[i] - player_x) < 30 && abs(bulletY[i] - player_y) < 30) {
                    lives--;
                     isBulletAlive[i] = false; 
                    if(lives > 0) { 
                    player_x = 550;
                     player_y = 150;
                      }
                    else { 
                    	window.close();
                    }
                }
            } 
        }
        

        // BALLS 
        moveBalls(ballX, ballY, isBallAlive, ballDir, 20, lvl, cell_size, enemyx, enemyy, isalive, currentenemy, score);
        
        
        for(int i = 0; i < 20; i++) { 
            if(isBallAlive[i]) { 
                // 1. GHOST
                if(ballType[i] == 0) { 
                    ghostSprite.setPosition(ballX[i], ballY[i]);
                    ghostSprite.setScale(0.7, 0.7); 
                    window.draw(ghostSprite);
                    ghostSprite.setScale(1.5, 1.5); 
                }
                // 2. SKELETON
                else if(ballType[i] == 1) { 
                    skeletonSprite.setPosition(ballX[i], ballY[i]);
                    skeletonSprite.setScale(0.7, 0.7);
                    window.draw(skeletonSprite);
                    skeletonSprite.setScale(1.5, 1.5); 
                }
               
                // 4. INVISIBLE MAN
                else if(ballType[i] == 2) 
                { 
                    invisiblemanSprite.setPosition(ballX[i], ballY[i]);
                    invisiblemanSprite.setScale(0.7, 0.7);
                    window.draw(invisiblemanSprite);
                    invisiblemanSprite.setScale(1.5, 1.5);
                }
                 // 3. CHELNOV
                else if(ballType[i] == 3) { 
                    chelnovSprite.setPosition(ballX[i], ballY[i]);
                    chelnovSprite.setScale(0.7, 0.7);
                    window.draw(chelnovSprite);
                    chelnovSprite.setScale(1.5, 1.5);
                }
            } 
        }

        if(ismoving) {
            int timer=((int)(player_x/20)%4);
            if(choice == 1) {
            
                if(timer==0) 
                PlayerSprite.setTextureRect(IntRect(16, 41, 32, 40));
                
                else if(timer==1) 
                PlayerSprite.setTextureRect(IntRect(387, 37 , 32 , 44));
                
                else if(timer==2)
                 PlayerSprite.setTextureRect(IntRect(220, 40, 32 , 41));    
                                  
                else PlayerSprite.setTextureRect(IntRect(185, 40 , 32 , 41)); 
                                   
            } 
            else if(choice == 2) {
                if(timer==0)
                 PlayerSprite.setTextureRect(IntRect(16, 231, 32, 39));
                 
                else if(timer==1) 
                PlayerSprite.setTextureRect(IntRect(319 ,230, 32, 40));
                
                else if(timer==2) 
                PlayerSprite.setTextureRect(IntRect(220, 231 , 32 ,39));
                
                else PlayerSprite.setTextureRect(IntRect(117 , 231 , 32 ,39 ));
            }
        } 
        else 
        {
                
            if(choice == 1){
            
             PlayerSprite.setTextureRect(IntRect(16, 41, 32, 40));
             
             }
             
            else   
                      
            PlayerSprite.setTextureRect(IntRect(16, 231, 32, 39));
                        
        }
        if(playerdirection == 1) {
        
         PlayerSprite.setScale(1.5,1.5);
         PlayerSprite.setPosition(player_x, player_y); 
         
         }
        else 
        {
         
        PlayerSprite.setScale(-1.5,1.5); 
        PlayerSprite.setPosition(player_x + PlayerWidth, player_y);
        
         }
        
        window.draw(scoretext);
        window.draw(timertext);
        window.draw(livestext);
        
        window.draw(PlayerSprite);
        window.display();
    }

    lvlMusic.stop();
    for (int i = 0; i < height; i++) delete[] lvl[i];
    delete[] lvl;

    return 0;
    
}

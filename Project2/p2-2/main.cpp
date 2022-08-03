//=================================================================
// The main program file.
//
// Copyright 2022 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <stdlib.h>

// Project includes
#include "globals.h"
#include "hardware.h"
#include "graphics.h"
#include "keyboard.h"


//some LED's to use for debugging.
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

void set_random_seed();

/*
* This function handles the main logic of the game. You should
* initialize the hardware in this function, make calls to 
* functions that update the keyboard and your guess of 
* the word. 
*/
int main()
{
    
    GameInputs inputs; 
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    pc.printf("Program Starting\n");
    //led1 hardware initialization
    
    
    myled1=1; 
    reset = 1; 
    Timer t;
    int dt; // delta time
    Timer timeWin;
    float timeCount;
    int LBIndex = 0;
    float leaderBoard[30];
    for (int i = 0; i < 30; i++) {
        leaderBoard[i] = 0.0;
    }
    float med;
    
    while(reset == 1) {
        /* Put code here to initialize the game state:
        1) you will need to use a psuedo random number generator such as
        rand() to randomly select a goal word from the dictionary.
        The random function needs to be seeded before you call rand(),
        otherwise, rand() will always generate the same series of numbers.
        Call the function set_random_seed -- you need to complete its
        definition below.*/
        set_random_seed();
        /*
        2) call init_keyboard() and show start screen
   
        3) initialize any other game state that you add.
        */
        init_keyboard();
        hardware_init();
        draw_sprite1();
    
    
        /* Insert code into this game loop to complete its implementation:
        */
        while(1){
            timeCount = 0;
            t.start(); //start a timer
            timeWin.start();
            draw_lower_status(); //draw the lower status bar
            inputs = read_inputs(); //read the inputs of the game
            
            if (inputs.b1 || inputs.b2 || inputs.b3 || inputs.b4) {
                button_click_sound();
            }
            
            /*
            your code here, make decisions based on those inputs, update the keyboard
            make selections, update words etc.
            */
        
            /*
            User can use accelerometer or button3/4 to move through the keyboard.
            */
            if (((float) inputs.ax > 0.4 || inputs.b3) && !inputs.b1) {
                moveleft();
                wait(0.25);
            }
        
            if (((float) inputs.ax < -0.4 || inputs.b4) && !inputs.b1) {
                moveright();
                wait(0.25);
            }
        
            if (roundCount < 6) {
                if (inputs.b1) {
                    
                    select_letter();

                    if (arrayIndex == 5) {
                        arrayIndex = 0;
                        roundCount++;
                    
                        check_word();

                        if (wordEqual == 1) {
                            uLCD.cls();
                            timeWin.stop();
                            timeCount = timeWin.read();
                            leaderBoard[LBIndex] = timeCount;
                            
                            if (LBIndex > 0) {  // sorting
                                if (LBIndex == 1) {
                                    if (leaderBoard[0] > leaderBoard[1]) {
                                        med = leaderBoard[0];
                                        leaderBoard[0] = leaderBoard[1];
                                        leaderBoard[1] = med;
                                    }
                                } else {
                                    for (int i = 0; i < LBIndex; i++) {
                                        for (int j = 0; j < LBIndex - i; j++) {
                                            if (leaderBoard[j] > leaderBoard[j + 1]) {
                                                med = leaderBoard[j];
                                                leaderBoard[j] = leaderBoard[j + 1];
                                                leaderBoard[j + 1] = med;
                                            }
                                        }
                                    }
                                }
                            }
                            
                            draw_fireworks();  // Animation
                            
                            uLCD.printf("Congratulation! \nYou win the game\nin %.2f seconds!", timeCount);
                            wait(0.2);
                            draw_thumbs_up();
                            wait(2);
                            uLCD.cls();

                            //Print leaderboard
                            draw_leaderboard();
                            uLCD.locate(4, 1);
                            uLCD.printf("LEADERBOARD");
                            for (int i = 0; i < LBIndex + 1; i++) {
                                uLCD.locate(2, 3 + 2 * i);
                                uLCD.printf("%d.     %.2f s", i + 1, leaderBoard[i]);
                            }
                            
                            wait(5);
                            uLCD.cls();
                            draw_arrow1();
                            uLCD.locate(0, 13);
                            uLCD.printf("Push button 4 to\nreset the game\n>>>");
                            LBIndex++;
                            
                            break;
                        }
                    }
                    wait(0.2);
                }
            } else {
                uLCD.cls();
                uLCD.printf("Too many tries. \nYou lost the game!");
                wait(0.2);
                draw_crying_face();
                wait(0.2);
                uLCD.locate(0, 13);
                uLCD.printf("Push button 4 to\nreset the game\n>>>");
                break;
            }
        
            if (inputs.b2) {
                remove_letter();
                wait(0.2);
            }
            
            
            t.stop();
            timeWin.stop();
            dt = t.read_ms();
            if (dt < 100) wait_ms(100 - dt);
        
        }
        while (1) {
            inputs = read_inputs();
            if (inputs.b4) { // Reset the game
                button_click_sound();
                uLCD.cls();
                reset = 1;
                timeWin.reset();
                break;
            }
        }
    }
}



/* This should be called in the main function above.
*
* This function sets the random seed for the game using srand(seed).
* One incomplete way to do this is given below: start a Timer and sample it
* to get a seed. The problem is that the same exact time will be read
* every time you reset the mbed.  You need to add code to introduce
* variability into when the timer is stopped.  An easy way to do this
* is to get the user to press a push button to stop the timer at a random
* time.  You can print a prompt to the screen to ask the user to push
* any button to start, then run an infinite while loop that waits for a push 
* button press to break. The Timer is then stopped and rea  d and elapsed time
* used as the seed. (This requires using read_inputs() into a GameInputs variable.)
*/
void set_random_seed() {
    uLCD.printf("Push any button to start the game!\n");
    draw_wordle();
    Timer t;
    t.start(); // start the timer
    wait_ms(200);
    // add code here
    
    GameInputs inputs;
    while (1) {
        inputs = read_inputs();
        if (inputs.b1 || inputs.b2 || inputs.b3 || inputs.b4) {
            button_click_sound();
            break;
        }
    }
    
    t.stop();  //  end the timer
    int seed = t.read_ms(); //read the number of milliseconds elapsed between the start and stop
    srand(seed); // use elapsed time as the seed
    
    uLCD.cls();
}
// ===User implementations end===

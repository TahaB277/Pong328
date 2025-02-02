# Pong328

A minimalist implementation of the classic Pong game built for the ATmega328P microcontroller. Programmed entirely in assembly, this project uses a monochrome LCD display (ST7735R with 128x160 resolution) and push buttons for paddle control. The game features two BCD 7-segment display to keep track of the score. Designed primarily for simulation in Proteus, with plans for real-world circuit optimization in the future, this project showcases low-level programming and embedded systems concepts.

---

## Features

- **Monochrome Pong Game:** Simple paddle and ball mechanics displayed on an LCD screen.
- **Button-Based Control:** Push buttons used for paddle movement.
- **Score Tracking:** 7-segment display shows the current score for each player. The first player to reach 3 points wins.
- **Assembly Code:** Entirely programmed in AVR assembly for efficient use of the ATmega328P’s resources.
- **Simulation & Realization:** Supports both Proteus simulation and potential future hardware implementation.

---

## Requirements

### Hardware:

- ATmega328P Microcontroller (16 Mhz clock)
- Monochrome LCD Screen: ST7735R with 128x160 resolution
- Push Buttons (2x for each paddle movement)
- BCD 7-Segment Display (1x for each player)


### Software:

- Atmel Studio 7 (or compatible AVR assembly IDE)
- Proteus 8 Professional (for simulation)

---

## How It Works

1. **Initialization:**

   - The LCD is initialized to set up the screen, enable communication (SPI), and define the monochrome color mode.
   - The paddles, ball positions, and scores are set to their starting values.

2. **Game Loop:**

   - Continuously checks push button inputs to move the paddle.
   - Updates ball velocity and detects collisions (with paddles and screen boundaries).
   - Updates the 7-segment display with the current score.

3. **Refresh Screen:**

   - An interrupt subroutine that is active based on the REFRESHRATE variable (Default is 20 FPS).
   - Updates ball and paddle positions and sends the respective instructions to display them on the LCD.

4. **End Condition:**

   - The game ends when one player reaches a score of 3, displayed on the 7-segment display.

---

## Setup Guide

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/TahaB277/Pong328.git
   ```

2. **Assemble the Circuit:**

   - Refer to the Proteus simulation schematic included in the repository for wiring instructions.
   - Connect the push buttons, LCD, 7-segment display, and other components as per the schematic below.
   
![image](https://github.com/user-attachments/assets/d7391816-b7de-4abe-8722-e15aed116f23)

3. **Compile and Upload Code:**

   - Open the project in Atmel Studio 7.
   - Compile the assembly code to generate the HEX file.

4. **Simulate in Proteus:**

   - Open the Proteus project file (.pdsprj)
   - Double-click on the atmega328p and use the same options as the image below (In the Program File select the HEX file)
   
![image](https://github.com/user-attachments/assets/34f0e4ff-f1cf-4958-b84d-67ecb4facf1a)

   - Run the simulation to test the game.

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Acknowledgments

- Inspired by the simplicity of the original Pong game.
- Thanks to open-source resources and datasheets for components like the ST7735R LCD


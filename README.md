# Sparty's Boots

## Game Overview
"Sparty's Boots" is an educational puzzle game that combines logic gates and conveyor belt mechanics to teach players about basic digital logic. Players must create circuits to command Sparty to kick the correct products off a conveyor belt based on given instructions.

## How to Play
- Products move down a conveyor belt.
- A sensor detects products as they pass by Sparty, activating outputs for specific types.
- A beam runs across the belt; when a product interrupts the beam, the beam's output becomes active.
- Players use logic gates to build a circuit that determines whether Sparty should kick a product off the belt.
- The goal is to kick off products based on the logic conditions specified on the scoreboard for each level.

## Game Levels
There are eight game levels, each with unique challenges and objectives:
- **Levels 1-6**: Predefined levels as per the prototype.
- **Levels 7-8**: Custom levels designed by the development team.
- **Level 0**: A test level for debugging and gameplay experimentation.

### Level Example: Level 4
1. **Objective**: Make Sparty kick all products from the conveyor that are not Izzo or Smith.
2. **Steps**:
   - Add an OR gate to process outputs from the Izzo and Smith sensors.
   - Connect sensor outputs to the OR gate inputs.
   - Verify OR gate operation by starting the conveyor.
   - Add a NOT gate to invert the OR gate output.
   - Add an AND gate to combine the NOT gate output with the beam sensor.
   - Connect the AND gate output to Sparty, enabling him to kick based on the defined logic.

## Scoring
- **Positive Score**: Awarded when Sparty correctly kicks or does not kick products based on the circuit logic.
- **Negative Score**: Deducted for incorrect actions (kicking when not supposed to, and vice versa).

## Gameplay Features
- **Dynamic Sensor and Beam Interaction**: Interact dynamically with products as they pass specific game zones.
- **Interactive Logic Gate Setup**: Drag and drop logic gates and draw connections to form functional circuits.
- **Real-Time Feedback**: Immediate visual feedback on circuit functionality through active (red) and inactive connections.
- **Level Selection Menu**: Jump to any level instantly for targeted gameplay or troubleshooting.

## How to Start the Game
To start playing "Sparty's Boots":
1. Open the game application.
2. Select a level from the menu.
3. Build the required circuit using logic gates and connections.
4. Start the conveyor to see the circuit in action.
5. Adjust the circuit as needed based on the game's feedback and objective.

## Resources
Additional resources, including level files and game assets, are available on the game's resource page.

Enjoy building circuits and help Sparty manage the conveyor belt efficiently!


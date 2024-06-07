# The 2048 Game

 - Made by Bobei Bogdan-Dumitru, CS Student @ Politehnica University of Bucharest

###  About 
The 2048 Game is a bash-based version of the popular 2048 puzzle 
game. The game was created in simple C with the NCurses library to 
handle the graphics. This implementation brings the addictive gameplay 
of 2048 to the terminal, providing a fun and engaging experience 
for users who enjoy playing old school games.

### Technical Details

- **Developed in C**: The game is implemented in the C programming language, providing a robust and efficient core for game logic and data handling.
- **NCurses Library**: Utilizes the NCurses library to handle all terminal display and input functionalities, ensuring a user-friendly and responsive interface.
- **Persistent Storage**: Game progress and high scores are saved in a file (`data.txt`).

###  Dependecies
- The game was created in simple C with the NCurses library to handle 
the graphics. The only problem you might encounter would be with the
NCurses library, but here I'll show you how to install it via Ubuntu.

###  How to install NCurses library
```bash
# Update the package index
sudo apt-get update

# Install NCurses library
sudo apt-get install libncurses5-dev libncursesw5-dev
```

###  How to run it?
```bash
# Clone the repository
git clone https://github.com/WolfishAtom7515/2048_Game.git

# Navigate to the project directory
cd 2048_Game

# Create the game via makefile
make build

# Open the game
make run

# If you want to delete the executable
make clean
```

### Contact

I'm always happy to connect with other gamedevs.
For any questions, suggestions, or feedback, please feel free to reach out:

- **Name**: Bobei Bogdan-Dumitru
- **GitHub**: [Bobei Bogdan-Dumitru](https://github.com/WolfishAtom7515)
- **Email**: [bobei.bogdan.off@gmail.com](bobei.bogdan.off@gmail.com)

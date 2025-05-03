#I fix thsi part later zzzzz


# WordHunt Bot

A full pipeline bot for WordHunt using computer vision, deep learning, and algorithmic pathfinding

##  Features

- **Screen Capture**: Automatically grabs the game board using `mss`
- **OCR with CNN**: Created and trained my own Pytorch CNN model to recognize letter tiles
- **Board Solver**: C++ backend that finds all valid words using a dictionary and efficient graph traversal + trie
- **Automated Swiping**: Uses `pynput` to swipe the paths of the word

##  Tech Stack

- **Python**: Image Processing, Model Inference, Automation
- **PyTorch**: For trainign and creating the OCR model
- **OpenCV**: Preprocessing tiles
- **C++**: For solving the board
- **pynput**: To swipe the words
- **mss**: Capture Screen 

## How it works
1. **Start Detection**: Bot clicks Start on the game
2. **Screenshot**: Captures the game board area using `mss`.
3. **Preprocessing**: Tiles are extracted and preprocessed using `Opencv`
4. **Tile OCR**: Feeds cropped tiles into our CNN model.
5. **Board Solve**: Our python script sends the tiles on the board to our C++ solver(via `subprocess`) to find words
6. **Auto-Swipe**: Simulates mouse dragging through tile paths to submit answers.

## Demo

<p align="center">
  <img src="wordHunt.gif" alt="Demo" width="1000"/>
</p>

<p align="center">
  <img src="win1.png" alt="Results 1" width="300"/>
  <img src="win2.png" alt="Results 2" width="300"/>
</p>

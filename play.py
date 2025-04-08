import pyautogui
import time
import mss
import numpy as np
import cv2
import subprocess
from collections import Counter
import torch
from torchvision import datasets, transforms
from pynput.mouse import Button, Controller


#
####Click start 
#Sleep
#Take screenshot
#Screenshot saved to png
#process 
#OCR
#insert into c++
#solve
#c++ back to vector in py
#swipe values in vector
#o7

# Start 
startButtonX = 1343
startButtonY = 610
pyautogui.moveTo(startButtonX, startButtonY)
pyautogui.click()
pyautogui.click()
# wait for board to load
time.sleep(5)


#Take screenshot
with mss.mss() as sct:
    monitor = sct.monitors[1] 
    screenshot = np.array(sct.grab(monitor))
    screenshot = cv2.cvtColor(screenshot, cv2.COLOR_BGRA2BGR)
cv2.imwrite("board_capture.png", screenshot)

#process board
image = screenshot
grayImage = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
ret, bnwImage = cv2.threshold(grayImage, 127, 255, cv2.THRESH_BINARY)
contours, hierarchy = cv2.findContours(bnwImage, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
for contour in contours:
    x, y, w, h = cv2.boundingRect(contour)

tile_boxes = []
for contour in contours:
    x, y, w, h = cv2.boundingRect(contour)
    if 90 <= w <= 120 and 90 <= h <= 120:
        tile_boxes.append((x, y, w, h))

tile_boxes = sorted(tile_boxes, key=lambda b: (round(b[1]/100), b[0]))
tile_boxes = tile_boxes[:16]

nTile_boxes = []

for x, y, w, h in tile_boxes:
    #crop
    tile = image[y:y+h, x:x+w]
    #gray
    gray = cv2.cvtColor(tile, cv2.COLOR_BGR2GRAY)
    #resize
    resized = cv2.resize(gray, (64, 64))
    #convert
    tensor = transforms.ToTensor()(resized).unsqueeze(0)
    nTile_boxes.append(tensor)


#OCR model
from myOcr.model import TileCNN
model = TileCNN()  
model.load_state_dict(torch.load("myOcr/tile_cnn.pth"))
model.eval()

transform = transforms.Compose([
    transforms.Grayscale(),
    transforms.Resize((64, 64)),
    transforms.ToTensor(),
])
dataset = datasets.ImageFolder("myOcr/tiles_dataset", transform=transform)
idx_to_class = dataset.classes
boardTest = []
for tile in nTile_boxes:
    output = model(tile)
    pred_idx = torch.argmax(output, dim=1).item()
    boardTest.append(pred_idx)
idx_to_class = dataset.classes  


tile_data = []

for idx, (x, y, w, h) in enumerate(tile_boxes):
    letter_idx = boardTest[idx]
    letter = idx_to_class[letter_idx]

    center_x = x + w // 2
    center_y = y + h // 2

    tile_data.append((letter, (center_x, center_y)))
    
inputString = "\n".join(f"{letter} {x} {y}" for letter, (x, y) in tile_data) + "\n"


# Run C++ script 
result = subprocess.run(
    ['./main'],               
    input=inputString,
    capture_output=True,
    text=True
)

#i fked up and was 2 lazy 2 fix so i just do 0,1 etc back to coords instead of doing it originally
# Convert C++ output into word + screen coordinate paths
board_size = int(16 ** 0.5)
wordPaths = []
for line in result.stdout.strip().splitlines():
    parts = line.strip().split()
    if not parts or len(parts) < 2:
        continue 

    word = parts[0]
    coords = []
    for r_c in parts[1:]:
        if ',' not in r_c:
            continue 
        try:
            r, c = map(int, r_c.split(','))
        except ValueError:
            continue

        idx = r * board_size + c
        if idx >= len(tile_boxes):
            continue

        x, y, w, h = tile_boxes[idx]
        center_x = x + w // 2
        center_y = y + h // 2
        coords.append((center_x, center_y))
    wordPaths.append((word, coords))

scaled = 0.5
scaledWordPaths = []
for word, coords in wordPaths:
    scaledCoords = [(x * scaled, y * scaled) for x, y in coords]
    scaledWordPaths.append((word, scaledCoords))
# Only process the first 5 words


mouse = Controller()

#swipe
for word, coords in scaledWordPaths:
    if len(coords) < 2:
        continue
    print(f"Swiping word: {word}")
    mouse.position = coords[0]
    time.sleep(0.05) 
    mouse.press(Button.left)
    for pos in coords[1:]:
        mouse.position = pos
        time.sleep(0.02)  
    mouse.release(Button.left)
    time.sleep(0.05)
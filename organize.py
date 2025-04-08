import os
import shutil

# Define folder structure
folders = {
    "myOcr": ["myOcr"],
    "src": ["boardSolver.cpp", "boardSolver.h", "trie.cpp", "trie.h", "main.cpp", "CMakeLists.txt"],
    "data": ["dictionary.txt", "filtered.txt"],
    "scripts": ["calibrate.py", "filterWord.cpp", "filterWord"],
    "assets": ["board_capture.png", "start_button.png"],
    "notebooks": ["main.ipynb"],
}

# Create folders if not exist
for folder in folders:
    os.makedirs(folder, exist_ok=True)

# Move files to corresponding folders
for folder, files in folders.items():
    for file in files:
        if os.path.exists(file):
            try:
                shutil.move(file, os.path.join(folder, file))
                print(f"✅ Moved {file} → {folder}/")
            except Exception as e:
                print(f"❌ Failed to move {file}: {e}")
        else:
            print(f"⚠️ Skipped (not found): {file}")

print("\n🧼 Done organizing your WordHunt project.")

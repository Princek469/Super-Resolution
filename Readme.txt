Instruction For Using The Application

# Selecting an Input Image
    - Click the "Choose Image" button.
    - In the file dialog that appears, navigate to the folder containing the image you want to enhance.
    - Select the image file and click "Open."
    - The selected image path will be displayed in the input field.

# Viewing the Input Image
    - After selecting an input image, you will see a "View" button in the application.
    - Click the "View" button to open the selected input image in a new window.
    - A new window will appear displaying the input image. You can close this window when you are done viewing the image.

# Choosing Scaling Options
    - After selecting an image, you will see radio buttons for scaling options (e.g., 2x and 4x).
    - Select the desired scaling factor by clicking on the corresponding radio button. Only one option can be selected at a time.

# Selecting Output Path
    - Click the "Choose Output Path" button.
    - In the save dialog that appears, navigate to the desired folder and enter a file name for the output image.
    - Click "Save." The selected output path will be displayed in the output field.

# Generating the Super Resolution Image
    - Click the "Generate" button to start the processing of the image.
    - The application will check the size of the selected image: 
       -> If the image size is less than 1 MB: The application will directly process the image using the selected radio button.
       -> If the image size is greater than 1 MB: A prompt will appear asking for confirmation to split the image into tiles.

# After processing the image, you will see a "View" button to open the output image in a new window.
    - If the output image was generated from a large input image, a tile viewer window will open displaying the first tile.
    - The application will check the size of the output image:
      -> If the output image size is less than 1 MB, a new window will open displaying the enhanced image directly.
      -> If the output image size is greater than 1 MB, the application will split the image into tiles and open a tile viewer window.
    - In the tile viewer window, you will find "Next Tile" and "Previous Tile" buttons to navigate through each tile individually. 
    - Click these buttons to view each tile one at a time, moving forwards or backwards through the tiles.

# Handling Large Images
    - If the image size is greater than 1 MB, a dialog box will appear with the following options:
       -> OK: Click this button to proceed with splitting the image into tiles based on the default tile size(256x256).
       -> Cancel: Click this button to cancel the operation and return to the main interface.
    - If you click Cancel, you can adjust the settings in the settings box, which is located at the top right corner. 
    - Click on the "Settings" button to open the settings box and modify the settings as needed.

# Updating Settings
    - To change the default settings (tile size, threshold size), click the "Settings" button.
    - Adjust the settings as needed and click "Continue" to save the changes.
    - After updating the settings, click the "Generate" button again to process the image based on the new settings.

# Resetting the Application
   - Click the "Reset" button to clear all input and output paths.
   - The application will reset to its default state, allowing you to start a new process.
   - After resetting, you can select a new input image, set the output path, and choose scaling options again.

# Error Handling
   - Input image path is invalid: Ensure that the file path is correct and that the image file is accessible.
   - Invalid destination path: Make sure you have specified a valid file name for the output image.
   - Make sure you choosing the radio button.



 
# Smart LCD Character Control Using LDR and Push Buttons

## Description
This project implements an interactive LCD display system where a custom character
moves across a 16x2 LCD based on user input and environmental light intensity.

The system operates in two modes:

### Manual Mode
The character moves one position left or right when the respective push button is pressed.

### Environment-Adaptive Automatic Mode
When the LDR detects light intensity above a threshold, the character moves automatically
across the LCD from left to right and then right to left (bounce movement).

If the LDR value falls below the threshold, the system stops the automatic movement.

### Auto Pause Feature
A third push button pauses the automatic movement for 60 seconds. After 60 seconds,
the system resumes automatic movement if the LDR value is still above the threshold.

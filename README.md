# Image-Processing Project with Bmplib Library

## Overview

Welcome to the Image-Processing project powered by C++ and the powerful Bmplib library! This project focuses on filtering image-processing techniques to enhance and transform images in various creative ways.

## Features

1. **Black & White Transformation:**
   - **Description:** Transforms an ordinary image into a classic black & white version.
   - **Usage:** `./image_processor -bw input_image.bmp output_image.bmp`

2. **Error Diffusion Dithering:**
   - **Description:** Adds artistic flair through advanced dithering techniques.
   - **Usage:** `./image_processor -dither input_image.bmp output_image.bmp`

3. **Invert & Merge:**
   - **Description:** Flips perspectives with inverted images or merges two visual tales into one.
   - **Usage:** `./image_processor -invert_merge input_image1.bmp input_image2.bmp output_image.bmp`

4. **Picture Flip & Rotate:**
   - **Description:** Turns things around! Rotation and flipping for a dynamic view.
   - **Usage:** `./image_processor -flip_rotate input_image.bmp output_image.bmp`

5. **Light & Dark Adjustment:**
   - **Description:** Adjusts the ambiance with picture lightening and darkening—mastering the art of contrast.
   - **Usage:** `./image_processor -light_dark input_image.bmp output_image.bmp`

6. **Enlarge & Shrink:**
   - **Description:** Plays with dimensions! Enlarges and shrinks images for a closer look or a broader perspective.
   - **Usage:** `./image_processor -enlarge_shrink input_image.bmp output_image.bmp`

7. **Edge Detection:**
   - **Description:** Unleashes the power to detect and highlight picture edges! Sharpens the focus.
   - **Usage:** `./image_processor -edge_detection input_image.bmp output_image.bmp`

**Note: This version is only compatible with 256x256 grayscale images.**

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/your-image-processing-project.git

2. Navigate to the project directory:
   ```bash
   cd your-image-processing-project
3. Build the project:
   ```bash
   make
## Usage
Run the executable with the desired image-processing option. For example:
   ```bash
   ./image_processor -bw input_image.bmp output_image.bmp

//
// Created by Sergio on 08/11/2019.
//


#include "Screen.h"
#include "../utils/Prng.h"

Screen::Screen(float width, float height, float focal_length,  int pixels_column,  int pixels_row) : width(
        width), height(height), focal_length(focal_length), pixels_column(pixels_column), pixels_row(pixels_row) {

    /*
     * As the screen in camera coordinates measures 2 (-1 to 1),
     * if you divide the size by the number of pixels you get how much each pixel measures.
     */
    size_X = 2 / (float) pixels_column;
    size_Y = 2 / (float) pixels_row;
    pixels_world_coordinates.resize(pixels_column * pixels_row);

}

Screen::Screen( int pixels_column,  int pixels_row, const Camera &camera) :
    Screen(camera.getLeft().modulus() * 2, camera.getUp().modulus() * 2, camera.getForward().modulus(),
           pixels_column, pixels_row) {
    calculate_world_coordinates(camera);
}

/**
 * Function that calculates the position of the upper left corner of each pixel in global coordinates and stores them in the vector.
 */
void Screen::calculate_world_coordinates(const Camera& camera) {
    // First we obtain the matrix of change of base of coordinates of the camera to coordinates of the world.
    Matrix transformation_matrix;
    transformation_matrix.setVectors(camera.getLeft(), camera.getForward(), camera.getUp());
    transformation_matrix.setPoint(camera.getPosition());

    for(int i = 0; i < this->pixels_row; i++){
        for(int j = 0; j < this->pixels_column; j++){
            // Since the camera has the vector left as X, 1.1 is the upper left corner.
            // Then we advance subtracting to 1 because pixel we are using the size of the pixel.
            // The Y axis is always 1 because it is in camera coordinates.
            Vector pixel(1 - (j * size_X), 1, 1 - (i * size_Y), 1);

            // Change the base of the camera to the world
            pixel = transformation_matrix * pixel;
            set_world_coordinates(i, j, pixel);
        }
    }
}


void Screen::set_world_coordinates( int row,  int column, const Vector &vector) {
    pixels_world_coordinates[pixels_column * row + column] = vector;
}


Vector Screen::get_world_coordinates( int row,  int column) const {
    return pixels_world_coordinates[pixels_column * row + column];
}

/**
 * Return the world coordinates of the pixel[row, column] with a offset defined by a random_number
 * @param pixel_row
 * @param pixel_column
 * @return
 */
Vector Screen::get_pixel( int pixel_row,  int pixel_column) const {
    /* We get the pixel size in world coordinates. Since all pixels measure the same,
     * we can use any pixel to calculate them.
     */
    float size_pixel_X = this->width  / (float) this->pixels_column;
    float size_pixel_Y = this->height / (float) this->pixels_row ;

    // Obtain the pixel in world coordinates
    Vector pixel = get_world_coordinates(pixel_row, pixel_column);

    // The pixel position is upper left with a offset defined by a random_number
    pixel.set(0, pixel.get(0) + (size_pixel_X/2 * Prng::random()));
    pixel.set(2, pixel.get(2) - (size_pixel_Y/2 * Prng::random()));

    // The pixel position is upper left with a offset defined by the center
    //pixel.set(0, pixel.get(0) + (size_pixel_X/2 * 0.5));
    //pixel.set(2, pixel.get(2) - (size_pixel_Y/2 * 0.5));



    return pixel;
}

 int Screen::getPixelsColumn() const {
    return pixels_column;
}

 int Screen::getPixelsRow() const {
    return pixels_row;
}

Screen::Screen() = default;


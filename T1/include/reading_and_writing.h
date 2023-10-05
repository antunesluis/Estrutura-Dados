#ifndef EDITOR_H
#define EDITOR_H

#include <stdbool.h>
#define MAX_SIZE_HEADER 3

typedef enum
{
    EDIT_BRIGHTNESS = 1,
    EDIT_NEGATIVE,
    EDIT_FLIP,
    EDIT_ROTATE,
    EDIT_CUT,
    EDIT_RESIZE,
    EDIT_SUBSET,
} EditingOptions;

typedef struct _pixel
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

typedef struct _photo
{
    Pixel **pixels;
    int rows, cols;
    int max_color;

} Photo;

void print_ppm_in_file(Photo *photo_ppm);
void print_ppm_in_terminal(Photo *photo_ppm);
void read_ppm_file(Photo *photo_ppm, char *filename);

Pixel **alocate_matrix_pixels(int n_rows, int n_cols);
void destroy_matrix_pixels(Pixel ***mat, int n_rows, int n_cols);

int get_editing_option();
bool ask_if_continue();

void update_photo_data(Photo *photo_ppm, Pixel **new_pixels,
                       int new_rows, int new_cols);

#endif

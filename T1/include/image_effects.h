#ifndef IMAGE_EFFECTS_H
#define IMAGE_EFFECTS_H

#include "reading_and_writing.h"
#define CONVERT_BASE_TWO 2
#define RGB_MAX 255
#define BRIGHTNESS_FACTOR 0.5

void execute_action(int action, Photo *photo_ppm);
void apply_brightness_effect(Photo *photo_ppm);
void apply_negative_effect(Photo *photo_ppm);
void apply_cut_effect(Photo *photo_ppm);
void apply_resize_effect(Photo *photo_ppm);
void apply_flip_effect(Photo *photo_ppm);
void apply_rotate_effect(Photo *photo_ppm);
void aply_subset_selection(Photo *photo_ppm);

#endif
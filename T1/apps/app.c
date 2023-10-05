#include "reading_and_writing.h"
#include "image_effects.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Numero de argumentos inválido!.\n");
        exit(-1);
    }

    Photo photo_ppm;

    do
    {
        read_ppm_file(&photo_ppm, argv[1]);
        int action = get_editing_option();
        execute_action(action, &photo_ppm);

        // print_ppm_in_terminal(&photo_ppm);
        print_ppm_in_file(&photo_ppm);

        destroy_matrix_pixels(&photo_ppm.pixels, photo_ppm.rows, photo_ppm.cols);

    } while (ask_if_continue());

    return 0;
}
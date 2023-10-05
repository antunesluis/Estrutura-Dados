#include "image_effects.h"
#include "reading_and_writing.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void aply_subset_selection(Photo *photo_ppm)
{
    apply_cut_effect(photo_ppm);

    printf("\n#### Agora defina o efeito que deseja aplicar nesse espaco:\n");
    int action = get_editing_option();
    execute_action(action, photo_ppm);
}

void apply_brightness_effect(Photo *photo_ppm)
{
    for (int i = 0; i < photo_ppm->rows; i++)
    {
        for (int j = 0; j < photo_ppm->cols; j++)
        {
            float new_red = photo_ppm->pixels[i][j].red * BRIGHTNESS_FACTOR;
            float new_green = photo_ppm->pixels[i][j].green * BRIGHTNESS_FACTOR;
            float new_blue = photo_ppm->pixels[i][j].blue * BRIGHTNESS_FACTOR;

            photo_ppm->pixels[i][j].red = (unsigned char)(new_red > RGB_MAX ? RGB_MAX : new_red);
            photo_ppm->pixels[i][j].green = (unsigned char)(new_green > RGB_MAX ? RGB_MAX : new_green);
            photo_ppm->pixels[i][j].blue = (unsigned char)(new_blue > RGB_MAX ? RGB_MAX : new_blue);
        }
    }
}

void apply_negative_effect(Photo *photo_ppm)
{
    for (int i = 0; i < photo_ppm->rows; i++)
    {
        for (int j = 0; j < photo_ppm->cols; j++)
        {
            photo_ppm->pixels[i][j].red = RGB_MAX - photo_ppm->pixels[i][j].red;
            photo_ppm->pixels[i][j].green = RGB_MAX - photo_ppm->pixels[i][j].green;
            photo_ppm->pixels[i][j].blue = RGB_MAX - photo_ppm->pixels[i][j].blue;
        }
    }
}

int get_resize()
{
    const char *editing_options[] = {"2 vezes", "4 vezes", "6 vezes", "8 vezes", "10 vezes"};
    const int num_options = sizeof(editing_options) / sizeof(editing_options[0]);

    printf("\nEscolha uma opção de edicao:\n");
    for (int i = 0; i < num_options; i++)
    {
        printf("[%d] %s\n", i + 1, editing_options[i]);
    }

    int option;
    do
    {
        printf("Digite o numero da opcao: ");
        scanf("%d", &option);
    } while (option < 1 || option > num_options);

    return option * CONVERT_BASE_TWO;
}

void apply_resize_effect(Photo *photo_ppm)
{
    int resize = get_resize();
    int new_rows = photo_ppm->rows * resize;
    int new_cols = photo_ppm->cols * resize;

    Pixel **m = alocate_matrix_pixels(new_rows, new_cols);

    for (int i = 0; i < new_rows; i++)
    {
        for (int j = 0; j < new_cols; j++)
        {
            int original_row = i / resize;
            int original_col = j / resize;

            m[i][j].red = photo_ppm->pixels[original_row][original_col].red;
            m[i][j].green = photo_ppm->pixels[original_row][original_col].green;
            m[i][j].blue = photo_ppm->pixels[original_row][original_col].blue;
        }
    }

    update_photo_data(photo_ppm, m, new_rows, new_cols);
}

void get_cut_values(int *x_ini, int *x_end, int *y_ini, int *y_end)
{
    printf("Informe os valores de corte (x_ini, x_end, y_ini, y_end): ");
    scanf("%d %d %d %d", x_ini, x_end, y_ini, y_end);
}

bool are_cut_values_valid(Photo *photo_ppm, int x_ini, int x_end, int y_ini, int y_end)
{
    return (x_ini >= 0 && x_end <= photo_ppm->cols && y_ini >= 0 && y_end <= photo_ppm->rows);
}

void apply_cut(Photo *photo_ppm, int x_ini, int x_end, int y_ini, int y_end)
{
    int new_rows = y_end - y_ini;
    int new_cols = x_end - x_ini;

    Pixel **m = alocate_matrix_pixels(new_rows, new_cols);

    for (int i = 0; i < new_rows; i++)
    {
        for (int j = 0; j < new_cols; j++)
        {
            m[i][j].red = photo_ppm->pixels[y_ini + i][x_ini + j].red;
            m[i][j].green = photo_ppm->pixels[y_ini + i][x_ini + j].green;
            m[i][j].blue = photo_ppm->pixels[y_ini + i][x_ini + j].blue;
        }
    }

    update_photo_data(photo_ppm, m, new_rows, new_cols);
}

void apply_cut_effect(Photo *photo_ppm)
{
    int x_ini, x_end, y_ini, y_end;

    get_cut_values(&x_ini, &x_end, &y_ini, &y_end);

    if (!are_cut_values_valid(photo_ppm, x_ini, x_end, y_ini, y_end))
    {
        fprintf(stderr, "Valores de corte fora dos limites da imagem.\n");
        return;
    }

    apply_cut(photo_ppm, x_ini, x_end, y_ini, y_end);
}

void apply_flip_effect(Photo *photo_ppm)
{
    for (int i = 0; i < photo_ppm->rows; i++)
    {
        for (int j = 0; j < photo_ppm->cols / 2; j++)
        {
            Pixel temp = photo_ppm->pixels[i][j];
            photo_ppm->pixels[i][j] = photo_ppm->pixels[i][photo_ppm->cols - 1 - j];
            photo_ppm->pixels[i][photo_ppm->cols - 1 - j] = temp;
        }
    }
}

void apply_rotate_effect(Photo *photo_ppm)
{
    Pixel **m = alocate_matrix_pixels(photo_ppm->rows, photo_ppm->cols);

    for (int i = 0; i < photo_ppm->rows; i++)
    {
        for (int j = 0; j < photo_ppm->cols; j++)
        {
            m[j][photo_ppm->rows - 1 - i].red = photo_ppm->pixels[i][j].red;
            m[j][photo_ppm->rows - 1 - i].green = photo_ppm->pixels[i][j].green;
            m[j][photo_ppm->rows - 1 - i].blue = photo_ppm->pixels[i][j].blue;
        }
    }

    update_photo_data(photo_ppm, m, photo_ppm->rows, photo_ppm->cols);
}

void execute_action(int action, Photo *photo_ppm)
{
    switch (action)
    {
    case EDIT_BRIGHTNESS:
        apply_brightness_effect(photo_ppm);
        break;

    case EDIT_NEGATIVE:
        apply_negative_effect(photo_ppm);
        break;

    case EDIT_FLIP:
        apply_flip_effect(photo_ppm);
        break;

    case EDIT_ROTATE:
        apply_rotate_effect(photo_ppm);
        break;

    case EDIT_CUT:
        apply_cut_effect(photo_ppm);
        break;

    case EDIT_RESIZE:
        apply_resize_effect(photo_ppm);
        break;

    case EDIT_SUBSET:
        aply_subset_selection(photo_ppm);
        break;
    }
}
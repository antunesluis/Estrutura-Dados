#include "reading_and_writing.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool ask_if_continue()
{
    char response;
    printf("\n\n");
    printf("Deseja re-editar o arquivo ppm original? (y/n): ");
    scanf(" %c", &response);

    return (response == 'y');
}

int get_editing_option()
{
    const char *editing_options[] = {"Diminuir brilho", "Negativo", "flipar", "girar",
                                     "cortar", "aumentar", "selecionar sub-conjunto"};
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

    return option;
}

void print_ppm_in_file(Photo *photo_ppm)
{
    FILE *outputFile = fopen("result.ppm", "w");
    if (!outputFile)
    {
        fprintf(stderr, "Erro ao abrir o arquivo de saída!\n");
        exit(-1);
    }

    fprintf(outputFile, "P3\n");
    fprintf(outputFile, "%d %d\n", photo_ppm->rows, photo_ppm->cols);
    fprintf(outputFile, "%d\n", photo_ppm->max_color);

    for (int i = 0; i < photo_ppm->rows; i++)
    {
        for (int j = 0; j < photo_ppm->cols; j++)
        {
            fprintf(outputFile, "%-3d %-3d %-3d ", photo_ppm->pixels[i][j].red,
                    photo_ppm->pixels[i][j].green, photo_ppm->pixels[i][j].blue);
        }
        fprintf(outputFile, "\n");
    }

    fclose(outputFile);
    printf("\n#### Arquivo result.ppm foi atualizado com o efeito pedido!");
}

void print_ppm_in_terminal(Photo *photo_ppm)
{
    // system("clear");
    printf("P3\n");
    printf("%d %d\n", photo_ppm->rows, photo_ppm->cols);
    printf("%d\n", photo_ppm->max_color);

    for (int i = 0; i < photo_ppm->rows; i++)
    {
        for (int j = 0; j < photo_ppm->cols; j++)
        {
            printf("%-3d %-3d %-3d ", photo_ppm->pixels[i][j].red,
                   photo_ppm->pixels[i][j].green, photo_ppm->pixels[i][j].blue);
        }
    }
}

void destroy_matrix_pixels(Pixel ***mat, int nrows, int ncols)
{
    int **aux = *mat;

    for (int i = 0; i < nrows; i++)
    {
        free(aux[i]);
    }
    free(aux);
    *mat = NULL;
}

Pixel **alocate_matrix_pixels(int n_rows, int n_cols)
{
    Pixel **mat = (Pixel **)calloc(n_rows, sizeof(Pixel *));
    for (int i = 0; i < n_rows; i++)
    {
        mat[i] = (Pixel *)calloc(n_cols, sizeof(Pixel));
    }

    return mat;
}

void update_photo_data(Photo *photo_ppm, Pixel **new_pixels, int new_rows, int new_cols)
{
    destroy_matrix_pixels(&photo_ppm->pixels, photo_ppm->rows, photo_ppm->cols);

    photo_ppm->pixels = new_pixels;
    photo_ppm->rows = new_rows;
    photo_ppm->cols = new_cols;
}

void read_pixels(Photo *photo_ppm, FILE *file)
{
    system("cls");

    fscanf(file, "%03d", &photo_ppm->max_color);

    for (int i = 0; i < photo_ppm->rows; i++)
    {
        for (int j = 0; j < photo_ppm->cols; j++)
        {
            fscanf(file, "%hhu %hhu %hhu", &photo_ppm->pixels[i][j].red,
                   &photo_ppm->pixels[i][j].green, &photo_ppm->pixels[i][j].blue);
        }
    }
}

void check_header(Photo *photo_ppm, FILE *file)
{
    char header_magic[MAX_SIZE_HEADER];
    fscanf(file, "%2s", header_magic);

    if (header_magic[0] != 'P' || header_magic[1] != '3')
    {
        fprintf(stderr, "Formato de arquivo PPM incorreto\n");
        fclose(file);
        exit(-1);
    }
}

void read_ppm_file(Photo *photo_ppm, char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Erro ao abrir arquivo!\n");
        exit(-1);
    }

    check_header(photo_ppm, file);
    fscanf(file, "%d %d", &photo_ppm->rows, &photo_ppm->cols);

    photo_ppm->pixels = alocate_matrix_pixels(photo_ppm->rows, photo_ppm->cols);
    read_pixels(photo_ppm, file);

    fclose(file);
}
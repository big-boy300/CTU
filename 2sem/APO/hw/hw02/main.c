#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WRONG_INPUT 101
#define MALLOC_ERROR 102

/**
 * Image Sharpening
 * 
 * The purpose of the task is to implement image convolution.
 * 
 * Input data: input.ppm 
 * Output data: output.ppm and output.txt 
 *
 * Online converter can be used to see sharpened picture.
 */

int main(int argc, char *argv[]) {
    int ret = EXIT_SUCCESS;
    const char *fname = argc > 1 ? argv[1] : NULL;
    int img_height, img_width, max_intensity;

    FILE *fp;
    fp = fopen(fname, "rb");

    // read image parameters
    if (fscanf(fp, "P6\n%d\n%d\n%d\n", &img_width, &img_height, &max_intensity) != 3) {
        ret = WRONG_INPUT;
    }

    // allocate space for an old image
    unsigned char *img = (unsigned char *)malloc(img_width * img_height * 3);
    if (img == NULL) {
        fprintf(stderr, "MALLOC ERROR ON LINE %d\n", __LINE__);
        return MALLOC_ERROR;
    }

    // read the contents
    if (!fread(img, sizeof(unsigned char), img_width * img_height * 3, fp)) {
        ret = WRONG_INPUT;
    }

    fclose(fp);

    // allocate space for a new image
    unsigned char *new_img = (unsigned char *)malloc(img_width * img_height * 3);
    if (new_img == NULL) {
        fprintf(stderr, "MALLOC ERROR ON LINE %d\n", __LINE__);
        return MALLOC_ERROR;
    }

    int pix_value;
    int histogram[] = {0, 0, 0, 0, 0};
    double var1 = 0, var2 = 0, var3 = 0;
    int brightness;
    // copy the contents of the original image into a new one
    // to access (x,y) in a 1D array: (y * image_width + x) * 3
    for (int y = 0; y < img_height; ++y) {
        for (int x = 0; x < img_width; ++x) {
            for (int i = 0; i < 3; ++i) {
                if (x == 0 || x == (img_width - 1) || y == 0 || y == (img_height - 1)) {  // only for the frame
                    new_img[(y * img_width + x) * 3 + i] = img[(y * img_width + x) * 3 + i];
                    // for grayscale
                    if (i == 0) {  // RED
                        var1 = 0.2126 * new_img[(y * img_width + x) * 3 + i];
                    }
                    if (i == 1) {  // GREEN
                        var2 = 0.7152 * new_img[(y * img_width + x) * 3 + i];
                    }
                    if (i == 2) {  // BLUE
                        var3 = 0.0722 * new_img[(y * img_width + x) * 3 + i];
                    }
                } else {
                    /*
                    change pixels with matrix:
                    0 -1 0
                    -1 5 -1
                    0 -1 0
                    */

                    pix_value = 5 * img[(y * img_width + x) * 3 + i] - img[(y * img_width + (x - 1)) * 3 + i] - img[(y * img_width + (x + 1)) * 3 + i] - img[((y - 1) * img_width + x) * 3 + i] - img[((y + 1) * img_width + x) * 3 + i];

                    new_img[(y * img_width + x) * 3 + i] = pix_value > 0 ? (pix_value < 255 ? pix_value : 255) : 0;

                    // for grayscale
                    if (i == 0) {  // RED
                        var1 = 0.2126 * new_img[(y * img_width + x) * 3 + i];
                    }
                    if (i == 1) {  // GREEN
                        var2 = 0.7152 * new_img[(y * img_width + x) * 3 + i];
                    }
                    if (i == 2) {  // BLUE
                        var3 = 0.0722 * new_img[(y * img_width + x) * 3 + i];
                    }
                }
            }
            brightness = round(var1 + var2 + var3);

            if (brightness >= 0 && brightness <= 50) {
                histogram[0]++;
            }
            if (brightness >= 51 && brightness <= 101) {
                histogram[1]++;
            }
            if (brightness >= 102 && brightness <= 152) {
                histogram[2]++;
            }
            if (brightness >= 153 && brightness <= 203) {
                histogram[3]++;
            }
            if (brightness >= 204 && brightness <= 255) {
                histogram[4]++;
            }
        }
    }

    // write a new image into a file
    FILE *fd;
    fd = fopen("output.ppm", "wb");
    fprintf(fd, "P6\n%d\n%d\n%d\n", img_width, img_height, max_intensity);
    fwrite(new_img, 1, img_width * img_height * 3, fd);

    // write histogram into a file
    FILE *f;
    f = fopen("output.txt", "w");
    fprintf(f, "%d %d %d %d %d", histogram[0], histogram[1], histogram[2], histogram[3], histogram[4]);

    // free memory
    free(img);
    free(new_img);
    fclose(fd);
    fclose(f);

    return ret;
}

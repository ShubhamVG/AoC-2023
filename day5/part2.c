#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_LEN 50
#define MAX_NUM_DIGITS 15
#define MAX_SEEDS 25

typedef struct GMap {
    unsigned long int dest_start;
    unsigned long int source_start;
    unsigned long int range;
} GMap;


unsigned long int seeds[MAX_SEEDS];
GMap seed_to_soil[MAX_ARRAY_LEN];
GMap soil_to_fertilizer[MAX_ARRAY_LEN];
GMap fertilizer_to_water[MAX_ARRAY_LEN];
GMap water_to_light[MAX_ARRAY_LEN];
GMap light_to_temp[MAX_ARRAY_LEN];
GMap temp_to_humidity[MAX_ARRAY_LEN];
GMap humidity_to_location[MAX_ARRAY_LEN];

void load_seeds(FILE* file);
void load_map_into_array(FILE* file, GMap gmap_array[]);

int gmap_contains(GMap gmap, unsigned long int val);
int is_null_gmap(GMap gmap);
unsigned long int xval_from_yval(GMap x[], unsigned long int yval);

void init() {
    for (int i = 0; i < MAX_SEEDS; i++) {
        seeds[i] = -1;
    }

    GMap null_gmap = (GMap) {.dest_start = 0, .source_start = 0, .range = 0};

    for (int i = 0; i < MAX_ARRAY_LEN; i++) {
        seed_to_soil[i] = null_gmap;
        soil_to_fertilizer[i] = null_gmap;
        fertilizer_to_water[i] = null_gmap;
        water_to_light[i] = null_gmap;
        light_to_temp[i] = null_gmap;
        temp_to_humidity[i] = null_gmap;
        humidity_to_location[i] = null_gmap;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error: No input file.\n");
        return 1;
    }

    init();
    char* path = argv[1];
    FILE* file = fopen(path, "r");

    if (file == NULL) {
        printf("Error: Failed to open file.\n");
        fclose(file);
        return 1;
    }

    load_seeds(file);
    load_map_into_array(file, seed_to_soil);
    load_map_into_array(file, soil_to_fertilizer);
    load_map_into_array(file, fertilizer_to_water);
    load_map_into_array(file, water_to_light);
    load_map_into_array(file, light_to_temp);
    load_map_into_array(file, temp_to_humidity);
    load_map_into_array(file, humidity_to_location);
    fclose(file);

    unsigned long int min_location = 999999999999999;

    for (int i = 0; i < MAX_SEEDS; i += 2) {
        if (seeds[i] == -1) {
           break; 
        }

        unsigned long int range = seeds[i + 1];

        for (int j = 0; j <= range; j++) {
            unsigned long int seed = seeds[i] + j;
            unsigned long int soil = xval_from_yval(seed_to_soil, seed);
            unsigned long int fertilizer = xval_from_yval(soil_to_fertilizer, soil);
            unsigned long int water = xval_from_yval(fertilizer_to_water, fertilizer);
            unsigned long int light = xval_from_yval(water_to_light, water);
            unsigned long int temp = xval_from_yval(light_to_temp, light);
            unsigned long int humidity = xval_from_yval(temp_to_humidity, temp);
            unsigned long int location = xval_from_yval(humidity_to_location, humidity);

            if (location < min_location) {
                min_location = location;
            }
        }
    }

    printf("Min location is %lu.\n", min_location);
}

int gmap_contains(GMap gmap, unsigned long int val) {
    if ((gmap.source_start <= val) && (gmap.source_start + gmap.range >= val)) {
        return 1;
    }

    return 0;
}

int is_null_gmap(GMap gmap) {
    if (gmap.range == 0) {
        return 1;
    }

    return 0;
}

void load_seeds(FILE* file) {
    char curr_char = '\0';
    char prev_char = '\0';
    char string[MAX_NUM_DIGITS];
    int i = 0;
    int array_index = 0;
    int start = 0;

    while ((curr_char = fgetc(file)) != EOF) {
         if (curr_char == prev_char && curr_char == '\n') {
             break;
         }

        if (start == 0) {
            if (curr_char == ' ' && prev_char == ':') {
                start = 1;
            }

            prev_char = curr_char;
            continue;
        }
        
        if (curr_char == ' ') {
           string[i] = '\0';
            i = 0;
            seeds[array_index] = atoll(&string[0]);
            array_index++;
        } else if (curr_char == '\n') {
            string[i] = '\0';
            seeds[array_index] = atoll(&string[0]);
        } else {
            string[i] = curr_char;
            i++;
        }

        prev_char = curr_char;
    }


}

void load_map_into_array(FILE* file, GMap gmap_array[]) {
    char curr_char = '\0';
    char prev_char = '\0';
    char string[MAX_NUM_DIGITS];
    int i = 0;
    unsigned long int values[3];
    int value_index = 0;
    int array_index = 0;
    int start = 0;

    while ((curr_char = fgetc(file)) != EOF) {
        if (curr_char == prev_char && curr_char == '\n') {
            break;
        }

        if (start == 0) {
            if (curr_char == '\n' && prev_char == ':') {
                start = 1;
            }

            prev_char = curr_char;
            continue;
        }

        if (curr_char == ' ') {
            string[i] = '\0';
            i = 0;
            values[value_index] = atoll(&string[0]);
            value_index++;
        } else if (curr_char == '\n') {
            string[i] = '\0';
            i = 0;
            values[value_index] = atoll(&string[0]);
            value_index = 0;

            GMap gmap;
            gmap.dest_start = values[0];
            gmap.source_start = values[1];
            gmap.range = values[2];
            gmap_array[array_index] = gmap;
            array_index++;
        } else {
            string[i] = curr_char;
            i++;
        }

        prev_char = curr_char;
    }
}

unsigned long int xval_from_yval(GMap x[], unsigned long int yval) {
    unsigned long int xval = yval; // default

    for (int i = 0; i < MAX_ARRAY_LEN; i++) {
        GMap gmap = x[i];

        if (is_null_gmap(gmap) == 1) {
            break;
        }

        if (gmap_contains(gmap, yval) == 1) {
            unsigned long int difference = yval - gmap.source_start;
            xval = gmap.dest_start + difference;
            break;
        }
    }

    return xval;
}

# define GOL_WIDTH  40
# define GOL_HEIGHT 16
# define GOL_FRAME_TIME 75
# define GOL_GLIDER_SIZE 3

/* 2D array declaration*/
static bool current_frame[GOL_WIDTH][GOL_HEIGHT] = {{false}};
static bool next_frame[GOL_WIDTH][GOL_HEIGHT]    = {{false}};
static bool glider[GOL_GLIDER_SIZE][GOL_GLIDER_SIZE] = {
    {false, true,  false},
    {false, false, true},
    {true,  true,  true}
};

uint8_t count_neighbors(uint8_t i, uint8_t j) {
    uint8_t live_neighbors  = 0;
    uint8_t previous_column = (i - 1 + GOL_WIDTH) % GOL_WIDTH;
    uint8_t next_column     = (i + 1) % GOL_WIDTH;
    uint8_t previous_row    = (j - 1 + GOL_HEIGHT) % GOL_HEIGHT;
    uint8_t next_row        = (j + 1) % GOL_HEIGHT;

    // previous row
    if (previous_column >= 0 && previous_row >= 0 && current_frame[previous_column][previous_row]) {
        live_neighbors++;
    }

    if (previous_row >= 0 && current_frame[i][previous_row]) {
        live_neighbors++;
    }

    if (next_column < GOL_WIDTH && previous_row >= 0 && current_frame[next_column][previous_row]) {
        live_neighbors++;
    }

    // current row
    if (previous_column >= 0 && current_frame[previous_column][j]) {
        live_neighbors++;
    }

    if (next_column < GOL_WIDTH && current_frame[next_column][j]) {
        live_neighbors++;
    }

    // next row
    if (previous_column >= 0 && next_row < GOL_HEIGHT && current_frame[previous_column][next_row]) {
        live_neighbors++;
    }

    if (next_row < GOL_HEIGHT && current_frame[i][next_row]) {
        live_neighbors++;
    }

    if (next_column < GOL_WIDTH && next_row < GOL_HEIGHT && current_frame[next_column][next_row]) {
        live_neighbors++;
    }

    return live_neighbors;
}

void iteration(void) {
    uint8_t i, j;
    for (i = 0; i < GOL_WIDTH; i++) {
        for (j = 0; j < GOL_HEIGHT; j++) {
            uint8_t live_neighbors = count_neighbors(i, j);
            if((current_frame[i][j] == 1) && (live_neighbors < 2 || live_neighbors > 3)) {
                next_frame[i][j] = 0;
            }
            else if((current_frame[i][j] == 0) && (live_neighbors == 3)) {
                next_frame[i][j] = 1;
            }
        }
    }

}

void show(void) {
    uint8_t i, j;
    for (i = 0; i < GOL_WIDTH; i++) {
        for (j = 0; j < GOL_HEIGHT; j++) {
            current_frame[i][j] = next_frame[i][j];
            oled_write_pixel(i * 2, j * 2, current_frame[i][j] == 1);
            oled_write_pixel(i * 2 + 1, j * 2, current_frame[i][j] == 1);
            oled_write_pixel(i * 2, j * 2 + 1, current_frame[i][j] == 1);
            oled_write_pixel(i * 2 + 1, j * 2 + 1, current_frame[i][j] == 1);
        }
    }
}

static void reset_gol(void) {
    uint8_t i,j;
    for (i = 0; i < GOL_WIDTH; i++) {
        for (j = 0; j < GOL_HEIGHT; j++) {
            current_frame[i][j] = rand() & 1;
        }
    }
}

static void blank_gol(void) {
    uint8_t i,j;
    for (i = 0; i < GOL_WIDTH; i++) {
        for (j = 0; j < GOL_HEIGHT; j++) {
            next_frame[i][j] = false;
            current_frame[i][j] = false;
        }
    }
}

void draw_glider(uint8_t origin_i, uint8_t origin_j) {
    uint8_t i, j;
    for (i = 0; i < GOL_GLIDER_SIZE; i++) {
        for (j = 0; j < GOL_GLIDER_SIZE; j++) {
            next_frame[origin_i + i][origin_j + j] = glider[i][j];
        }
    }
}

static void draw_gliders(void) {
    blank_gol();
    uint8_t glider_origin;
    for (glider_origin = 0; glider_origin < GOL_WIDTH; glider_origin = glider_origin + 8) {
        uint8_t j = 8 + (rand() % 4);
        draw_glider(glider_origin, j);
    }
}

static void draw_gol(void) {
    if (timer_elapsed32(anim_timer) > GOL_FRAME_TIME) {
        anim_timer = timer_read32();
        oled_clear();
        iteration();
        show();
    }
}

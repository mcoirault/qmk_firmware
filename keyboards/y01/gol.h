# define GOL_WIDTH  40
# define GOL_HEIGHT 16

/* 2D array declaration*/
static bool current_frame[GOL_WIDTH][GOL_HEIGHT] = {{false}};
static bool next_frame[GOL_WIDTH][GOL_HEIGHT] = {{false}};

uint8_t count_neighbors(uint8_t i, uint8_t j) {
    uint8_t live_neighbors = 0;
    uint8_t previous_column = i-1;
    uint8_t next_column = i+1;
    uint8_t previous_row = j-1;
    uint8_t next_row = j+1;

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
            oled_write_pixel(i, j, current_frame[i][j] == 1);
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

static void draw_gol(void) {
    if (timer_elapsed32(anim_timer) > 33) {
        anim_timer = timer_read32();
        oled_clear();
        iteration();
        show();
    }
}

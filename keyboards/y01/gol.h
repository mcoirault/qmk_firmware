# define GOL_WIDTH  40
# define GOL_HEIGHT 16
# define GOL_FRAME_TIME 66
# define GOL_GLIDER_SIZE 3

/* 2D array declaration*/
bool current_frame[GOL_WIDTH][GOL_HEIGHT]        = {{false}};
bool next_frame[GOL_WIDTH][GOL_HEIGHT]           = {{false}};
bool glider[GOL_GLIDER_SIZE][GOL_GLIDER_SIZE]    = {
    {false, true,  false},
    {false, false, true},
    {true,  true,  true}
};

int live_count  = 0;
int birth_count = 0;

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
    live_count = 0;
    birth_count = 0;
    for (i = 0; i < GOL_WIDTH; i++) {
        for (j = 0; j < GOL_HEIGHT; j++) {
            uint8_t live_neighbors = count_neighbors(i, j);
            if((current_frame[i][j] == 1) && (live_neighbors < 2 || live_neighbors > 3)) {
                next_frame[i][j] = 0;
            }
            else if((current_frame[i][j] == 0) && (live_neighbors == 3)) {
                next_frame[i][j] = 1;
                live_count++;
                birth_count++;
            } else if (current_frame[i][j] == 1) {
                live_count++;
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

void blank_gol(void) {
    uint8_t i,j;
    for (i = 0; i < GOL_WIDTH; i++) {
        for (j = 0; j < GOL_HEIGHT; j++) {
            next_frame[i][j] = false;
            current_frame[i][j] = false;
        }
    }
}

void draw_glider(uint8_t origin_i, uint8_t origin_j) {
    for (uint8_t i = 0; i < GOL_GLIDER_SIZE; i++) {
        for (uint8_t j = 0; j < GOL_GLIDER_SIZE; j++) {
            next_frame[origin_i + i][origin_j + j] = glider[i][j];
        }
    }
}

void draw_box(uint8_t origin_i, uint8_t origin_j) {
    for (uint8_t i = 0; i < 3; i++) {
        for (uint8_t j = 0; j < 3; j++) {
            if (i == 1 && j == 1) {
                continue;
            }
            next_frame[origin_i + i][origin_j + j] = true;
        }
    }
}

void draw_tub(uint8_t origin_i, uint8_t origin_j) {
    next_frame[origin_i + 1][origin_j] = true;
    next_frame[origin_i][origin_j + 1] = true;
    next_frame[origin_i + 2][origin_j + 1] = true;
    next_frame[origin_i + 1][origin_j + 2] = true;
}

void draw_stats(void) {
    oled_set_cursor(15, 2);
    oled_write_P(PSTR("L "), false);
    oled_write(get_u8_str(live_count, ' '), false);
    oled_set_cursor(15, 3);
    oled_write_P(PSTR("B "), false);
    oled_write(get_u8_str(birth_count, ' '), false);
}

static void reset_gol(void) {
    uint8_t i,j;
    for (i = 0; i < GOL_WIDTH; i++) {
        for (j = 0; j < GOL_HEIGHT; j++) {
            current_frame[i][j] = rand() & 1;
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

static void draw_pulsar(uint8_t origin_i, uint8_t origin_j) {
    blank_gol();

    draw_box(origin_i, origin_j);
    draw_box(origin_i + 6, origin_j);
}

static void draw_eureka(uint8_t origin_i, uint8_t origin_j) {
    blank_gol();

    // offset to accomodate for the full height of the oscillator
    origin_j = origin_j + 2;
    draw_box(origin_i + 9, origin_j + 1);
    draw_box(origin_i + 9, origin_j + 7);
    draw_tub(origin_i, origin_j);
    draw_tub(origin_i, origin_j + 8);
    draw_tub(origin_i + 15, origin_j);
    draw_tub(origin_i + 15, origin_j + 8);
}

static void draw_gol(void) {
    if (timer_elapsed32(anim_timer) > GOL_FRAME_TIME) {
        anim_timer = timer_read32();
        oled_clear();
        iteration();
        show();
        draw_stats();
    }
}

#define BERRY_COLORS 4
HSV berryColorsHsv[BERRY_COLORS] = {
    {HSV_PURPLE},
    {HSV_CYAN},
    {HSV_MAGENTA},
    {HSV_TEAL}
};

int colorIndex = 0;
int nextIndex = 0;
long int colorCounter = 0;
long int colorRepeat = 100000;

static HSV berryLerpImpl(HSV hsv, uint8_t i, uint8_t time) {
    colorCounter += (int)(rgb_matrix_config.speed / 8);

    if (colorCounter >= colorRepeat) {
        colorIndex += 1;
        if (colorIndex == BERRY_COLORS) {
            colorIndex = 0;
        }
        colorCounter = 0;
    }

    nextIndex = colorIndex + 1;
    if (nextIndex == BERRY_COLORS) {
        nextIndex = 0;
    }

    HSV a = berryColorsHsv[colorIndex];
    HSV b = berryColorsHsv[nextIndex];

    float t = (1.0f * colorCounter) / (1.0f * colorRepeat);
    return hsvLerp(a, b, t);
}

bool berryLerp(effect_params_t* params) { return effect_runner_i(params, &berryLerpImpl); }


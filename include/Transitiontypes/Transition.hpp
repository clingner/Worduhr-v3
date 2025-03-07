#include "Transition.h"
#include "Uhr.h"
#include <Arduino.h>

#define STRIPE NULL
#define MAX_RANDOM 10

Transition::Transition(uint8_t rows, uint8_t cols) {
    maxRows = rows;
    maxCols = cols;
    sizeofColumn = cols * sizeof(RgbfColor);
    old = new RgbfColor *[rows];
    act = new RgbfColor *[rows];
    work = new RgbfColor *[rows];
    for (uint8_t row = 0; row < rows; row++) {
        old[row] = new RgbfColor[cols];
        act[row] = new RgbfColor[cols];
        work[row] = new RgbfColor[cols];
    }
    rain = new Rain[cols];
    balls = new Ball[cols];
    for (uint8_t col = 0; col < cols; col++) {
        rain[col] = Rain(rows, cols);
        balls[col] = Ball(rows);
    }
    snake = new Snake(rows, cols);
    firework = new Firework(rows, cols);
    transitionType = (Transition_t)G.transitionType;
    lastTransitionType = (Transition_t)G.transitionType;
    lastTransitionDemo = G.transitionDemo;
    lastTransitionDuration = G.transitionDuration;
    lastTransitionColorize = G.transitionColorize;
}

//------------------------------------------------------------------------------

Transition::~Transition() {
#if 0
    // matrix type changes during runtime forces a ESP reset
    // probably to avoid reinitializing the Neopixelbus
    for (uint8_t row = 0; row < maxRows; row++) {
        delete[] old[row];
        delete[] act[row];
        delete[] work[row];
    }
    delete[] old;
    delete[] act;
    delete[] work;
    delete[] tmp;
    delete[] rain;
#endif
}

//------------------------------------------------------------------------------

bool Transition::isSilvester(Transition_t &type, struct tm &tm, bool trigger) {
    static uint8_t minutesAfterMidnight;

    if (trigger) {
#if 1
        if ((tm.tm_mon == 12) && (tm.tm_mday == 31) && (tm.tm_hour == 23) &&
            (tm.tm_min == 59))
#else
        if (tm.tm_min == G.autoLdrBright) // for testing
#endif
        {
            minutesAfterMidnight = 0;
            type = COUNTDOWN;
        } else {
            minutesAfterMidnight++;
        }
        if ((type == NEWYEAR) && (minutesAfterMidnight >= 11)) {
            type = getTransitionType(true);
        }
    }
    return (type == COUNTDOWN) || (type == NEWYEAR);
}

//------------------------------------------------------------------------------

Transition_t Transition::getTransitionType(bool trigger) {
    if (G.transitionType == RANDOM) {
        if (trigger) {
            return (Transition_t)random(transitionTypeFirst,
                                        transitionTypeLast + 1);
        } else {
            return transitionType;
        }
    }
    return (Transition_t)G.transitionType;
}

//------------------------------------------------------------------------------
bool Transition::isColorization() {
    return (transitionType != NO_TRANSITION && G.transitionColorize);
}

//------------------------------------------------------------------------------

bool Transition::changeBrightness() {
    RgbfColor newForeground, newBackground;
    // determine only foreground and background from LED stripe
    analyzeColors(NULL, STRIPE, newForeground, newBackground);
    bool adjustFg = newForeground != foreground,
         adjustBg = newBackground != background;

    if (adjustFg || adjustBg) {
        HsbColor hsbColor;
        float brightness = HsbColor(newForeground).B;
        hsbColor = HsbColor(foregroundMinute);
        hsbColor.B = brightness;
        foregroundMinute = RgbColor(hsbColor);
        RgbfColor **matrix[3] = {act, old, work};
        for (uint8_t m = 0; m < 3; m++) {
            for (uint8_t row = 0; row < maxRows; row++) {
                for (uint8_t col = 0; col < maxCols; col++) {
                    if (adjustBg) {
                        if (!matrix[m][row][col].isForeground()) {
                            matrix[m][row][col] = newBackground;
                        }
                    }
                    if (adjustFg) {
                        if (matrix[m][row][col].isForeground()) {
                            if (isColorization()) {
                                hsbColor = HsbColor(matrix[m][row][col]);
                                hsbColor.B = brightness;
                                matrix[m][row][col].changeRgb(hsbColor);
                            } else {
                                matrix[m][row][col].changeRgb(newForeground);
                            }
                        }
                    }
                }
            }
        }
        background = newBackground;
        foreground = newForeground;
    }
    return (adjustFg || adjustBg);
}

//------------------------------------------------------------------------------
// returns hue values with a difference of at least 0.1 (360 * 0,1 = 36 degree)
// avoiding neighbors with very similar colors

float Transition::pseudoRandomHue() {
    static bool first = true;
    if (first) {
        first = false;
        return pseudoRandomHue(true);
    }
    return pseudoRandomHue(false);
}

//------------------------------------------------------------------------------

float Transition::pseudoRandomHue(bool init) {
    static uint16_t lastColors[MAX_RANDOM];
    static uint16_t lastColor = 1000;
    static uint8_t inUse = 1;
    uint16_t hue;
    uint32_t i, tries;

    if (init || (inUse == (MAX_RANDOM - 1))) {
        inUse = 1;
        lastColors[0] = lastColor;
        for (i = 1; i < MAX_RANDOM; i++) {
            lastColors[i] = 9999;
        }
    }
    hue = 1000 + random(1000); // 1000 ... 2000
    tries = i = 0;
    do {
        if (lastColors[i] == 9999) { // empty array element
            inUse = i;
            lastColor = lastColors[i] = hue;
            return (static_cast<float>(hue - 1000)) / 1000.0; // 0.0 ... 1.0
        }
        if (((hue > (lastColors[i] - 100)) && (hue < (lastColors[i] + 100)))) {
            // hue matches an existing color, try new hue
            hue = 1000 + random(1000);
            tries++;
            i = 0;
        } else {
            // check next array element
            i++;
        }
    } while ((i < MAX_RANDOM) && (tries < 20));
    return pseudoRandomHue(true);
}

//------------------------------------------------------------------------------
// colorize foreground

void Transition::colorize(RgbfColor **dest) {
    bool changeColor = true;
    HsbColor hsbColor = HsbColor(foreground);
    hsbColor.H = pseudoRandomHue();
    foregroundMinute = isColorization() ? RgbColor(hsbColor) : foreground;
    hsbColor.H = pseudoRandomHue();
    for (uint8_t row = 0; row < maxRows; row++) {
        for (uint8_t col = 0; col < maxCols; col++) {
            if (dest[row][col].isForeground()) {
                if ((G.transitionColorize == CHARACTERS) || changeColor) {
                    changeColor = false;
                    hsbColor.H = pseudoRandomHue();
                }
                dest[row][col].changeRgb(isColorization() ? hsbColor
                                                          : foreground);
            } else {
                changeColor = true;
            }
        }
    }
}

//------------------------------------------------------------------------------

void Transition::saveMatrix() {
    static bool firstRun = true;
    copyMatrix(old, act);
    analyzeColors(act, STRIPE, foreground, background);
    foregroundMinute = foreground;
    if (isColorization()) {
        colorize(act);
    }
    if (firstRun) {
        firstRun = false;
        copyMatrix(work, act);
    }
    return;
}

//------------------------------------------------------------------------------
// copy (internal matrix or from LED stripe) and determine foreground and
// background color

void Transition::analyzeColors(RgbfColor **dest, RgbfColor **source,
                               RgbfColor &foreground, RgbfColor &background) {
    RgbfColor color, color1(0), color2(0);
    uint32_t colorCounter1 = 0, colorCounter2 = 0;
    for (uint8_t row = 0; row < maxRows; row++) {
        for (uint8_t col = 0; col < maxCols; col++) {
            if (source == STRIPE) {
                color = RgbfColor(
                    led.getPixel(usedUhrType->getFrontMatrixIndex(row, col)));
            } else {
                color = source[row][col];
            }
            if (dest != NULL) {
                dest[row][col] = color;
            }
            if (color == color1) {
                colorCounter1++;
            } else {
                if (color == color2) {
                    colorCounter2++;
                } else {
                    // no color assigned yet
                    if (colorCounter1 > 0) {
                        color2 = color;
                        colorCounter2 = 1;
                    } else {
                        color1 = color;
                        colorCounter1 = 1;
                    }
                }
            }
        }
    }
    if (colorCounter1 > colorCounter2) { // Majority vote ?!
        background = color1;
        foreground = color2;
    } else {
        background = color2;
        foreground = color1;
    }
    foreground.setForeground(true);
    foreground.setOverlay(false);
    background.setForeground(false);
    background.setOverlay(false);
    if (dest != NULL) {
        for (uint8_t row = 0; row < maxRows; row++) {
            for (uint8_t col = 0; col < maxCols; col++) {
                dest[row][col].setForeground(dest[row][col] == foreground);
            }
        }
    }
}

//------------------------------------------------------------------------------

void Transition::setMinute() {
    if (G.minuteVariant != MinuteVariant::Off) {
        uint8_t m = lastMinute % 5;
        uint16_t minArray[4];
        usedUhrType->getMinuteArray(minArray,
                                    clockWork.determineWhichMinuteVariant());
        if (G.layoutVariant[ReverseMinDirection]) {
            std::reverse(std::begin(minArray), std::end(minArray));
        }
        for (uint8_t i = 0; i < 4; i++) {
            led.setPixel(minArray[i],
                         HsbColor{m > i ? foreground : background});
            // TODO: foregroundMinute
        }
    }
}

//------------------------------------------------------------------------------
// Overwrite the LEDs with internal matrix

void Transition::copy2Stripe(RgbfColor **source) {
    for (uint8_t row = 0; row < maxRows; row++) {
        for (uint8_t col = 0; col < maxCols; col++) {
            led.setPixel(
                usedUhrType->getFrontMatrixIndex(row, col),
                HsbColor{RgbColor(source[row][col].R, source[row][col].G,
                                  source[row][col].B)});
        }
    }
    setMinute();
}

//------------------------------------------------------------------------------

void Transition::copyMatrix(RgbfColor **dest, RgbfColor **source) {
    for (uint8_t row = 0; row < maxRows; row++) {
        memcpy(dest[row], source[row], sizeofColumn);
    }
}

//------------------------------------------------------------------------------

void Transition::copyMatrixFlags(RgbfColor **dest, RgbfColor **source) {
    for (uint8_t row = 0; row < maxRows; row++) {
        for (uint8_t col = 0; col < maxCols; col++) {
            dest[row][col].setFlags(source[row][col].getFlags());
        }
    }
}

//------------------------------------------------------------------------------

void Transition::fillMatrix(RgbfColor **matrix, RgbfColor color) {
    for (uint8_t row = 0; row < maxRows; row++) {
        for (uint8_t col = 0; col < maxCols; col++) {
            matrix[row][col] = color;
        }
    }
}

//------------------------------------------------------------------------------

bool Transition::changesInTransitionTypeDurationOrDemo() {
    return (transitionType != lastTransitionType) ||
           (G.transitionDuration != lastTransitionDuration) ||
           (G.transitionDemo != lastTransitionDemo);
}

//------------------------------------------------------------------------------

uint16_t Transition::reverse(uint16_t num, bool mirrored) {
    // reverse left 11 bits
    if (mirrored) {
        uint16_t res = 0;
        for (uint8_t i = 0; i < 11; i++) {
            if (num & (1 << i)) {
                res |= 0b10000000000 >> i;
            }
        }
        num = res;
    }
    return num;
}

//------------------------------------------------------------------------------
// slow == 1 -> 5s
// mid  == 2 -> 3.5s
// fast == 3 -> 2s

uint16_t Transition::calcDelay(uint16_t frames) {
    uint32_t pause;
    if (frames == 0) { // avoid div 0
        frames = 10;
    }
    switch (G.transitionDuration) {
    case 1:
        pause = 2000 / frames;
        break; // 2 seconds
    case 3:
        pause = 5000 / frames;
        break; // 5 seconds
    default:
        pause = 3500 / frames;
        break; // 3.5 seconds
    }
    if (pause == 0) {
        pause = 1;
    }
    return pause;
}

//------------------------------------------------------------------------------

void Transition::setPixelForChar(uint8_t col, uint8_t row, uint8_t offsetCol,
                                 unsigned char unsigned_d1, HsbColor color) {
    if (pgm_read_byte(&(font_7x5[unsigned_d1][col])) & (1u << row)) {
        work[row + 1][col + offsetCol].changeRgb(color);
    }
}

//------------------------------------------------------------------------------
// Transitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// the new matrix slides in from above       | below
//                      row                  |               row
// phase | 9876543210   old  act   wechsel   | 9876543210   old  act   wechsel
//       | unten oben                        | unten oben
//   1   | aaaaaaaaan   0-8  9     0         | naaaaaaaaa   1-9  0     9
//   2   | aaaaaaaann   0-7  8-9   1         | nnaaaaaaaa   2-9  0-1   8
//   3   | aaaaaaannn   0-6  7-9   2         | nnnaaaaaaa   3-9  0-2   7
//   4   | aaaaaannnn   0-5  6-9   3         | nnnnaaaaaa   4-9  0-3   6
//   5   | aaaaannnnn   0-4  5-9   4         | nnnnnaaaaa   5-9  0-4   5
//   6   | aaaannnnnn   0-3  4-9   5         | nnnnnnaaaa   6-9  0-5   4
//   7   | aaannnnnnn   0-4  3-9   6         | nnnnnnnaaa   7-9  0-6   3
//   8   | aannnnnnnn   0-1  2-9   7         | nnnnnnnnaa   8-9  0-7   2
//   9   | annnnnnnnn   0    1-9   8         | nnnnnnnnna   9    0-8   1
//  10   | nnnnnnnnnn        0-9   9         | nnnnnnnnnn        0-9   0

uint16_t Transition::transitionScrollDown(bool dirDown) {
    uint32_t wechsel, rowAlt, rowNeu;
    bool copyFromNeu;

    if (phase == 1) {
        transitionDelay = calcDelay(maxRows) / 4;
    }
    if (dirDown) {
        wechsel = phase;
        rowAlt = 0;
        rowNeu = maxRows - phase;
    } else {
        wechsel = maxRows - phase;
        rowAlt = phase;
        rowNeu = 0;
    }
    for (uint8_t row = 0; row < maxRows; row++) {
        copyFromNeu = (row >= wechsel) ^ dirDown;
        for (uint8_t col = 0; col < maxCols; col++) {
            if (copyFromNeu) {
                work[row][col] = act[rowNeu][col];
            } else {
                work[row][col] = old[rowAlt][col];
            }
        }
        if (copyFromNeu) {
            rowNeu++;
        } else {
            rowAlt++;
        }
    }
    if (phase >= maxRows) {
        return 0;
    }
    return phase + 1;
}

//------------------------------------------------------------------------------
// the new matrix slides in from the right / in from the left
//                       col
// phase | 01234567890   old  act   Wechsel  01234567890   old  act   Wechsel
//   1   | aaaaaaaaaan   1-10 0      0       naaaaaaaaaa   0-9  10    10
//   2   | aaaaaaaaann   2-10 0-1    1       nnaaaaaaaaa   0-8  9-10   9
//   3   | aaaaaaaannn   3-10 0-2    2       nnnaaaaaaaa   0-7  8-10   8
//
//  10   | annnnnnnnnn   10   0-9    9       nnnnnnnnnna   0    1-10   1
//  11   | nnnnnnnnnnn        0-10  10       nnnnnnnnnnn        0-10   0

uint16_t Transition::transitionScrollRight(bool dirRight) {
    uint32_t wechsel, colAlt, colNeu;
    bool copyFromNeu;

    if (phase == 1) {
        transitionDelay = calcDelay(maxCols) / 4;
    }
    if (dirRight) {
        wechsel = phase;
        colAlt = 0;
        colNeu = maxCols - phase;
    } else {
        wechsel = maxCols - phase;
        colAlt = phase;
        colNeu = 0;
    }
    for (uint8_t col = 0; col < maxCols; col++) {
        copyFromNeu = (col >= wechsel) ^ dirRight;
        for (uint8_t row = 0; row < maxRows; row++) {
            if (copyFromNeu) {
                work[row][col] = act[row][colNeu];
            } else {
                work[row][col] = old[row][colAlt];
            }
        }
        if (copyFromNeu) {
            colNeu++;
        } else {
            colAlt++;
        }
    }
    if (phase >= maxCols) {
        return 0;
    }
    return phase + 1;
}

//------------------------------------------------------------------------------
// In each column, one ball falls from the highest letter.

uint16_t Transition::transitionBalls() {
    static uint32_t starttime;
    static uint32_t numBalls;
    uint32_t oldR, row, col, ballsDown;
    uint32_t timeDelta, now;

    if (phase == 1) {
        transitionDelay = 50; // 20 Frames per second
        numBalls = 0;
        for (col = 0; (col < maxCols) && (numBalls < maxCols); col++) {
            for (row = 0; (row < maxRows) && (numBalls < maxCols); row++) {
                if (work[row][col].isForeground()) {
                    balls[numBalls].begin(row, col, work[row][col], background,
                                          100 * numBalls);
                    numBalls++;
                    break;
                }
            }
        }
        starttime = millis();
    }

    now = millis();
    timeDelta = now - starttime;
    starttime = now;
    ballsDown = 0;
    for (uint8_t i = 0; i < numBalls; i++) {
        oldR = balls[i].row;
        ballsDown += balls[i].move(timeDelta);
        row = balls[i].row; // row, col new coordinates
        col = balls[i].col;
        if (row > oldR) { // down
            for (; row > oldR; oldR++) {
                work[oldR][col] = background;
            }
        } else { // up
            for (; row < oldR; oldR--) {
                work[oldR][col] = background;
            }
        }
        work[row][col] = balls[i].color;
    }
    if (ballsDown >= numBalls) {
        copyMatrix(work, act);
        return 0;
    }
    return phase + 1;
}

//------------------------------------------------------------------------------

uint16_t Transition::transitionFire() {
    static const uint8_t blendingFrames = 20;
    static bool sparkle, mirrored = false;
    static uint32_t subPhase;

    if (phase == 1) {
        // FIRE_1 .. 6 + 4 = 10
        transitionDelay = calcDelay(blendingFrames * 10) / 2;
        phase = FIRE_1;
        sparkle = false;
        subPhase = 1;
        firework->prepare(0, _white, FIRE_1, mirrored);
        // use current colors to be blended to act
        copyMatrix(old, work);
        copyMatrixFlags(work, act);
    }

    bool lastSubPhase = subPhase == blendingFrames;
    if (subPhase > blendingFrames) {
        subPhase = 1;
        phase++;
        switch (phase) {
        case FIRE_4:
            firework->prepare(0, _red, FIRE_4, mirrored);
            break;
        case FIRE_5:
            firework->prepare(0, _red, FIRE_5, mirrored);
            break;
        case FIRE_6:
            firework->prepare(0, _red, FIRE_6, mirrored);
            break;
        case (FIRE_6 + 1):
            firework->prepare(0, _blue, FIRE_6, mirrored);
            firework->prepare(1, _green, FIRE_4, mirrored);
            firework->prepare(2, _yellow, FIRE_5, mirrored);
            break;
        case (FIRE_6 + 2):
            transitionDelay *= 2;
            sparkle = true;
            break;
        case (FIRE_6 + 3):
            break;
        case (FIRE_6 + 4):
            mirrored = !mirrored;
            copyMatrix(old, act); // old contains artefacts
            if ((transitionType == NEWYEAR)) {
                transitionDelay = 500;
                return 1; // next transition in 500ms
            }
            return 0; // end of transition
            break;
        default:
            firework->prepare(0, _white, static_cast<Icons>(phase), mirrored);
        }
    }

    RgbColor overlayColor;
    float progress = static_cast<float>(subPhase) / blendingFrames;
    if (progress > 1.0) {
        progress = 1.0;
    }
    float fading =
        static_cast<float>((phase - FIRE_1) * blendingFrames + subPhase) /
        (blendingFrames * (FIRE_6 - FIRE_1 + 2));
    if (fading > 1.0) {
        fading = 1.0;
    }
    bool overlay;
    for (uint8_t col = 0; col < maxCols; col++) {
        for (uint8_t row = 0; row < maxRows; row++) {
            overlay = firework->getPixel(row, col, overlayColor);
            if (sparkle) {
                if (work[row][col].isOverlay()) {
                    // overlayed in previous run
                    work[row][col] = old[row][col]; // restore color
                    work[row][col].setOverlay(false);
                } else {
                    if (overlay && (random(10) == 0) && (!lastSubPhase)) {
                        old[row][col] = work[row][col]; // save color
                        work[row][col].changeRgb(_white);
                        work[row][col].setOverlay();
                    }
                }
            } else {
                // blend old -> act
                RgbColor color =
                    color.LinearBlend(old[row][col], act[row][col], fading);
                if (overlay && !lastSubPhase) {
                    // blend in overlay
                    overlayColor =
                        overlayColor.LinearBlend(color, overlayColor, progress);
                    work[row][col].changeRgb(overlayColor);
                    work[row][col].setOverlay();
                } else {
                    if (work[row][col].isOverlay()) {
                        // blend out overlay
                        color =
                            color.LinearBlend(overlayColor, color, progress);
                        work[row][col].changeRgb(color);
                        if (lastSubPhase) {
                            work[row][col].setOverlay(false);
                        }
                    } else {
                        // set mix of old and act
                        work[row][col].changeRgb(color);
                    }
                }
            }
        }
    }
    subPhase++;
    return phase;
}

//------------------------------------------------------------------------------

uint16_t Transition::transitionCountdown(struct tm &tm) {
    static uint8_t lastSecond = 99, countDown = 60;
    uint8_t _second = tm.tm_sec; // 0 - 59
    if (_second != lastSecond) {
        if (phase == 1) {
            transitionDelay = 50;
        }
        if (countDown < 0) { // 60 - 0
            countDown = 60;
            lastSecond = 99;
            transitionType = NEWYEAR;
            return 1; // continue FIRE in phase 1
        }
        lastSecond = _second;
        fillMatrix(work, background);
        HsbColor hsbColor_1 = HsbColor(foreground);
        HsbColor hsbColor_2 = HsbColor(foreground);
        hsbColor_1.H = pseudoRandomHue();
        hsbColor_2.H = pseudoRandomHue();
        char seconds[8];
        // start 23:59:00     60 - 0
        snprintf(seconds, sizeof(seconds), "%d", countDown);
        // for (uint8_t i = 0; i < 5; i++) {
        for (uint8_t row = 0; row < 8; row++) {     // row
            for (uint8_t col = 0; col < 5; col++) { // column
                if (countDown >= 10) {
                    // 1. Number without Offset
                    setPixelForChar(col, row, 0,
                                    static_cast<unsigned char>(seconds[0]),
                                    hsbColor_1);
                    // 2. Number with Offset
                    setPixelForChar(col, row, 6,
                                    static_cast<unsigned char>(seconds[1]),
                                    hsbColor_2);
                } else {
                    setPixelForChar(col, row, 3,
                                    static_cast<unsigned char>(seconds[0]),
                                    hsbColor_1);
                }
            }
        }
        countDown--;
        phase++;
    }
    return phase;
}

//------------------------------------------------------------------------------

void Transition::transitionColorChange() {
    static uint32_t lastTimeColor = 0;
    static uint32_t pauseZeitColor = 50;

    if (isColorization() && (G.transitionSpeed > 0)) {
        uint32_t now = millis();
        if (now >= (lastTimeColor + pauseZeitColor)) {
            lastTimeColor = now;
            float deltaHue = fmod(1.0 / (G.transitionSpeed * 20.0), 1.0);
            HsbColor hsbColor;
            for (uint8_t row = 0; row < maxRows; row++) {
                for (uint8_t col = 0; col < maxCols; col++) {
                    if (work[row][col].isForeground()) {
                        hsbColor = HsbColor(work[row][col]);
                        hsbColor.H = fmod(hsbColor.H + deltaHue, 1.0);
                        work[row][col].changeRgb(hsbColor);
                    }
                }
            }
            hsbColor = HsbColor(foregroundMinute);
            hsbColor.H = fmod(hsbColor.H + deltaHue, 1.0);
            foregroundMinute = RgbColor(hsbColor);
        }
    }
}

//------------------------------------------------------------------------------

uint16_t Transition::transitionLaser() {
    static uint8_t row = 0, col = 0;
    static bool loeschPhase = true;
    static RgbfColor strahl(255);

    if (phase == 1) {
        transitionDelay = calcDelay(maxRows * maxCols * 2);
        row = 0;
        col = 0;
        copyMatrix(work, old);
        loeschPhase = true;
    }

    if (loeschPhase) {
        work[row][col] = background;
    } else {
        work[row][col] = act[row][col];
    }

    if (++col >= maxCols) {
        col = 0;
        row++;
    }
    if (row < maxRows) {
        work[row][col] = strahl;
    } else {
        row = 0;
        if (loeschPhase == false) {
            return 0;
        }
        loeschPhase = false;
    }
    return phase + 1;
}

//------------------------------------------------------------------------------

uint16_t Transition::transitionFade() {
    uint16_t frames = 100;
    RgbColor color;

    if (phase == 1) {
        transitionDelay = calcDelay(frames);
        // copyMatrix(old, work);
    }
    float progress = static_cast<float>(phase) / static_cast<float>(frames);

    for (uint8_t col = 0; col < maxCols; col++) {
        for (uint8_t row = 0; row < maxRows; row++) {
            color = color.LinearBlend(old[row][col], act[row][col], progress);
            work[row][col].changeRgb(color);
        }
    }
    if (phase >= frames) {
        copyMatrix(work, act); // take all color.Foreground's from act
        return 0;
    }
    return phase + 1;
}

//------------------------------------------------------------------------------

uint16_t Transition::transitionMatrixRain() {
    uint16_t frames = 100;
    int8_t row, col;
    RgbfColor fadeColor;
    RgbaColor rainColor;

    if (phase == 1) {
        transitionDelay = calcDelay(frames);
        copyMatrix(old, work); // work is still the previous transition array
        uint8_t stop;
        uint8_t brightness = foreground.CalculateBrightness();
        for (col = 0; col < maxCols; col++) {
            stop = maxRows - 1;
            for (row = maxRows - 1; row >= 0; row--) {
                if (work[row][col].isForeground()) {
                    stop = row;
                    break;
                }
            }
            rain[col].begin(frames, stop, brightness);
        }
    }
    float progress = static_cast<float>(phase) / static_cast<float>(frames);
    for (col = 0; col < maxCols; col++) {
        for (row = 0; row < maxRows; row++) {
            fadeColor =
                fadeColor.LinearBlend(old[row][col], act[row][col], progress);
            rainColor = rain[col].get(row);
            rainColor = rainColor.LinearBlend(fadeColor, rainColor,
                                              rainColor.getAlpha());
            work[row][col].changeRgb(rainColor);
        }
    }
    if (phase >= frames) {
        copyMatrix(work, act); // take all color.Foreground's from act
        return 0;
    }
    return phase + 1;
}

//------------------------------------------------------------------------------

uint16_t Transition::transitionSnake() {
    uint16_t food = 40;

    if (phase == 1) {
        transitionDelay = calcDelay(food);
        snake->begin(this);
    }

    if (!snake->drawSnake()) {
        return 0;
    }
    return phase + 1;
}

//------------------------------------------------------------------------------
// Loop Helper Functions
//------------------------------------------------------------------------------

void Transition::demoMode(uint8_t &_minute, uint8_t _second) {
    static uint8_t test_second = 0;
    static uint8_t test_minute = 45;
    if (G.transitionDemo) {
        if (isIdle() && ((_second % 10) == 0) && (test_second != _second)) {
            test_minute += 5;
            if (test_minute >= 60) {
                test_minute = _minute % 5;
            }
        }
        _minute = test_minute;
        test_second = _second;
    }
}

//------------------------------------------------------------------------------

void Transition::initTransitionStart() {
    nextActionTime = 0;
    phase = 1;
}

//------------------------------------------------------------------------------

bool Transition::hasMinuteChanged() {
    if (lastMinute != _minute) {
        lastMinute = _minute;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// 'WordclockChanges::Parameters', e.g. color modifications -> Apply w/o Trans
// 'WordclockChanges::Minute', e.g. minute iterations -> Apply w/o Transition
// 'WordclockChanges::Words', e.g. word changes -> Apply with Transition

bool Transition::isOverwrittenByTransition(WordclockChanges changesInWordMatrix,
                                           uint8_t minute) {
    if (transitionType == NO_TRANSITION) {
        if (changesInWordMatrix != WordclockChanges::Parameters &&
            hasMinuteChanged()) {
            // Needed in Case the Transition is switched off
            matrixChanged = true;
        }
    } else {
        if (changesInWordMatrix != WordclockChanges::Parameters) {
            if (changesInWordMatrix == WordclockChanges::Words ||
                changesInWordMatrix == WordclockChanges::Layout) {
                initTransitionStart();
            }
            lastMinute = minute;
            matrixChanged = true;
            return false;
        } else {
            if (changeBrightness()) {
                copy2Stripe(work);
            }
            return isIdle();
        }
    }
    return true;
}

//------------------------------------------------------------------------------
// Loop Functions
//------------------------------------------------------------------------------

void Transition::loop(struct tm &tm) {
    if (matrixChanged) {
        matrixChanged = false;
        saveMatrix();
        copyMatrix(work, act);
    }

    if (G.prog == COMMAND_IDLE || G.prog == COMMAND_MODE_WORD_CLOCK) {
        if (!isSilvester(transitionType, tm, hasMinuteChanged())) {
            transitionType = getTransitionType(hasMinuteChanged());
        }

        if (transitionType == NO_TRANSITION) {
            if (lastTransitionType != NO_TRANSITION) {
                lastTransitionType = NO_TRANSITION;
                copyMatrix(work, act);
                colorize(work);
                copy2Stripe(work);
                led.show();
            }
        } else {
            if (changesInTransitionTypeDurationOrDemo()) {
                lastTransitionType = transitionType;
                lastTransitionDemo = G.transitionDemo;
                lastTransitionDuration = G.transitionDuration;
                phase = 1;
            }
            if (G.transitionColorize != lastTransitionColorize) {
                lastTransitionColorize = G.transitionColorize;
                colorize(isIdle() ? work : act);
            }

            uint32_t now = millis();
            if ((!isIdle()) && (now >= nextActionTime)) {
                nextActionTime = now + transitionDelay;
                // Serial.printf("Transition: type %d phase %d\n",
                // transitionType,phase);
                switch (transitionType) {
                case ROLL_UP:
                    phase = transitionScrollDown(false);
                    break;
                case ROLL_DOWN:
                    phase = transitionScrollDown(true);
                    break;
                case SHIFT_LEFT:
                    phase = transitionScrollRight(false);
                    break;
                case SHIFT_RIGHT:
                    phase = transitionScrollRight(true);
                    break;
                case FADE:
                    phase = transitionFade();
                    break;
                case LASER:
                    phase = transitionLaser();
                    break;
                case MATRIX_RAIN:
                    phase = transitionMatrixRain();
                    break;
                case BALLS:
                    phase = transitionBalls();
                    break;
                case NEWYEAR:
                case FIRE:
                    phase = transitionFire();
                    break;
                case SNAKE:
                    phase = transitionSnake();
                    break;
                case COUNTDOWN:
                    phase = transitionCountdown(tm);
                    break;
                case RANDOM:
                case NO_TRANSITION:
                    break;
                }
            }
            transitionColorChange();
            copy2Stripe(work);
            setMinute(); // TODO: Is setMinute() on the right place ?
            led.show();
        }
    }
}

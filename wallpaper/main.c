#include <raylib.h>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define BUFFER_SIZE 512   // smaller = lower latency

int main(void) {

    // CHANGE THIS to your monitor name
    const char *device = "bluez_output.80_C3_BA_76_FF_34.1.monitor";

    pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = 44100,
        .channels = 1
    };

    pa_buffer_attr attr;
    attr.fragsize = BUFFER_SIZE * sizeof(int16_t);
    attr.maxlength = -1;
    attr.minreq   = -1;
    attr.prebuf   = -1;
    attr.tlength  = -1;

    int error;
    pa_simple *pa = pa_simple_new(
        NULL, "RaylibVisualizer", PA_STREAM_RECORD,
        device, "record",
        &ss, &attr, NULL, &error
    );

    if (!pa) {
        fprintf(stderr, "PulseAudio error: %s\n", pa_strerror(error));
        return 1;
    }

    InitWindow(800, 450, "Raylib + PulseAudio (Low Latency)");
    SetTargetFPS(60);

    int16_t buffer[BUFFER_SIZE];

    while (!WindowShouldClose()) {

        if (pa_simple_read(pa, buffer, sizeof(buffer), &error) < 0) {
            printf("pa_simple_read: %s\n", pa_strerror(error));
            break;
        }

        float sum = 0;
        for (int i = 0; i < BUFFER_SIZE; i++) {
            float s = buffer[i] / 32768.0f;
            sum += s * s;
        }

        float rms = sqrtf(sum / BUFFER_SIZE);
        float bar = rms * 400;

        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(350, 450 - bar, 100, bar, GREEN);
        DrawText(device, 10, 10, 20, YELLOW);
        DrawText(TextFormat("RMS: %.3f", rms), 10, 40, 20, RAYWHITE);

        EndDrawing();
    }

    pa_simple_free(pa);
    CloseWindow();
    return 0;
}

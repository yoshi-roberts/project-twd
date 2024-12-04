#include "audio.h"
#include "../lib/raylib/src/raylib.h"
#include "log.h"

static float music_volume = 1.0f;
static bool muted = false;
static bool show_invalid_volume = false;
static float invalid_volume_timer = 0.0f;

static Asset* bg_music = NULL;

void audio_init() {
    InitAudioDevice();
    if (IsAudioDeviceReady()) {
        log_info("Audio device initialized successfully");
    } else {
        log_error("Failed to initialize audio device");
        return;
    }
    bg_music = assets_get("assets/audio/background.ogg");
    if (bg_music && bg_music->type == ASSET_AUDIO) {
        log_info("Audio loaded successfully");
        SetMusicVolume(bg_music->data.audio, music_volume);
        PlayMusicStream(bg_music->data.audio);
    } else {
        log_error("Failed to load background music");
    }
}

void audio_update() {
    if (bg_music && bg_music->type == ASSET_AUDIO) {
        UpdateMusicStream(bg_music->data.audio);
    } else {
        log_error("Background music not loaded");
    }

    if (show_invalid_volume) {
        invalid_volume_timer -= GetFrameTime();
        if (invalid_volume_timer <= 0.0f) {
            show_invalid_volume = false;
        }
    }
}

void audio_shutdown() {
    if (!IsAudioDeviceReady()) {
        log_error("Audio device not ready. Shutdown skipped.");
        return;
    }

    StopMusicStream(bg_music->data.audio);
    CloseAudioDevice();
    log_info("Audio device shut down.");
}

void audio_toggle_mute() {
    if (!bg_music || bg_music->type != ASSET_AUDIO) return;

    muted = !muted;
    SetMusicVolume(bg_music->data.audio, muted ? 0.0f : music_volume);
    if (muted) {
        PauseMusicStream(bg_music->data.audio);
    } else {
        ResumeMusicStream(bg_music->data.audio);
    }
}

void audio_increase_volume() {
    if (!bg_music || bg_music->type != ASSET_AUDIO) return;

    if (music_volume >= 1.0f) {
        show_invalid_volume = true;
        invalid_volume_timer = 1.5f;
    } else {
        music_volume += 0.1f;
        if (music_volume > 1.0f) music_volume = 1.0f;
        SetMusicVolume(bg_music->data.audio, music_volume);
    }
}

void audio_decrease_volume() {
    if (!bg_music || bg_music->type != ASSET_AUDIO) return;

    if (music_volume <= 0.0f) {
        show_invalid_volume = true;
        invalid_volume_timer = 1.5f;
    } else {
        music_volume -= 0.1f;
        if (music_volume < 0.0f) music_volume = 0.0f;
        SetMusicVolume(bg_music->data.audio, music_volume);
    }
}

void audio_draw_ui() {
    if (show_invalid_volume) {
        DrawText("Volume: X", 416, 260, 10, RED);
    } else {
		char volume_str[64];
		sprintf(volume_str, "Volume: %.0f%%", music_volume * 100);
		DrawText(volume_str, 416, 260, 10, WHITE);
	}
}
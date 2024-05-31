#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <allegro5/allegro_physfs.h>
#include <physfs.h>

struct Resource
{
    static ALLEGRO_FONT *builtin8;

    static ALLEGRO_BITMAP *genericTitlePng;
    static ALLEGRO_BITMAP *genericOverworldPng;
    static ALLEGRO_BITMAP *genericResultsPng;
    static ALLEGRO_BITMAP *genericBeingPng;
    static ALLEGRO_BITMAP *genericTilePng;

    static ALLEGRO_SAMPLE *genericBgmMp3;
    static ALLEGRO_SAMPLE_INSTANCE *genericBgmSampleInstance;
    static ALLEGRO_SAMPLE *genericPickupCoinWav;
    static ALLEGRO_SAMPLE_INSTANCE *genericPickupCoinSampleInstance;
    static ALLEGRO_SAMPLE *genericClickWav;
    static ALLEGRO_SAMPLE_INSTANCE *genericClickSampleInstance;
    static ALLEGRO_SAMPLE *genericLaserShootWav;
    static ALLEGRO_SAMPLE_INSTANCE *genericLaserShootSampleInstance;

    static bool Initialize(char **argv);
    static void Uninitialize();

private:
    static void LoadFontResources();
    static void LoadImageResources();
    static void LoadAudioResources();

    static void UnloadFontResources();
    static void UnloadImageResources();
    static void UnloadAudioResources();
};

#endif // RESOURCE_H_INCLUDED

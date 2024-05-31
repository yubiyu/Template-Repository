#include "resource.h"

ALLEGRO_FONT* Resource::builtin8;

ALLEGRO_BITMAP* Resource::genericTitlePng;
ALLEGRO_BITMAP* Resource::genericOverworldPng;
ALLEGRO_BITMAP* Resource::genericResultsPng;
ALLEGRO_BITMAP* Resource::genericBeingPng;
ALLEGRO_BITMAP* Resource::genericTilePng;

ALLEGRO_SAMPLE* Resource::genericBgmMp3;
ALLEGRO_SAMPLE_INSTANCE* Resource::genericBgmSampleInstance;
ALLEGRO_SAMPLE* Resource::genericPickupCoinWav;
ALLEGRO_SAMPLE_INSTANCE* Resource::genericPickupCoinSampleInstance;
ALLEGRO_SAMPLE* Resource::genericClickWav;
ALLEGRO_SAMPLE_INSTANCE* Resource::genericClickSampleInstance;
ALLEGRO_SAMPLE* Resource::genericLaserShootWav;
ALLEGRO_SAMPLE_INSTANCE* Resource::genericLaserShootSampleInstance;

bool Resource::Initialize(char **argv)
{
    PHYSFS_init(argv[0]);
    if(!PHYSFS_mount("./data.zip", "/", 1))
    {
        assert("data.zip not found");
        return false;
    }
    al_set_physfs_file_interface();

    LoadFontResources();
    LoadImageResources();
    LoadAudioResources();

    return true;
}

void Resource::Uninitialize()
{
    UnloadFontResources();
    UnloadImageResources();
    UnloadAudioResources();

    PHYSFS_deinit();
}

void Resource::LoadFontResources()
{
    builtin8 = al_create_builtin_font();
}

void Resource::LoadImageResources()
{
    genericTitlePng = al_load_bitmap("genericTitlePng.png");
    genericOverworldPng = al_load_bitmap("genericOverworldPng.png");
    genericResultsPng = al_load_bitmap("genericResultsPng.png");
    genericBeingPng = al_load_bitmap("genericBeingPng.png");
    genericTilePng = al_load_bitmap("genericTilePng.png");
}

void Resource::LoadAudioResources()
{
    al_reserve_samples(10);

    genericBgmMp3 = al_load_sample("genericBgmMp3.mp3");
    genericBgmSampleInstance = al_create_sample_instance(genericBgmMp3);
    al_attach_sample_instance_to_mixer(genericBgmSampleInstance, al_get_default_mixer());

    genericPickupCoinWav = al_load_sample("genericPickupCoinWav.wav");
    genericPickupCoinSampleInstance = al_create_sample_instance(genericPickupCoinWav);
    al_attach_sample_instance_to_mixer(genericPickupCoinSampleInstance, al_get_default_mixer());

    genericClickWav = al_load_sample("genericClickWav.wav");
    genericClickSampleInstance = al_create_sample_instance(genericClickWav);
    al_attach_sample_instance_to_mixer(genericClickSampleInstance, al_get_default_mixer());

    genericLaserShootWav = al_load_sample("genericLaserShootWav.wav");
    genericLaserShootSampleInstance = al_create_sample_instance(genericLaserShootWav);
    al_attach_sample_instance_to_mixer(genericLaserShootSampleInstance, al_get_default_mixer());
}

void Resource::UnloadFontResources()
{
    al_destroy_font(builtin8);
}

void Resource::UnloadImageResources()
{
    al_destroy_bitmap(genericTitlePng);
    al_destroy_bitmap(genericOverworldPng);
    al_destroy_bitmap(genericResultsPng);
    al_destroy_bitmap(genericBeingPng);
    al_destroy_bitmap(genericTilePng);
}

void Resource::UnloadAudioResources()
{
    al_destroy_sample_instance(genericBgmSampleInstance);
    al_destroy_sample(genericBgmMp3);

    al_destroy_sample_instance(genericPickupCoinSampleInstance);
    al_destroy_sample(genericPickupCoinWav);

    al_destroy_sample_instance(genericClickSampleInstance);
    al_destroy_sample(genericClickWav);

    al_destroy_sample_instance(genericLaserShootSampleInstance);
    al_destroy_sample(genericLaserShootWav);
}

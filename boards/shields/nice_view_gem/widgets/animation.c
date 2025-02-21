#include <stdlib.h>
#include <zephyr/kernel.h>
#include "animation.h"
#include <zephyr/kernel.h>



LV_IMG_DECLARE(goph1);
LV_IMG_DECLARE(goph2);
LV_IMG_DECLARE(goph3);
LV_IMG_DECLARE(goph4);
LV_IMG_DECLARE(goph5);
LV_IMG_DECLARE(goph6);
LV_IMG_DECLARE(goph7);
LV_IMG_DECLARE(goph8);
// LV_IMG_DECLARE(crystal_09);
// LV_IMG_DECLARE(crystal_10);
// LV_IMG_DECLARE(crystal_11);
// LV_IMG_DECLARE(crystal_12);
// LV_IMG_DECLARE(crystal_13);
// LV_IMG_DECLARE(crystal_14);
// LV_IMG_DECLARE(crystal_15);
// LV_IMG_DECLARE(crystal_16);

const lv_img_dsc_t *anim_imgs[] = {
  // look from left to right
    &goph1, &goph2, &goph3, &goph4, &goph5, 
    // right to middle
    &goph4, &goph3, 
    // surprise
    // &goph6, &goph7, &goph6, 
    // middle to left
    &goph3, &goph2,
};

// #include <stdlib.h>
// #include <lvgl.h>

// Function to restart the animation
static void restart_animation(lv_timer_t * timer) {
    lv_obj_t * art = (lv_obj_t *)timer->user_data; // Correct way to get user data
    lv_animimg_start(art); // Restart the animation

    // Schedule the next restart
    int delay = (rand() % 11 + 5) * 1000; // Random delay between 5s and 15s
    lv_timer_reset(timer);
    lv_timer_set_period(timer, delay);
}

// Function to create a timer for animation replay
static void schedule_animation_restart(lv_obj_t * art) {
    int delay = (rand() % 11 + 5) * 1000; // Random delay between 5s and 15s
    lv_timer_t * timer = lv_timer_create(restart_animation, delay, art);
}

void draw_animation(lv_obj_t *canvas) {
#if IS_ENABLED(CONFIG_NICE_VIEW_GEM_ANIMATION)
    lv_obj_t *art = lv_animimg_create(canvas);
    lv_obj_center(art);

    lv_animimg_set_src(art, (const void **)anim_imgs, 9);
    lv_animimg_set_duration(art, CONFIG_NICE_VIEW_GEM_ANIMATION_MS);
    lv_animimg_set_repeat_count(art, CONFIG_NICE_VIEW_GEM_ANIMATION_REPEAT);
    lv_animimg_start(art);

    // Schedule animation restart after a random delay
    schedule_animation_restart(art);

    lv_img_set_src(art, anim_imgs[0]);

#else
    lv_obj_t *art = lv_img_create(canvas);

    int length = sizeof(anim_imgs) / sizeof(anim_imgs[0]);
    srand(k_uptime_get_32());
    int random_index = rand() % length;

    lv_img_set_src(art, anim_imgs[random_index]);
#endif

    lv_obj_align(art, LV_ALIGN_TOP_LEFT, -65, 0);
}
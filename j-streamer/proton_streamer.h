// #include <bits/pthreadtypes.h>
#include <semaphore.h>
#define NUM_STREAMER_TEXTURES (4)

struct proton_streamer_shm {
  int texture_width;
  int texture_height;
  int texture_size;
  
  int texture_fd_array[NUM_STREAMER_TEXTURES];
  
  sem_t new_texture;
  pthread_mutex_t latest_texture_lock;
  int latest_texture;

  pthread_mutex_t texture_locks[NUM_STREAMER_TEXTURES];
};

__cdecl struct proton_streamer_shm *allocate_proton_streamer_shm();

__cdecl void proton_streamer_signal_new_texture(struct proton_streamer_shm *shm, int texture);

__cdecl void proton_streamer_get_output_texture(struct proton_streamer_shm *shm, int *out_texture);



#include "proton_streamer.h"

#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <memory.h>
#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>

#include <windef.h>
#include <stdint.h>
#include <pthread.h>

 struct proton_streamer_shm * WINAPI allocate_proton_streamer_shm() {
  char shm_name[256];
  int len = sprintf(shm_name, "/proton_streamer_%lu", (uint64_t)getpid());
  shm_name[len] = 0;
  
  shm_unlink(shm_name);
  int shm_handle = shm_open(shm_name, O_CREAT | O_RDWR, 0);
  if (shm_handle == -1) {
    exit(1);
  }

  printf("ShmHandle open success\n");

  if (ftruncate(shm_handle, sizeof(struct proton_streamer_shm)) == -1) {
    printf("Failed to truncate gamescope shm buff\n");
    exit(1);
  }

  printf("FTruncate success\n");

  struct proton_streamer_shm *shmbuf = (struct proton_streamer_shm *)mmap(
      NULL, sizeof(struct proton_streamer_shm ), PROT_READ | PROT_WRITE, MAP_SHARED,
      shm_handle, 0);

  if (shmbuf == MAP_FAILED) {
    printf("Failed to mmap gamescope shm buff\n");
    exit(1);
  }

  memset(shmbuf, 0, sizeof(struct proton_streamer_shm ));

  for(int i = 0; i < NUM_STREAMER_TEXTURES; ++i) {
    pthread_mutexattr_t att;
    pthread_mutexattr_init(&att);
    // pthread_mutexattr_setrobust(&att, PTHREAD_MUTEX_ROBUST);
    pthread_mutexattr_setpshared(&att, PTHREAD_PROCESS_SHARED);
    if(pthread_mutex_init(&shmbuf->texture_locks[i], &att) == -1) {
      printf("Failed to initialize shmbuf lock\n");
      exit(1);
    }
  }

  pthread_mutexattr_t att;
  pthread_mutexattr_init(&att);
  // pthread_mutexattr_setrobust(&att, PTHREAD_MUTEX_ROBUST);
  pthread_mutexattr_setpshared(&att, PTHREAD_PROCESS_SHARED);
  if(pthread_mutex_init(&shmbuf->latest_texture_lock, &att) == -1) {
    printf("Failed to initialize shmbuf lock\n");
    exit(1);
  }


  if (sem_init(&shmbuf->new_texture, 1, 0) == -1) {
      printf("Failed to allocate sem\n");
      exit(1);
  }


  
  return shmbuf;
}

void WINAPI proton_streamer_signal_new_texture(struct proton_streamer_shm *shm, int texture) {
  // Signal the texture

  // printf("Attemping to unlock: %i\n", texture);
  int unlock = pthread_mutex_unlock(&shm->texture_locks[texture]);
  // printf("Unlock: %i %i\n", texture, unlock);

  pthread_mutex_lock(&shm->latest_texture_lock);
  shm->latest_texture = texture;
  pthread_mutex_unlock(&shm->latest_texture_lock);
  
  sem_post(&shm->new_texture);
}

void WINAPI proton_streamer_get_output_texture(struct proton_streamer_shm *shm, int *out_texture) {
  pthread_mutex_lock(&shm->latest_texture_lock); 
  for(int i = 0; i < NUM_STREAMER_TEXTURES; ++i) {

    // printf("Attemping to lock: %i\n", i);
    int lck_result = pthread_mutex_trylock(&shm->texture_locks[i]); 
    if(lck_result == 0) {
      // printf("Locked %i\n", i);
      *out_texture = i;
      pthread_mutex_unlock(&shm->latest_texture_lock); 
      return;
    }

  }

  *out_texture = -1;
  pthread_mutex_unlock(&shm->latest_texture_lock); 
}




// wafer.h - code for writing 8-bit PCM WAVE files

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Byte that is not available yet
#define NA 0

// Byte extractors
#define B0(i) i       & 255
#define B1(i) i >>  8 & 255
#define B2(i) i >> 16 & 255
#define B3(i) i >> 24 & 255

typedef struct wafer_file {
  FILE     *std_file;
  uint32_t data_size;
  uint32_t samples_per_sec;
  uint16_t channels;
} wafer_file;

static wafer_file *wafer_open(const char filename[]) {
  wafer_file *file = malloc(sizeof *file);

  if (!file)
    return 0;

  file->data_size = 0;
  file->std_file = fopen(filename, "wb");
  return file->std_file ? file : 0;
}

static void wafer_set_channels(wafer_file *file, uint16_t channels) {
  file->channels = channels;
}

static void wafer_set_samples_per_sec(wafer_file *file, uint32_t samples_per_sec) {
  file->samples_per_sec = samples_per_sec;
}

static _Bool wafer_write_metadata(wafer_file *file) {
  uint32_t avg_bytes_per_sec = file->channels * file->samples_per_sec;
  uint16_t block_align = file->channels;

  uint8_t header[44] = {
    82,                        73,                        70,                        70, // 'RIFF'
    NA,                        NA,                        NA,                        NA, // RIFF-chunk size
    87,                        65,                        86,                        69, // 'WAVE'
    102,                       109,                       116,                       32, // 'fmt '
    16,                        0,                         0,                         0,  // fmt-chunk size
    1,                         0,                                                        // WAVE_FORMAT_PCM
    B0(file->channels),        B1(file->channels),
    B0(file->samples_per_sec), B1(file->samples_per_sec), B2(file->samples_per_sec), B3(file->samples_per_sec),
    B0(avg_bytes_per_sec),     B1(avg_bytes_per_sec),     B2(avg_bytes_per_sec),     B3(avg_bytes_per_sec),
    B0(block_align),           B1(block_align),
    8,                         0,                                                        // Bits per sample
    100,                       97,                        116,                       97, // 'data'
    NA,                        NA,                        NA,                        NA  // data-chunk size
  };

  return fwrite(header, 1, 44, file->std_file) == 44;
}

static _Bool wafer_write_data(const uint8_t data[], uint32_t len, wafer_file *file) {
  uint32_t written = fwrite(data, 1, len, file->std_file);
  file->data_size += written;
  return written == len;
}

static _Bool wafer_close(wafer_file *file) {
  uint32_t form_size = 36 + file->data_size;

  uint8_t riff_chunk_size[4] = {
    B0(form_size),
    B1(form_size),
    B2(form_size),
    B3(form_size)
  };

  uint8_t data_chunk_size[4] = {
    B0(file->data_size),
    B1(file->data_size),
    B2(file->data_size),
    B3(file->data_size)
  };

  if (file->data_size & 1 && fwrite(&((uint8_t) {0}), 1, 1, file->std_file) != 1 ||
      fseek(file->std_file, 40, SEEK_SET) ||
      fwrite(data_chunk_size, 1, 4, file->std_file) != 4 ||
      fseek(file->std_file, 4, SEEK_SET) ||
      fwrite(riff_chunk_size, 1, 4, file->std_file) != 4 ||
      fclose(file->std_file) == EOF)
    return 0;

  free(file);
  return 1;
}

#undef NA
#undef B0
#undef B1
#undef B2
#undef B3

#ifndef __WAVE_H__
#define __WAVE_H__

/**
 * Simple wave file I/O library
 *
 * Author: Zhaosheng Pan <brglng at gmail dot com>
 *
 * The API is similar to fopen/fclose/freopen/fread/fwrite/ftell/fseek/feof/ferror/fflush/rewind
 *
 * This library does not support:
 *  - formats other than PCM, IEEE float and log-PCM
 *  - extra chunks after the data chunk
 *  - big endian platforms (might be supported in the future)
 *
 * Must use WaveFile* . WaveFile objects on the stack is not supported,
 * as the size of the struct is not available at compile time. This is intended
 * because the access to the internal of the struct is forbidden, so as to prevent
 * errors.
 *
 */

#ifdef __cpluscplus
extern "C" {
#endif

#include "wave_defs.h"

WaveFile*   wave_open(char* filename, char* mode);
int         wave_close(WaveFile* wave);
WaveFile*   wave_reopen(char* filename, char* mode, WaveFile* wave);

/** function:       wave_read
 *  description:    Read a block of samples from the wave file
 *  parameters:
 *      buffers:    A list of pointers to a buffer where the data of each single channel will be placed
 *      count:      The number of frames (block size)
 *      wave:       The pointer to the WaveFile structure
 *  return:         The number of frames read
 *                  If returned value < {count}, either EOF reached or an error occured
 *  remarks:        This API does not support extensible format.
 *                  For extensible format, use {wave_read_raw} instead.
 */
size_t      wave_read(void** buffers, size_t count, WaveFile* wave);

/** function:       wave_write
 *  description:    Write a block of samples to the wave file
 *  parameters:
 *      buffers:    A list of pointers to a buffer of the data of a single channel.
 *      count:      The number of frames (block size)
 *      wave:       The pointer to the WaveFile structure
 *  return:         The number of frames written
 *                  If returned value < {count}, either EOF reached or an error occured.
 *  remarks:        This API does not support extensible format.
 *                  For extensible format, use {wave_read_raw} instead.
 */
size_t      wave_write(void** buffers, size_t count, WaveFile* wave);

/** function:       wave_tell
 *  description:    Tell the current position in the wave file.
 *  parameters:
 *      wave:       The pointer to the WaveFile structure.
 *  return:         The current frame number.
 */
long int    wave_tell(WaveFile* wave);

int         wave_seek(WaveFile* wave, long int offset, int origin);
void        wave_rewind(WaveFile* wave);

/** function:       wave_eof
 *  description:    Tell if the end of the wave file is reached.
 *  parameters:
 *      wave:       The pointer to the WaveFile structure.
 *  return:         Non-zero integer if the end of the wave file is reached,
 *                  otherwise zero.
 */
int         wave_eof(WaveFile* wave);

/** function:       wave_error
 *  description:    Tell if an error occurred in the last operation
 *  parameters:
 *      wave:       The pointer to the WaveFile structure
 *  return:         Non-zero if there is an error, otherwise zero
 */
int         wave_error(WaveFile* wave);

int         wave_flush(WaveFile* wave);

/** function:       wave_set_format
 *  description:    Set the format code
 *  parameters:
 *      self:       The WaveFile object
 *      format:     The format code, which should be one of WAVE_FORMAT_*
 *  return:         None
 *  remarks:        All data will be cleared after the call
 *                  {wave_get_last_error} can be used to get the error code if there is an error.
 */
void        wave_set_format(WaveFile* self, WaveUInt16 format);

/** function:       wave_set_n_channels
 *  description:    Set the number of channels
 *  parameters:
 *      self:           The WaveFile object
 *      n_channels:     The number of channels
 *  return:         None
 *  remarks:        All data will be cleared after the call
 *                  {wave_get_last_error} can be used to get the error code if there is an error.
 */
void        wave_set_n_channels(WaveFile* self, WaveUInt16 n_channels);

/** function:       wave_set_sample_rate
 *  description:    Set the sample rate
 *  parameters:
 *      self:           The WaveFile object
 *      sample_rate:    The sample rate
 *  return:         None
 *  remarks:        All data will be cleared after the call
 *                  {wave_get_last_error} can be used to get the error code if there is an error.
 */
void        wave_set_sample_rate(WaveFile* self, WaveUInt16 sample_rate);

/** function:       wave_set_valid_bits_per_sample
 *  description:    get the number of valid bits per sample
 *  parameters:
 *      self:       The WaveFile object
 *      bits:       The value of valid bits to set
 *  return:         None
 *  remarks:        If {bits} is 0 or larger than 8*{sample_size}, an error will occur.
 *                  All data will be cleared after the call.
 *                  {wave_get_last_error} can be used to get the error code if there is an error.
 */
void        wave_set_valid_bits_per_sample(WaveFile* self, WaveUInt16 bits);

/** function:       wave_set_sample_size
 *  description:    Set the size (in bytes) per sample
 *  parameters:
 *      self:           the WaveFile object
 *      sample_size:    the sample size value
 *  return:         None
 *  remarks:        When this function is called, the {BitsPerSample} and {ValidBitsPerSample}
 *                  fields in the wave file will be set to 8*{sample_size}.
 *                  All data will be cleared after the call.
 *                  {wave_get_last_error} can be used to get the error code if there is an error.
 */
void        wave_set_sample_size(WaveFile* self, size_t sample_size);

/**
 */
WaveUInt16  wave_get_format(WaveFile* self);
WaveUInt16  wave_get_n_channels(WaveFile* self);
WaveUInt32  wave_get_sample_rate(WaveFile* self);
WaveUInt32  wave_get_valid_bits_per_sample(WaveFile* self);
size_t      wave_get_sample_size(WaveFile* self);
size_t      wave_get_length(WaveFile* self);

/** function:       wave_get_last_error
 *  description:    Get the error code of the last operation.
 *  parameters:
 *      self        The pointer to the WaveFile structure.
 *  return:         A WaveError value, see {enum _WaveError}.
 */
WaveError   wave_get_last_error(WaveFile* self);

#ifdef __cplusplus
}
#endif

#endif /* __WAVE_H__ */

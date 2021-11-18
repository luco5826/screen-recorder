
#ifndef SCREENRECORDER_FFMPEG_H
#define SCREENRECORDER_FFMPEG_H

#pragma warning(disable : 4819)
#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <ctime>
#include <iomanip>

extern "C"
{
#define __STDC_CONSTANT_MACROS
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavutil/avutil.h>
#include <libavutil/file.h>
#include <libavutil/time.h>
#include <libavutil/audio_fifo.h>
#include <libavutil/imgutils.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
}

#endif //SCREENRECORDER_FFMPEG_H

#ifndef AUDIORECORDER_AUDIORECORDER_H
#define AUDIORECORDER_AUDIORECORDER_H

#ifdef WINDOWS
#include "ListAVDevices.h"
#endif

#include <string>
#include <cstdint>
#ifdef __linux__
#include <atomic>
#include <thread>
#endif

using std::string;

class ScreenRecorder
{

private:
  int width, height, framerate;
  string outfile;
  string deviceName;
  string failReason;

  AVFormatContext *audioInFormatCtx = nullptr;
  AVStream *audioInStream = nullptr;
  AVCodecContext *audioInCodecCtx = nullptr;

  AVFormatContext *videoInFormatCtx = nullptr;
  AVStream *videoInStream = nullptr;
  AVCodecContext *videoInCodecCtx = nullptr;

  SwrContext *audioConverter = nullptr;
  AVAudioFifo *audioFifo = nullptr;

  AVFormatContext *outFormatCtx = nullptr;

  AVStream *audioOutStream = nullptr;
  AVCodecContext *audioOutCodecCtx = nullptr;
  AVStream *videoOutStream = nullptr;
  AVCodecContext *videoOutCodecCtx = nullptr;

  std::atomic_bool isRun, isPaused;
  std::thread workerThread;

public:
  ScreenRecorder(string filepath, string device)
      : outfile(filepath), deviceName(device), failReason(""), isRun(false), isPaused(false) {}

  void Init();
  void OpenAudio();
  void OpenVideo(int x = 0, int y = 0, int width = 800, int height = 600, int framerate = 30);
  void Start();
  void Stop();
  void SetPaused(bool paused);

  ~ScreenRecorder()
  {
  }

  std::string GetLastError() { return failReason; }

private:
  void StartEncode();
  AVStream *getStreamByMediaType(AVFormatContext *context, AVMediaType type);
};
#endif

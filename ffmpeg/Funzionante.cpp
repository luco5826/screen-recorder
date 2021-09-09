
#ifndef AUDIORECORDER_FFMPEG_H
#define AUDIORECORDER_FFMPEG_H

#pragma warning(disable : 4819)
#include <exception>
#include <stdexcept>
#include <iostream>

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

#endif //AUDIORECORDER_FFMPEG_H

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

class AudioRecorder
{

private:
  string outfile;
  string deviceName;
  string failReason;

  AVFormatContext *audioInFormatCtx;
  AVStream *audioInStream;
  AVCodecContext *audioInCodecCtx;

  AVFormatContext *videoInFormatCtx;
  AVStream *videoInStream;
  AVCodecContext *videoInCodecCtx;

  SwrContext *audioConverter;
  AVAudioFifo *audioFifo;

  AVFormatContext *outFormatCtx;

  AVStream *audioOutStream;
  AVCodecContext *audioOutCodecCtx;
  AVStream *videoOutStream;
  AVCodecContext *videoOutCodecCtx;

  std::atomic_bool isRun;
  std::thread *audioThread;

  void StartEncode();

public:
  AudioRecorder(string filepath, string device)
      : outfile(filepath), deviceName(device), failReason(""), isRun(false) {}

  void Init();
  void OpenAudio();
  void OpenVideo();
  void Start();
  void Stop();

  // ~AudioRecorder()
  // {
  //   Stop();
  // }

  std::string GetLastError() { return failReason; }
};
#endif //AUDIORECORDER_AUDIORECORDER_H

#ifdef __linux__
#include <assert.h>
#endif

const AVSampleFormat requireAudioFmt = AV_SAMPLE_FMT_FLTP;

void AudioRecorder::OpenAudio()
{
  // input context

  AVDictionary *options = nullptr;
  audioInFormatCtx = nullptr;
  int ret;

  //ref: https://ffmpeg.org/ffmpeg-devices.html
#ifdef WINDOWS
  if (deviceName == "")
  {
    deviceName = DS_GetDefaultDevice("a");
    if (deviceName == "")
    {
      throw std::runtime_error("Fail to get default audio device, maybe no microphone.");
    }
  }
  deviceName = "audio=" + deviceName;
  AVInputFormat *inputFormat = av_find_input_format("dshow");
#elif MACOS
  if (deviceName == "")
    deviceName = ":0";
  AVInputFormat *inputFormat = av_find_input_format("avfoundation");
  //"[[VIDEO]:[AUDIO]]"
#elif __linux
  if (deviceName == "")
    deviceName = "default";
  AVInputFormat *inputFormat = av_find_input_format("pulse");
#endif

  ret = avformat_open_input(&audioInFormatCtx, deviceName.c_str(), inputFormat, &options);
  if (ret != 0)
  {
    throw std::runtime_error("Couldn't open input audio stream.");
  }

  if (avformat_find_stream_info(audioInFormatCtx, nullptr) < 0)
  {
    throw std::runtime_error("Couldn't find audio stream information.");
  }

  audioInStream = nullptr;
  for (int i = 0; i < audioInFormatCtx->nb_streams; i++)
  {
    if (audioInFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
    {
      audioInStream = audioInFormatCtx->streams[i];
      break;
    }
  }
  if (!audioInStream)
  {
    throw std::runtime_error("Couldn't find a audio stream.");
  }

  AVCodec *audioInCodec = avcodec_find_decoder(audioInStream->codecpar->codec_id);
  audioInCodecCtx = avcodec_alloc_context3(audioInCodec);
  avcodec_parameters_to_context(audioInCodecCtx, audioInStream->codecpar);

  if (avcodec_open2(audioInCodecCtx, audioInCodec, nullptr) < 0)
    throw std::runtime_error("Could not open audio codec.");

  // audio converter, convert other fmt to requireAudioFmt
  audioConverter = swr_alloc_set_opts(nullptr,
                                      av_get_default_channel_layout(audioInCodecCtx->channels),
                                      requireAudioFmt, // aac encoder only receive this format
                                      audioInCodecCtx->sample_rate,
                                      av_get_default_channel_layout(audioInCodecCtx->channels),
                                      (AVSampleFormat)audioInStream->codecpar->format,
                                      audioInStream->codecpar->sample_rate,
                                      0, nullptr);
  swr_init(audioConverter);

  // 2 seconds FIFO buffer
  audioFifo = av_audio_fifo_alloc(requireAudioFmt, audioInCodecCtx->channels,
                                  audioInCodecCtx->sample_rate * 2);

  //--------------------------------------------------------------------------
  // output context

  AVCodec *audioOutCodec = avcodec_find_encoder(AV_CODEC_ID_AAC);
  if (!audioOutCodec)
    throw std::runtime_error("Fail to find aac encoder. Please check your DLL.");

  audioOutCodecCtx = avcodec_alloc_context3(audioOutCodec);
  audioOutCodecCtx->channels = audioInStream->codecpar->channels;
  audioOutCodecCtx->channel_layout = av_get_default_channel_layout(audioInStream->codecpar->channels);
  audioOutCodecCtx->sample_rate = audioInStream->codecpar->sample_rate;
  audioOutCodecCtx->sample_fmt = audioOutCodec->sample_fmts[0]; //for aac , there is AV_SAMPLE_FMT_FLTP =8
  audioOutCodecCtx->bit_rate = 48000;
  audioOutCodecCtx->time_base.num = 1;
  audioOutCodecCtx->time_base.den = audioOutCodecCtx->sample_rate;

  int res = avcodec_open2(audioOutCodecCtx, audioOutCodec, NULL);
  if (res < 0)
  {
    throw std::runtime_error("Fail to open ouput audio encoder.");
  }

  //Add a new stream to output,should be called by the user before avformat_write_header() for muxing
  audioOutStream = avformat_new_stream(outFormatCtx, audioOutCodec);

  if (audioOutStream == NULL)
  {
    throw std::runtime_error("Fail to new a audio stream.");
  }
  avcodec_parameters_from_context(audioOutStream->codecpar, audioOutCodecCtx);
}

void AudioRecorder::OpenVideo()
{
  // input context

  AVDictionary *options = nullptr;
  av_dict_set(&options, "video_size", "1920x1080", 0);
  av_dict_set(&options, "show_region", "1", 0);
  av_dict_set(&options, "framerate", "30", 0);
  videoInFormatCtx = nullptr;
  int ret;

  //ref: https://ffmpeg.org/ffmpeg-devices.html
#ifdef WINDOWS
  if (deviceName == "")
  {
    deviceName = DS_GetDefaultDevice("a");
    if (deviceName == "")
    {
      throw std::runtime_error("Fail to get default audio device, maybe no microphone.");
    }
  }
  deviceName = "audio=" + deviceName;
  AVInputFormat *inputFormat = av_find_input_format("dshow");
#elif MACOS
  if (deviceName == "")
    deviceName = ":0";
  AVInputFormat *inputFormat = av_find_input_format("avfoundation");
  //"[[VIDEO]:[AUDIO]]"
#elif __linux
  deviceName = ":0.0+1080,1000";
  AVInputFormat *inputFormat = av_find_input_format("x11grab");
#endif

  ret = avformat_open_input(&videoInFormatCtx, deviceName.c_str(), inputFormat, &options);
  if (ret != 0)
  {
    throw std::runtime_error("Couldn't open input video stream.");
  }

  if (avformat_find_stream_info(videoInFormatCtx, nullptr) < 0)
  {
    throw std::runtime_error("Couldn't find video stream information.");
  }

  videoInStream = nullptr;
  for (int i = 0; i < videoInFormatCtx->nb_streams; i++)
  {
    if (videoInFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
    {
      videoInStream = videoInFormatCtx->streams[i];
      break;
    }
  }
  if (!videoInStream)
  {
    throw std::runtime_error("Couldn't find a video stream.");
  }

  AVCodec *videoInCodec = avcodec_find_decoder(videoInStream->codecpar->codec_id);
  videoInCodecCtx = avcodec_alloc_context3(videoInCodec);
  avcodec_parameters_to_context(videoInCodecCtx, videoInStream->codecpar);

  if (avcodec_open2(videoInCodecCtx, videoInCodec, nullptr) < 0)
    throw std::runtime_error("Could not open video codec.");

  //--------------------------------------------------------------------------
  // output context

  AVCodec *videoOutCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
  if (!videoOutCodec)
    throw std::runtime_error("Fail to find aac encoder. Please check your DLL.");

  videoOutCodecCtx = avcodec_alloc_context3(videoOutCodec);
  // videoOutCodecCtx->channels = videoInStream->codecpar->channels;
  // videoOutCodecCtx->channel_layout = av_get_default_channel_layout(videoInStream->codecpar->channels);
  // videoOutCodecCtx->sample_rate = videoInStream->codecpar->sample_rate;
  // videoOutCodecCtx->sample_fmt = videoOutCodec->sample_fmts[0]; //for aac , there is AV_SAMPLE_FMT_FLTP =8
  videoOutCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
  videoOutCodecCtx->bit_rate = 1200000;
  videoOutCodecCtx->width = 1920;
  videoOutCodecCtx->height = 1080;
  videoOutCodecCtx->time_base = (AVRational){1, 30};
  // videoOutCodecCtx->time_base = videoInCodecCtx->time_base;
  // videoOutCodecCtx->time_base.num = 1;
  // videoOutCodecCtx->time_base.den = videoOutCodecCtx->sample_rate;

  if (avcodec_open2(videoOutCodecCtx, videoOutCodec, NULL) < 0)
  {
    throw std::runtime_error("Fail to open ouput video encoder.");
  }

  //Add a new stream to output,should be called by the user before avformat_write_header() for muxing
  videoOutStream = avformat_new_stream(outFormatCtx, videoOutCodec);

  if (videoOutStream == NULL)
  {
    throw std::runtime_error("Fail to new a video stream.");
  }
  avcodec_parameters_from_context(videoOutStream->codecpar, videoOutCodecCtx);
}

void AudioRecorder::Init()
{
  int ret = 0;
  ret = avformat_alloc_output_context2(&outFormatCtx, NULL, "mp4", NULL);
  if (ret < 0)
  {
    throw std::runtime_error("Failed to alloc ouput context");
  }

  ret = avio_open(&outFormatCtx->pb, outfile.c_str(), AVIO_FLAG_WRITE);
  if (ret < 0)
  {
    throw std::runtime_error("Fail to open output file.");
  }
}

void AudioRecorder::Start()
{

  // write file header
  if (outFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
    audioOutCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
  if (avformat_write_header(outFormatCtx, NULL) < 0)
  {
    throw std::runtime_error("Fail to write header for audio.");
  }

  av_dump_format(audioInFormatCtx, 0, NULL, 0);
  av_dump_format(videoInFormatCtx, 0, NULL, 0);
  av_dump_format(outFormatCtx, 0, NULL, 1);
  audioThread = new std::thread([this]()
                                {
                                  this->isRun = true;
                                  puts("Start record.");
                                  fflush(stdout);
                                  try
                                  {
                                    this->StartEncode();
                                  }
                                  catch (std::exception e)
                                  {
                                    this->failReason = e.what();
                                  }
                                });
}

void AudioRecorder::Stop()
{
  bool r = isRun.exchange(false);
  if (!r)
    return; //avoid run twice
  audioThread->join();

  int ret = av_write_trailer(outFormatCtx);
  if (ret < 0)
    throw std::runtime_error("can not write file trailer.");
  avio_close(outFormatCtx->pb);

  swr_free(&audioConverter);
  av_audio_fifo_free(audioFifo);

  avcodec_free_context(&audioInCodecCtx);
  avcodec_free_context(&audioOutCodecCtx);

  avformat_close_input(&audioInFormatCtx);
  avformat_free_context(outFormatCtx);
  puts("Stop record.");
  fflush(stdout);
}

void AudioRecorder::StartEncode()
{
  int ret;
  AVFrame *inputFrame = av_frame_alloc();
  AVPacket *inputPacket = av_packet_alloc();

  AVFrame *outputFrame = av_frame_alloc();
  outputFrame->format = AV_PIX_FMT_YUV420P;
  outputFrame->width = 1920;
  outputFrame->height = 1080;
  ret = av_frame_get_buffer(outputFrame, 0);
  if (ret < 0)
  {
    throw std::runtime_error("Unable to allocate video frame");
  }
  AVPacket *outputPacket = av_packet_alloc();
  uint64_t audioFrameCount = 0;
  uint64_t videoFrameCount = 0;

  int64_t nextVideoPTS = 0, nextAudioPTS = 0;

  auto swsContext = sws_getContext(1920, 1080, videoInCodecCtx->pix_fmt, 1920, 1080, AV_PIX_FMT_YUV420P, SWS_BICUBIC, 0, 0, 0);
  while (isRun)
  {
    int choice = av_compare_ts(nextVideoPTS, videoOutStream->time_base, nextAudioPTS, audioOutStream->time_base);
    if (choice == -1)
    {
      // Video packet
      av_read_frame(videoInFormatCtx, inputPacket);
      avcodec_send_packet(videoInCodecCtx, inputPacket);
      avcodec_receive_frame(videoInCodecCtx, inputFrame);

      sws_scale(swsContext, inputFrame->data, inputFrame->linesize, 0, 1080, outputFrame->data, outputFrame->linesize);
      outputFrame->pts = videoFrameCount++ * videoOutStream->time_base.den / 30;

      avcodec_send_frame(videoOutCodecCtx, outputFrame);
      if (avcodec_receive_packet(videoOutCodecCtx, outputPacket) == AVERROR(EAGAIN))
        continue;

      outputPacket->stream_index = videoOutStream->index;
      outputPacket->duration = 0; //videoOutStream->time_base.den / 30;
      outputPacket->dts = outputPacket->pts = videoFrameCount * videoOutStream->time_base.den / 30;
      std::cerr << "\tVideo::PTS (" << outputFrame->pts << ") timebase " << videoOutStream->time_base.num << "/" << videoOutStream->time_base.den << " real: " << (outputPacket->pts / (double)videoOutStream->time_base.den) << std::endl;
      nextVideoPTS = outputFrame->pts;
      av_write_frame(outFormatCtx, outputPacket);
    }
    else
    {
      //  decoding
      ret = av_read_frame(audioInFormatCtx, inputPacket);
      if (ret < 0)
      {
        throw std::runtime_error("can not read frame");
      }
      ret = avcodec_send_packet(audioInCodecCtx, inputPacket);
      if (ret < 0)
      {
        throw std::runtime_error("can not send pkt in decoding");
      }
      ret = avcodec_receive_frame(audioInCodecCtx, inputFrame);
      if (ret < 0)
      {
        throw std::runtime_error("can not receive frame in decoding");
      }
      //--------------------------------
      // encoding

      uint8_t **cSamples = nullptr;
      ret = av_samples_alloc_array_and_samples(&cSamples, NULL, audioOutCodecCtx->channels, inputFrame->nb_samples, requireAudioFmt, 0);
      if (ret < 0)
      {
        throw std::runtime_error("Fail to alloc samples by av_samples_alloc_array_and_samples.");
      }
      ret = swr_convert(audioConverter, cSamples, inputFrame->nb_samples, (const uint8_t **)inputFrame->extended_data, inputFrame->nb_samples);
      if (ret < 0)
      {
        throw std::runtime_error("Fail to swr_convert.");
      }
      if (av_audio_fifo_space(audioFifo) < inputFrame->nb_samples)
        throw std::runtime_error("audio buffer is too small.");

      ret = av_audio_fifo_write(audioFifo, (void **)cSamples, inputFrame->nb_samples);
      if (ret < 0)
      {
        throw std::runtime_error("Fail to write fifo");
      }

      av_freep(&cSamples[0]);

      av_frame_unref(inputFrame);
      av_packet_unref(inputPacket);

      while (av_audio_fifo_size(audioFifo) >= audioOutCodecCtx->frame_size)
      {
        AVFrame *outputFrame = av_frame_alloc();
        outputFrame->nb_samples = audioOutCodecCtx->frame_size;
        outputFrame->channels = audioInCodecCtx->channels;
        outputFrame->channel_layout = av_get_default_channel_layout(audioInCodecCtx->channels);
        outputFrame->format = requireAudioFmt;
        outputFrame->sample_rate = audioOutCodecCtx->sample_rate;

        ret = av_frame_get_buffer(outputFrame, 0);
        assert(ret >= 0);
        ret = av_audio_fifo_read(audioFifo, (void **)outputFrame->data, audioOutCodecCtx->frame_size);
        assert(ret >= 0);

        outputFrame->pts = audioFrameCount * audioOutStream->time_base.den * audioOutCodecCtx->frame_size / audioOutCodecCtx->sample_rate;

        ret = avcodec_send_frame(audioOutCodecCtx, outputFrame);
        if (ret < 0)
        {
          throw std::runtime_error("Fail to send frame in encoding");
        }
        av_frame_free(&outputFrame);
        ret = avcodec_receive_packet(audioOutCodecCtx, outputPacket);
        if (ret == AVERROR(EAGAIN))
        {
          continue;
        }
        else if (ret < 0)
        {
          throw std::runtime_error("Fail to receive packet in encoding");
        }

        outputPacket->stream_index = audioOutStream->index;
        outputPacket->duration = audioOutStream->time_base.den * audioOutCodecCtx->frame_size / audioOutCodecCtx->sample_rate;
        outputPacket->dts = outputPacket->pts = audioFrameCount * audioOutStream->time_base.den * audioOutCodecCtx->frame_size / audioOutCodecCtx->sample_rate;

        audioFrameCount++;
        nextAudioPTS = outputPacket->pts;
        std::cerr << "Audio::PTS (" << nextAudioPTS << ") timebase " << audioOutStream->time_base.num << "/" << audioOutStream->time_base.den << " real: " << (outputPacket->pts / (double)videoOutStream->time_base.den) << std::endl;

        ret = av_write_frame(outFormatCtx, outputPacket);
        av_packet_unref(outputPacket);
      }
    }
  }

  av_packet_free(&inputPacket);
  av_packet_free(&outputPacket);
  av_frame_free(&inputFrame);
  printf("encode %lu audio packets in total.\n", audioFrameCount);
}

#include <string>
using namespace std;

int main()
{
  puts("==== Audio Recorder ====");
  avdevice_register_all();

  AudioRecorder recorder{"testAudio.mp4", ""};
  try
  {
    recorder.Init();
    recorder.OpenAudio();
    recorder.OpenVideo();
    recorder.Start();

    //record 10 seconds.
    std::this_thread::sleep_for(10s);

    recorder.Stop();
    string reason = recorder.GetLastError();
    if (!reason.empty())
    {
      throw std::runtime_error(reason);
    }
  }
  catch (std::exception &e)
  {
    fprintf(stderr, "[ERROR] %s\n", e.what());
    exit(-1);
  }

  puts("END");
  return 0;
}
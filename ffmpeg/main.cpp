#include <string>
#include "ScreenRecorder.h"
using namespace std;

int main()
{
  puts("==== Screen Recorder ====");
  avdevice_register_all();

  ScreenRecorder recorder{"testAudio.mp4", ""};
  try
  {
    recorder.Init();
    recorder.OpenAudio();
    recorder.OpenVideo(0, 0, 1920, 1080, 60);
    recorder.Start();

    for (size_t i = 0; i < 5; i++)
    {
      std::cout << "Sleeping minute " << i + 1 << std::endl;
      std::this_thread::sleep_for(std::chrono::minutes(1));
    }

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
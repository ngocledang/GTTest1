#include "GTTest01Window.h"

int mainee(int, char const*[])
{
#if defined(_DEBUG)
    LogReporter reporter(
        "LogReport.txt",
        Logger::Listener::LISTEN_FOR_ALL,
        Logger::Listener::LISTEN_FOR_ALL,
        Logger::Listener::LISTEN_FOR_ALL,
        Logger::Listener::LISTEN_FOR_ALL);
#endif

    Window::Parameters parameters(L"GTTest01Window", 0, 0, 512, 512);
    auto window = TheWindowSystem.Create<GTTest01Window>(parameters);
    TheWindowSystem.MessagePump(window, TheWindowSystem.DEFAULT_ACTION);
    TheWindowSystem.Destroy<GTTest01Window>(window);
    return 0;
}

GTTest01Window::GTTest01Window(Parameters& parameters)
    :
    Window3(parameters)
{
}

void GTTest01Window::OnIdle()
{
    mTimer.Measure();

    mEngine->ClearBuffers();
    mEngine->Draw(8, mYSize - 8, { 0.0f, 0.0f, 0.0f, 1.0f }, mTimer.GetFPS());
    mEngine->DisplayColorBuffer(0);

    mTimer.UpdateFrameCount();
}

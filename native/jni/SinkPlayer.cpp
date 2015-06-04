#define LOG_NDEBUG 0
#define LOG_TAG "SinkPlayer"

#include "SinkPlayer.h"

#include "ANetworkSession.h"
#include "WifiDisplaySink.h"
#include <gui/ISurfaceTexture.h>
#include <gui/Surface.h>

namespace android {

SinkPlayer::SinkPlayer() {
}

SinkPlayer::~SinkPlayer() {
}

status_t SinkPlayer::start(const char *host, int32_t port) {
    mLooper = new ALooper;
    mNetSession = new ANetworkSession;
    mSink = new WifiDisplaySink(mNetSession, mSurfaceTexture);

	//建立网络，初始化管道，设置文件描述符mPipe
    mNetSession->start();
    mLooper->setName("sink_player");
    mLooper->registerHandler(mSink);

    //LOGD("will start sink by %s:%d", host, port);

	//在网络建立好后，设置host和port
    mSink->start(host, port);


    mLooper->start(true /* runOnCallingThread */);
    return OK;
}

status_t SinkPlayer::setSurfaceTexture(const sp<ISurfaceTexture> &surfaceTexture) {
    ALOGD("setSurfaceTexture called. surfacetexture = %p", surfaceTexture.get());
    mSurfaceTexture = surfaceTexture;
    return OK;
}

status_t SinkPlayer::dispose() {
    /*mSink->stop();

    mLooper->stop();
    mNetSession->stop();*/

    return OK;
}

}  // namespace android

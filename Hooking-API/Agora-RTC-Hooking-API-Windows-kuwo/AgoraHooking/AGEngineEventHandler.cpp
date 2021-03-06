#include "StdAfx.h"
#include "AGEngineEventHandler.h"
#include "AGEventDef.h"

CAGEngineEventHandler::CAGEngineEventHandler(void)
{
}

CAGEngineEventHandler::~CAGEngineEventHandler(void)
{
}

void CAGEngineEventHandler::SetMsgReceiver(HWND hWnd)
{
	m_hMainWnd = hWnd;
}

void CAGEngineEventHandler::onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_JOINCHANNEL_SUCCESS lpData = new AGE_JOINCHANNEL_SUCCESS;

	int nChannelLen = strlen(channel) + 1;
	lpData->channel = new char[nChannelLen];
	lpData->uid = uid;
	lpData->elapsed = elapsed;

	strcpy_s(lpData->channel, nChannelLen, channel);

	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_JOINCHANNEL_SUCCESS), (WPARAM)lpData, 0);
}

void CAGEngineEventHandler::onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_REJOINCHANNEL_SUCCESS lpData = new AGE_REJOINCHANNEL_SUCCESS;

	int nChannelLen = strlen(channel) + 1;
	lpData->channel = new char[nChannelLen];
	lpData->uid = uid;
	lpData->elapsed = elapsed;

	strcpy_s(lpData->channel, nChannelLen, channel);

	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_REJOINCHANNEL_SUCCESS), (WPARAM)lpData, 0);

}

void CAGEngineEventHandler::onWarning(int warn, const char* msg)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	CString str;

	str = _T("onWarning");
}

void CAGEngineEventHandler::onError(int err, const char* msg)
{
	if (NULL != msg){

		CAgoraFormatStr::AgoraOutDebugStr(_T("EventHandle OnError err: %d, msg: %s"), err, s2cs(msg));
		LPAGE_ERROR lpData = new AGE_ERROR;

		int nMsgLen = 0;

		// attention: the pointer of msg maybe NULL!!!
		if (msg != NULL) {
			nMsgLen = strlen(msg) + 1;
			lpData->msg = new char[nMsgLen];
			strcpy_s(lpData->msg, nMsgLen, msg);
		}
		else
			lpData->msg = NULL;

		lpData->err = err;



		if (m_hMainWnd != NULL)
			::PostMessage(m_hMainWnd, WM_MSGID(EID_ERROR), (WPARAM)lpData, 0);
	}
}

void CAGEngineEventHandler::onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_AUDIO_QUALITY lpData = new AGE_AUDIO_QUALITY;

	lpData->uid = uid;
	lpData->quality = quality;
	lpData->delay = delay;
	lpData->lost = lost;

	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_AUDIO_QUALITY), (WPARAM)lpData, 0);
}


void CAGEngineEventHandler::onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_AUDIO_VOLUME_INDICATION lpData = new AGE_AUDIO_VOLUME_INDICATION;

	lpData->speakers = new AudioVolumeInfo[speakerNumber];
	memcpy(lpData->speakers, speakers, speakerNumber*sizeof(AudioVolumeInfo));
	lpData->speakerNumber = speakerNumber;
	lpData->totalVolume = totalVolume;

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_AUDIO_VOLUME_INDICATION), (WPARAM)lpData, 0);

}

void CAGEngineEventHandler::onLeaveChannel(const RtcStats& stat)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_LEAVE_CHANNEL lpData = new AGE_LEAVE_CHANNEL;

	memcpy(&lpData->rtcStat, &stat, sizeof(RtcStats));

	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_LEAVE_CHANNEL), (WPARAM)lpData, 0);
}

void CAGEngineEventHandler::onRtcStats(const RtcStats& stat)
{
	CString str;

	str = _T("stat");
}


void CAGEngineEventHandler::onMediaEngineEvent(int evt)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_MEDIA_ENGINE_EVENT lpData = new AGE_MEDIA_ENGINE_EVENT;

	lpData->evt = evt;

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_MEDIA_ENGINE_EVENT), (WPARAM)lpData, 0);

}

void CAGEngineEventHandler::onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_AUDIO_DEVICE_STATE_CHANGED lpData = new AGE_AUDIO_DEVICE_STATE_CHANGED;

	int nDeviceIDLen = strlen(deviceId) + 1;

	lpData->deviceId = new char[nDeviceIDLen];

	strcpy_s(lpData->deviceId, nDeviceIDLen, deviceId);
	lpData->deviceType = deviceType;
	lpData->deviceState = deviceState;

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_AUDIO_DEVICE_STATE_CHANGED), (WPARAM)lpData, 0);

}

void CAGEngineEventHandler::onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_VIDEO_DEVICE_STATE_CHANGED lpData = new AGE_VIDEO_DEVICE_STATE_CHANGED;

	int nDeviceIDLen = strlen(deviceId) + 1;

	lpData->deviceId = new char[nDeviceIDLen];

	strcpy_s(lpData->deviceId, nDeviceIDLen, deviceId);
	lpData->deviceType = deviceType;
	lpData->deviceState = deviceState;

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_VIDEO_DEVICE_STATE_CHANGED), (WPARAM)lpData, 0);

}

void CAGEngineEventHandler::onRequestChannelKey()
{
	if (m_hMainWnd){
		::PostMessage(m_hMainWnd, WM_MSGID(EID_REQUEST_CHANNELKEY), 0, 0);
	}
}

void CAGEngineEventHandler::onLastmileQuality(int quality)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_LASTMILE_QUALITY lpData = new AGE_LASTMILE_QUALITY;

	lpData->quality = quality;

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_LASTMILE_QUALITY), (WPARAM)lpData, 0);
}

void CAGEngineEventHandler::onFirstLocalVideoFrame(int width, int height, int elapsed)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_FIRST_LOCAL_VIDEO_FRAME lpData = new AGE_FIRST_LOCAL_VIDEO_FRAME;

	lpData->width = width;
	lpData->height = height;
	lpData->elapsed = elapsed;

	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_FIRST_LOCAL_VIDEO_FRAME), (WPARAM)lpData, 0);

}

void CAGEngineEventHandler::onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_FIRST_REMOTE_VIDEO_DECODED lpData = new AGE_FIRST_REMOTE_VIDEO_DECODED;

	lpData->uid = uid;
	lpData->width = width;
	lpData->height = height;
	lpData->elapsed = elapsed;

	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_FIRST_REMOTE_VIDEO_DECODED), (WPARAM)lpData, 0);

}

void CAGEngineEventHandler::onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_FIRST_REMOTE_VIDEO_FRAME lpData = new AGE_FIRST_REMOTE_VIDEO_FRAME;

	lpData->uid = uid;
	lpData->width = width;
	lpData->height = height;
	lpData->elapsed = elapsed;

	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_FIRST_REMOTE_VIDEO_FRAME), (WPARAM)lpData, 0);

}

void CAGEngineEventHandler::onUserJoined(uid_t uid, int elapsed)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T("onUserJoined uid: %u, elapsed: %d"), uid, elapsed);
	LPAGE_USER_JOINED lpData = new AGE_USER_JOINED;

	lpData->uid = uid;
	lpData->elapsed = elapsed;

	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_USER_JOINED), (WPARAM)lpData, 0);

}

void CAGEngineEventHandler::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T("onUserOffline uid: %u, reason: %d"), uid, reason);
	LPAGE_USER_OFFLINE lpData = new AGE_USER_OFFLINE;

	lpData->uid = uid;
	lpData->reason = reason;

	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_USER_OFFLINE), (WPARAM)lpData, 0);
}

void CAGEngineEventHandler::onUserMuteAudio(uid_t uid, bool muted)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_USER_MUTE_AUDIO lpData = new AGE_USER_MUTE_AUDIO;

	lpData->uid = uid;
	lpData->muted = muted;

	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_USER_MUTE_AUDIO), (WPARAM)lpData, 0);

}

void CAGEngineEventHandler::onUserMuteVideo(uid_t uid, bool muted)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_USER_MUTE_VIDEO lpData = new AGE_USER_MUTE_VIDEO;

	lpData->uid = uid;
	lpData->muted = muted;

	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_USER_MUTE_VIDEO), (WPARAM)lpData, 0);

}

void CAGEngineEventHandler::onApiCallExecuted(const char* api, int error)
{
	return;
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_APICALL_EXECUTED lpData = new AGE_APICALL_EXECUTED;

	strcpy_s(lpData->api, 128, api);
	lpData->error = error;

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_APICALL_EXECUTED), (WPARAM)lpData, 0);
}

void CAGEngineEventHandler::onLocalVideoStats(const LocalVideoStats& stats)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_LOCAL_VIDEO_STAT lpData = new AGE_LOCAL_VIDEO_STAT;

	lpData->sentBitrate = stats.sentBitrate;
	lpData->sentFrameRate = stats.sentFrameRate;

	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_LOCAL_VIDEO_STAT), (WPARAM)lpData, 0);

}

void CAGEngineEventHandler::onRemoteVideoStats(const RemoteVideoStats& stats)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_REMOTE_VIDEO_STAT lpData = new AGE_REMOTE_VIDEO_STAT;

	lpData->uid = stats.uid;
	lpData->delay = stats.delay;
	lpData->width = stats.width;
	lpData->height = stats.height;
	lpData->receivedFrameRate = stats.receivedFrameRate;
	lpData->receivedBitrate = stats.receivedBitrate;
	lpData->receivedFrameRate = stats.receivedFrameRate;

	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_REMOTE_VIDEO_STAT), (WPARAM)lpData, 0);
}

void CAGEngineEventHandler::onCameraReady()
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_CAMERA_READY), 0, 0);

}

void CAGEngineEventHandler::onVideoStopped()
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_VIDEO_STOPPED), 0, 0);
}

void CAGEngineEventHandler::onConnectionLost()
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	if(m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_CONNECTION_LOST), 0, 0);
}

void CAGEngineEventHandler::onConnectionInterrupted()
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	CString str;

	str = _T("onConnectionInterrupted");
}

void CAGEngineEventHandler::onUserEnableVideo(uid_t uid, bool enabled)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T("onUserEnableVideo uid: %u, enable: %d"),uid,enabled);

	LPAGE_USER_MUTE_VIDEO lpData = new AGE_USER_MUTE_VIDEO;
	if (lpData){

		lpData->muted = enabled;
		lpData->uid = uid;
	}

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_USER_MUTE_VIDEO), WPARAM(lpData), 0);
}

void CAGEngineEventHandler::onStartRecordingService(int error)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_START_RCDSRV), 0, 0);

}

void CAGEngineEventHandler::onStopRecordingService(int error)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_STOP_RCDSRV), 0, 0);

}

void CAGEngineEventHandler::onRefreshRecordingServiceStatus(int status)
{
	CAgoraFormatStr::AgoraOutDebugStr(_T(__FUNCTION__));
	LPAGE_RCDSRV_STATUS lpData = new AGE_RCDSRV_STATUS;

	lpData->status = status;

	if (m_hMainWnd != NULL)
		::PostMessage(m_hMainWnd, WM_MSGID(EID_REFREASH_RCDSRV), (WPARAM)lpData, 0);
}
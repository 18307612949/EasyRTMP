/*
	Copyright (c) 2012-2016 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
#ifndef _EasyRTMP_API_H
#define _EasyRTMP_API_H

#ifdef _WIN32
#define Easy_API  __declspec(dllexport)
#define Easy_APICALL  __stdcall
#define Easy_FASTCALL __fastcall
#define WIN32_LEAN_AND_MEAN
#else
#define Easy_API
#define Easy_APICALL 
#endif

#define Easy_RTMP_Handle void*

typedef int						Easy_I32;
typedef unsigned char           Easy_U8;
typedef unsigned char           Easy_UChar;
typedef unsigned short          Easy_U16;
typedef unsigned int            Easy_U32;
typedef unsigned char			Easy_Bool;

/* ��Ƶ���� */
#define EASY_SDK_VIDEO_CODEC_H264	0x1C		/* H264 */

/* ��Ƶ���� */
#define EASY_SDK_AUDIO_CODEC_AAC	0x15002		/* AAC */

/* ����Ƶ֡��ʶ */
#define EASY_SDK_VIDEO_FRAME_FLAG	0x00000001		/* ��Ƶ֡��־ */
#define EASY_SDK_AUDIO_FRAME_FLAG	0x00000002		/* ��Ƶ֡��־ */
#define EASY_SDK_EVENT_FRAME_FLAG	0x00000004		/* �¼�֡��־ */
#define EASY_SDK_MEDIA_INFO_FLAG	0x00000020		/* ý�����ͱ�־*/

/* ��Ƶ�ؼ��ֱ�ʶ */
#define EASY_SDK_VIDEO_FRAME_I		0x01		/* I֡ */
#define EASY_SDK_VIDEO_FRAME_P		0x02		/* P֡ */
/* �������� */
typedef enum __EASY_RTMP_TYPE
{
	EASY_RTMP_CLIENT	=	0x01,		/* RTMP Client */
	EASY_RTMP_PUSHER					/* RTMP Pusher */
}EASY_RTMP_TYPE;

#pragma pack(1)
typedef struct __EASY_AV_Frame
{
    Easy_U32    u32AVFrameFlag;		/* ֡��־  ��Ƶ or ��Ƶ */
    Easy_U32    u32AVFrameLen;		/* ֡�ĳ��� */
    Easy_U32    u32VFrameType;		/* ��Ƶ�����ͣ�I֡��P֡ */
	Easy_U32	u32TimestampSec;	/* ʱ���(��)*/
	Easy_U32	u32TimestampUsec;	/* ʱ���(΢��) */
	Easy_U8     *pBuffer;			/* ���� */	
}EASY_AV_Frame;

/* ý����Ϣ */
typedef struct __EASY_MEDIA_INFO_T
{
	Easy_U32 u32VideoCodec;				/* ��Ƶ�������� */
	Easy_U32 u32VideoFps;				/* ��Ƶ֡�� */

	Easy_U32 u32AudioCodec;				/* ��Ƶ�������� */
	Easy_U32 u32AudioSamplerate;		/* ��Ƶ������ */
	Easy_U32 u32AudioChannel;			/* ��Ƶͨ���� */
	Easy_U32 u32AudioBitsPerSample;		/* ��Ƶ�������� */

	Easy_U32 u32H264SpsLength;			/* ��Ƶsps֡���� */
	Easy_U32 u32H264PpsLength;			/* ��Ƶpps֡���� */
	Easy_U8	 u8H264Sps[128];			/* ��Ƶsps֡���� */
	Easy_U8	 u8H264Pps[36];				/* ��Ƶsps֡���� */
}EASY_MEDIA_INFO_T;

/*
	_frameType:		EASY_SDK_VIDEO_FRAME_FLAG/EASY_SDK_AUDIO_FRAME_FLAG/EASY_SDK_EVENT_FRAME_FLAG/...	
	_pBuf:			�ص������ݲ��֣������÷���Demo
	_frameInfo:		֡�ṹ����
	_userPtr:		�û��Զ�������
*/
typedef int (Easy_FASTCALL *EasyRTMPCallBack)(int _frameType, char *pBuf, EASY_AV_Frame* _frameInfo, void *_userPtr);

#ifdef __cplusplus
extern "C"
{
#endif
	/* ����EasyRTMP���  ����Ϊ���ֵ */
	Easy_API Easy_RTMP_Handle Easy_FASTCALL EasyRTMP_Create(EASY_RTMP_TYPE _rtmpType);

	/* �ͷ�EasyRTMP ����ΪEasyRTMP��� */
	Easy_API int Easy_FASTCALL EasyRTMP_Release(Easy_RTMP_Handle *handle);

	/* �������ݻص� */
	Easy_API int Easy_FASTCALL EasyRTMP_SetCallback(Easy_RTMP_Handle handle, EasyRTMPCallBack _callback);

	/* ��������(��ȡ��������) */
	Easy_API int Easy_APICALL EasyRTMP_StartStream(Easy_RTMP_Handle handle, char *_url, void *userPtr, int _reconn/*1000��ʾ������,���������Ͽ��Զ�����, ����ֵΪ���Ӵ���*/, int _verbosity/*��־��ӡ����ȼ���0��ʾ�����*/);
	
	/* ���� frame:�������͵���ý��֡H.264/AAC */
	Easy_API Easy_U32 Easy_FASTCALL EasyRTMP_PushFrame(Easy_RTMP_Handle handle, EASY_AV_Frame* frame );

#ifdef __cplusplus
}
#endif

#endif

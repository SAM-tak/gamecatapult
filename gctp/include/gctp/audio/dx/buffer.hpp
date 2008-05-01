#ifndef _GCTP_AUDIO_DX_BUFFER_HPP_
#define _GCTP_AUDIO_DX_BUFFER_HPP_
/** @file
 * GameCatapult DirectSoundBuffer�N���X�w�b�_�t�@�C��
 *
 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
 * @date 2004/01/25 19:35:25
 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
 */
#include <gctp/audio/dx/device.hpp>

namespace gctp { namespace audio {
	class Clip;
}}

namespace gctp { namespace audio { namespace dx {

	/** DirectSoundBuffer���ۊ��N���X
	 *
	 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
	 * @date 2004/01/19 19:29:37
	 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
	 */
	class Buffer : public Object {
	public:
		virtual ~Buffer();

		virtual bool isPlaying() = 0;
		virtual HRslt play(int times) = 0;
		virtual HRslt stop() = 0;
		virtual HRslt rewind() = 0;
		virtual HRslt setVolume(float) = 0;
		virtual float getVolume() = 0;
		virtual HRslt setPan(float) = 0;
		virtual float getPan() = 0;
		virtual HRslt onNotified() = 0;
#ifndef GCTP_AUDIO_USE_TIMER
		virtual HANDLE event() = 0;
#endif
		virtual HRslt restore() = 0;
		virtual void cleanUp() = 0;
	};

	Pointer<Buffer> newStaticBuffer(IDirectSound8Ptr device, Handle<Clip> clip, bool global_focus);
	Pointer<Buffer> newStreamingBuffer(IDirectSound8Ptr device, Handle<Clip> clip, bool global_focus);

}}} // namespace gctp

#endif //_GCTP_AUDIO_DX_BUFFER_HPP_
#ifndef _GCTP_GRAPHIC_SPRITE_HPP_
#define _GCTP_GRAPHIC_SPRITE_HPP_
/** @file
 * GameCatapult �X�v���C�g�N���X�w�b�_�t�@�C��
 *
 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
 * @date 2004/02/18 21:54:52
 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
 */
#include <gctp/class.hpp>
#include <gctp/pointer.hpp>
#include <gctp/color.hpp>
#include <gctp/graphic/rsrc.hpp>
#include <gctp/graphic/vertexbuffer.hpp>
#include <gctp/matrix2.hpp>
#include <gctp/types.hpp>

namespace gctp { namespace graphic {

	/** �X�v���C�g��`���
	 *
	 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
	 * @date 2004/07/15 5:46:30
	 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
	 */
	struct SpriteDesc {
		Point2f pos[4];
		Point2f uv[4];
		Color32 color[4];
		Color32 hilight[4];
		/// �e�N�X�`���������\������ݒ�
		SpriteDesc &setUp(const class Texture &tex);

		/// �ϓ��g�k
		SpriteDesc &scale(const Point2f &center, float scl)
		{
			Matrix2 m; m.scale(scl, scl);
			pos[0] -= center; pos[0] = m*pos[0]; pos[0] += center;
			pos[1] -= center; pos[1] = m*pos[1]; pos[1] += center;
			pos[2] -= center; pos[2] = m*pos[2]; pos[2] += center;
			pos[3] -= center; pos[3] = m*pos[3]; pos[3] += center;
			return *this;
		}
		/// �g�k
		SpriteDesc &scale(const Point2f &center, const Vector2 &scl)
		{
			Matrix2 m; m.scale(scl);
			pos[0] -= center; pos[0] = m*pos[0]; pos[0] += center;
			pos[1] -= center; pos[1] = m*pos[1]; pos[1] += center;
			pos[2] -= center; pos[2] = m*pos[2]; pos[2] += center;
			pos[3] -= center; pos[3] = m*pos[3]; pos[3] += center;
			return *this;
		}
		/// ��]
		SpriteDesc &rot(const Point2f &center, float theta)
		{
			Matrix2 m; m.rot(theta);
			pos[0] -= center; pos[0] = m*pos[0]; pos[0] += center;
			pos[1] -= center; pos[1] = m*pos[1]; pos[1] += center;
			pos[2] -= center; pos[2] = m*pos[2]; pos[2] += center;
			pos[3] -= center; pos[3] = m*pos[3]; pos[3] += center;
			return *this;
		}
		/// �s���K�p
		SpriteDesc &mult(const Point2f &center, const Matrix2 &m)
		{
			pos[0] -= center; pos[0] = m*pos[0]; pos[0] += center;
			pos[1] -= center; pos[1] = m*pos[1]; pos[1] += center;
			pos[2] -= center; pos[2] = m*pos[2]; pos[2] += center;
			pos[3] -= center; pos[3] = m*pos[3]; pos[3] += center;
			return *this;
		}
		/// �I�t�Z�b�g��������
		SpriteDesc &addOffset(Point2f ofs) {
			pos[0] += ofs;
			pos[1] += ofs;
			pos[2] += ofs;
			pos[3] += ofs;
			return *this;
		}
		/// �������N�g����S���_��ݒ�
		SpriteDesc &setPos(Rect rc) {
			pos[0].x = rc.left-0.5f;  pos[0].y = rc.top-0.5f;
			pos[1].x = rc.right-0.5f; pos[1].y = rc.top-0.5f;
			pos[2].x = rc.left-0.5f;  pos[2].y = rc.bottom-0.5f;
			pos[3].x = rc.right-0.5f; pos[3].y = rc.bottom-0.5f;
			return *this;
		}
		/// ���N�g����S���_��ݒ�
		SpriteDesc &setPos(Rectf rc) {
			pos[0].x = rc.left;  pos[0].y = rc.top;
			pos[1].x = rc.right; pos[1].y = rc.top;
			pos[2].x = rc.left;  pos[2].y = rc.bottom;
			pos[3].x = rc.right; pos[3].y = rc.bottom;
			return *this;
		}
		/// ���N�g����S���_���̂t�u��ݒ�
		SpriteDesc &setUV(Rectf rc) {
			uv[0].x = rc.left;  uv[0].y = rc.top;
			uv[1].x = rc.right; uv[1].y = rc.top;
			uv[2].x = rc.left;  uv[2].y = rc.bottom;
			uv[3].x = rc.right; uv[3].y = rc.bottom;
			return *this;
		}
		/// �S���_���ׂĂɓ���̐F�w��
		SpriteDesc &setColor(Color32 col) { color[0] = color[1] = color[2] = color[3] = col; return *this; }
		/// �S���_���ׂĂɓ���̃n�C���C�g�w��
		SpriteDesc &setHilight(Color32 col) { hilight[0] = hilight[1] = hilight[2] = hilight[3] = col; return *this; }
	};

	/** �X�v���C�g�o�b�t�@�N���X
	 *
	 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
	 * @date 2004/07/15 4:02:46
	 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
	 */
	class SpriteBuffer : public VertexBuffer {
	public:
		struct TLVertex;
		struct LVertex;

		HRslt setUp(const char *name);
		HRslt setUp(uint maxnum = default_maxnum_, bool is_TL = true);

		SpriteBuffer &begin(bool do_filter = true);
		SpriteBuffer &begin(const class Texture &tex, bool do_filter = true);
		SpriteBuffer &begin(const Size2 &screen/**< ���z�X�N���[���T�C�Y */, bool do_filter = true);
		SpriteBuffer &begin(const Size2 &screen/**< ���z�X�N���[���T�C�Y */, const class Texture &tex, bool do_filter = true);
		SpriteBuffer &draw(const SpriteDesc &desc);
		SpriteBuffer &draw(const Texture &tex, const SpriteDesc &desc);
		SpriteBuffer &set(const Texture &tex);
		SpriteBuffer &end();

		bool isFull();

		uint maxnum();

		static void setDefaultMaxnum(uint maxnum) { default_maxnum_ = maxnum; }

	GCTP_DECLARE_CLASS

	protected:
		static uint default_maxnum_;
		HRslt draw();

		uint cur_;
		uint maxnum_;
		uint lastfreenum_;

		Pointer<class SpriteSB>	sb_;
	private:
		void *locked_;
		bool is_TL_;
	};

}}

#endif //_GCTP_GRAPHIC_SPRITE_HPP_
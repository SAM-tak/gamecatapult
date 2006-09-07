#ifndef _GCTP_CONTEXT_HPP_
#define _GCTP_CONTEXT_HPP_
#include <gctp/config.hpp>
#ifdef GCTP_ONCE
#pragma once
#endif // GCTP_ONCE
/** @file
 * GameCatapult ���\�[�X�R���e�L�X�g�N���X�w�b�_�t�@�C��
 *
 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
 * @date 2004/02/08 11:18:38
 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
 */
#include <gctp/pointerlist.hpp>
#include <gctp/extension.hpp>
#include <gctp/tuki.hpp>

namespace gctp {

	class Serializer;

	/** ���\�[�X�R���e�L�X�g�N���X
	 *
	 * ���̃R���e�L�X�g�Ń��[�h�������\�[�X��ێ����A��̎��ɕێ����Ă������\�[�X�����������
	 * �������B
	 *
	 * �J�����g�R���e�L�X�g���A�X�^�b�N��ɕێ�����@�\������
	 *
	 * �f�[�^�x�[�X�ւ̓o�^���Ǘ����A�v�����\�[�X�\�[�X������̃R���X�g���N�^�����A
	 * ���\�[�X�\�[�X�����烊�\�[�X���ւ̕ϊ��A�c�a�̃K�x�[�W�A��S������B
	 * @see Extention
	 * 
	 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
	 * @date 2004/02/08 11:18:11
	 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
	 */
	class Context : public Object {
	public:
		/** �R���X�g���N�^
		 *
		 * �����ɃJ�����g�ɐݒ�B�i�R���e�L�X�g�X�^�b�N�Ɏ������v�b�V���j
		 *
		 * �ł��ŋ߂ɐ����������͑��삳�ꂽ�R���e�L�X�g���J�����g�ɂȂ�
		 */
		Context(bool open = true);

		/** �f�X�g���N�^
		 *
		 * �����ɃR���e�L�X�g�X�^�b�N���|�b�v
		 *
		 * �R���e�L�X�g�͐������ꂽ���ɊJ������Ȃ���΂Ȃ�Ȃ��B�i�������Ȃ���
		 * �t���O�����g���N��������j�J�����g�������Ŗ��������ꍇ�A�G���[���b�Z�[�W�𑗏o����
		 *
		 * �f�X�g���N�^���Ȃ̂ŁA��O�͓����Ȃ�
		 */
		~Context();

		/// �R���e�L�X�g���J��
		void open();
		/// �R���e�L�X�g�����
		void close();

		/** ���[�h�v��
		 *
		 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
		 * @date 2004/02/08 11:18:22
		 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
		 */
		bool load(const char *name);

		/** �I�u�W�F�N�g�o�^
		 *
		 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
		 * @date 2004/02/08 11:18:22
		 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
		 */
		Hndl add(const Ptr ptr, const char *name = 0);

		/** �I�u�W�F�N�g����
		 *
		 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
		 * @date 2004/02/08 11:18:22
		 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
		 */
		Hndl create(const GCTP_TYPEINFO &typeinfo, const char *name = 0);
		
		/** �I�u�W�F�N�g����
		 *
		 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
		 * @date 2004/02/08 11:18:22
		 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
		 */
		Hndl create(const char *classname, const char *name = 0);

		/// �V�[�P���X�̐擪��Ԃ�
		PtrList::iterator begin()
		{
			return ptrs_.begin();
		}
		/// �V�[�P���X�̐擪��Ԃ�
		PtrList::const_iterator begin() const
		{
			return ptrs_.begin();
		}
		/// �V�[�P���X�̍Ō��Ԃ�
		PtrList::iterator end()
		{
			return ptrs_.end();
		}
		/// �V�[�P���X�̍Ō��Ԃ�
		PtrList::const_iterator end() const
		{
			return ptrs_.end();
		}

	GCTP_DECLARE_CLASS
	public:
		virtual void serialize(Serializer &);

	public:
		// luapp
		bool setUp(luapp::Stack &L);
		int luaLoad(luapp::Stack &L);
		int luaCreate(luapp::Stack &L);
	TUKI_DECLARE(Context)

		friend Context &context();
	private:
		bool is_open_;
		PtrList ptrs_;
		Context *prev_;

		static Context *current_;
	};

	/// �J�����g�R���e�L�X�g
	inline Context &context() { return *Context::current_; }

} // namespace gctp

#endif //_GCTP_CONTEXT_HPP_